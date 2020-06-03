#pragma once
#include <cstring>
#include "Property.h"
using namespace std;
class PrivateProperty :public Property
{
	//DATA MEMBERS
	int houseCount;
	int hotelCount;
	int shopCount;
	bool hasWifi;
	bool hasGas;
	bool hasElectricity;
public:
	//CONSTRUCTORS
	PrivateProperty();
	PrivateProperty(char*, int*, int, char*, char*, int, int, bool, int, int, int,int, int, int, bool, bool, bool);
	PrivateProperty(PrivateProperty&);
	//SETTERS
	void setHouseCount(int);
	void setHotelCount(int);
	void setShopCount(int);
	void setHasWifi(bool);
	void setHasGas(bool);
	void setHasElectricity(bool);
	//GETTERS
	int getHouseCount();
	int getHotelCount();
	int getShopCount();
	bool getHasWifi();
	bool getHasGas();
	bool getHasElectricity();
	//SPECIAL FUNCTIONS
	void addHouse();
	void addHotel();
	void addShop();
	void addWifi();
	void addGas();
	void addElectricity();
	int calculateRent();
	//DESTRUCTOR
	~PrivateProperty();
};


