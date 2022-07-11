#pragma once
#include <fstream>
#include <sstream>
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")
#include "../CJsonObject/CJsonObject.hpp"
using namespace std;
class TiledMap;
class TiledJsonLoader
{
	friend class TiledMap;
public:
	TiledJsonLoader();
	TiledJsonLoader(const char* jsonPath);
	~TiledJsonLoader();

public:
	void loadJsonFile(const char* jsonPath);
private:
	void loadData();

	wstring stringTowstring(const string& s);

public:
	int getPixelWidth() { return _pixelWidth; }
	int getPixelHeight() { return _pixelHeight; }
	int getHeight() { return _height; }
	int getWidth() { return _width; }
	int getTileHeight() { return _tileHeight; }
	int getTileWeight() { return _tileWidth; }
	int getLayersNum() { return _layersNum; }
	bool isError() { return _error; }
	int getFirstId() { return _firstId; }
	const wstring& getImagePath() { return _image; }
private:
	vector<vector<int> > getMap() { return _layers; }
	neb::CJsonObject _oJson;
	bool _error;
private:
	//��ͼ���ؿ�
	int _pixelWidth;
	//��ͼ���ظ�
	int _pixelHeight;
	//һ�ŵ�ͼ�߶�����Ƭ����
	int _height;
	//һ�ŵ�ͼ�������Ƭ����
	int _width;
	//��Ƭ���ظ�
	int _tileHeight;
	//��Ƭ���ؿ�
	int _tileWidth;
	//��ͼͼ����
	int _layersNum;
	//��ԴͼƬ��Ƭ����
	int _imageTileWidth;
	//��ԴͼƬ��Ƭ����
	int _imageTileHeight;
	//��ԴͼƬ���ؿ�
	int _imageWidth;
	//��ԴͼƬ���ظ�
	int _imageHeight;

	vector<vector<int> > _layers;

	int _firstId;
	wstring _image;
};

