
#include <iostream>

using namespace std;

class Player
{
private:
	char* name;
	int playerid;
	int cash;
	int* propertylist;
	int  propertylistsize;
	bool isInJail;
	bool hasJailRescueCard;
	bool isbankrupt;
public:
	Player();
	Player(const char* Name, int Playerid);
	Player(const Player& P);
	char* getName();
	int getPlayerID();
	int getCash();
	int* getPropertyList();
	int getPropertyListSize();
	bool getIsInJail();
	bool getHasJailRescueCard();
	bool getIsBankrupt();
	void setName(char* Name);
	void setPlayerID(int id);
	void setCash(int amount);
	void setPropertyList(int* list);
	void setPropertyListSize(int size);
	void setIsInJail(bool);
	void setHasJailRescueCard(bool);
	void setIsBankrupt(bool);
	void addProperty(int propertyid);
	void removeProperty(int propertyid);
	void addCash(int amount);
	void deductCash(int amount);
	
	Player& operator = (const Player& p)
	{
		int i = 0, f = 0, j = 0;
		for (int k = 0; p.name[k] != '\0'; k++)
		{
			f++;
		}
		name = new char[f + 1];
		for (j = 0; j < f; j++)
		{
			name[j] = p.name[j];

		}
		name[j] = '\0';
		playerid = p.playerid;
		cash = p.cash;
		propertylist = p.propertylist;
		propertylistsize = p.propertylistsize;
		isInJail = p.isInJail;
		hasJailRescueCard = p.hasJailRescueCard;
		isbankrupt = p.isbankrupt;
	}

};