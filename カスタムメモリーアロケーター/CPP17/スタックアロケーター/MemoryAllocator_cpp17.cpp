#define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING //vc++17ではallocator.constructが非推奨のようだ

#include <iostream>
#include <cassert>
#include <new>
#include <cstdlib>
#include <map>
#include <vector>
#include <utility>
#include <cstddef>
#include <cassert>
#include <cstdint>



template<typename T, size_t N, typename Allocator = std::allocator<T>>
class stack_allocator
{
    using traits = std::allocator_traits<Allocator>;

public:

    using value_type = T;
    using allocator_type = Allocator;
    using size_type = unsigned int;
    using difference_type = int;
    using reference = T&;
    using const_reference = const T&;
    using pointer = typename traits::pointer;
    using const_pointer = typename traits::const_pointer;

    typedef std::map<void*/*アドレス*/, size_t> size_map_t;
    typedef std::map<size_t, std::vector<void*>> free_list_t;
    typedef std::byte byte;

    typedef Allocator allocator_type;

private:
    //使用可能なメモリータグ(一度割り当て、後に開放された領域)
    //管理領域

    typename allocator_type m_allocator;

    size_map_t m_size_map; //スタック領域内のチャンク,各リクエストサイズごとにフリーチャンクのリストを持つデータオブジェクト
    free_list_t m_free_list;//各フリーチャンクに対して、リクエストサイズを持つデータオブジェクト

    const size_type m_block_size; //アロケーターが割り当てるブロック(最小単位)サイズ
    const size_type m_max_objects; //割り当て可能な最大オブジェクト数
    byte  m_buffer[N];
    byte* m_begin; //内部バッファーの先頭
    byte* m_end;//内部バッファーの末尾
    byte* m_stack_pointer;//現在使用中の最新位置

public:
    explicit stack_allocator(const allocator_type& alloc = allocator_type())
        : m_allocator(alloc)
        , m_block_size(sizeof(std::byte[N]) < 8 ? sizeof(long long/*最大アライメントサイズ*/) : sizeof(std::byte[N]))
        , m_max_objects(N)
        , m_begin(m_buffer)
        , m_end(m_buffer + m_block_size * m_max_objects)
        , m_stack_pointer(m_buffer)
    {}

    ~stack_allocator() {}

    template<typename U>
    struct rebind
    {
        typedef typename stack_allocator<U, N, allocator_type> other;
    };

    pointer allocate(size_t n)
    {
        auto& free_chunks = m_free_list[n * m_block_size];
        if (!free_chunks.empty())
        {
            //再利用
            pointer available_block = static_cast<T*>(free_chunks.back());
            free_chunks.pop_back(); //free listの末尾を削除
            std::cout << "reuse pointer" << available_block << std::endl;
            return available_block;
        }
        else if (m_end - m_stack_pointer >= n * m_block_size) //終端を超えない大きさのオブジェクト
        {
            std::printf("alocate on the stack");
            pointer new_block = reinterpret_cast<pointer>(m_stack_pointer);
            m_stack_pointer += n * m_block_size; //次に使用するアドレスを計算

            m_size_map[new_block] = n * m_block_size;
            std::cout << "new pointer :" << new_block << std::endl;
            std::cout << "m_stack_pointer:" << m_stack_pointer << std::endl;
            return new_block;
        }
        else
        {
            std::printf("alocate on heap");
            return m_allocator.allocate(n);

        }

    }

    void deallocate(pointer p, size_type n)
    {
        auto freed_chunk_size = m_size_map[(void*)p];

        if (internal_buffer(p) || freed_chunk_size != 0)
        {
            m_free_list[freed_chunk_size].push_back((void*)p); //フリーチャンクに登録
            std::printf("dealocate on stack");
        }
        else if (m_stack_pointer > m_end)
        {
            m_allocator.deallocate(p, n);
            freed_chunk_size = n * m_block_size;
            std::printf("dealocate on heap");
        }
    }



    size_type max_size() const noexcept
    {
        return (size_type)(~0) / sizeof(T); //処理系(x86,x64)によって異なる
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        if (internal_buffer(p))
        {
            std::cout << "internal buffer construct" << '\n';
            ::new ((void*)p) T(args...); //placement newでスタック領域に作成
        }
        else
        {
            std::cout << "construct on the heap" << '\n';
            m_allocator.construct(p, std::forward<Args>(args)...); //invoke new
        }

    }

    template<typename U>
    void destroy(U* p)
    {
        if (internal_buffer(p))
        {
            std::cout << "internal buffer destroy" << '\n';
            p->~T();
        }
        else
        {
            std::cout << "destroy on the heap" << '\n';
            m_allocator.destroy(p);
        }
    }

    pointer addressof(reference x) const noexcept
    {
        if (internal_buffer(x))
        {
            return std::addressof(x);
        }
        else
        {
            m_allocator.addressof(x);
        }
    }

    pointer buffer() const noexcept
    {
        return m_begin;
    }

    constexpr static size_type capacity()
    {
        return N;
    }

private:
    bool internal_buffer(const_pointer p) const
    {
        return ((const_pointer)m_begin <= p && p <= (const_pointer)m_end);
    }
};

template<typename T1, std::size_t N, typename Allocator, typename T2>
bool operator==(const stack_allocator<T1, N, Allocator>& lhs, const stack_allocator<T2, N, Allocator>& rhs)
{
    return lhs.buffer() == rhs.buffer();
}

template<typename T1, std::size_t N, typename Allocator, typename T2>
bool operator!=(const stack_allocator<T1, N, Allocator>& lhs, const stack_allocator<T2, N, Allocator>& rhs)
{
    return !(lhs == rhs);
}


constexpr std::size_t stack_size = 8;

int main()
{
    typedef stack_allocator<int, stack_size> alloc_t;
    alloc_t test;

    const int requestsize = 1;
    int* t = test.allocate(requestsize);
    test.construct(t, 100);

    std::cout << *t << std::endl;
    test.destroy(t);
    test.deallocate(t, 1);

    int* d[16];
    for (int i = 0; i < 5; ++i)
    {
        d[i] = test.allocate(1);
    }

}
