#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <random>
#include <ctime>
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "windows.h"
#include "Levelmap.h"
#include "Villager.h"
#pragma warning(disable : 4996)

bool fightOver = false;
bool battleresolve(Player &player, Monster &monster, bool playerturn, bool fightOver, char level[10][30], char playlevel[10][30]);
bool battle(Player &player, Monster &monster, char level[10][30], char playlevel[10][30]);
unsigned spawnMonsterX();
unsigned spawnMonsterY();
void getPlayerName(Player &player);
unsigned spawnPlayerX();
unsigned spawnPlayerY();
void gameStart(Player &player);
void generateMonsters(int lnr, Monster monsters[10]);
void generateItems(int lnr, Item item, Monster monsters[10]);
void equipMonsters(int lnr, Monster monsters[10]);
void equipPlayer(Player& player);
void buysell(Player &player);
void ClearScreen();
void printLevel(Levelmap Level, char level[10][30], char playlevel[10][30],  Player& player, Monster monsters[10]);
void gameLoop();
int Victory();
Player initPlayer(Player &player);
Monster initMonster(Monster &monster, std::string monstername);
Item initItem(Item& item, std::string itemname);

void monsterMove()
{
	//int initiative;
	//int rand(initiative);

}

int main()
{
	gameLoop();
	std::cout << "Do you want to play again? (y/n)" << std::endl;
	char startagain;
	std::cin >> startagain;
	if (startagain == 'y')
	{
		gameLoop();
	}
	return 0;
}

unsigned spawnMonsterX()
{
	unsigned monsterX = rand() % 28 + 1;
	return monsterX;
}

unsigned spawnMonsterY()
{
	unsigned monsterY = rand() % 8 + 1;
	return monsterY;
}

unsigned spawnPlayerX()
{
	
	unsigned int playerX = rand() % 28 + 1;
	return playerX;
}

unsigned spawnPlayerY()
{

	unsigned int playerY = rand() % 8 + 1;
	return playerY;
}

unsigned spawnVillagerX()
{

	unsigned int villagerX = rand() % 28 + 1;
	return villagerX;
}

unsigned spawnVillagerY()
{

	unsigned int villagerY = rand() % 8 + 1;
	return villagerY;
}

void buysell(Player &player)
{
	Item item;
	ClearScreen();
	int equip = -10;
	while (equip != 0)
	{
		//setup sell screen
		std::cout << "inventory slots " << std::endl;

		for (int i = 0; i < 6; i++)
		{
			std::cout << i + 1 << "           ";
		}
		std::cout << std::endl;

		std::cout << "item names" << std::endl;
		for (int i = 0; i < 6; i++)
		{
			if (player.playerInvetory[i].counter < 1 || player.playerInvetory[i].counter > 6)
			{
				player.playerInvetory[i].counter = 0;
				player.playerInvetory[i]._itemname = "           ";
				std::cout << player.playerInvetory[i]._itemname << "   ";
			}
			if (!player.playerInvetory[i]._itemname.empty())
			{
				std::cout << player.playerInvetory[i]._itemname << "   ";
			}
			else
			{
				player.playerInvetory[i]._itemname = "   ";
				std::cout << player.playerInvetory[i]._itemname << "   ";
			}
		}
		std::cout << std::endl;

		std::cout << "item values" << std::endl;
		for (int i = 0; i < 6; i++)
		{
			int result1 = player.playerInvetory[i].getGold();
			int result2 = player.playerInvetory[i].getSilver();
			int result3 = player.playerInvetory[i].getCopper();
			if (result1 < 0)
			{
				result1 = 0;
			}
			if (result2 < 0)
			{
				result2 = 0;
			}
			if (result3 < 0)
			{
				result3 = 0;
			}

			std::cout << result1 << "G " << result2	<< "S " << result3 << "C ";
		}
		std::cout << std::endl;
		std::cout << "damage (for weapons positive value, armour has negative value)" << std::endl;

		for (int i = 0; i < 6; i++)
		{
			//disable trash values
			if (player.playerInvetory[i]._damage <= -100)
			{
				player.playerInvetory[i]._damage = 0;
			}
			std::cout << player.playerInvetory[i]._damage << "           ";
		}
		std::cout << std::endl;

		for (int i = 0; i < 6; i++)
		{
			std::cout << "x " << player.playerInvetory[i].counter << "          ";
		}
		std::cout << std::endl;
		std::cout << "Which item do you want to sell (1/6)? 0 to escape" << std::endl;
		std::cin >> equip;
		if (equip == 0)
		{
			break;
		}
		equip -= 1;
		if (equip == 0)
		{
			std::cout << "Cant sell your fists" << std::endl;
		}
		if ((equip > 0) && (equip < 7))
		{
			if (player.playerInvetory[equip]._itemname == "")
			{
				std::cout << "Empty slot";
				ClearScreen();
			}
			if (player.playerInvetory[equip].counter == 1)
			{
				player.getMoney(equip, player.playerInvetory[equip].getGold(),
					player.playerInvetory[equip].getSilver(), player.playerInvetory[equip].getCopper());
				player.playerInvetory[equip].counter--;
				player.playerInvetory[equip] = item;
				ClearScreen();
			}
			else
			{
				player.getMoney(equip, player.playerInvetory[equip].getGold(),
					player.playerInvetory[equip].getSilver(), player.playerInvetory[equip].getCopper());
				player.playerInvetory[equip].counter--;
				ClearScreen();
			}
		}
	}
	ClearScreen();
}


