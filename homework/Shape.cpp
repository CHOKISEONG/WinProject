#include "Shape.h"

void Shape::draw(HDC hDC) const
{
	if (type == Type::NONE
		|| isDrawing == false) return;


	if (shape.type == Type::RECT)
	{

	}
	else if (shape.type == Type::CIRCLE)
	{

	}
	else if (shape.type == Type::CIRCLE)
	{

	}

}

void Shape::setDir(float degree)
{
	moveDir.x = cos(degree);
	moveDir.y = sin(degree);
}
