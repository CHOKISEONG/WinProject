#include "Image.h"

void Image::push(POINT p, float t)
{
	target.push_back(Target());
	target.back().pos = p;
	target.back().sizeRatio = t;
	if (target.size() > 10) target.clear();
}

void Image::load(int idx)
{
	// 800 x 800 으로 그림 맞춰야 잘 작동함
	switch (idx)
	{
	case 1:
		bitmap = LoadBitmap(ws.instance, MAKEINTRESOURCE(IDB_BITMAP1));
		break;
	case 2:
		bitmap = LoadBitmap(ws.instance, MAKEINTRESOURCE(IDB_BITMAP2));
		break;
	}

	GetObject(bitmap, sizeof(BITMAP), &bmp);
	width = bmp.bmWidth;
	height = bmp.bmHeight;

	Message::OnSize(ws.hWnd, width, height);
}

void Image::draw(HDC hDC, HDC mDC)
{
	// 디폴트 이미지
	if (magAll)
	{
		// f 돋보기 그리기면
		StretchBlt(
			hDC,
			0, 0, ws.width, ws.height,
			mDC,
			mag.p[0].x + mag.zoomDiff, mag.p[0].y + mag.zoomDiff,
			mag.width - mag.zoomDiff, mag.height - mag.zoomDiff,
			SRCCOPY
		);
	}
	else
	{
		StretchBlt(hDC, 0, 0, ws.width, ws.height, mDC, 0, 0, width, height, SRCCOPY);
	}
	

	// 클릭한 돋보기
	if (mag.activate)
	{
		// 복사된 그림들
		for (const auto& t : target)
		{
			int width = mag.width * t.sizeRatio;
			int height = mag.height * t.sizeRatio;
			int px = t.pos.x - width / 2;
			int py = t.pos.y - height / 2;

			if (hInvert)
			{
				px += width;
				width = -width;
			}

			if (vInvert)
			{
				py += height;
				height = -height;
			}

			StretchBlt(
				hDC,
				px, py, width, height,
				mDC,
				mag.p[0].x + mag.zoomDiff, mag.p[0].y + mag.zoomDiff,
				mag.width - mag.zoomDiff, mag.height - mag.zoomDiff,
				targetRaster
			);
		}

		// 돋보기 그림들
		StretchBlt(
			hDC,
			mag.p[0].x, mag.p[0].y,
			mag.width, mag.height,
			mDC,
			mag.p[0].x + mag.zoomDiff, mag.p[0].y + mag.zoomDiff,
			mag.width - mag.zoomDiff, mag.height - mag.zoomDiff,
			SRCCOPY
		);

		mag.draw(hDC);
	}
}

void Image::reset()
{
	mag = Magnifier();
	target.clear();
	isMoving = false;
	isResizing = false;
	magAll = false;
	hInvert = false;
	vInvert = false;
	targetRaster = SRCCOPY;
}

void Image::move()
{
	for (int i{}; i < 4; ++i)
	{
		mag.p[i].x += dir.x;
		mag.p[i].y += dir.y;
	}

	int speedMax = 9;
	int speedMin = 3;

	if (mag.p[1].x > ws.width)
		dir.x = -(uid(gen) % speedMax + speedMin);

	if (mag.p[0].x < 0)
		dir.x = (uid(gen) % speedMax + speedMin);

	if (mag.p[0].y < 0)
		dir.y = (uid(gen) % speedMax + speedMin);

	if (mag.p[2].y > ws.height)
		dir.y = -(uid(gen) % speedMax + speedMin);
}

void Image::resize()
{
	static float d = 0.1f;
	
	tResize += d;

	if (tResize > 0.5f) d = -0.1f;
	if (tResize < -0.5f) d = 0.1f;

	mag.p[0].x -= tResize * 10;
	mag.p[0].y -= tResize * 10;

	mag.p[1].x += tResize * 10;
	mag.p[1].y -= tResize * 10;

	mag.p[2].x += tResize * 10;
	mag.p[2].y += tResize * 10;

	mag.p[3].x -= tResize * 10;
	mag.p[3].y += tResize * 10;
}