void equipPlayer(Player &player)
{
	int equip = -10;
	while (equip != 0)
	{
		//setup equip screen
		std::cout << "inventory slots " << std::endl;

		for (int i = 0; i < 6; i++)
		{
			std::cout << i + 1 << "           ";
		}
		std::cout << std::endl;
		std::cout << "item names" << std::endl;

		for (int i = 0; i < 6; i++)
		{
			std::cout << player.playerInvetory[i]._itemname << "   ";
		}
		std::cout << std::endl;
		std::cout << "damage (for weapons positive value, armour has negative value)" << std::endl;

		for (int i = 0; i < 6; i++)
		{
			//disable trash values
			if (player.playerInvetory[i]._damage <= -100)
			{
				player.playerInvetory[i]._damage = 0;
			}
			std::cout << player.playerInvetory[i]._damage << "           ";

		}
		std::cout << std::endl;

		for (int i = 0; i < 6; i++)
		{
			std::cout << "x " << player.playerInvetory[i].counter << "         ";
		}
		std::cout << std::endl;
		std::cout << "Which item do you want to equip (1/6)? 0 to escape" << std::endl;
		std::cin >> equip;

		if (player.playerInvetory[equip - 1]._itemtype == "weapon")
		{
			player.setweapon(player.playerInvetory[equip - 1]);
			ClearScreen();
		}
		if (player.playerInvetory[equip - 1]._itemtype == "armour")
		{
			player.setarmour(player.playerInvetory[equip - 1]);
			ClearScreen();
		}
		if (player.playerInvetory[equip - 1]._itemtype == "consumable")
		{
			player.consume(player.playerInvetory[equip - 1], equip - 1);
			ClearScreen();
		}
		if (equip == 9)
		{
			ClearScreen();
			buysell(player);
			ClearScreen();
		}
	}
	//set equip to arbitrary value for reuse
	equip = 100;
}

void getPlayerName(Player &player)
{ // get name of the player
	std::string playerName;
	std::cout << "What is thy name, sir? \n";
	std::cin >> playerName;
	player.playerName = playerName;
}

Player initPlayer(Player &player)
{
	Item fists;
	fists.counter = 0;
	fists.setItemvariables("fists", "defaultweapon", 1, 0, 0, 0);
	for (int i = 0; i < 6; i++)
	{
		player.playerInvetory[i].counter = 0;
	}
	player.playerInvetory[0] = fists;
	player.playerInvetory[0].counter++;
	player.playerInvetory[0].equipped = true;
	player._playerX = spawnPlayerX();
	player._playerY = spawnPlayerY();
	return player;
}

