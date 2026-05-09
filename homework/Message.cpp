#include "Message.h"
#include "KeyHandler.h"
#include "resource.h"
#include "Image.h"
#include "CardManager.h"
#include "Character.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <algorithm>

void Message::OnCreate(HWND hWnd)
{
	// event id를 관리해야할 필요가 느껴질 때 두번째 인자 수정하기
	SetTimer(hWnd, 0, 1000 / TimerFuncFPS, (TIMERPROC)TimerFunc);

	ws.makeOOWRect();

	Card::initDatabase();

	// 임시로 초기덱 세팅
	for (int i{}; i < 4; ++ i)
		cardManager.add(NameEnum::수비);
	for (int i{}; i < 5; ++i)
		cardManager.add(NameEnum::타격);
	cardManager.add(NameEnum::강타);

	// 5장 뽑아봄
	cardManager.shuffleDeck();
	cardManager.drawCards(5);

	// 임시 배경 설정
	background.initBG();

	// 테스트용 적 5마리 생성 (지금은 랜덤적 나옴)
	for (int i{}; i < 5; ++i)
		enemies.push_back(new Enemy);

	ironclad = new Player;

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	if (ironclad)
	{
		ironclad->tick();

		if (ironclad->getMp() == 0 && !ironclad->isEnemyTurn)
			ironclad->endTurn();
	}
		
	for (auto& e : enemies)
		e->tick();

	// (적들을 관리하는 EnemyManager로 나중에 발전시킬 예정)
	// 임시로 적 죽으면 다음적 나오는 로직으로 함
	if (!enemies.empty())
	{
		if (!enemies[0]->getAlive())
		{
			enemies.erase(enemies.begin());
		}
	}

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, width, height);
	HBITMAP hOldMemBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);

	FillRect(hMemDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

	HDC mDC = CreateCompatibleDC(hDC);


	POINT windowSZ{ ws.width,ws.height };
	for (auto& b : background.images)
	{
		b->setPos(POINT{ ws.width / 2, ws.height / 2 });
		b->draw(hMemDC, mDC, windowSZ);
	}

	ironclad->setPos(POINT{ ws.width / 4, ws.height / 2 });
	ironclad->drawWithState(hMemDC, mDC);
	ironclad->showMp(hMemDC);

	enemies[0]->setPos(POINT{ ws.width * 3 / 4, ws.height / 2 });
	enemies[0]->drawWithState(hMemDC, mDC);
	enemies[0]->showCurrentPattern(hMemDC);

	cardManager.draw(hMemDC, mDC);

	std::wstring deckCount = L"덱 수:" + std::to_wstring(cardManager.getDeckCount());
	TextOut(hMemDC, 0, ws.height * 9 / 10, deckCount.c_str(), deckCount.size());

	std::wstring discardCount = L"버린 카드:" + std::to_wstring(cardManager.getDiscardCount());
	TextOut(hMemDC, ws.width * 9 / 10, ws.height * 9 / 10, discardCount.c_str(), discardCount.size());


	BitBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(mDC);

	SelectObject(hMemDC, hOldMemBitmap);
	DeleteObject(hMemBitmap);
	DeleteDC(hMemDC);

	EndPaint(hWnd, &ps);
}

void Message::LMouseDown(int mouse_x, int mouse_y)
{
	ws.mouseDownPos = POINT{ mouse_x, mouse_y };
	ws.mousePos = ws.mousePrevPos = ws.mouseDownPos;

	cardManager.selectCard(ws.mouseDownPos);
}

void Message::LMouseUp(int mouse_x, int mouse_y)
{
	int xDiff = mouse_x - ws.mouseDownPos.x;
	int yDiff = mouse_y - ws.mouseDownPos.y;

	ws.mouseUpPos.x = mouse_x;
	ws.mouseUpPos.y = mouse_y;
	ws.mousePos = ws.mouseUpPos;

	// 임시
	if (ws.mousePos.y < ws.height * 3 / 5)
		cardManager.useCard(ws.mouseUpPos);

	handIdx = -1;
}

void Message::MouseMove(int mouse_x, int mouse_y)
{
	ws.mousePrevPos = ws.mousePos;
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;
	cardManager.move(POINT{ ws.mousePos.x - ws.mousePrevPos.x, ws.mousePos.y - ws.mousePrevPos.y });

	// InvalidateRect(ws.hWnd, NULL, FALSE);
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
	keyboard[tolower(wParam)] = true;

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
	switch (wParam)
	{
	
		default:
			break;
	}
}

void Message::OnDestroy(HWND hWnd)
{
	Image::ReleaseCachedBitmaps();
	PostQuitMessage(0);
}
