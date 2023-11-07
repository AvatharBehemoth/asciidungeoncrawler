#pragma once

class Levelmap
{
	

public:
	Levelmap();
	Levelmap(int i, int j) { y = i; x = j; }

	int lnr;
	int x = 30;
	int y = 10;
	char z[10][30] = {'0'};
	char portal = 'P';
	void getLevel(int i, int j, Levelmap &Level);
	int getPortalY();
	int getPortalX();
	int PortalY;
	int PortalX;
private:

};
