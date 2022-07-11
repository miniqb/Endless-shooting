#include "TiledMap.h"

TiledMap::TiledMap():
	_mapLoader(),
	_image(),
	_drawRect(),
	_bufferRect(),
	_bufferBitmap(0),
	_bufferHeight(0),
	_bufferWidth(0),
	_regionPos(),
	_hasBuffered(false),
	_bufferTiledHeight(0),
	_bufferTiledWidth(0),
	_newBufferBitmap(0)
{
}

TiledMap::TiledMap(const char* jsonPath, int w, int h):
	TiledMap()
{
	init(jsonPath, w, h);
}

TiledMap::~TiledMap()
{
}

void TiledMap::init(const char* jsonPath, int w, int h)
{
	_mapLoader.loadJsonFile(jsonPath);
	_image=new ZY_Graph();
	_image->LoadImageFile(L"res/map/" + _mapLoader._image);

	_bufferTiledWidth = ceilf((float)w / _mapLoader._tileWidth);
	_bufferTiledHeight = ceilf((float)h / _mapLoader._tileHeight);
	if (_bufferTiledWidth % 2 == 0) _bufferTiledWidth += 1;
	if (_bufferTiledHeight % 2 == 0) _bufferTiledHeight += 1;
	_bufferTiledRect.setRect(-99999,-99999,_bufferTiledWidth, _bufferTiledHeight);

	_bufferWidth = _bufferTiledWidth *_mapLoader._tileWidth;
	_bufferHeight = _bufferTiledHeight * _mapLoader._tileHeight;
	_bufferRect.setRect(-99999, -99999, _bufferWidth, _bufferHeight);

	_bufferBitmap = T_Graph::CreateBlankBitmap(_bufferWidth, _bufferHeight, RGB(10, 15, 15));
	_newBufferBitmap = T_Graph::CreateBlankBitmap(_bufferWidth, _bufferHeight, RGB(10, 15, 15));

	_drawRect.setRect(0, 0, wndWidth, wndHeight);

	Vec2 center = getMapIndexXY(_drawRect.origin + _drawRect.size * 0.5f);
	int oriX = center.x - _bufferTiledWidth * 0.5;
	int oriY = center.y - _bufferTiledHeight * 0.5;

	_newBufferRect.size = _bufferRect.size;
	_newBufferRect.origin.set(oriX*_mapLoader._tileWidth, oriY*_mapLoader._tileHeight);
	_newBufferTiledRect.size = _bufferTiledRect.size;
	_newBufferTiledRect.origin.set(oriX, oriY);
}

void TiledMap::SetCamera(Camera* c)
{
	camera = c;
}

void TiledMap::updateBuffer()
{
	_drawRect.origin = camera->getTransRect().origin;
	if (!_bufferRect.contain(_drawRect))
	{
		_hasBuffered = false;
		Vec2 center = getMapIndexXY(_drawRect.origin + _drawRect.size * 0.5f);
		int oriX = center.x - (int)(_bufferTiledWidth * 0.5);
		int oriY = center.y - (int)(_bufferTiledHeight * 0.5);
		_newBufferTiledRect.origin.set(oriX, oriY);
		_newBufferRect.origin.set(oriX * _mapLoader._tileWidth, oriY * _mapLoader._tileHeight);
	}
}

int TiledMap::getMapIndexX(int x)
{
	x = min(max(0, x), _mapLoader._pixelWidth-1);
	return x / _mapLoader._tileWidth;
}

int TiledMap::getMapIndexY(int y)
{
	y = min(max(0, y), _mapLoader._pixelWidth-1);
	return y / _mapLoader._tileHeight;
}

int TiledMap::getMapStanderPxX(int x)
{
	x = min(max(0, x), _mapLoader._pixelWidth-1);
	return x / _mapLoader._tileWidth * _mapLoader._tileWidth;
}

int TiledMap::getMapStanderPxY(int y)
{
	y = min(max(0, y), _mapLoader._pixelWidth-1);
	return y / _mapLoader._tileHeight * _mapLoader._tileHeight;
}

Vec2 TiledMap::getMapIndexXY(const Vec2& pos)
{
	int x = pos.x;
	int y = pos.y;
	x= min(max(0, x), _mapLoader._pixelWidth-1);
	y= min(max(0, y), _mapLoader._pixelWidth-1);
	return Vec2(x / _mapLoader._tileWidth, 
		y / _mapLoader._tileHeight);
}

Vec2 TiledMap::getMapIndexPxXY(const Vec2& pos)
{
	int x = pos.x;
	int y = pos.y;
	x = min(max(0, x), _mapLoader._pixelWidth-1);
	y = min(max(0, y), _mapLoader._pixelWidth-1);
	return Vec2(x / _mapLoader._tileWidth * _mapLoader._tileWidth, 
		y / _mapLoader._tileHeight * _mapLoader._tileHeight);
}

