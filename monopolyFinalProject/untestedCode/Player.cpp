#include <iostream>
#include "Header.h"
using namespace std;
class player
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
	player();
	player(const char* Name, int Playerid);
	player(const player& p);
	char* getname();
	int getplayerid();
	int getcash();
	int* getpropertylist();
	int getpropertylistsize();
	bool getIfisinjail();
	bool getIfHasJailRescueCard();
	bool getIfBankrupt();
	void setname(char* Name);
	void setplayerid(int id);
	void setcash(int amount);
	void setpropertylist(int* list);
	void setpropertylistsize(int size);
	void setIfisinjail(bool set);
	void setIfHasJailRescueCard(bool set);
	void setIfBankrupt(bool set);
	void addproperty(int propertyid);
	void removeproperty(int propertyid);
	void addcash(int amount);
	void deductcash(int amount);
	player& operator=(const player& p)
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
	friend ostream& operator<<(ostream& out, player& p);

};
ostream& operator<<(ostream& out, player& p)
{
	out << "Player name: " << p.getname() << endl;
	out << "Player id: " << p.getplayerid() << endl;
	out << "Cash: " << p.getcash() << endl;
	out << "Properties : ";
	for (int i = 0; i < p.getpropertylistsize(); i++)
	{
		out << p.getpropertylist()[i] << " ";
	}
	out << endl;
	out << "Currently in Jail: ";
	if (p.getIfisinjail() == 0)
		out << "NO" << endl;
	else
		out << "Yes" << endl;
	out << "Currently is Bankrupt: ";
	if (p.getIfBankrupt() == 0)
		out << "NO" << endl;
	else
		out << "Yes" << endl;
	out << "Currently Has a Jail Resccue Card: ";
	if (p.getIfHasJailRescueCard() == 0)
		out << "NO" << endl;
	else
		out<<"Yes" << endl;
	return out;

}
player::player()
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
player::player(const char* Name, int Playerid)
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
player::player(const player& p)
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
void player::addcash(int amount)
{
	cash = cash + amount;
}
void player::deductcash(int amount)
{
	if (cash >= amount)
	{
		cash = cash - amount;

	}
	else
	{
		isbankrupt = true;
	}

}
void player::addproperty(int id)
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
void player::removeproperty(int id)
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
int player::getcash()
{
	return cash;
}
int player::getpropertylistsize()
{
	return propertylistsize;
}
int player::getplayerid()
{
	return playerid;
}
char* player::getname()
{
	return name;
}
bool player::getIfBankrupt()
{
	return isbankrupt;
}
bool player::getIfHasJailRescueCard()
{
	return hasJailRescueCard;
}
bool player::getIfisinjail()
{
	return isInJail;
}
void player::setcash(int amount)
{
	cash = amount;
}
void player::setpropertylistsize(int size)
{
	propertylistsize = size;
}
void player::setpropertylist(int* amount)
{
	propertylist = amount;
}
void player::setplayerid(int id)
{
	playerid = id;
}
void player::setname(char* Name)
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
void player::setIfisinjail(bool a)
{
	isInJail = a;
}
void player::setIfBankrupt(bool a)
{
	isbankrupt = a;
}
void player::setIfHasJailRescueCard(bool a)
{
	hasJailRescueCard = a;
}
int* player::getpropertylist()
{
	return propertylist;
}
int main()
{
	player a("Salman",1);
	cout << a<<endl;
	a.addproperty(4);
	a.addproperty(5);
	a.addproperty(6);
	a.addproperty(1);
	cout << a<<endl;
	a.removeproperty(6);
	cout << a << endl;
}