void Magnifier::setArrangeType(int x, int y)
{
	if (x >= p[0].x - 3 && x <= p[0].x + 3
		&& y >= p[0].y - 3 && y <= p[0].y + 3)
	{
		arrangeType = ArrangeType::TopLeft;
	}
	else if (x >= p[1].x - 3 && x <= p[1].x + 3
		&& y >= p[1].y - 3 && y <= p[1].y + 3)
	{
		arrangeType = ArrangeType::TopRight;
	}
	else if (x >= p[2].x - 3 && x <= p[2].x + 3
		&& y >= p[2].y - 3 && y <= p[2].y + 3)
	{
		arrangeType = ArrangeType::BottomRight;
	}
	else if (x >= p[3].x - 3 && x <= p[3].x + 3
		&& y >= p[3].y - 3 && y <= p[3].y + 3)
	{
		arrangeType = ArrangeType::BottomLeft;
	}
	else if (y >= p[0].y - 3 && y <= p[0].y + 3
		&& x >= p[0].x && x <= p[1].x)
	{
		arrangeType = ArrangeType::Top;
	}
	else if (y >= p[2].y - 3 && y <= p[2].y + 3
		&& x >= p[0].x && x <= p[1].x)
	{
		arrangeType = ArrangeType::Bottom;
	}
	else if (x >= p[0].x - 3 && x <= p[0].x + 3
		&& y >= p[0].y && y <= p[3].y)
	{
		arrangeType = ArrangeType::Left;
	}
	else if (x >= p[1].x - 3 && x <= p[1].x + 3
		&& y >= p[0].y && y <= p[3].y )
	{
		arrangeType = ArrangeType::Right;
	}
	else if (x >= p[0].x && y >= p[0].y
		&& x <= p[2].x && y <= p[2].y)
	{
		arrangeType = ArrangeType::Middle;
	}
	else
	{
		arrangeType = ArrangeType::None;
	}
}

void Magnifier::setMag(POINT pos)
{
	p[0] = POINT{ pos.x - 50, pos.y - 50 };
	p[1] = POINT{ pos.x + 50, pos.y - 50 };
	p[2] = POINT{ pos.x + 50, pos.y + 50 };
	p[3] = POINT{ pos.x - 50, pos.y + 50 };

	width = 100;
	height = 100;

	activate = true;
}

void Magnifier::draw(HDC hDC)
{
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	Rectangle(hDC, p[0].x, p[0].y, p[2].x, p[2].y);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void Magnifier::arrange(POINT pos)
{
	switch (arrangeType)
	{
	case ArrangeType::None:
		break;

	case ArrangeType::Middle:
		move(pos);
		break;

	case ArrangeType::Top:
		if (p[0].y + pos.y < p[2].y)
		{
			p[0].y += pos.y;
			p[1].y += pos.y;
		}
		break;

	case ArrangeType::Bottom:
		if (p[2].y + pos.y > p[0].y)
		{
			p[2].y += pos.y;
			p[3].y += pos.y;
		}
		break;

	case ArrangeType::Left:
		if (p[0].x + pos.x < p[1].x)
		{
			p[0].x += pos.x;
			p[3].x += pos.x;
		}
		break;

	case ArrangeType::Right:
		if (p[1].x + pos.x > p[0].x)
		{
			p[1].x += pos.x;
			p[2].x += pos.x;
		}
		break;

	case ArrangeType::TopLeft:
		arrangeType = ArrangeType::Top;
		arrange(POINT{ 0, pos.y });
		arrangeType = ArrangeType::Left;
		arrange(POINT{ pos.x, 0 });
		arrangeType = ArrangeType::TopLeft;
		break;

	case ArrangeType::TopRight:
		arrangeType = ArrangeType::Top;
		arrange(POINT{ 0, pos.y });
		arrangeType = ArrangeType::Right;
		arrange(POINT{ pos.x, 0 });
		arrangeType = ArrangeType::TopRight;
		break;

	case ArrangeType::BottomLeft:
		arrangeType = ArrangeType::Bottom;
		arrange(POINT{ 0, pos.y });
		arrangeType = ArrangeType::Left;
		arrange(POINT{ pos.x, 0 });
		arrangeType = ArrangeType::BottomLeft;
		break;

	case ArrangeType::BottomRight:
		arrangeType = ArrangeType::Bottom;
		arrange(POINT{ 0, pos.y });
		arrangeType = ArrangeType::Right;
		arrange(POINT{ pos.x, 0 });
		arrangeType = ArrangeType::BottomRight;
		break;

	default:
		break;
	}

	width = p[1].x - p[0].x;
	height = p[2].y - p[0].y;
}
