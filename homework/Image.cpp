#include "Image.h"
#include "Board.h"

void Image::load(int idx)
{
	if (bitmap != NULL)
	{
		DeleteObject(bitmap);
		bitmap = NULL;
	}

	if (idx < 0)
		bitmap = LoadBitmap(ws.instance, MAKEINTRESOURCE(IDB_BITMAPCOL));
	else
		bitmap = LoadBitmap(ws.instance, MAKEINTRESOURCE(IDB_BITMAP1 + idx));
	GetObject(bitmap, sizeof(BITMAP), &bmp);
	bWidth = bmp.bmWidth;
	bHeight = bmp.bmHeight;
}

void Image::draw(HDC hDC, HDC mDC)
{
	if (bitmap == NULL) return;

	HBITMAP old = (HBITMAP)SelectObject(mDC, bitmap);

	StretchBlt(
		hDC,
		pos.x - rad, pos.y - rad,
		rad * 2, rad * 2,
		mDC,
		0, 0, bWidth, bHeight,
		SRCCOPY
	);

	SelectObject(mDC, old);
}