Item initItem(Item &item, std:: string itemname)
{
	if (itemname == "rustsword")
	{
		item.setItemvariables("rustsword", "weapon", 3, 0, 3, 5);
		item.counter = 0;
		return item;
	}
	if (itemname == "rustycuras")
	{
		item.setItemvariables("rustycuras", "armour", -2, 0, 7, 1);
		item.counter = 0;
		return item;
	}
	if (itemname == "sword")
	{
		item.setItemvariables("sword", "weapon", 4, 0, 4, 7);
		item.counter = 0;
		return item;
	}
	if (itemname == "curas")
	{
		item.setItemvariables("curas", "armour", -3, 0, 9, 9);
		item.counter = 0;
		return item;
	}
	if (itemname == "steel sword")
	{
		item.setItemvariables("steel sword", "weapon", 5, 0, 8, 0);
		item.counter = 0;
		return item;
	}
	if (itemname == "steel curas")
	{
		item.setItemvariables("steel curas", "armour", -4, 1, 2, 4);
		item.counter = 0;
		return item;
	}
	if (itemname == "healtpotion")
	{
		item.setItemvariables("healtpotion", "consumable", 0, 0, 8, 0);
		item.counter = 0;
		return item;
	}
}

void generateItems(int lnr, Item item, Monster monsters[10])
{
	Item rustsword;
	Item rustycuras;
	Item sword;
	Item curas;
	Item steelsword;
	Item steelcuras;
	Item healthpotion;
	if ((lnr > 1) && (lnr < 5))
	{
		for (int i = 0; i < 10; i++)
		{
			if (monsters[i]._name == "")
			{
				break;
			}
			else
			{
				monsters[i].monsterInvetory[0] = initItem(rustsword, "rustsword");
				monsters[i].monsterInvetory[1] = initItem(rustycuras, "rustycuras");
			}
		}
	}

	if (lnr == 1)
	{
		monsters[0].monsterInvetory[0] = initItem(rustsword, "rustsword");
		monsters[0].monsterInvetory[1] = initItem(rustycuras, "rustycuras");
		monsters[0].monsterInvetory[2] = initItem(healthpotion, "healtpotion");
	}

	if (lnr == 5)
	{
		for (int i = 0; i < 10; i++)
		{
			if (monsters[i]._name == "")
			{
				break;
			}
			else if (monsters[i]._name == "skeletonguard")
			{
				monsters[i].monsterInvetory[0] = initItem(sword, "sword");
				monsters[i].monsterInvetory[1] = initItem(curas, "curas");
			}
			else if (monsters[i]._name == "skeletonking")
			{
				monsters[i].monsterInvetory[0] = initItem(sword, "steelsword");
				monsters[i].monsterInvetory[1] = initItem(curas, "steelcuras");
			}
		}
	}
}

void equipMonsters(int lnr, Monster monsters[10])
{
	for (int i = 0; i < 10; i++)
	{
		if (monsters[i]._name == "")
		{
			break;
		}
		for (int j = 0; j < 6; j++)
		{
			monsters[i].monsterInvetory[j].counter = 0;
			if (monsters[i].monsterInvetory[j]._itemname != "")
			{
				monsters[i].monsterInvetory[j].counter++;
			}
			if (monsters[i].monsterInvetory[j]._itemtype == "weapon")
			{
				monsters[i].setweapon(monsters[i].monsterInvetory[j]);
			}
			if ((monsters[i].monsterInvetory[j]._itemtype == "armour") && (lnr != 1))
			{
				monsters[i].setarmour(monsters[i].monsterInvetory[j]);
			}
			if (monsters[i].monsterInvetory[j]._itemtype == "consumable")
			{
				monsters[i].setarmour(monsters[i].monsterInvetory[j]);
			}
		}
	}
}

Monster initMonster(Monster& monster, std::string monstername)
{
	if (monstername == "skeleton")
	{
		monster.setMonstervariables("skeleton", "skeleton", "rustsword", '&', 1, 1, 0, 5, 3);
		monster._monsterX = spawnMonsterX();
		monster._monsterY = spawnMonsterY();
		return monster;
	}

	if (monstername == "skeletonguard")
	{
		monster.setMonstervariables("skeleton guard", "skeleton guard", "sword",
			'$', 3, 4, 1, 0, 5);
		monster._monsterX = spawnMonsterX();
		monster._monsterY = spawnMonsterY();
		return monster;
	}

	if (monstername == "skeletonking")
	{
		monster.setMonstervariables("skeletonking", "skeleton king", "steelsword",
			'*', 4, 5, 10, 9, 9);
		monster._monsterX = spawnMonsterX();
		monster._monsterY = spawnMonsterY();
		return monster;
	}
}

