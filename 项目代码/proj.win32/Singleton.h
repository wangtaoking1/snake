#pragma once
#include <cstddef>

template <class T>
class Singleton
{
public:
	static inline T* instance()
	{
		if( !_instance )
			_instance = new T;
		return _instance;
	}
	void release()
	{
		if( !_instance)
			delete _instance;
		_instance = NULL;
	}
protected:
	Singleton(){}
	~Singleton(){}
	static T* _instance;
};

template <class T>
T* Singleton<T>::_instance;
