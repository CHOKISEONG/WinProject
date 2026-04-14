#include "global.h"

SZ ws;

int currentROP2 = R2_COPYPEN;

int playerAnimEvent = 1;
int playerAnimFPS = 10;

int timerProcCnt = 2;

bool isGameStarted = false;
bool isAkeyToggled = false;

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);
