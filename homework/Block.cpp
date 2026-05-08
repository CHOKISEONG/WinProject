#include "Block.h"
#include "Board.h"

Block::Block()
{
	load(0);
	pos = board.getRandPos();
}
