#include "KeyHandler.h"

void KeyHandler::KeyDown(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
		KeyHandler::Esc();
		break;
	case VK_BACK:
		KeyHandler::BackSpace();
		break;
	case VK_RETURN:
		KeyHandler::Enter();
		break;
	case VK_UP:case VK_DOWN: case VK_LEFT: case VK_RIGHT:
		KeyHandler::Arrow(wParam);
		break;
	case VK_TAB:
		KeyHandler::Tab();
		break;
	case VK_HOME:
		KeyHandler::Home();
		break;
	case VK_END:
		KeyHandler::End();
		break;
	case VK_INSERT:
		KeyHandler::Insert();
		break;
	case VK_DELETE:
		KeyHandler::Del();
		break;
	case VK_PRIOR:
		KeyHandler::PgUp();
		break;
	case VK_NEXT:
		KeyHandler::PgDown();
	default:
		break;
	}
}

void KeyHandler::Default(WPARAM wParam)
{
	if (!isalnum(wParam)) return;

	if (pos.x < MAX_LETTER)
	{
		textBuffer[pos.y][pos.x] = wParam;
		++pos.x;
	}
	else
	{
		++pos.y;
		pos.x = 0;
		if (pos.y == MAX_LINE)
		{
			pos.y = 0;
		}
		textBuffer[pos.y][pos.x] = wParam;
	}
}

void KeyHandler::Enter()
{
	pos.y = (pos.y + 1) % MAX_LINE;
	pos.x = 0;
}

void KeyHandler::BackSpace()
{
	if (pos.x == 0 && pos.y == 0) return;

	if (pos.x == 0)
	{
		--pos.y;
		pos.x = checkLetterCnt(pos.y);
	}
	else
	{
		--pos.x;
		textBuffer[pos.y][pos.x] = 0;
	}
}

void KeyHandler::Esc()
{
	for (int i{}; i < MAX_LINE; ++i)
	{
		for (int j{}; j < MAX_LETTER; ++j)
		{
			textBuffer[i][j] = NULL;
		}
	}
	pos.x = 0;
	pos.y = 0;
}

void KeyHandler::Arrow(WPARAM wParam)
{
}

void KeyHandler::Tab()
{
}

void KeyHandler::Home()
{
}

void KeyHandler::End()
{
}

void KeyHandler::Insert()
{
}

void KeyHandler::Del()
{
}

void KeyHandler::PgUp()
{
}

void KeyHandler::PgDown()
{
}