void generateMonsters(int lnr, Monster monsters[10])
{
	if ((lnr > 1) && (lnr < 5))
	{
		Monster skeleton;
		int min = 0;
		int max = 10;
		int result = min + (rand() * static_cast <int>(max - min + 1) % 10);
		for (int i = 0; i < result; i++)
		{
			monsters[i] = initMonster(skeleton, "skeleton");
		}

	}

	if (lnr == 1)
	{
		Monster skeleton;
		monsters[0] = initMonster(skeleton, "skeleton");
	}

	if (lnr == 5)
	{
		Monster skeletonguard;
		for (int i = 0; i < 9; i++)
		{
			monsters[i] = skeletonguard;
			monsters[i] = initMonster(skeletonguard, "skeletonguard");
			skeletonguard._monsterY = spawnMonsterY();
			skeletonguard._monsterX = spawnMonsterX();
		}
		Monster skeletonking;
		monsters[10] = initMonster(skeletonking, "skeletonking");
	}
}

void gameStart(Player &player)
{
	getPlayerName(player);
}

bool battleresolve(Player& player, Monster& monster, bool playerturn, bool fightOver, char level[10][30], char playlevel[10][30])
{
	Item item;
	while (!fightOver)
	{
		if (playerturn == false)
		{
			if (monster.getmonsterdamage() + player.armour <= 0)
			{
				std::cout << "Monster hits with his " << monster.getmonsterWeapon() << " and does "
					 << "0 damage" << std::endl;
			}
			else
			{
				std::cout << "Monster hits with his " << monster.getmonsterWeapon() << " and does "
					<< (monster.getmonsterdamage() + player.armour) << " damage" << std::endl;
				player.health -= (monster.getmonsterdamage() + player.armour);
			}
			playerturn = true;
			system("PAUSE");
		}
		else
		{
			if (player.getplayerDamage() + monster.armour <= 0)
			{
				std::cout << "You hit with your " << player.getplayerWeapon() << " and do "
					<<  "0 damage" << std::endl;
			}
			else
			{
				std::cout << "You hit with your " << player.getplayerWeapon() << " and do "
					<< (player.getplayerDamage() + monster.armour) << " damage" << std::endl;
				monster._health -= (player.getplayerDamage() + monster.armour);
			}
			playerturn = false;
			system("PAUSE");
		}

		if (monster._health <= 0)
		{
			player.setPlayerStats(monster.getmonsterGold(), monster.getmonsterSilver(), monster.getmonsterCopper());
			std::cout << "The monster is dead ";
			std::cout << "you have found " << monster.getmonsterGold() << " goldcoin, " << monster.getmonsterSilver() << " silvercoin "
				<< "and " << monster.getmonsterCopper() << " copper" << std::endl;
			//loop through dead monster inventory
			for (int monsterinv = 0; monsterinv < 6; monsterinv++)
			{
				if (monster.monsterInvetory[monsterinv]._itemname == "")
				{
					break;
				}
				std::cout << "you have found: " << monster.getMonsterItem(monsterinv) << std::endl;
				std::cout << "Do you want to take: " << monster.getMonsterItem(monsterinv) << " (y/n) " << std::endl;
				char itemtake;
				std::cin >> itemtake;
				if (itemtake == 'y')
				{
					//loop through player inventory
					for (int i = 0; i < 6; i++)
					{
						if ((player.playerInvetory[i]._itemname == "") ||
							(player.playerInvetory[i]._itemname == monster.monsterInvetory[monsterinv]._itemname))
						{
							if (player.playerInvetory[i].counter < 5)
							{
								monster.monsterInvetory[monsterinv].equipped = false;
								monster.monsterInvetory[monsterinv].counter--;
								int tempcounter = player.playerInvetory[i].counter;
								player.playerInvetory[i] = monster.monsterInvetory[monsterinv];
								player.playerInvetory[i].counter = tempcounter;
								player.playerInvetory[i].counter++;
								break;
							}
							else
							{
								for (int j = i + 1; j < 6; j++)
								{
									if ((player.playerInvetory[j]._itemname == "") ||
										((player.playerInvetory[j]._itemname == monster.monsterInvetory[monsterinv]._itemname)
											&& (player.playerInvetory[j].counter < 5)))
									{
										monster.monsterInvetory[monsterinv].equipped = false;
										monster.monsterInvetory[monsterinv].counter--;
										int tempcounter = player.playerInvetory[j].counter;
										player.playerInvetory[j] = monster.monsterInvetory[monsterinv];
										player.playerInvetory[j].counter = tempcounter;
										player.playerInvetory[j].counter++;
										monsterinv++;										
									}
								}
								std::cout << " Your inventory is full!";
								break;
							}
						}
						if (i == 5)
						{
							std::cout << " Your inventory is full!";
							monsterinv++;
						}
					}
				}
				else
				{
					monsterinv++;
				}
			}
			playlevel[monster._monsterY][monster._monsterX] = level[monster._monsterY][monster._monsterX];
			return true;
			//check to debug playerinventory
			//std::cout << player.playerInvetory[i]._itemname;
		}
		if (player.health <= 0)
		{
			system("PAUSE");
			return true;
		}
	}	
}


