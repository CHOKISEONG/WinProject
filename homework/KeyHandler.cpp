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
		break;
	}
}

void KeyHandler::Default(WPARAM wParam)
{
	if (wParam == 'c')
	{
		
	}
	else if (wParam == 's')
	{
		
	}
	else if (wParam == 'p')
	{
		
	}
	else if (wParam == 'e')
	{

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

void KeyHandler::Arrow(WPARAM wParam)
{
	if (wParam == VK_UP)
	{
		// 상/하 도형 스왑
		shapeSwap(shapes[0], shapes[2]);
	}
	else if (wParam == VK_DOWN)
	{
		// 좌/우 도형 스왑
		shapeSwap(shapes[1], shapes[3]);
	}
	else if (wParam == VK_LEFT)
	{
		// 반시계방향 회전
		shapeSwap(shapes[0], shapes[1]);
		shapeSwap(shapes[1], shapes[2]);
		shapeSwap(shapes[2], shapes[3]);
	}
	else if (wParam == VK_RIGHT)
	{
		// 시계방향 회전
		shapeSwap(shapes[0], shapes[3]);
		shapeSwap(shapes[3], shapes[2]);
		shapeSwap(shapes[2], shapes[1]);
	}

	midShapeIdx = 0;
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
