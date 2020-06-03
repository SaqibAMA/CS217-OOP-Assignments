#include "Bank.h"

/*

Revisions before addition:

Get all the properties from a file
and encode them into the List array.

OR

Use the monopoly class to pass in the
array through parameterized constructor.


*/


//DEFUALT CONSTRUCTOR
Bank::Bank() {
	List = nullptr;
	size = 0;
}

//PARAMATRIZED CONSTRUCTOR
Bank::Bank(Property** List, int size) {
	this->size = size;
	this->List = new Property * [size];
	for (int i = 0; i < size; i++) {
		List[i] = new Property();
	}
	for (int i = 0; i < size; i++) {
		this->List[i] = List[i];
	}
}

//COPY CONSTRUCTOR
Bank::Bank(Bank& obj) {
	this->size = obj.size;
	this->List = new Property * [obj.size];
	for (int i = 0; i < obj.size; i++) {
		List[i] = new Property();
	}
	for (int i = 0; i < size; i++) {
		this->List[i] = List[i];
	}
}


//PROPERTY LIST SETTER
void Bank::setPropertyList(Property** List) {
	if (this->List != nullptr) {
		delete[] this->List;
		this->List = nullptr;
	}

	
	this->size = size;
	
	
	this->List = new Property * [size];
	for (int i = 0; i < size; i++) {
		List[i] = new Property();
	}
	for (int i = 0; i < size; i++) {
		this->List[i] = List[i];
	}
}

//PROPERTY LIST GETTER
Property** Bank::getPropertyList() {
	return this->List;
}

//SELL PROPERTY FUNCTION
void Bank::sellPropertyToPlayerByID(int Propertyid, Player player) {
	player.addProperty(Propertyid);
	player.deductCash(List[Propertyid][0].getPurchasePrice());
	List[Propertyid][0].setOwnerID(player.getPlayerID());
}

//BUY PROPERTY FUNCTION
void Bank::purchasePropertyFromPlayerByID(int Propertyid, Player player) {
	player.removeProperty(Propertyid);
	player.addCash(List[Propertyid][0].getPurchasePrice());
	List[Propertyid][0].setOwnerID(-1);
}

//MORTAGE FUNCTION
void Bank::payMortageToPlayerByID(int Propertyid, Player player) {
	int mortage = 0;
	mortage = int( List[Propertyid][0].getPurchasePrice() / 2.0 );
	player.addCash(mortage);
	List[Propertyid][0].setOwnerID(-1);
}


//CHECK BANKRUPT FUNCTION
void Bank::declarePlayerBankruptByID(Player player) {
	bool found = false;
	if (player.getCash() == 0) {
		for (int i = 0; i < size; i++) {
			if (List[i][0].getOwnerID() == player.getPlayerID()) {
				found = true;
			}
		}
		if (found == false) {
			player.setIsBankrupt(true);
		}
	}
}
