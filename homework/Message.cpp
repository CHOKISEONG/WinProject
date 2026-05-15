#include "Message.h"
#include "KeyHandler.h"
#include "Board.h"
#include "resource.h"
#include "Image.h"
#include "Block.h"
#include "Cat.h"
#include "Enemy.h"
#include "Particle.h"
#include <string>
#include <algorithm>

void Message::OnCreate(HWND hWnd)
{
	// event id를 관리해야할 필요가 느껴질 때 두번째 인자 수정하기
	SetTimer(hWnd, 0, 1000 / TimerFuncFPS, (TIMERPROC)TimerFunc);

	cat.load(0);
	cat.initialize();
	cat.pos = { ws.width / 2, ws.height * 4 / 5 };

	background[0].pos = {ws.width / 2, ws.height / 2};
	background[0].rad = max(ws.width, ws.height);
	background[0].width = WIDTH;
	background[0].height = HEIGHT;
	background[0].load(4);

	background[1].pos = { ws.width / 2, ws.height * 4 / 5};
	background[1].rad = max(ws.width, ws.height);
	background[1].width = WIDTH;
	background[1].height = HEIGHT; 
	background[1].load(5);

	background[2].pos = { ws.width * 3 / 2 + WIDTH, ws.height / 2 };
	background[2].rad = max(ws.width, ws.height);
	background[2].width = WIDTH;
	background[2].height = HEIGHT;
	background[2].load(4);

	background[3].pos = { ws.width * 3/ 2 + WIDTH, ws.height * 4 / 5 };
	background[3].rad = max(ws.width, ws.height);
	background[3].width = WIDTH;
	background[3].height = HEIGHT;
	background[3].load(5);

	enemy.load(1);
	enemy.pos = { ws.width + 100, ws.height * 4 / 5 };

	ws.makeOOWRect();

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static float t = 0.0f;
	t += 0.1f;
	if (t >= 0.3f)
	{
		cat.animate();
		enemy.move();
		t = 0.0f;
	}

	for (auto& p : particles)
		p.move();
	for (int i{}; i < (int)particles.size(); ++i)
	{
		if (particles[i].getPos().x < 0 || particles[i].getPos().x > ws.width
			|| particles[i].getPos().y < 0 || particles[i].getPos().y > ws.height)
		{
			particles.erase(particles.begin() + i);
			--i;
		}
	}

	static float enemyT = 0.0f;
	enemyT += 0.1f;
	if (enemyT >= 20.0f)
	{
		enemy.load(1);

		if (uid(gen) % 2)
		{
			enemy.pos = { -5, ws.height * 4 / 5 };
		}
		else
		{
			enemy.pos = { -5, ws.height * 4 / 5 - 20};
		}
		
		enemyT = 0.0f;
	}

	for (int i{}; i < 2; ++i)
	{
		background[i].pos.x -= 1 + (1 - i);
		background[i + 2].pos.x -= 1 + (1 - i);
		if (background[i].pos.x + WIDTH <= 0)
			background[i].pos.x = ws.width * 3 / 2 + WIDTH;
		if (background[i + 2].pos.x + WIDTH <= 0)
			background[i + 2].pos.x = ws.width * 3 / 2 + WIDTH;
	}

	

	if (keyboard[tolower(VK_LEFT)] && !keyboard[tolower(VK_RIGHT)])
		cat.move(Direction::LEFTDIR);
	else if (keyboard[tolower(VK_RIGHT)] && !keyboard[tolower(VK_LEFT)])
		cat.move(Direction::RIGHTDIR);

	if (keyboard[tolower(VK_DOWN)])
	{
		cat.squeeze();
	}
	else
	{
		cat.original();
	}

	RECT catRt{
		cat.dPos.x + cat.pos.x - cat.width,
		cat.dPos.y + cat.pos.y - cat.height,
		cat.dPos.x + cat.pos.x + cat.width,
		cat.dPos.y + cat.pos.y + cat.height
	};

	RECT enemyRt{
		enemy.dPos.x + enemy.pos.x - enemy.width + 40,
		enemy.dPos.y + enemy.pos.y - enemy.height + 40,
		enemy.dPos.x + enemy.pos.x + enemy.width - 40,	
		enemy.dPos.y + enemy.pos.y + enemy.height - 40
	};

	RECT inter{};
	if (IntersectRect(&inter, &catRt, &enemyRt))
	{
		particles.push_back(Particle(cat.pos));
		cat.isCollide = true;
	}
	else
		cat.isCollide = false;

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ai도움 많이 받음
	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, width, height);
	HBITMAP hOldMemBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);

	FillRect(hMemDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

	HDC mDC = CreateCompatibleDC(hDC);

	for (int i{}; i < 2; ++i)
	{
		background[i].draw(hMemDC, mDC);
		background[i + 2].draw(hMemDC, mDC);
	}

	cat.draw(hMemDC, mDC);

	enemy.draw(hMemDC, mDC);

	for (auto& p : particles)
		p.draw(hMemDC);

	BitBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(mDC);

	SelectObject(hMemDC, hOldMemBitmap);
	DeleteObject(hMemBitmap);
	DeleteDC(hMemDC);

	EndPaint(hWnd, &ps);
}

void Message::LMouseDown(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;
}

void Message::LMouseUp(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;
}

void Message::MouseMove(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;
}

void Message::RMouseDown(int mouse_x, int mouse_y)
{
}

void Message::RMouseUp(int mouse_x, int mouse_y)
{
}

void Message::LMouseDBClick(int mouse_x, int mouse_y)
{

}

void Message::RMouseDBClick(int mouse_x, int mouse_y)
{

}


void Message::OnKeyDown(HWND hWnd, WPARAM wParam)
{
	keyboard[tolower(wParam)] = true;

	switch (wParam)
	{
	case VK_UP:case VK_DOWN:case VK_LEFT:case VK_RIGHT:
	case VK_ESCAPE:case VK_BACK:case VK_RETURN:case VK_TAB:
	case VK_HOME:case VK_END:case VK_INSERT:
	case VK_DELETE:case VK_PRIOR:case VK_NEXT:
	case VK_F1:case VK_F2:case VK_F3:case VK_F4:
	case VK_F5:case VK_F6:case VK_F7:case VK_F8:
	case VK_OEM_PLUS: case VK_OEM_MINUS:
		KeyHandler::KeyDown(hWnd, wParam);
		InvalidateRect(hWnd, NULL, FALSE);
		return;
	default:
		KeyHandler::Default(hWnd, wParam);
		break;
	}
	

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnKeyUp(HWND hWnd, WPARAM wParam)
{
	keyboard[tolower(wParam)] = false;
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnChar(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnSize(HWND hWnd, int width, int height)
{
	ws.width = width;
	ws.height = height;
	ws.makeOOWRect();
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnMessage(HWND hWnd, WPARAM wParam)
{
}

void Message::OnDestroy(HWND hWnd)
{
	Image::ReleaseCachedBitmaps();
	PostQuitMessage(0);
}
