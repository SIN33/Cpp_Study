#pragma once


//カスタムアロケーター（あらかじめ確保したヒープに格納）
#include <cstddef>
#include <memory>
#include <cassert>
#include <new>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <list>

#define MAX_OBJECTS 32
#define MAX_ALLOCS 4

template<std::size_t N>
class allocator
{
	typedef std::size_t size_type;

	//member
	//使用可能なメモリータグ(一度割り当て、後に開放された領域)
private:
	struct block_not_in_use
	{
		block_not_in_use* next;
	};

private:
	const size_t m_BlockSize;
	const unsigned m_MaxObjects;
	block_not_in_use* m_Head;
	std::byte* m_PoolAry; //pool領域を管理する配列、(あらかじめ割り当てるヒープ領域を管理する今回は4こ)
	unsigned m_PoolIndex; //
	std::byte Mp_Mem_[sizeof(std::byte[N]) * MAX_OBJECTS];
	unsigned m_BlockInUse[MAX_ALLOCS]; //使用中のヒープを管理



public:
	explicit inline allocator()
		: m_BlockSize(sizeof(std::byte[N]))
		, m_MaxObjects(MAX_OBJECTS)
		, m_Head(nullptr)
		, m_PoolIndex(0)
	{
		m_PoolAry = new(&Mp_Mem_)std::byte[sizeof(std::byte[N]) * MAX_OBJECTS];
	}

	~allocator() = default;

	inline void* allocate()
	{
		void* pblock = pop_from_pool();

		if (pblock == nullptr)
		{
			if (m_PoolIndex < m_MaxObjects)
			{
				++m_PoolIndex;
				pblock = static_cast<void*>(m_PoolAry + (m_PoolIndex * m_BlockSize));
			}
			else
			{
				assert(false);
			}
		}
		return pblock;
	}

	inline void deallocate(void* memory)
	{
		rewind(memory);
	}

	inline size_t get_block_size() const
	{
		return m_BlockSize;
	}

	private:
		//関数(deallocate)時に使用可能領域を更新
		void rewind(void* memory)
		{
			auto pblock = static_cast<block_not_in_use*>(memory);

			pblock->next = m_Head; //先頭ポインタを次にすすめる
			m_Head = pblock;
		}

		//割り当て(allocate)時に開放された使用可能領域から使う
		void* pop_from_pool()
		{
			block_not_in_use* pblock = nullptr;

			if (m_Head != nullptr)
			{
				pblock = m_Head;
				m_Head = m_Head->next;
			}

			return static_cast<void*>(pblock);
		}

};

template<typename T>
class block_allocator
{
private:
	static allocator<8> s_Alloc8;
	static allocator<16> s_Alloc16;
	static allocator<32> s_Alloc32;
	static allocator<64> s_Alloc64;

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template<typename U>
	struct rebind //この関数の使用方法は、std::vectorの内部処理を参考にするです
	{
		typedef block_allocator<U> other;
	};

public: //ctor dtor
	block_allocator() = default;

	~block_allocator() = default;


	inline explicit block_allocator(const block_allocator&) noexcept {}

	template<typename U> inline constexpr block_allocator(const block_allocator<U>&) noexcept {}


	inline pointer allocate(std::size_t n)
	{
		auto s = sizeof(T) * n;

		if (s <= 8) return reinterpret_cast<T*>(s_Alloc8.allocate());
		else if (s <= 16) return reinterpret_cast<T*>(s_Alloc16.allocate());
		else if (s <= 32) return reinterpret_cast<T*>(s_Alloc32.allocate());
		else if (s <= 64) return reinterpret_cast<T*>(s_Alloc64.allocate());
		else assert(false);
	}


	void deallocate(T* p, size_t n) noexcept
	{
		auto s = sizeof(T) * n;

		if (s <= 8) s_Alloc8.deallocate(reinterpret_cast<void*>(p));
		else if (s <= 16) s_Alloc16.deallocate(reinterpret_cast<void*>(p));
		else if (s <= 32) s_Alloc32.deallocate(reinterpret_cast<void*>(p));
		else if (s <= 64) s_Alloc64.deallocate(reinterpret_cast<void*>(p));
		else assert(false);
	}

	inline size_type max_size() const
	{
		return std::numeric_limits<size_type>::max();
	}

	static size_type capacity()
	{
		return MAX_OBJECTS;
	}

	template<typename U, typename... Args>
	void construct(U* p, Args&&... args)
	{
		::new((void*)p)T(args...);
	}

	template<typename U, typename... Args>
	void destroy(U* p)
	{
		p->~U();
	}

};

template<typename T>
allocator<8> block_allocator<T>::s_Alloc8;
template<typename T>
allocator<16> block_allocator<T>::s_Alloc16;
template<typename T>
allocator<32> block_allocator<T>::s_Alloc32;
template<typename T>
allocator<64> block_allocator<T>::s_Alloc64;


template<>
class block_allocator<void>
{
public:
	typedef void* pointer;
	typedef const void* const_pointer;
	typedef void value_type;

	template<typename U>
	struct rebind
	{
		typedef block_allocator<U> other;
	};

public: //ctor dtor
	block_allocator() = default;

	template<typename U>
	block_allocator(const block_allocator<U>&){}

	template<typename U>
	block_allocator(std::allocator<U>&){}
};

template<typename Allocator, typename U>
using rebind_t = typename block_allocator<U>::template rebind<U>::type;

template<typename T, typename T2>
inline bool operator==(const block_allocator<T>&, const block_allocator<T2>&)
{
	return true;
}

template<typename T, typename OtherAllocator>
inline bool operator==(const block_allocator<T>&, const OtherAllocator&)
{
	return false;
}
//カスタムアロケータ―
template<typename Allocator, typename U>
struct block_rebind
{
	typedef typename Allocator::template rebind<U>::other type;
};

//カスタムアロケータ―型のエイリアス
template<typename Allocator, typename U>
using block_rebind_t = typename block_rebind<Allocator, U>::type;



//std::unique_ptrのカスタムデリータ
template<typename Allocator, typename T>
class block_delete
{
private :
	mutable block_rebind_t<Allocator, T> m_Alloc;

public:
	block_delete(const Allocator& alloc) noexcept
		:m_Alloc(alloc) {}

	template<typename Other, typename U>
	block_delete(const block_delete<Other, U>& d) noexcept
		: m_Alloc(d.m_Alloc) {}


	void operator()(T* p)const
	{
		p->~T();
		m_Alloc.deallocate(p, 1);
	}

};

//カスタムアロケータ―に割り当てるスマートポインターの型
template<typename Allocator, typename T>
using block_ptr = std::unique_ptr <T, block_delete<Allocator, T> >;

//割り当て関数
template<typename T, typename Allocator, typename... Args>
block_ptr<Allocator, T> allocate_block(const Allocator& alloc, Args&&... args)
{
	block_rebind_t<Allocator, T> rebound_alloc(alloc);
	T* praw = rebound_alloc.allocate(1);

	try
	{
		T* p = new(praw) T(std::forward<Args>(args)...);
		return block_ptr<Allocator, T>(p, block_delete<Allocator, T>(rebound_alloc));
	}
	catch (...)
	{
		rebound_alloc.deallocate(praw, 1);
	}
};

struct A {
	int x, y, z, a;
};



int main()
{
	
	using int_allocator = block_allocator<int>;
	using a_allocator = block_allocator<A>;

	int_allocator alloc;
	int_allocator alloc_copy;
	a_allocator alloc_a;

	for (int i = 0; i < 2; ++i)
	{
		auto x = allocate_block<int, int_allocator>(alloc, 200);
	}

	return 0;
}
