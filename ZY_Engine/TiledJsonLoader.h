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
	//地图像素宽
	int _pixelWidth;
	//地图像素高
	int _pixelHeight;
	//一张地图高度上瓦片个数
	int _height;
	//一张地图宽度是瓦片个数
	int _width;
	//瓦片像素高
	int _tileHeight;
	//瓦片像素宽
	int _tileWidth;
	//地图图层数
	int _layersNum;
	//资源图片瓦片数宽
	int _imageTileWidth;
	//资源图片瓦片数高
	int _imageTileHeight;
	//资源图片像素宽
	int _imageWidth;
	//资源图片像素高
	int _imageHeight;

	vector<vector<int> > _layers;

	int _firstId;
	wstring _image;
};

