#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
#include <thread>
#include "Item.h"
class Monster
{
public:

	Monster();
	~Monster();

	void growl()
	{
		std::cout << "Begone mortal! " << std::endl;
		system("PAUSE");
	}

	//gettter
	char getmonsterChar() { return _monsterchar; }
	std::string getmonsterWeapon() { return _weapon; }
	int getmonsterdamage() { return _damage; }
	int getmonsterGold() { return _goldPCoin; }
	int getmonsterSilver() {return _silverCoin;	}
	int getmonsterCopper() { return _copperCoin; }

	unsigned getMonsterCoord();

	unsigned int getMonsterX() { return _monsterX; }
	unsigned int getMonsterY() { return _monsterY; }
	int getMonsterHealth() { return _health; }
	std::string getMonsterItem(int i) { return monsterInvetory[i]._itemname; }

	//setter
	void setMonstervariables(std::string name, std::string monsterName, std::string weapon,
		char monsterchar, int health, int damage, int goldPCoin, int silverCoin, int copperCoin)
	{
		_name = name;
		_monsterName = monsterName;
		_weapon = weapon;
		_monsterchar = monsterchar;
		_health = health;
		_damage = damage;
		_goldPCoin = goldPCoin;
		_silverCoin = silverCoin;
		_copperCoin = copperCoin;
	}
	void setMonsterHealth(int tempmonsterhealth) { _health = tempmonsterhealth;	}
	void setMonsterChar(char monsterchar) { _monsterchar = monsterchar; }
	void setMonsterCoord();
	void setMonsterX() { _monsterX = 16; }
	void setMonsterY() { _monsterY = 6; }
	void setweapon(Item& item) { item.equipped = true; _weapon = item._itemname; _damage = item._damage; }
	void setarmour(Item& item) { item.equipped = true; _chest = item._itemname; armour = item._damage; }

	int _health;
	unsigned _monsterX;
	unsigned _monsterY;
	Item monsterInvetory[6];
	std::string _name;
	int _damage;
	int armour = 0;
private:

	Item weapon;
	std::string _arms = "arms";
	std::string _boots = "feet";
	std::string _pants = "legs";
	std::string _chest = "chest";
	std::string _helmet = "head";


	std::string _monsterName;
	std::string _weapon;
	char _monsterchar;


	int _goldPCoin;
	int _silverCoin;
	int _copperCoin;
};

