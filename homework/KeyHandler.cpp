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
	
	POINT pos;
	static std::vector<POINT> p;
	static int choicedNum{ -1 };

	switch (_key)
	{
	case 'e':
		pos = getEmptyTile();
		boards[pos.x][pos.y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		boards[pos.x][pos.y].type = Shape::Cirle;
		applyPolygon(pos.x, pos.y);
		break;
	case 't':
		pos = getEmptyTile();
		boards[pos.x][pos.y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		boards[pos.x][pos.y].type = Shape::Triangle;
		applyPolygon(pos.x, pos.y);
		break;
	case 'r':
		pos = getEmptyTile();
		boards[pos.x][pos.y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		boards[pos.x][pos.y].type = Shape::Rect;
		applyPolygon(pos.x, pos.y);
		break;
	case'+':
		break;
	case'-':
		break;
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
	if (whosTurn == 2)	return;
	whosTurn = 2;

	POINT pos, target;
	target = pos = getTile(Shape::Player1);
	if (key == VK_UP)
	{
		target.y = (target.y - 1 + boardRow) % boardRow;
	}
	else if (key == VK_DOWN)
	{
		target.y = (target.y + 1 + boardRow) % boardRow;
	}
	else if (key == VK_LEFT)
	{
		target.x = (target.x - 1 + boardCol) % boardCol;
	}
	else if (key == VK_RIGHT)
	{
		target.x = (target.x + 1 + boardCol) % boardCol;
	}

	if (boards[target.x][target.y].tileType == Shape::Obstacle) return;

	moveTile(pos, target);

	if (boards[target.x][target.y].reShapeCnt > 0)
	{
		--boards[target.x][target.y].reShapeCnt;
	}
	else
	{
		boards[target.x][target.y].type = Shape::SandClock;
		applyPolygon(target.x, target.y);
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
