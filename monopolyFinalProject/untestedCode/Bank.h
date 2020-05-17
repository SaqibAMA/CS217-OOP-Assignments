#include <iostream>
#include <cstring>
using namespace std;

class Bank {
private:
	Property** List;
	int size = 0;
public:
	Bank();
	Bank(Property**,int);
	Bank(Bank&);
	void setPropertyList(Property**);
	Property** getPropertyList();
	void sellPropertyToPlayerByID(int, Player);
	void purchasePropertyFromPlayerByID(int, Player);
	void payMortageToPlayerByID(int, Player);
	void declarePlayerBankruptByID(Player player);
};