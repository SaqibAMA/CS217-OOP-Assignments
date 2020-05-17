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
public:
	//CONSTRUCTORS
	Property();
	Property(char* , int*, int,char*, char*, int, int, bool);
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
	//DESTRUCTOR
	~Property();
};