bool battle(Player &player, Monster &monster, char level[10][30], char playlevel[10][30])
{
	std::cout << "Battle!" << std::endl;
	system("PAUSE");

	int min = 0;
	int max = 10;
	int result = min + (rand() * static_cast <int>(max - min + 1) % 10);
	bool playerturn = false;
	if (result < 7)
	{
		bool playerturn = false;
	}
	else
	{
		playerturn = true;
	}
	fightOver = false;

	while (!fightOver)
	{
		std::cout << "Your healt is: " << player.health << " and the monster's health is: " << monster._health << std::endl;
		fightOver = battleresolve(player, monster, playerturn, fightOver, level, playlevel);
		if (!fightOver)
		{
			if (playerturn == false)
			{
				playerturn = true;
			}
			else
			{
				playerturn = false;
			}
		}
	}
	return fightOver;
}

// from https://cplusplus.com/articles/4z18T05o/#Windows clear screen in C++ on a windows machine
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void printLevel(Levelmap Level, char level[10][30], char playlevel[10][30], Player& player, Monster monsters[10])
{
	for (int i = 0; i < 10; i++)
	{
		if (monsters[i]._name == "")
		{
			break;
		}
		else
		{
			playlevel[monsters[i]._monsterY][monsters[i]._monsterX] = monsters[i].getmonsterChar();
		}
	}

	playlevel[player._playerY][player._playerX] = player.getPlayerChar();
	bool fightOver = false;
	Level.PortalY = Level.getPortalY();
	Level.PortalX = Level.getPortalX();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			std::cout << playlevel[i][j];
		}
		std::cout << std::endl;
	}
}

