#pragma once
#include"../TinyEngine/T_Audio.h"
#include <vector>
class ManySound
{
public:
	ManySound();
	ManySound(AudioDX& ds, const wchar_t* path, unsigned int size);
	~ManySound();
	void init(AudioDX& ds, const wchar_t* path, unsigned int size);
	void play();
	AudioDXBuffer* getSound();
	void release();
private:
	std::vector<AudioDXBuffer> _sounds;
	unsigned int _index;
};

