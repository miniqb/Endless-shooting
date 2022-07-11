#include "BloodHearts.h"

BloodHearts::BloodHearts():
	_health(33),
	_wsum(10),
	_hsum(2),
	_graph(),
	_oX(14),
	_oY(14),
	_clearance(1.2f),
	_maxHealth(40)
{
	_scaleX = 0.7f;
}

BloodHearts::BloodHearts(int health, int h, int w, const wstring& fileName):
	_health(health),
	_wsum(h),
	_hsum(w),
	_oX(20),
	_oY(20),
	_clearance(1.2f)
{
	_graph.LoadImageFile(fileName);
	_scaleX = 1;
	_cellW = _graph.GetImageWidth() / 3;
	_cellH = _graph.GetImageHeight();
}

BloodHearts::~BloodHearts()
{
}

void BloodHearts::drawSelf(HDC hdc)
{
	if (_graph.GetBmpHandle())
	{
		int length = 0;
		int width = _scaleX * _clearance * _cellW;
		int height = _scaleX * _clearance * _cellH;
		while (length<_maxHealth)
		{
			int c = _health - length;
			int destX, destY;
			destX = _oX + ((int)(length * 0.5) % _wsum) * width;
			destY = _oY + ((int)(length * 0.5) / _wsum) * height;
			int count;
			if (c > 1)
			{
				count = 1;
			}
			else if(c==1)
			{
				count = 2;
			}
			else
			{
				count = 0;
			}
			T_Graph::PaintFrame(_graph.GetBmpHandle(), hdc, destX, destY, count, 3,
				_cellW, _cellH, _scaleX);
			length += 2;
		}
	}
		
}

void BloodHearts::setGraph(const wstring& fileName)
{
	_graph.LoadImageFile(fileName);
	_cellW = _graph.GetImageWidth() / 3;
	_cellH = _graph.GetImageHeight();
}
