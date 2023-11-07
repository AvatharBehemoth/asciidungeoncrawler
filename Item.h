#pragma once
#include <string>

class Item
{
public:
	
	Item();
	~Item();

	//getters
	std::string getItemName() { return _itemname; }
	int getGold() {	return _goldCoinvalue; }
	int getSilver() { return _silverCoinvalue; }
	int getCopper() { return _copperCoinvalue; }

	//setters
	void setItemvariables(std::string itemname, std::string itemtype, int damage, int goldCoinvalue, 
		int silverCoinvalue, int copperCoinvalue)
	{
		_itemname = itemname;
		_itemtype = itemtype;
		_damage = damage;
		_goldCoinvalue = goldCoinvalue;
		_silverCoinvalue = silverCoinvalue;
		_copperCoinvalue = copperCoinvalue;
	}
	
	bool equipped = false;
	bool consumed = false;
	unsigned int counter;
	std::string _itemname;
	std::string _itemtype;
	int _damage;
private:

	int _goldCoinvalue;
	int _silverCoinvalue;
	int _copperCoinvalue;
};

