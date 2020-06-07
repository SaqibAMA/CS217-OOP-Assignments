#include "Monopoly.h"

const char* diceTextureImg[6] =
{
	"assets/dice_1.png",
	"assets/dice_2.png",
	"assets/dice_3.png",
	"assets/dice_4.png",
	"assets/dice_5.png",
	"assets/dice_6.png"

};


Monopoly::Monopoly() {

	board.setPlayerCount(0);

	bCoord = new Point[40];

	ifstream fin;
	fin.open("files/bCoord.txt");

	for (int i = 0; !fin.eof(); i++) {

		int x, y;

		fin >> x;
		fin >> y;

		bCoord[i].set(x, y);

		fin.ignore();

	}

	playerPosition = nullptr;

	dealChoice = -1;


	fin.close();


}

// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	board.setPlayerCount(totalPlayers);
	board.allocatePrevTurns();
	board.allocatePlayers();

}

int Monopoly::getTotalPlayers() {

	return board.getPlayerCount();

}

Board Monopoly::getBoard() {
	return board;
}


// Member functions

void Monopoly::printPlayerOnCell(
	sf::RenderWindow& window, sf::RectangleShape shape, int cell,
	int deviation) {

	if ((cell >= 0 && cell <= 10) ||
		(cell >= 21 && cell <= 29)) {


		sf::Vector2f playerPos = window.mapPixelToCoords(
			sf::Vector2i(bCoord[cell].x + (deviation * 7), bCoord[cell].y)
		);

		shape.setPosition(playerPos);
	}
	else {

		sf::Vector2f playerPos = window.mapPixelToCoords(
			sf::Vector2i(bCoord[cell].x, bCoord[cell].y + (deviation * 7))
		);

		shape.setPosition(playerPos);

	}

	window.draw(shape);


}


void Monopoly::initializePositions() {


	playerPosition = new int[board.getPlayerCount()];

	for (int i = 0; i < board.getPlayerCount(); i++) {
		playerPosition[i] = 0;
	}


}

int Monopoly::getPlayerPosition(int playerID) {

	return playerPosition[playerID];

}

