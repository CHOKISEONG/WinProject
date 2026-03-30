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
	if (!isalnum(wParam) && wParam != ' ') return;


	if (pos.x >= MAX_LETTER)
	{
		pos.y = (pos.y + 1) % MAX_LINE;
		pos.x = 0;
	}

	if (type == LetterType::PUSH)
	{
		for (int i{ getLetterLength(pos.y) }; i > pos.x; --i)
		{
			textBuffer[pos.y][i] = textBuffer[pos.y][i - 1];
		}
	}

	if (isUpper)
		wParam = toupper(wParam);
	textBuffer[pos.y][pos.x] = wParam;
	++pos.x;
	textBuffer[pos.y][MAX_LETTER] = '\0';
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
		pos.x = getLetterLength(pos.y);
		return;
	}

	if (pos.x == 0) return;

	--pos.x;

	const int len = getLetterLength(pos.y);

	for (int i = pos.x; i < len; ++i)
	{
		textBuffer[pos.y][i] = textBuffer[pos.y][i + 1];
	}

	textBuffer[pos.y][len] = NULL;
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
	if (wParam == VK_DOWN)
	{
		pos.y = (pos.y + 1) % MAX_LINE;
		if (textBuffer[pos.y][pos.x] == NULL)
		{
			pos.x = getLetterLength(pos.y);
		}
	}
	else if (wParam == VK_UP)
	{
		pos.y = (pos.y + MAX_LINE - 1) % MAX_LINE;
		if (textBuffer[pos.y][pos.x] == NULL)
		{
			pos.x = getLetterLength(pos.y);
		}
	}
	else if (wParam == VK_LEFT)
	{
		if (pos.x > 0) --pos.x;
	}
	else if (wParam == VK_RIGHT)
	{
		if (pos.x < getLetterLength(pos.y)) ++pos.x;
	}
}

void KeyHandler::Tab()
{
	for (int i{}; i < 4; ++i)
	{
		if (getLetterLength(pos.y) < MAX_LETTER)
			KeyHandler::Default(' ');
	}
}

void KeyHandler::Home()
{
	pos.x = 0;
}

void KeyHandler::End()
{
	pos.x = getLetterLength(pos.y);
}

void KeyHandler::Insert()
{
	type = (type == LetterType::OVERWRITE) ? LetterType::PUSH : LetterType::OVERWRITE;
}

void KeyHandler::Del()
{
	if (textBuffer[pos.y][pos.x] == ' ' || pos.x == getLetterLength(pos.y)) return;

	while (textBuffer[pos.y][pos.x] != ' ')
	{
		if (pos.x == 0) break;
		--pos.x;
	}

	int wordLen{ 1 };
	while (textBuffer[pos.y][pos.x + wordLen] != ' ' && pos.x + wordLen < getLetterLength(pos.y))
	{
		++wordLen;
	}

	pos.x += wordLen;
	for (int i{}; i < wordLen; ++i)
	{
		KeyHandler::BackSpace();
	}
}

void KeyHandler::PgUp()
{
	pos.y = (pos.y + MAX_LINE - 3) % MAX_LINE;

	if (textBuffer[pos.y][pos.x] == NULL)
	{
		pos.x = getLetterLength(pos.y);
	}
}

void KeyHandler::PgDown()
{
	pos.y = (pos.y + MAX_LINE + 3) % MAX_LINE;

	if (textBuffer[pos.y][pos.x] == NULL)
	{
		pos.x = getLetterLength(pos.y);
	}
}

void KeyHandler::F1()
{
	isUpper = !isUpper;
}

void KeyHandler::F2()
{
	// 숫자가포함되어있는줄에서숫자앞에4칸의*을넣는다.  
	// 이때는30자가넘어도한줄에그대로출력한다.  
	// 다시누르면없어진다
	printType.addTapToNum = !printType.addTapToNum;
}

void KeyHandler::F3()
{
	// 공백으로 구분되는단어를괄호가둘러싸고단어를대문자로출력한다. 
	// 이때는30자가넘어도한줄에그대로출력한다. 
	// 다시누르면괄호가삭제되고모든문자들은원래문자로바뀐다
	printType.putInParentheses = !printType.putInParentheses;
}

void KeyHandler::F4()
{
	// 공백문자를모두삭제되고소문자로출력한다.  
	// 다시입력하면다시원래위치에공백이생기고원래문자로출력한다. 
	printType.deleteSpace = !printType.deleteSpace;
}

void KeyHandler::F5()
{
	// 각줄에서가장많은문자를@로바꿔출력한다.  
	// 다시입력하면원래문자가출력된다
	printType.changeToC = !printType.changeToC;
}

void KeyHandler::F6()
{
	// 줄의순서가한줄씩앞으로이동한다.  
	// (3줄이있다면, 3→2, 2→1, 1→3줄)
	shiftLine();
}

void KeyHandler::F7()
{
	// 입력되어있는모든숫자에1을더한다. 
	addNumberToText(1);
}

void KeyHandler::F8()
{
	// 입력되어있는모든숫자에1을뺀다.  (0 →9, 9 →8, … 2 → 1)
	addNumberToText(-1);
}
