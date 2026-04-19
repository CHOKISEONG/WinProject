#include "KeyHandler.h"
#include "Message.h"
#include "Car.h"
#include "TrafficLight.h"

void KeyHandler::Default(HWND hWnd, WPARAM key)
{
	const char _key = (char)tolower(key);
	
	switch (_key)
	{
	case'a':
		isKeyDown['a'] = !isKeyDown['a'];
		if (isKeyDown['a'])
		{
			SetTimer(hWnd, 99, 2000, (TIMERPROC)SwitchTimer);
		}
		else
		{
			KillTimer(hWnd, 99);
		}
		break;
	case'q':
	{
		exit(0);
		break;
	}
	}
}

void KeyHandler::Enter(HWND hWnd)
{
	
}

void KeyHandler::Space()
{
	
}

void KeyHandler::BackSpace()
{

}

void KeyHandler::Esc()
{
	
}

void KeyHandler::Arrow(HWND hWnd, WPARAM key)
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
	for (auto& c : cars)
	{
		c->changeSpeed(0.1f);
	}
}

void KeyHandler::Minus(HWND hWnd)
{
	for (auto& c : cars)
	{
		c->changeSpeed(-0.1f);
	}
}

void KeyHandler::KeyDown(HWND hWnd, WPARAM key)
{
	switch (key)
	{
	case VK_SPACE:
		KeyHandler::Space();
		break;
	case VK_ESCAPE:
		KeyHandler::Esc();
		break;
	case VK_BACK:
		KeyHandler::BackSpace();
		break;
	case VK_RETURN:
		KeyHandler::Enter(hWnd);
		break;
	case VK_UP:case VK_DOWN: case VK_LEFT: case VK_RIGHT:
		KeyHandler::Arrow(hWnd, key);
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