void Monopoly::movePlayer(int playerID, int currRollCount, sf::RenderWindow& window, int dealChoice = -1, bool toJail = false) {


	sf::Font cardFont;
	cardFont.loadFromFile("fonts/Nexa-Light.otf");

	sf::Font stdFont;
	stdFont.loadFromFile("fonts/Montserrat-Black.ttf");


	Player* player = board.getPlayerByID(playerID);

	int propertiesOwned = 0;

	for (int i = 0; i < 40; i++) {

		if (strcmp(board.getCells()[i]->getSpaceType(), "PRIVATE") == 0 || strcmp(board.getCells()[i]->getSpaceType(), "COMMERCIAL") == 0) {


			Property* property = (Property*)board.getCells()[i];

			if (property->getOwnerID() == player->getPlayerID()) {

				propertiesOwned++;

			}



		}

	}

	if (!player->getIsInJail()) {

		playerPosition[playerID] += currRollCount;
		playerPosition[playerID] %= 40;

		if (playerPosition[playerID] <= player->getPlayerPosition()) {

			player->addCash(500);

		}

		board.getPlayerByID(playerID)->setPlayerPosition(playerPosition[playerID]);
		
		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "PRIVATE") == 0) {
		

			PrivateProperty* property = (PrivateProperty*)board.getCells()[playerPosition[playerID]];


			sf::RenderWindow buyOrRentPrompt(sf::VideoMode(265, 166), "Buy or Rent", sf::Style::Titlebar);

			

			// Assets for the prompt

			//Buttons for Prompt

			sf::Texture buyButtonTexture;
			buyButtonTexture.loadFromFile("assets/property_prompt_rent.png");

			sf::RectangleShape buyButton(sf::Vector2f(128.0f, 74.0f));
			buyButton.setTexture(&buyButtonTexture);
			buyButton.setPosition(15.0f, 100.0f);

			sf::Texture rentButtonTexture;
			rentButtonTexture.loadFromFile("assets/property_prompt_rent.png");

			sf::RectangleShape rentButton(sf::Vector2f(128.0f, 74.0f));
			rentButton.setTexture(&rentButtonTexture);
			rentButton.setPosition(140.0f, 100.0f);

			// 0 index -> propertyName
			// 1 index -> propertyPrice
			// 2 index -> propertyRent
			// 3 index -> buy
			// 4 index -> sell

			int dealChoice = -1; // 0 for purchase, 1 for rent
			bool showPurchasePrompt = false;
			int onRent = -1;

			sf::Text* promptText = new sf::Text[5];


			for (int i = 0; i < 5; i++) {

				promptText[i].setFont(cardFont);
				promptText[i].setCharacterSize(14);
				promptText[i].setFillColor(sf::Color::Black);

			}

			promptText[0].setString(property->getPropertyName());
			promptText[0].setPosition(25.0f, 5.0f);

			promptText[1].setString(to_string(property->getPurchasePrice()));
			promptText[1].setPosition(25.0f, 45.0f);
			promptText[1].setFillColor(sf::Color(53, 73, 94));


			promptText[2].setString(to_string(property->getRentPrice()));
			promptText[2].setPosition(25.0f, 70.0f);
			promptText[2].setFillColor(sf::Color(53, 73, 94));


			promptText[3].setString("BUY");
			promptText[3].setFont(stdFont);
			promptText[3].setPosition(55.0f, 120.0f);
			promptText[3].setFillColor(sf::Color(236, 240, 241));

			promptText[4].setString("RENT");
			promptText[4].setFont(stdFont);
			promptText[4].setPosition(175.0f, 120.0f);
			promptText[4].setFillColor(sf::Color(236, 240, 241));




			while (buyOrRentPrompt.isOpen()) {
			
				sf::Event evt;

				while (buyOrRentPrompt.pollEvent(evt)) {
			

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					



						sf::Vector2f mousePos = buyOrRentPrompt.mapPixelToCoords(sf::Mouse::getPosition(buyOrRentPrompt));
						sf::FloatRect buyButtonBounds = buyButton.getGlobalBounds();
						sf::FloatRect rentButtonBounds = rentButton.getGlobalBounds();


						
						if (buyButtonBounds.contains(mousePos)) {
						

							dealChoice = 0;

							buyOrRentPrompt.close();


						}

						if (rentButtonBounds.contains(mousePos)) {
						

							dealChoice = 1;

							buyOrRentPrompt.close();


						}


					
					
					}

				
				
				}

				buyOrRentPrompt.clear(sf::Color::White);
				buyOrRentPrompt.draw(buyButton);
				buyOrRentPrompt.draw(rentButton);
				for (int i = 0; i < 5; i++)
					buyOrRentPrompt.draw(promptText[i]);

				buyOrRentPrompt.display();




			}



			if (player->getCash() >= property->getPurchasePrice() && dealChoice == 0) {
			

				if (property->getOwnerID() != -1)
					board.getPlayerByID(property->getOwnerID())->addCash(property->getPurchasePrice());

				property->setOwnerID(player->getPlayerID());
				player->deductCash(property->getPurchasePrice());


			}
			else if (player->getCash() >= property->getRentPrice() && dealChoice == 1) {
			
				if (property->getOwnerID() != -1)
					board.getPlayerByID(property->getOwnerID())->addCash(property->getRentPrice());

				player->setIsRenting(property->getPropertyID());
				player->deductCash(property->getRentPrice());

			}
			else if (propertiesOwned) {

				Property* barter = nullptr;

				for (int i = 0; i < 40 && !barter; i++) {
				
					
					if (strcmp(board.getCells()[i]->getSpaceType(), "PRIVATE") == 0
						|| strcmp(board.getCells()[i]->getSpaceType(), "COMMERCIAL") == 0) {
					
						Property* temp = (Property*)board.getCells()[i];
					
						if (temp->getPurchasePrice() >= property->getPurchasePrice()
							&& temp->getOwnerID() == player->getPlayerID()) {

							barter = (Property*)board.getCells()[i];

						}

					
					}


				}

				if (!barter) {

					player->setIsBankrupt(true);
					player->setCash(0);

				}
				else {

					player->addCash(barter->getPurchasePrice());
					barter->setOwnerID(-1);
					player->deductCash(property->getPurchasePrice());
					property->setOwnerID(player->getPlayerID());

				}


			}
			else if (propertiesOwned == 0) {
			
				player->setIsBankrupt(true);
				player->setCash(0);

			}



		}
		
		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "GO") == 0) {

			board.getPlayerByID(playerID)->addCash(500);

		}

		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "COMMUNITY") == 0) {


			int randCard = rand() % 15;

			CommunityCard* c = (CommunityCard*)board.getCommunityChest()[randCard];

			sf::RenderWindow card(sf::VideoMode(500, 170), "Community Chest Card", sf::Style::Titlebar);


			sf::Text cardTitle;
			cardTitle.setString("Community\nChest.");
			cardTitle.setCharacterSize(25);
			cardTitle.setFont(stdFont);
			cardTitle.setPosition(5.0f, 5.0f);
			cardTitle.setFillColor(sf::Color::White);


			char* _cardText = c->getCardAction();
			char* modCardText = nullptr;

			if (strlen(_cardText) >= 34) {

				modCardText = new char[strlen(_cardText) + 2];


				int spaceAt = 34;

				while (_cardText[spaceAt] != ' ' && _cardText[spaceAt] != '\0') spaceAt++;

				for (unsigned int i = 0; i < strlen(_cardText) + 2; i++)
					modCardText[i] = _cardText[i];

				modCardText[spaceAt] = '\n';

			}

			sf::Text cardText;
			cardText.setFont(cardFont);
			cardText.setString((modCardText) ? modCardText : _cardText);
			cardText.setPosition(5.0f, 100.0f);
			cardText.setCharacterSize(15);
			cardText.setFillColor(sf::Color::White);

			sf::Texture closeButtonTexture;
			closeButtonTexture.loadFromFile("assets/upgrade_prompt_close.png");
			sf::RectangleShape closeButton(sf::Vector2f(20.0f, 20.0f));
			closeButton.setTexture(&closeButtonTexture);
			closeButton.setPosition(470.0f, 10.0f);
			closeButtonTexture.setSmooth(true);


			while (card.isOpen()) {


				sf::Event evt;
				while (card.pollEvent(evt)) {


					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

						sf::Vector2f mousePos = card.mapPixelToCoords(sf::Mouse::getPosition(card));
						sf::FloatRect closeButtonBounds = closeButton.getGlobalBounds();

						if (closeButtonBounds.contains(mousePos)) {

							card.close();

						}


					}


				}

				card.clear(sf::Color(52, 152, 219));

				card.draw(cardTitle);
				card.draw(cardText);
				card.draw(closeButton);
				card.display();


			}



			// Functionality of All Cards

			if (randCard == 0) {


				playerPosition[playerID] = 0;
				player->setPlayerPosition(0);
				player->addCash(400);


			}
			else if (randCard == 1) {

				player->addCash(200);

			}
			else if (randCard == 2) {
			
				player->deductCash(200);

			}
			else if (randCard == 3) {
			
				player->addCash(50);

			}
			else if (randCard == 4) {
			
				player->setHasJailRescueCard(player->getHasJailRescueCard() + 1);

			}
			else if (randCard == 5) {

				player->addCash(150);

			}
			else if (randCard == 6) {

				player->addCash(200);
			
			}
			else if (randCard == 7) {
			
				player->deductCash(100);

			}
			else if (randCard == 8) {
			
				player->deductCash(200);

			}
			else if (randCard == 9) {

				player->addCash(50);

			}
			else if (randCard == 10) {

				Space** cells = board.getCells();

				int totalCharges = 0;
				
				for (int i = 0; i < 40; i++) {
				
					if (strcmp(cells[i]->getSpaceType(), "PRIVATE") == 0 ||
						strcmp(cells[i]->getSpaceType(), "COMMERCIAL") == 0) {
					
						Property* temp = (Property*)cells[i];


						if (temp->getOwnerID() == player->getPlayerID()) {
						
							totalCharges += ((temp->getHotelCount() * 125) +
								(temp->getHouseCount() * 50));

						}


					
					}

				}

				player->deductCash(totalCharges);


			}
			else if (randCard == 11) {
			
				player->addCash(300);

			}
			else if (randCard == 12) {

				player->deductCash(50);

			}
			else if (randCard == 13) {
			
				player->deductCash(80);

			}
			else if (randCard == 14) {

				player->deductCash(50);

			}


		}

		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "CHANCE") == 0) {
		

			int randCard = rand() % 15;

			ChanceCard* c = (ChanceCard*)board.getChance()[randCard];

			sf::RenderWindow card(sf::VideoMode(500, 170), "Chance Card", sf::Style::Titlebar);


			sf::Text cardTitle;
			cardTitle.setString("Chance.");
			cardTitle.setCharacterSize(25);
			cardTitle.setFont(stdFont);
			cardTitle.setPosition(5.0f, 5.0f);
			cardTitle.setFillColor(sf::Color::White);


			char* _cardText = c->getCardAction();
			char* modCardText = nullptr;

			if (strlen(_cardText) >= 34) {

				modCardText = new char[strlen(_cardText) + 2];


				int spaceAt = 34;

				while (_cardText[spaceAt] != ' ' && _cardText[spaceAt] != '\0') spaceAt++;

				for (unsigned int i = 0; i < strlen(_cardText) + 2; i++)
					modCardText[i] = _cardText[i];

				modCardText[spaceAt] = '\n';

			}

			sf::Text cardText;
			cardText.setFont(cardFont);
			cardText.setString((modCardText) ? modCardText : _cardText);
			cardText.setPosition(5.0f, 100.0f);
			cardText.setCharacterSize(15);
			cardText.setFillColor(sf::Color::White);

			sf::Texture closeButtonTexture;
			closeButtonTexture.loadFromFile("assets/upgrade_prompt_close.png");
			sf::RectangleShape closeButton(sf::Vector2f(20.0f, 20.0f));
			closeButton.setTexture(&closeButtonTexture);
			closeButton.setPosition(470.0f, 10.0f);
			closeButtonTexture.setSmooth(true);


			while (card.isOpen()) {


				sf::Event evt;
				while (card.pollEvent(evt)) {


					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

						sf::Vector2f mousePos = card.mapPixelToCoords(sf::Mouse::getPosition(card));
						sf::FloatRect closeButtonBounds = closeButton.getGlobalBounds();

						if (closeButtonBounds.contains(mousePos)) {

							card.close();

						}


					}


				}

				card.clear(sf::Color(230, 126, 34));

				card.draw(cardTitle);
				card.draw(cardText);
				card.draw(closeButton);
				card.display();


			}



			// card actions

			if (randCard == 0) {
			
				playerPosition[playerID] = 0;
				player->setPlayerPosition(0);
				player->addCash(300);

			}
			else if (randCard == 1) {
			
				
				int diff = abs(player->getPlayerPosition() - 26);
				movePlayer(playerID, diff, window);


			}
			else if (randCard == 2) {

				Space** cells = board.getCells();

				int nearestIndex = 0;

				for (int i = playerPosition[playerID]; i < playerPosition[playerID] + 40 && !nearestIndex; i++) {
				
					

					if (strcmp(cells[i % 40]->getSpaceType(), "COMMERCIAL") == 0) {

						Property* temp = (Property* )cells[i % 40];

						if (strcmp(temp->getPropertyGroup(), "UTILITY") == 0) {
						
							nearestIndex = i % 40;

						}

					}

				}

				Property* nearestUtility = (Property* )cells[nearestIndex];

				if (nearestUtility->getOwnerID() == -1) {
				
					int diff = abs(nearestIndex - playerPosition[playerID]);
					
					movePlayer(playerID, diff, window);


				}
				else {

					int diceRolled = board.getPrevTurns()[board.getPlayerCount()][0] + 
						board.getPrevTurns()[board.getPlayerCount()][1];

					board.getPlayerByID(nearestUtility->getOwnerID())->addCash(diceRolled * 5);
					player->deductCash(diceRolled * 5);

					playerPosition[playerID] = nearestIndex;
					player->setPlayerPosition(nearestIndex);

				}



			}
			else if (randCard == 3 || randCard == 4) {
			



				Space** cells = board.getCells();

				int nearestIndex = 0;

				for (int i = playerPosition[playerID]; i < playerPosition[playerID] + 40 && !nearestIndex; i++) {



					if (strcmp(cells[i % 40]->getSpaceType(), "COMMERCIAL") == 0) {

						Property* temp = (Property*)cells[i % 40];

						if (strcmp(temp->getPropertyGroup(), "STATION") == 0) {

							nearestIndex = i % 40;

						}

					}

				}

				Property* nearestUtility = (Property*)cells[nearestIndex];

				if (nearestUtility->getOwnerID() == -1) {

					int diff = abs(nearestIndex - playerPosition[playerID]);

					movePlayer(playerID, diff, window);


				}
				else {

					board.getPlayerByID(nearestUtility->getOwnerID())->addCash(nearestUtility->getPurchasePrice() * 2);
					player->deductCash(nearestUtility->getPurchasePrice() * 2);

					playerPosition[playerID] = nearestIndex;
					player->setPlayerPosition(nearestIndex);

				}




			}
			else if (randCard == 5) {

			
				int diff = 16 - player->getPlayerPosition();

				if (diff <= 0) {

					player->deductCash(200);
					movePlayer(playerID, abs(diff), window);

				}
				else {

					movePlayer(playerID, diff, window);

				}


			}
			else if (randCard == 6) {

				player->addCash(100);

			}
			else if (randCard == 7) {

				player->setHasJailRescueCard(player->getHasJailRescueCard() + 1);

			}
			else if (randCard == 8) {


				if (player->getPlayerPosition() >= 4) {
				
					movePlayer(playerID, 36, window);
					player->deductCash(500);

				}


			}
			else if (randCard == 9) {

			
				Space** cells = board.getCells();

				int totalCharges = 0;

				for (int i = 0; i < 40; i++) {

					if (strcmp(cells[i]->getSpaceType(), "PRIVATE") == 0 ||
						strcmp(cells[i]->getSpaceType(), "COMMERCIAL") == 0) {

						Property* temp = (Property*)cells[i];


						if (temp->getOwnerID() == player->getPlayerID()) {

							totalCharges += ((temp->getHotelCount() * 100) +
								(temp->getHouseCount() * 50));

						}


					}
					
				}

			

				player->deductCash(totalCharges);


			}
			else if (randCard == 10) {


				player->deductCash(25);


			}
			else if (randCard == 11) {
				
				Player** allPlayers = board.getPlayers();

				for (int i = 0; i < board.getPlayerCount(); i++) {

					if (!allPlayers[i]->getIsBankrupt()) {

						player->deductCash(25);
						allPlayers[i]->addCash(25);

					}

				}


			}
			else if (randCard == 12) {

				player->addCash(150);

			}
			else if (randCard == 13) {

				playerPosition[playerID] = 35;
				player->setPlayerPosition(35);

			}
			else if (randCard == 14) {

				int diff = abs(player->getPlayerPosition() - 5);
				movePlayer(playerID, diff, window);

			}



		}

	}
	else {

		player->setIsInJailCount(player->getIsInJailCount() - 1);

		if (player->getIsInJailCount() == 0)
			player->setIsInJail(false);

	}


	{


		if (toJail || playerPosition[playerID] == 30) {
			// also set the boolean to true
			// also set the inJailCount to 2
			playerPosition[playerID] = 10;
			player->setIsInJail(true);
			player->setIsInJailCount(2);

		}


	}





}

