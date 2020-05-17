#include "Space.h"
#include <cstring>
using namespace std;
class Property :public Space
{
	//DATA MEMBERS
	char* propertyName;
	char* propertyGroup;
	int propertyID;
	int ownerID;
	bool mortgaged;

	int purchasePrice;
	int rentPrice;
	int mortgagePrice;

public:
	//CONSTRUCTORS
	Property();
	Property(char* , int*, int,char*, char*, int, int, bool,
		int, int, int);
	Property(Property&);
	//SETTERS
	void setPropertyName(char*);
	void setPropertyGroup(char*);
	void setPropertyID(int);
	void setOwnerID(int);
	void setMortgaged(bool);
    //GETTERS
	char* getPropertyName();
	char* getPropertyGroup();
	int getPropertyID();
	int getOwnerID();
	bool getMortgaged();

	int getPurchasePrice();
	int getRentPrice();
	int getMortgagePrice();

	//DESTRUCTOR
	~Property();
};