int TiledMap::getPositionType(const Vec2& pos, int layer)
{
	//int index=(int)pos->x+(int)pos->y*_mapLoader->
	int x = this->getMapIndexX(pos.x);
	int y = this->getMapIndexY(pos.y);
	int index = x + y * _mapLoader._width;
	return _mapLoader._layers[layer][index];
}

int TiledMap::getPositionTypeByIndex(int x, int y, int layer)
{
	x = min(max(0, x), _mapLoader._pixelWidth - 1);
	y = min(max(0, y), _mapLoader._pixelWidth - 1);
	int index = x + y * _mapLoader._width;
	return _mapLoader._layers[layer][index];
}

void TiledMap::drawSelf(HDC hdc)
{
	drawBuffer(hdc);

	Vec2 pos = _drawRect.origin - _bufferRect.origin;
	ZY_Graph::PaintRegion(_bufferBitmap, hdc, Vec2::ZERO,pos, _drawRect.size.width, _drawRect.size.height, 255);
	
}

void TiledMap::updateSelf(float dt)
{
	updateBuffer();
}

void TiledMap::drawBuffer(HDC hdc)
{
	if (!_hasBuffered) {
		HBITMAP srcBmp = _image->GetBmpHandle();
		HDC aimDC = CreateCompatibleDC(hdc);
		HDC srcDC = CreateCompatibleDC(hdc);

		HBITMAP oldAimDC = (HBITMAP)SelectObject(aimDC, _newBufferBitmap);
		HBITMAP oldSrcDC = (HBITMAP)SelectObject(srcDC, _bufferBitmap);

		BLENDFUNCTION ftn;
		ftn.BlendOp = AC_SRC_OVER;
		ftn.BlendFlags = 0;
		ftn.SourceConstantAlpha = 255;
		ftn.AlphaFormat = AC_SRC_ALPHA;

		int startDrawX = 0, startDrawY = 0, endDrawX = -1, endDrawY = -1;
		int startDrawX2 = 0, startDrawY2 = 0, endDrawX2 = -1, endDrawY2 = -1;

		int cellw = _mapLoader._tileWidth;
		int cellh = _mapLoader._tileHeight;

		if (_bufferTiledRect.intersectsRect(_newBufferTiledRect))//已绘制矩形与当前矩形相交
		{
			//计算相交矩形
			ZY_Rect unionRect = _bufferTiledRect.intersectWithRect(_newBufferTiledRect);

			int startUnionX = unionRect.origin.x * cellw;
			int startUnionY = unionRect.origin.y * cellh;
			int unionWidth = unionRect.size.width * cellw;
			int unionHeight = unionRect.size.height * cellh;

			//相交部分直接复制到相应位置
			AlphaBlend(aimDC,
				startUnionX - _newBufferRect.origin.x,
				startUnionY - _newBufferRect.origin.y,
				unionWidth, unionHeight,
				srcDC,
				startUnionX - _bufferRect.origin.x,
				startUnionY - _bufferRect.origin.y,
				unionWidth, unionHeight,
				ftn);

			//然后分4种情况
			if (_newBufferTiledRect.origin == unionRect.origin)//左上
			{
				startDrawX = unionRect.getMaxX();
				endDrawX = _newBufferTiledRect.getMaxX();
				startDrawY = unionRect.origin.y;
				endDrawY = unionRect.getMaxY();
				startDrawX2 = _newBufferTiledRect.origin.x;
				endDrawX2 = endDrawX;
				startDrawY2 = unionRect.getMaxY();
				endDrawY2 = _newBufferTiledRect.getMaxY();
			}
			else if (_newBufferTiledRect.origin.y == unionRect.origin.y &&
				_newBufferTiledRect.getMaxX() == unionRect.getMaxX())//右上
			{
				startDrawX = _newBufferTiledRect.origin.x;
				endDrawX = unionRect.origin.x;
				startDrawY = unionRect.origin.y;
				endDrawY = unionRect.getMaxY();
				startDrawX2 = startDrawX;
				endDrawX2 = _newBufferTiledRect.getMaxX();
				startDrawY2 = unionRect.getMaxY();
				endDrawY2 = _newBufferTiledRect.getMaxY();
			}
			else if (_newBufferTiledRect.origin.x == unionRect.origin.x &&
				_newBufferTiledRect.getMaxY() == unionRect.getMaxY())//左下
			{
				startDrawX = _newBufferTiledRect.origin.x;
				endDrawX = _newBufferTiledRect.getMaxX();
				startDrawY = _newBufferTiledRect.origin.y;
				endDrawY = unionRect.origin.y;
				startDrawX2 = unionRect.getMaxX();
				endDrawX2 = endDrawX;
				startDrawY2 = unionRect.origin.y;
				endDrawY2 = unionRect.getMaxY();
			}
			else if ((_newBufferTiledRect.getMaxX() == unionRect.getMaxX() &&
				_newBufferTiledRect.getMaxY() == unionRect.getMaxY()))//右下
			{
				startDrawX = _newBufferTiledRect.origin.x;
				endDrawX = _newBufferTiledRect.getMaxX();
				startDrawY = _newBufferTiledRect.origin.y;
				endDrawY = unionRect.origin.y;
				startDrawX2 = startDrawX;
				endDrawX2 = unionRect.origin.x;
				startDrawY2 = unionRect.origin.y;
				endDrawY2 = unionRect.getMaxY();
			}
		}
		else//已绘制矩形与当前矩形不相交
		{
			startDrawX = _newBufferTiledRect.origin.x;
			startDrawY = _newBufferTiledRect.origin.y;
			endDrawX = _newBufferTiledRect.getMaxX();
			endDrawY = _newBufferTiledRect.getMaxY();
		}
		SelectObject(srcDC, srcBmp);

		int numw = _mapLoader._width;
		int numh = _mapLoader._height;

		int src_numw = _mapLoader._imageTileWidth;
		//int src_numh = _mapLoader._imageTileHeight;

		const vector<vector<int> >& layers = _mapLoader._layers;
		int length = _mapLoader._layersNum;
		for (size_t lay = 0; lay < length; ++lay)
		{
			const vector<int>& map = layers[lay];
			if (startDrawX < endDrawX) {//如果第一个矩形存在
				startDrawX = max(0, startDrawX);
				startDrawY = max(0, startDrawY);
				endDrawX = min(endDrawX, _mapLoader._width);
				endDrawY = min(endDrawY, _mapLoader._height);

				for (int y = startDrawY, dy = startDrawY - _newBufferTiledRect.origin.y; y < endDrawY; ++y, ++dy)
				{
					for (int x = startDrawX, dx = startDrawX - _newBufferTiledRect.origin.x; x < endDrawX; ++x, ++dx)
					{
						int type = map[y * numw + x];
						if (type == 0)
							continue;
						int drawX = dx * cellw;
						int drawY = dy * cellh;

						int srcX = ((type - 1) % src_numw) * cellw;
						int srcY = ((type - 1) / src_numw) * cellh;
						AlphaBlend(aimDC, drawX, drawY, cellw, cellh, srcDC, srcX, srcY, cellw, cellh, ftn);
					}
				}
			}
			if (startDrawX2 < endDrawX2) {//如果第二个矩形存在
				startDrawX2 = max(0, startDrawX2);
				startDrawY2 = max(0, startDrawY2);
				endDrawX2 = min(endDrawX2, _mapLoader._width);
				endDrawY2 = min(endDrawY2, _mapLoader._height);
				for (int y = startDrawY2, dy = startDrawY2 - _newBufferTiledRect.origin.y; y < endDrawY2; ++y, ++dy)
				{
					for (int x = startDrawX2, dx = startDrawX2 - _newBufferTiledRect.origin.x; x < endDrawX2; ++x, ++dx)
					{
						int type = map[y * numw + x];
						if (type == 0)
							continue;
						int drawX = dx * cellw;
						int drawY = dy * cellh;

						int srcX = ((type - 1) % src_numw) * cellw;
						int srcY = ((type - 1) / src_numw) * cellh;
						AlphaBlend(aimDC, drawX, drawY, cellw, cellh, srcDC, srcX, srcY, cellw, cellh, ftn);
					}
				}
			}
		}
		_hasBuffered = true;
		_bufferTiledRect.origin = _newBufferTiledRect.origin;
		_bufferRect.origin.x = _bufferTiledRect.origin.x * cellw;
		_bufferRect.origin.y = _bufferTiledRect.origin.y * cellh;

		DeleteObject(_bufferBitmap);
		_bufferBitmap = _newBufferBitmap;
		_newBufferBitmap = T_Graph::CreateBlankBitmap(_bufferWidth, _bufferHeight, RGB(0, 0, 0));
		SelectObject(aimDC, oldAimDC);
		SelectObject(srcDC, oldSrcDC);
		DeleteObject(oldAimDC);
		DeleteObject(oldSrcDC);
		DeleteDC(aimDC);
		DeleteDC(srcDC);
	}
}

Camera* TiledMap::camera = nullptr;