void Monopoly::playDice(sf::RenderWindow& window,
	sf::RectangleShape* dice, sf::Texture* diceTexture, int dealChoice) {

	int* diceNum = board.rollDice();

	//if (existsInProp) {

	board.getPlayerByID(board.getTurn())->setIsRenting(-1);

	if (diceNum[0] > 0 && diceNum[1] > 0 && board.getDRollCount() < 3) {


		if (diceNum[0] == diceNum[1] && board.getDRollCount()) {

			movePlayer(board.getTurn(), diceNum[0] + diceNum[1], window, dealChoice);

		}
		else if (diceNum[0] != diceNum[1] && !board.getDRollCount()) {

			movePlayer(board.getPreviousTurn(), diceNum[0] + diceNum[1], window, dealChoice);

		}
		else if (diceNum[0] != diceNum[1] && board.getDRollCount()) {

			board.setDRollCount(0);

			movePlayer(board.getPreviousTurn(), diceNum[0] + diceNum[1], window, dealChoice);

			board.setTurn(

				(board.getTurn() + 1) % board.getPlayerCount()

			);

		}
	}
	else {

		if (board.getDRollCount() == 3) {

			movePlayer(board.getTurn(), 0, window, dealChoice, true);


			board.setTurn(

				(board.getTurn() + 1)
				% board.getPlayerCount()

			);

			board.setDRollCount(0);

		}

	}
	//}

}

