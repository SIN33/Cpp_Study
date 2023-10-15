#pragma once

#include <memory>

template <class T>
class Singleton
{
public :
  static T& GetInstance()
  {
    static typename T::singleton_pointer_type s_singleton(T::_CreateInstance()) ;
    return _GetInstance(s_singleton) ;
  }


protected :
  Singleton() {}

private:
  typedef std::unique_ptr<T> singleton_pointer_type ;
  inline static T *_CreateInstance() { return new T() ; }
  inline static T &_GetInstance(const singleton_pointer_type &ptr) { return *ptr ; }



private :
  Singleton(const Singleton &) = delete;
  Singleton& operator=(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton& operator=(Singleton &&) = delete;
};

//usage 
//#define GAMESYS NSGameEngine::GetInstance()
//
//class NSGameEngine : public Singleton<NSGameEngine>
//{
//	 friend class Singleton<NSGameEngine>;
//
//public:
// 
//	void Initialize();
//	void Execute();
// 
//private:
//	NSGameEngine() = default;
//
//public:
//	// create instance
//	static NSGameEngine* CreateInstance()
//	{
//		return new NSGameEngine();
//	}
//
//};
// 