void gameLoop()
{
	//start gameloop
	std::srand((int)std::time(nullptr));
	Levelmap Level;
	Player player;
	Monster monster;
	Monster skeleton;
	Item item;
	Item rustsword;
	Item rustyuras;
	Item sword;
	Item curas;
	Item steelsword;
	Item steelcuras;
	Monster monsters[10];
	Villager villager;

	char level[10][30];
	char playlevel[10][30];
	gameStart(player);

	player = initPlayer(player);
	Level.lnr = 1;
	Level.getLevel(10, 30, Level);
	int PortalY = Level.getPortalY();
	int PortalX = Level.getPortalX();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			level[i][j] = Level.z[i][j];
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			playlevel[i][j] = level[i][j];
		}
	}
	
	generateMonsters(Level.lnr, monsters);
	generateItems(Level.lnr, item, monsters);
	equipMonsters(Level.lnr, monsters);

	if ((Level.lnr == 1) && (villager.haddialogue == false))
	{
		villager.villagerX = spawnVillagerX();
		villager.villagerY = spawnVillagerY();
		playlevel[villager.villagerY][villager.villagerX] = villager.villagerchar;
	}

	char input;
	while (!(player.health <= 0))
	{
		ClearScreen();
		printLevel(Level, level, playlevel, player, monsters);

		//to debug monster distance to player
		for (int i = 0; i < 10; i++)
		{
			if (monsters[i]._name == "")
			{
				break;
			}
			else
			{			
				//debug for monster to player distance	
				//std::cout << "X to monster: " << abs(int(player._playerX - monsters[i].getMonsterX())) <<
					//" Y to monster: " << abs(int(player._playerY - monsters[i].getMonsterY())) << std::endl;
			}
		}
		std::cout << "w, a, s, d to move e to equip/use inventory or buy/sell" << std::endl;
		//show player stats
		std::cout << "Health = " << player.getPlayerHealth() << " Weapon = " << player.getplayerWeapon() << " Gold = " <<
			player.getPlayerGold() << " Silver = " << player.getPlayerSilver() << " Copper = " << player.getPlayerCopper() << std::endl;

		input = _getch();
		char tempChar;
		if ((Level.lnr == 1) && (villager.haddialogue == false))
		{
			if ((abs(int(player._playerY - villager.villagerY)) <= 3) && (abs(int(player._playerX - villager.villagerX)) <= 3))
			{
				villager.comeOver();
			}
			if ((abs(int(player._playerX - villager.villagerX)) <= 1) && (abs(int(player._playerY - villager.villagerY)) <= 1))
			{
				villager.dialogue();
				villager.haddialogue = true;
			}
		}

		for (int i = 0; i < 10; i++)
		{ 
			//check for battle or monster growl
			if (monsters[i]._name == "")
			{
				break;
			}
			else
			{
				if ((abs(int(player._playerY - monsters[i]._monsterY)) <= 3) && (abs(int(player._playerX - monsters[i]._monsterX)) <= 3))
				{
					monster.growl();

					if ((abs(int(player._playerX - monsters[i]._monsterX)) <= 1) && (abs(int(player._playerY - monsters[i]._monsterY)) <= 1))
					{
						fightOver = battle(player, monsters[i], level, playlevel);
						if (fightOver == true)
						{
							//set monster coordinates far outside of map
							monsters[i].setMonsterCoord();
							if (monsters[i]._name == "skeltonking")
							{
								ClearScreen();
								std::cout << "You have won the game!" << std::endl;
								Victory();
							}
							fightOver = false;
						}
					}
				}
			}
		}

		int PortalY = Level.getPortalY();
		int PortalX = Level.getPortalX();

		//transition levels
		if ((abs(int(player._playerX - PortalX)) <= 1) && (abs(int(player._playerY - PortalY)) <= 1))
		{
			std::cout << "Do you want to go to a different level?(y/n) " << std::endl;
			input = _getch();
			switch (input)
			{
			case 'y':
				if ((Level.lnr > 1) && (Level.lnr < 5))
				{
					char goDownLevel;
					std::cout << "Do you want to go down? (y/n) " << std::endl;
					std::cin >> goDownLevel;
					if (goDownLevel == 'y')
					{
						Level.lnr++;
						Level.getLevel(10, 30, Level);
						generateMonsters(Level.lnr, monsters);
						generateItems(Level.lnr, item, monsters);
						equipMonsters(Level.lnr, monsters);
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 30; j++)
							{
								level[i][j] = Level.z[i][j];
								playlevel[i][j] = level[i][j];
							}
						}
						if (playlevel[player._playerY][player._playerX] == '#')
						{
							int templayerx = player._playerX;							
							while (playlevel[player._playerY][templayerx] = '#')
							{
								if (templayerx <= 29)
								{
									templayerx += 1;
								}
								else
								{
									templayerx -= 1;
								}
							}
							templayerx = player._playerX;
						}
						break;
					}
					else if (goDownLevel == 'n')
					{
						char goUpLevel;
						std::cout << " Do you want to go up? " << std::endl;
						std::cin >> goUpLevel;
						if (goUpLevel == 'y')
						{
							Level.lnr--;
							generateMonsters(Level.lnr, monsters);
							generateItems(Level.lnr, item, monsters);
							equipMonsters(Level.lnr, monsters);
							Level.getLevel(10, 30, Level);
							for (int i = 0; i < 10; i++)
							{
								for (int j = 0; j < 30; j++)
								{
									level[i][j] = Level.z[i][j];
									playlevel[i][j] = level[i][j];
								}
							}
							break;
						}
					}
				}
				else if (Level.lnr == 1)
				{
					char goDownLevel;
					std::cout << "Do you want to go down? (y/n) " << std::endl;
					std::cin >> goDownLevel;
					if (goDownLevel == 'y')
					{
						Level.lnr++;
						Level.getLevel(10, 30, Level);
						generateMonsters(Level.lnr, monsters);
						generateItems(Level.lnr, item, monsters);
						equipMonsters(Level.lnr, monsters);

						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 30; j++)
							{
								level[i][j] = Level.z[i][j];
								playlevel[i][j] = level[i][j];
							}
						}
						break;
					}
				}
				else
				{
					break;
				}
				if (Level.lnr == 5)
				{
					char goDownLevel;
					std::cout << "Do you want to go up? (y/n) " << std::endl;
					std::cin >> goDownLevel;
					if (goDownLevel == 'y')
					{
						Level.lnr--;
						Level.getLevel(10, 30, Level);
						generateMonsters(Level.lnr, monsters);
						generateItems(Level.lnr, item, monsters);
						equipMonsters(Level.lnr, monsters);
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 30; j++)
							{
								level[i][j] = Level.z[i][j];
								playlevel[i][j] = level[i][j];
							}
						}
						break;
					}
				}
			}
		}

		if (player.health <= 0)
		{
			ClearScreen();
			std::cout << "You have died! " << std::endl;
			system("PAUSE");
			return;
		}

		int equip = -19;
		switch (input)
		{
		case 'e':
			ClearScreen();
			//choose equipment player

			while (equip != 0)
			{
				std::cout << "Press 9 to buy or sell items (only if you have the brochure), 8 to equip items" << std::endl
					<< "or  0 to exit " << std::endl;
				std::cin >> equip;
				if (equip == 9)
				{
					if (villager.brochure)
					{
						ClearScreen();
						buysell(player);
						ClearScreen();
					}
					else
					{
						std::cout << "Sorry you have to get the brochure first, try talking to the villager!"
							<< std::endl;
					}
				}

				if (equip == 8)
				{
					ClearScreen();
					equipPlayer(player);
					ClearScreen();
				}

			}
			ClearScreen();
			printLevel(Level, level, playlevel, player, monsters);
			//set int equip to arbitrary value for reuse
			equip = 100; 
			break;
		case 'w':
			if ((playlevel[player._playerY - 1][player._playerX] == '#') ||
				(playlevel[player._playerY - 1][player._playerX] == monster.getmonsterChar())
				|| (playlevel[player._playerY - 1][player._playerX] == 'P'))
			{
				player._playerY = player._playerY;
			}
			else
			{
				player._playerY--;
				tempChar = level[player._playerY][player._playerX];
				playlevel[player._playerY][player._playerX] = player.getPlayerChar();
				playlevel[player._playerY + 1][player._playerX] = tempChar;
			}

			break;
		case 's':
			if ((playlevel[player._playerY + 1][player._playerX] == '#') ||
				(playlevel[player._playerY + 1][player._playerX] == monster.getmonsterChar())
				|| (playlevel[player._playerY + 1][player._playerX] == 'P'))
			{
				player._playerY = player._playerY;
			}
			else
			{
				player._playerY++;
				tempChar = level[player._playerY][player._playerX];
				playlevel[player._playerY][player._playerX] = player.getPlayerChar();
				playlevel[player._playerY - 1][player._playerX] = tempChar;
			}
			break;
		case 'd':
			if ((playlevel[player._playerY][player._playerX + 1] == '#') ||
				(playlevel[player._playerY][player._playerX + 1] == monster.getmonsterChar())
				|| (playlevel[player._playerY][player._playerX + 1] == 'P'))
			{
				player._playerX = player._playerX;
			}
			else
			{
				player._playerX++;
				tempChar = level[player._playerY][player._playerX];
				playlevel[player._playerY][player._playerX] = player.getPlayerChar();
				playlevel[player._playerY][player._playerX - 1] = tempChar;
			}
			break;
		case 'a':
			if ((playlevel[player._playerY][player._playerX - 1] == '#') ||
				(playlevel[player._playerY][player._playerX - 1] == monster.getmonsterChar())
				|| (playlevel[player._playerY][player._playerX - 1] == 'P'))
			{
				player._playerX = player._playerX;
			}
			else
			{
				player._playerX--;
				tempChar = level[player._playerY][player._playerX];
				playlevel[player._playerY][player._playerX] = player.getPlayerChar();
				playlevel[player._playerY][player._playerX + 1] = tempChar;
			}
			break;
		}
	}
}

int Victory()
{
	ClearScreen();
	std::cout << "You have won the game! " << std::endl;
	system("PAUSE");
	return 0;
}