void Monopoly::updateDiceTextures(sf::Texture* diceTexture) {


	diceTexture[0].loadFromFile(
		diceTextureImg[
			board.getPrevTurns()[board.getPlayerCount() - 1][0]
				- (board.getPrevTurns()[board.getPlayerCount() - 1][0] > 0)
		]
	);

	diceTexture[1].loadFromFile(
		diceTextureImg[
			board.getPrevTurns()[board.getPlayerCount() - 1][1]
				- (board.getPrevTurns()[board.getPlayerCount() - 1][1] > 0)
		]
	);


}


Bank Monopoly::getBank() {
	return bank;
}


void Monopoly::setDealChoice(int dealChoice) {

	this->dealChoice = dealChoice;

}


// REVIEW

/***
bool Monopoly::canBuildHouse(int group, int playerid)
{
	bool canbuild = true;
	if (group == 0)
	{
		if (Playersarray[playerid].searchInProperty(0) &&
			Playersarray[playerid].searchInProperty(1) &&
			Playersarray[playerid].searchInProperty(2))
		{
			return true;
		}
		else return false;

	}
	if (group == 1)
	{
		if (Playersarray[playerid].searchInProperty(3) &&
			Playersarray[playerid].searchInProperty(4))
		{
			return true;
		}
		else return false;

	}
	if (group == 2)
	{
		if (Playersarray[playerid].searchInProperty(5) &&
			Playersarray[playerid].searchInProperty(6) &&
			Playersarray[playerid].searchInProperty(7))
		{
			return true;
		}
		else return false;

	}
	if (group == 3)
	{
		if (Playersarray[playerid].searchInProperty(8) &&
			Playersarray[playerid].searchInProperty(9) &&
			Playersarray[playerid].searchInProperty(10))
		{
			return true;
		}
		else return false;

	}
	if (group == 4)
	{
		if (Playersarray[playerid].searchInProperty(11) &&
			Playersarray[playerid].searchInProperty(12) &&
			Playersarray[playerid].searchInProperty(13))
		{
			return true;
		}
		else return false;

	}
	if (group == 5)
	{
		if (Playersarray[playerid].searchInProperty(14) &&
			Playersarray[playerid].searchInProperty(15) &&
			Playersarray[playerid].searchInProperty(16))
		{
			return true;
		}
		else return false;

	}
	if (group == 6)
	{
		if (Playersarray[playerid].searchInProperty(17) &&
			Playersarray[playerid].searchInProperty(18) &&
			Playersarray[playerid].searchInProperty(19))
		{
			return true;
		}
		else return false;

	}
}
**/





