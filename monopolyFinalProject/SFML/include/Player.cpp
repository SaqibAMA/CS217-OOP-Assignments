#include "Player.h"

Player::Player()
{
	name = nullptr;
	playerid = 0;
	cash = 0;
	propertylist = nullptr;
	propertylistsize = 0;
	isInJail = false;
	hasJailRescueCard = false;
	isbankrupt = false;

}
Player::Player(const char* Name, int Playerid)
{
	int i = 0, f = 0, j = 0;
	for (int k = 0; Name[k] != '\0'; k++)
	{
		f++;
	}
	name = new char[f + 1];
	for (j = 0; j < f; j++)
	{
		name[j] = Name[j];

	}
	name[j] = '\0';
	playerid = Playerid;
	cash = 5000;
	propertylist = nullptr;
	propertylistsize = 0;
	isInJail = false;
	hasJailRescueCard = false;
	isbankrupt = false;

}

Player::Player(const Player& p)
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

void Player::addCash(int amount)
{
	cash += amount;
}
void Player::deductCash(int amount)
{

	cash -= amount;

}
void Player::addProperty(int id)
{
	int i = 0;
	int* newpropertylist = new int[propertylistsize + 1];
	for (i = 0; i < propertylistsize; i++)
	{
		newpropertylist[i] = propertylist[i];

	}
	newpropertylist[i] = id;
	propertylistsize++;
	propertylist = newpropertylist;
}
void Player::removeProperty (int id)
{
	int i = 0, j;
	int* newpropertylist = new int[propertylistsize - 1];
	for (i = 0, j = 0; i < propertylistsize; i++)
	{
		if (propertylist[i] != id)
		{
			newpropertylist[j] = propertylist[i];
			j++;
		}
	}
	propertylistsize--;
	propertylist = newpropertylist;
}

int Player::getCash()
{
	return cash;
}

int Player::getPropertyListSize()
{
	return propertylistsize;
}

int Player::getPlayerID()
{
	return playerid;
}

char* Player::getName()
{
	return name;
}

bool Player::getIsBankrupt()
{
	return isbankrupt;
}

bool Player::getHasJailRescueCard()
{
	return hasJailRescueCard;
}


bool Player::getIsInJail()
{
	return isInJail;
}

void Player::setCash(int amount)
{
	cash = amount;
}
void Player::setPropertyListSize(int size)
{
	propertylistsize = size;
}

void Player::setPropertyList(int* amount)
{
	propertylist = amount;
}

void Player::setPlayerID(int id)
{
	playerid = id;
}

void Player::setName(char* Name)
{
	int i = 0, f = 0, j = 0;
	for (int k = 0; Name[k] != '\0'; k++)
	{
		f++;
	}
	name = new char[f + 1];
	for (j = 0; j < f; j++)
	{
		name[j] = Name[j];

	}
	name[j] = '\0';
}
void Player::setIsInJail(bool a)
{
	isInJail = a;
}
void Player::setIsBankrupt(bool a)
{
	isbankrupt = a;
}

void Player::setHasJailRescueCard(bool a)
{
	hasJailRescueCard = a;
}

int* Player::getPropertyList()
{
	return propertylist;
}