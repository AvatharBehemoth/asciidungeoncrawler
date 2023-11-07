#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::getMoney(int i, int gold, int silver, int copper)
{
	_goldCoin += gold;
	_silverCoin += silver;
	_copperCoin += copper;

}

void Player::setPlayerStats(int gC, int sC, int cC)
{
	_goldCoin += gC;
	_silverCoin += sC;
	_copperCoin += cC;
}
void Player::setweapon(Item& item) 
{
	for (int i = 0; i < 6; i++)
	{
		if (playerInvetory[i]._itemtype == "weapon")
		{
			playerInvetory[i].equipped = false;
		}
	}
	item.equipped = true;
	_weapon = item._itemname;
	_damage = item._damage;
}

void Player::setarmour(Item& item)
{ 
	for (int i = 0; i < 6; i++)
	{
		if (playerInvetory[i]._itemtype == "armour")
		{
			playerInvetory[i].equipped = false;
		}
	}
	item.equipped = true;
	_chest = item._itemname;
	armour = item._damage; 
}

void Player::consume(Item item,int equip)
{
	Item _item;
	if (playerInvetory[equip].counter == 1)
	{
		health = 10;
		playerInvetory[equip] = _item;
	}
	else
	{
		playerInvetory[equip].counter--;
		health = 10;
	}
}