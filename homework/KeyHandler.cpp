#include "KeyHandler.h"

void KeyHandler::KeyDown(WPARAM key)
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
	default:
		KeyHandler::Default(key);
		break;
	}
}

void KeyHandler::Default(WPARAM key)
{
	const char _key = (char)tolower(key);
	
	switch (_key)
	{
	// 마우스를 클릭하는 곳에 사각형
	case'r':
	{
		shape.setType(Type::RECT);
		break;
	}
	// 마우스를 클릭하는 곳에 원
	case'e':
	{
		shape.setType(Type::CIRCLE);
		break;
	}
	// 마우스를 클릭하는 곳에 삼각형
	case't':
	{
		shape.setType(Type::TRIANGLE);
		break;
	}
	// 현재 위치에서 우측으로 자동 이동
	case'h':
	{
		shape.setDir(0.0f);
		break;
	}
	// 현재 위치에서 아래쪽으로 자동 이동
	case'v':
	{
		shape.setDir(-90.0f);
		break;
	}
	// 현재 위치에서 대각선 방향으로 자동 이동
	case's':
	{
		POINT sPos = shape.getPos();
		shape.setDir(atan2(ws.mouse.y - sPos.y, ws.mouse.x - sPos.x)  * 180.0f / PI);
		break;
	}
	// 이동을 멈추기
	case'p':
	{
		shape.setDir(0.0f);
		shape.isMoving = false;
		break;
	}
	// 이동 속도 늘이기
	case'+':
	{
		shape.changeSpeed(1.0f);
		break;
	}
	// 이동 속도 줄이기
	case'-':
	{
		shape.changeSpeed(-1.0f);
		break;
	}
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
		
	}
	else if (key == VK_DOWN)
	{
		
	}
	else if (key == VK_LEFT)
	{
		
	}
	else if (key == VK_RIGHT)
	{
		
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
