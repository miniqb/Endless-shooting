#pragma once
#ifndef _TILEDMAP_H_
#define _TILEDMAP_H_

#include "Node.h"
#include "TiledJsonLoader.h"
#include "ZY_Graph.h"
#include "Camera.h"

class TiledMap :
    public Node
{
public:

    TiledMap();
    TiledMap(const char* jsonPath, int w, int h);
    ~TiledMap();

    void init(const char* jsonPath, int w, int h);
    static void SetCamera(Camera* c);
    //int getPositionType()
public:

    int getMapIndexX(int x);
    int getMapIndexY(int y);

    int getMapStanderPxX(int x);
    int getMapStanderPxY(int y);

    Vec2 getMapIndexXY(const Vec2& pos);
    Vec2 getMapIndexPxXY(const Vec2& pos);

    int getPositionType(const Vec2& pos, int layer);
    int getPositionTypeByIndex(int x, int y, int layer);

    int getMapPixWidth() { return _mapLoader._pixelWidth; }
    int getMapPixHeight() { return _mapLoader._pixelHeight; }

    //void setObstacles(int o) { _obstacles = o; }
    //int getbstacles() { return _obstacles; }

    //void setCover(int c) { _cover = c; }
    //int getCover() { return _cover; }

protected:
    void updateBuffer();
    virtual void drawSelf(HDC hdc);
    virtual void updateSelf(float dt);
    void drawBuffer(HDC hdc);
protected:
    TiledJsonLoader _mapLoader;

    T_Graph* _image;
    //ÏñËØ
    ZY_Rect _drawRect;
    //ÏñËØ
    ZY_Rect _bufferRect;
    //ÏñËØ
    ZY_Rect _newBufferRect;

    //Í¼¿é
    ZY_Rect _bufferTiledRect;
    ZY_Rect _newBufferTiledRect;
    int _bufferTiledWidth;
    int _bufferTiledHeight;

    HBITMAP _bufferBitmap;
    HBITMAP _newBufferBitmap;

    int _bufferHeight;
    int _bufferWidth;
    Vec2 _regionPos;
    bool _hasBuffered;

    static Camera* camera;
};

#endif // !_TILEDMAP_H_
