#pragma once
#include<iostream>
#include <string>
#include <chrono>
#include <random>
#include "Item.h"


class Player
{
public:
	Player();
	~Player();

	//getters
	int getPlayerCoord() 
	{
		return _playerX;
		return _playerY;
	}
	char getPlayerChar() { return playerchar; }
	int getPlayerHealth() { return health; }
	std::string getplayerWeapon() { return _weapon; }
	int getplayerDamage() { return _damage; }
	int getPlayerGold() { return _goldCoin; }
	int getPlayerSilver() { return _silverCoin; }
	int getPlayerCopper() { return _copperCoin; }
	void consume(Item item, int equip);
	void getMoney(int i, int gold, int silver, int copper);
	//setters
	void setPlayerHealth(int tempplayerhealth) { health = tempplayerhealth;	}

	int setPlayerCoord() 
	{
		_playerX = 1;
		_playerY = 1;
	}

	//set player money after battle
	void setPlayerStats(int gC, int sC, int cC);
	

	void setweapon(Item& item);
	void setarmour(Item& item);

	int health = 10;
	int _playerX;
	int _playerY;
	std::string playerName;
	Item playerInvetory[6];
	int _damage = 1;
	int armour = 0;
private:
	
	char playerchar = '@';

	Item weapon;
	std::string _arms = "arms";
	std::string _boots = "feet";
	std::string _pants = "legs";
	std::string _chest = "chest";
	std::string _helmet = "head";
	std::string _weapon = "Fists";
	
	int _goldCoin = 5;
	int _silverCoin = 6;
	int _copperCoin = 9;
};

