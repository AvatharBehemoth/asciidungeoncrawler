#include "Monster.h"
#include <string>

Monster::Monster()
{
}

unsigned Monster::getMonsterCoord() {
	return _monsterX;
	return _monsterY;
}

void Monster::setMonsterCoord()
{
	_monsterX = 100;
	_monsterY = 100;
}

Monster::~Monster()
{
}
