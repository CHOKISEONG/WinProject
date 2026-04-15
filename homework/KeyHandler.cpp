#include "KeyHandler.h"
#include "Board.h"
#include "Message.h"

void KeyHandler::KeyDown(HWND hWnd, WPARAM key)
{
	switch (key)
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
		KeyHandler::Arrow(key);
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
		break;
	case VK_F1:
		KeyHandler::F1();
		break;
	case VK_F2:
		KeyHandler::F2();
		break;
	case VK_F3:
		KeyHandler::F3();
		break;
	case VK_F4:
		KeyHandler::F4();
		break;
	case VK_F5:
		KeyHandler::F5();
		break;
	case VK_F6:
		KeyHandler::F6();
		break;
	case VK_F7:
		KeyHandler::F7();
		break;
	case VK_F8:
		KeyHandler::F8();
		break;
	case VK_OEM_PLUS:
		KeyHandler::Plus(hWnd);
		break;
	case VK_OEM_MINUS:
		KeyHandler::Minus(hWnd);
	default:
		break;
	}
}

void KeyHandler::Default(HWND hWnd, WPARAM key)
{
	const char _key = (char)tolower(key);
	
	switch (_key)
	{
	case 's':
		isGameStarted = true;
		break;
	case 'j':
	{
		// 주인공원과그꼬리들은그자리에서(또는이동하면서)
		// 이동방향에수직방향으로점프하도록한다.
		Direction dir = board.getDir();
		if (dir == Direction::UPDIR)
		{
			board.changeDir(Direction::LEFTDIR);
			board.changeDir(Direction::UPDIR);
			board.changeDir(Direction::UPDIR);
			board.changeDir(Direction::RIGHTDIR);
			board.changeDir(Direction::UPDIR);
		}
		else if (dir == Direction::DOWNDIR)
		{
			board.changeDir(Direction::RIGHTDIR);
			board.changeDir(Direction::DOWNDIR);
			board.changeDir(Direction::DOWNDIR);
			board.changeDir(Direction::LEFTDIR);
			board.changeDir(Direction::DOWNDIR);
		}
		else if (dir == Direction::LEFTDIR)
		{
			board.changeDir(Direction::UPDIR);
			board.changeDir(Direction::LEFTDIR);
			board.changeDir(Direction::LEFTDIR);
			board.changeDir(Direction::DOWNDIR);
			board.changeDir(Direction::LEFTDIR);
		}
		else if (dir == Direction::RIGHTDIR)
		{
			board.changeDir(Direction::UPDIR);
			board.changeDir(Direction::RIGHTDIR);
			board.changeDir(Direction::RIGHTDIR);
			board.changeDir(Direction::DOWNDIR);
			board.changeDir(Direction::RIGHTDIR);
		}
		break;
	}
	case 't':
		// 주인공원이맨뒤의꼬리원이되고, 첫번째꼬리원이주인공원이된다.
		board.swapSnake();
		break;
	case 'a':
		//  아주빠른속도로지그재그이동
		isAkeyToggled = !isAkeyToggled;

		if (isAkeyToggled)
		{
			board.setHighSnake();
			KillTimer(hWnd, playerAnimEvent);
			SetTimer(hWnd, playerAnimEvent, 1000 / (playerAnimFPS * 30), (TIMERPROC)Message::SnakeTimer);
		}
		else
		{
			board.setNormalSnake();
			KillTimer(hWnd, playerAnimEvent);
			SetTimer(hWnd, playerAnimEvent, 1000 / playerAnimFPS, (TIMERPROC)Message::SnakeTimer);
		}

		break;
	case'q':
	{
		exit(0);
		break;
	}
	}
}

void KeyHandler::Enter()
{
}

void KeyHandler::BackSpace()
{

}

void KeyHandler::Esc()
{
	
}

void KeyHandler::Arrow(WPARAM key)
{
	if (key == VK_UP)
	{
		board.changeDir(Direction::UPDIR);
	}
	else if (key == VK_DOWN)
	{
		board.changeDir(Direction::DOWNDIR);
	}
	else if (key == VK_LEFT)
	{
		board.changeDir(Direction::LEFTDIR);
	}
	else if (key == VK_RIGHT)
	{
		board.changeDir(Direction::RIGHTDIR);
	}
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
{}

void KeyHandler::PgUp()
{
}

void KeyHandler::PgDown()
{
}

void KeyHandler::F1()
{
}

void KeyHandler::F2()
{
}

void KeyHandler::F3()
{
}

void KeyHandler::F4()
{
}

void KeyHandler::F5()
{
}

void KeyHandler::F6()
{
}

void KeyHandler::F7()
{
}

void KeyHandler::F8()
{
}

void KeyHandler::Plus(HWND hWnd)
{
	KillTimer(hWnd, playerAnimEvent);
	if (playerAnimFPS < 20)
		playerAnimFPS += 3;
	SetTimer(hWnd, playerAnimEvent, 1000 / playerAnimFPS, (TIMERPROC)Message::SnakeTimer);
}

void KeyHandler::Minus(HWND hWnd)
{
	KillTimer(hWnd, playerAnimEvent);
	if (playerAnimFPS > 1)
		playerAnimFPS -= 3;
	SetTimer(hWnd, playerAnimEvent, 1000 / playerAnimFPS, (TIMERPROC)Message::SnakeTimer);
}
