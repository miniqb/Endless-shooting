#include "TiledJsonLoader.h"

TiledJsonLoader::TiledJsonLoader():
     _error(true),
     _pixelWidth(0),
     _pixelHeight(0),
     _height(0),
     _width(0),
     _tileHeight(0),
     _tileWidth(0),
     _layersNum(0),
     _firstId(1),
    _imageTileHeight(0),
    _imageTileWidth(0),
    _imageWidth(0),
    _imageHeight(0)
{
}

TiledJsonLoader::TiledJsonLoader(const char* jsonPath):
    _error(true)
{
    loadJsonFile(jsonPath);
}

TiledJsonLoader::~TiledJsonLoader()
{
}

void TiledJsonLoader::loadJsonFile(const char* jsonPath)
{
    ifstream fin(jsonPath);
    if (fin.good())
    {
        std::stringstream ssContent;
        string str;
        ssContent << fin.rdbuf();
        if (_oJson.Parse(ssContent.str()))
        {
            _error = false;
        }
        fin.close();
    }
    loadData();
}

void TiledJsonLoader::loadData()
{
    _height = _oJson.getInt("height");
    _width = _oJson.getInt("width");
    _tileHeight = _oJson.getInt("tileheight");
    _tileWidth = _oJson.getInt("tilewidth");
    _pixelHeight = _height * _tileHeight;
    _pixelWidth = _width * _tileWidth;
    _layersNum = _oJson["layers"].GetArraySize();
    for (size_t i = 0; i < _layersNum; ++i)
    {
        vector<int> layer;
        _oJson["layers"][i]["data"].getNums(layer);
        _layers.push_back(layer);
    }
    _firstId = _oJson["tilesets"][0].getInt("firstgid");
    _image = stringTowstring(_oJson["tilesets"][0]("image"));
    _imageHeight= _oJson["tilesets"][0].getInt("imageheight");
    _imageWidth= _oJson["tilesets"][0].getInt("imagewidth");
    _imageTileHeight = _imageHeight / _tileHeight;
    _imageTileWidth = _imageWidth / _tileWidth;
}

wstring TiledJsonLoader::stringTowstring(const string& s)
{
    _bstr_t t = s.c_str();
    wchar_t* pwchar = (wchar_t*)t;
    wstring result = pwchar;
    return result;
}