// Destructor

Monopoly::~Monopoly() {


}



void Monopoly::loadGame() {
	ifstream SavedGame;
	SavedGame.open("Saved.txt");
	int count = 0;
	int i = 0;
	SavedGame >> count;
	setTotalPlayers(count);
	while (!SavedGame.eof()) {
		Property** propertylist = nullptr;
		int id = i;
		char* temp = new char[20];
		int cash;
		int propertySize = 0;
		bool isInJail;
		int hasJailRescueCard;
		bool isbankrupt;
		int playerPosition;
		int inJailCount;
		bool hasWifi;
		bool hasGas;
		bool hasElectricity;
		SavedGame >> temp;
		SavedGame >> cash;
		SavedGame >> propertySize;
		Property** plots = new  Property * [propertySize];
		for (int i = 0; i < propertySize; i++) {
			plots[i] = new Property;
		}
		int ProID;
		int check = 0;
		for (int i = 0; i < propertySize; i++) {
			SavedGame >> ProID;
			plots[i] = bank.getProperty(ProID);
			bank.appendPropertyList(bank.getProperty(ProID));
			SavedGame >> check;
			for (int i = 0; i < check; i++) {
				plots[i]->addHouse();
			}
			SavedGame >> check;
			for (int i = 0; i < check; i++) {
				plots[i]->addShop();
			}
			SavedGame >> check;
			for (int i = 0; i < check; i++) {
				plots[i]->addHotel();
			}
			SavedGame >> hasWifi;
			if (hasWifi == true) {
				plots[i]->addWifi();
			}
			SavedGame >> hasGas;
			if (hasGas == true) {
				plots[i]->addGas();
			}
			SavedGame >> hasElectricity;
			if (hasElectricity == true) {
				plots[i]->addElectricity();
			}
		}
		SavedGame >> isInJail;
		SavedGame >> hasJailRescueCard;
		SavedGame >> isbankrupt;
		SavedGame >> playerPosition;
		SavedGame >> inJailCount;
		board.setPlayerData(id, temp, cash, propertySize, plots, isInJail, hasJailRescueCard, isbankrupt, playerPosition, inJailCount);
	}

}

void Monopoly::saveGame() {
	ofstream save;
	save.open("Save.txt");
	save << getTotalPlayers();
	for (int i = 0; i < getTotalPlayers(); i++) {
		save << board.getPlayerName(i) << " ";
		save << board.getPlayercash(i) << " ";
		save << board.getPlayerListSize(i) << " ";
		Property** temp = new Property * [board.getPlayerListSize(i)];
		temp = board.getPlayerList(i);
		for (int j = 0; j < board.getPlayerListSize(i); j++) {
			save << temp[i]->getPropertyID() << " ";
			save << temp[i]->getHouseCount() << " ";
			save << temp[i]->getShopCount() << " ";
			save << temp[i]->getHotelCount() << " ";
			save << temp[i]->getHasWifi() << " ";
			save << temp[i]->getHasGas() << " ";
			save << temp[i]->getHasElectricity() << " ";
		}
		save << board.getPlayerisInJail(i) << " ";
		save << board.getPlayerhasJailRescueCard(i) << " ";
		save << board.getPlayerisbankrupt(i) << " ";
		save << board.getPlayerplayerPosition(i) << " ";
		save << board.getPlayerinJailCount(i);
		if (i < getTotalPlayers() - 1) {
			save << endl;
		}
	}
}