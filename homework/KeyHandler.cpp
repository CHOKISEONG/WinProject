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

	switch (_key)
	{
	case 'e':
		pos = getEmptyTile();
		boards[pos.x][pos.y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		boards[pos.x][pos.y].type = Shape::Cirle;
		applyPolygon(pos.x, pos.y);

		p.push_back(pos);
		break;
	case 't':
		pos = getEmptyTile();
		boards[pos.x][pos.y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		boards[pos.x][pos.y].type = Shape::Triangle;
		applyPolygon(pos.x, pos.y);

		p.push_back(pos);
		break;
	case 'r':
		pos = getEmptyTile();
		boards[pos.x][pos.y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		boards[pos.x][pos.y].type = Shape::Rect;
		applyPolygon(pos.x, pos.y);

		p.push_back(pos);
		break;

	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9':
		choicedNum = static_cast<int>(_key - '0');
		if (choicedNum < 0 || choicedNum > 9)
		{
			choicedNum = 0;
		}

		if (p.size() <= choicedNum) choicedNum = p.size() - 1;

		break;

	case 'c':
		for (int i{}; i < p.size(); ++i)
		{
			if (i == choicedNum) break;

			if (boards[p[i].x][p[i].y].type == boards[p[choicedNum].x][p[choicedNum].y].type)
			{
				boards[p[i].x][p[i].y].type = Shape::Pentagon;
				boards[p[i].x][p[i].y].color.r = boards[p[choicedNum].x][p[choicedNum].y].color.r;
				boards[p[i].x][p[i].y].color.g = boards[p[choicedNum].x][p[choicedNum].y].color.g;
				boards[p[i].x][p[i].y].color.b = boards[p[choicedNum].x][p[choicedNum].y].color.b;
				applyPolygon(p[i].x, p[i].y);
			}

		}
		break;

	case'k': // 확대
		if (choicedNum == -1) return;

		boards[p[choicedNum].x][p[choicedNum].y].resizeNum += 1;
		if (boards[p[choicedNum].x][p[choicedNum].y].resizeNum > 3)
			boards[p[choicedNum].x][p[choicedNum].y].resizeNum = 3;
		break;

	case'l': // 축소
		if (choicedNum == -1) return;

		boards[p[choicedNum].x][p[choicedNum].y].resizeNum -= 1;
		if (boards[p[choicedNum].x][p[choicedNum].y].resizeNum < -3)
			boards[p[choicedNum].x][p[choicedNum].y].resizeNum = -3;
		break;

	case'd':
		if (choicedNum == -1) return;
		boards[p[choicedNum].x][p[choicedNum].y].type = Shape::None;
		applyPolygon(p[choicedNum].x, p[choicedNum].y);
		p.erase(p.begin() + choicedNum);
		choicedNum = -1;
		break;

	case 'p':
		choicedNum = -1;
		p.clear();
		makeBoard();
		setPosition();
		break;

	case 'q':
		exit(0);
		break;
	}

	if (p.size() > 10)
	{
		boards[p[0].x][p[0].y].type = Shape::None;
		applyPolygon(p[0].x, p[0].y);
		p.erase(p.begin());
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
	if (choicedNum == -1) return;

	POINT pos, target;
	target = pos = p[choicedNum];
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

	moveTile(pos, target);

	p[choicedNum] = target;
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
