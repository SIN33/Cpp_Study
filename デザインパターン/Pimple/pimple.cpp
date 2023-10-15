//利点
//結合度の削減 > 依存性を.cppに移動し、結合要素をすべて除去できる
//コンパイル時間の高速化 > APIのインクルード階層が削減できる
//バイナリ互換性の向上 > pimplオブジェクトはシングルポインタ１つのみ > オブジェクトのバイナリ表現を変更せずに、実装に大きな変更を加えることができる
//レイジー割当て > mimplクラスは必要に応じて作成できる > ネットワーク接続などの制限のあるリソースやコストの高いリソースをクラスが割当てる場合に役立つ

//欠点
//作成したオブジェクトごとに追加の実装オブジェクトを割当て > 割当て解除しなくてはいけない
//コンパイラがconstメソッド内のメンバ変数の変更をキャッチしなくなる (メンバ変数がもはや別のオブジェクトに存在するから)


#include <memory>
#include <string>

class Person
{
 public:
   // ...
   Person();
   ~Person();

   Person( Person const& other );
   Person& operator=( Person const& other );

   Person( Person&& other );
   Person& operator=( Person&& other );

   int year_of_birth() const;
   // ... Many more access functions

 private:
   struct Impl;
   std::unique_ptr<Impl> const pimpl_;
};



struct Person::Impl
{
   std::string forename;
   std::string surname;
   std::string address;
   std::string city;
   std::string country;
   std::string zip;
   int year_of_birth;
   // ... Potentially many more data members
};


Person::Person()
   : pimpl_{ std::make_unique<Impl>() }
{}

Person::~Person() = default;

Person::Person( Person const& other )
   : pimpl_{ std::make_unique<Impl>(*other.pimpl_) }
{}

Person& Person::operator=( Person const& other )
{
   *pimpl_ = *other.pimpl_;
   return *this;
}

Person::Person( Person&& other )
   : pimpl_{ std::make_unique<Impl>(std::move(*other.pimpl_)) }
{}

Person& Person::operator=( Person&& other )
{
   *pimpl_ = std::move(*other.pimpl_);
   return *this;
}

int Person::year_of_birth() const
{
   return pimpl_->year_of_birth;
}


int main()
{
   Person p1{};

   return EXIT_SUCCESS;
}
