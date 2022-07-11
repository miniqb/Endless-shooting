#pragma once
#include <vector>

template<class T>
class SpritePool
{
public:
	SpritePool();
	SpritePool(unsigned int size);
	T* getSprite();
	void initPool(unsigned int size);
	unsigned int getSize() { return _pool.size(); }
	T& get(unsigned int i) { return _pool[i]; }
private:
	std::vector<T> _pool;
	unsigned int _index;
};

template<class T>
inline SpritePool<T>::SpritePool()
{
}

template<class T>
inline SpritePool<T>::SpritePool(unsigned int size)
{
	initPool(size);
}

template<class T>
inline T* SpritePool<T>::getSprite()
{
	if (_index >= _pool.size())
		_index = 0;
	return &(_pool[_index++]);
}

template<class T>
inline void SpritePool<T>::initPool(unsigned int size)
{
	_pool.resize(size);
}
