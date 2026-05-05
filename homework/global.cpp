#include "global.h"

SZ ws;

int currentROP2 = R2_COPYPEN;

int TimerFuncFPS = 60;
bool isInvert = false;
int dividedNum = 1;
int selectedNum = 0;
POINT paintDiff;

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);

float getDistance(POINT p1, POINT p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}
