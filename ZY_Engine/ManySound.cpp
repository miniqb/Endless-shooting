#include "ManySound.h"

ManySound::ManySound():
	_index(0)
{
}

ManySound::ManySound(AudioDX& ds, const wchar_t* path, unsigned int size)
{
	init(ds, path, size);
}

ManySound::~ManySound()
{
}

void ManySound::init(AudioDX& ds, const wchar_t* path, unsigned int size)
{
	_sounds.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		_sounds[i].LoadWave(ds, path);
	}
}

void ManySound::play()
{
	if (_index >= _sounds.size())
		_index = 0;
	_sounds[_index].Restore();
	_sounds[_index++].Play();
}

AudioDXBuffer* ManySound::getSound()
{
	if (_index >= _sounds.size())
		_index = 0;
	AudioDXBuffer* s = &_sounds[_index];
	++_index;
	return s;
}

void ManySound::release()
{
	int length = _sounds.size();
		for (size_t i = 0; i < length; i++)
		{
			_sounds[i]->Release();
		}
}
