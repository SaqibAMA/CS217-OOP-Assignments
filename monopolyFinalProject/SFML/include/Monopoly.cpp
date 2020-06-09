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

	bankruptPlayers = nullptr;

	gameWon = false;


	fin.close();


}

// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	board.setPlayerCount(totalPlayers);
	board.allocatePrevTurns();
	board.allocatePlayers();
	bankruptPlayers = new bool[board.getPlayerCount()];

	for (int i = 0; i < totalPlayers; i++) {

		bankruptPlayers[i] = false;

	}

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

			if (player->getPlayerID() != property->getOwnerID()) {

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

				
				sf::Texture closeBtnTexture;
				closeBtnTexture.loadFromFile("assets/upgrade_prompt_close.png");

				sf::RectangleShape closeBtn(sf::Vector2f(20.0f, 20.f));
				closeBtn.setTexture(&closeBtnTexture);
				closeBtn.setPosition(220.0f, 15.0f);



				while (buyOrRentPrompt.isOpen()) {

					sf::Event evt;

					while (buyOrRentPrompt.pollEvent(evt)) {


						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {




							sf::Vector2f mousePos = buyOrRentPrompt.mapPixelToCoords(sf::Mouse::getPosition(buyOrRentPrompt));
							sf::FloatRect buyButtonBounds = buyButton.getGlobalBounds();
							sf::FloatRect rentButtonBounds = rentButton.getGlobalBounds();

							sf::FloatRect closeBtnBounds = closeBtn.getGlobalBounds();



							if (buyButtonBounds.contains(mousePos)) {


								dealChoice = 0;

								buyOrRentPrompt.close();


							}

							if (rentButtonBounds.contains(mousePos)) {


								dealChoice = 1;

								buyOrRentPrompt.close();


							}

							if (closeBtnBounds.contains(mousePos)) {
							

								// buyOrRentPrompt.close();

								sf::RenderWindow bid(sf::VideoMode(265, 166), "BIDDING", sf::Style::Titlebar);

								sf::Clock clk;

								sf::Text timeDisplay;
								timeDisplay.setFont(stdFont);
								timeDisplay.setCharacterSize(25);
								timeDisplay.setPosition(230.f, 15.0f);
								timeDisplay.setFillColor(sf::Color(52, 73, 94));

								while (bid.isOpen()) {
								

									// Implement the bidding system
									// Clock has been setup.
									// Check turn management.

									sf::Event bEvt;
									while (bid.pollEvent(bEvt)) {


										if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


											clk.restart();


										}


									}

									bid.clear(sf::Color::White);

									int currTime = abs(10 - clk.getElapsedTime().asSeconds());

									if (currTime == 0) {

										clk.restart();

									}

									timeDisplay.setString(to_string(currTime));
									bid.draw(timeDisplay);

									bid.display();


								}




							}




						}



					}

					buyOrRentPrompt.clear(sf::Color::White);
					buyOrRentPrompt.draw(buyButton);
					buyOrRentPrompt.draw(rentButton);
					for (int i = 0; i < 5; i++)
						buyOrRentPrompt.draw(promptText[i]);

					buyOrRentPrompt.draw(closeBtn);

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
				else if (propertiesOwned && (dealChoice == 1 || dealChoice == 0)) {

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

		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "PARKING") == 0) {
		
			player->addCash(10);

		}

		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "LANDTAX") == 0) {

			float totalTax = 0;

			Space** cells = board.getCells();

			for (int i = 0; i < 40; i++) {
			
				if (strcmp(board.getCells()[i]->getSpaceType(), "PRIVATE") == 0 || strcmp(board.getCells()[i]->getSpaceType(), "COMMERCIAL") == 0) {
				

					Property* temp = (Property* ) cells[i];

					if (temp->getOwnerID() == player->getPlayerID()) {
					
						totalTax += (int)(temp->getPurchasePrice() * 0.2);

					}
				

				}

			}

			sf::RenderWindow taxPrompt(sf::VideoMode(300, 160), "Land Tax", sf::Style::Titlebar);


			sf::Text cardTitle;
			cardTitle.setString("Land Tax.");
			cardTitle.setCharacterSize(25);
			cardTitle.setFont(stdFont);
			cardTitle.setPosition(15.0f, 15.0f);
			cardTitle.setFillColor(sf::Color::White);

			sf::Text cardText;
			cardText.setFont(cardFont);
			cardText.setString("20% Land Tax has been deducted!");
			cardText.setPosition(15.0f, 100.0f);
			cardText.setCharacterSize(15);
			cardText.setFillColor(sf::Color::White);

			sf::Texture closeButtonTexture;
			closeButtonTexture.loadFromFile("assets/upgrade_prompt_close.png");
			sf::RectangleShape closeButton(sf::Vector2f(20.0f, 20.0f));
			closeButton.setTexture(&closeButtonTexture);
			closeButton.setPosition(270.0f, 10.0f);
			closeButtonTexture.setSmooth(true);





			while (taxPrompt.isOpen()) {
			

				sf::Event evt;
				while (taxPrompt.pollEvent(evt)) {
				
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					
						sf::Vector2f mousePos = taxPrompt.mapPixelToCoords(sf::Mouse::getPosition(taxPrompt));
						sf::FloatRect closeButtonBounds = closeButton.getGlobalBounds();


						if (closeButtonBounds.contains(mousePos)) {
						

							taxPrompt.close();
							player->deductCash((int)totalTax);

						}




					}

				
				}


				taxPrompt.clear(sf::Color(26, 188, 156));
				taxPrompt.draw(cardTitle);
				taxPrompt.draw(cardText);
				taxPrompt.draw(closeButton);

				taxPrompt.display();


			}







		}
		
		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "GOTOJAIL") == 0) {
		


			sf::RenderWindow jail(sf::VideoMode(500, 200), " ", sf::Style::Titlebar);

			sf::Text cardTitle;
			cardTitle.setString("JAIL OPTIONS");
			cardTitle.setCharacterSize(25);
			cardTitle.setFont(stdFont);
			cardTitle.setPosition(15.0f, 15.0f);
			cardTitle.setFillColor(sf::Color(52, 73, 94));

			sf::Text cardText;
			cardText.setFont(cardFont);
			cardText.setString("You have been jailed.\nSelect the option that you would like\nto use.");
			cardText.setPosition(15.0f, 60.0f);
			cardText.setCharacterSize(15);
			cardText.setFillColor(sf::Color(52, 73, 94));

			sf::RectangleShape* btn = new sf::RectangleShape[4];
			for (int i = 0; i < 4; i++) {
			
				btn[i].setFillColor(sf::Color(52, 73, 94));
				btn[i].setSize(sf::Vector2f(100.f, 50.0f));
				btn[i].setPosition(15.0f + (i * 120.0f), 130.0f);

			}

			sf::Text* btnText = new sf::Text[4];
			for (int i = 0; i < 4; i++) {

				btnText[i].setCharacterSize(12);
				btnText[i].setFont(stdFont);
				btnText[i].setFillColor(sf::Color(236, 240, 241));

			}

			btnText[0].setString("\t TRY\nDOUBLES");
			btnText[1].setString("USE CARD");
			btnText[2].setString("PAY FINE");
			btnText[3].setString("BUY CARD");

			btnText[0].setPosition(30.0f , 140.0f);
			btnText[1].setPosition(150.0f, 148.0f);
			btnText[2].setPosition(275.0f, 148.0f);
			btnText[3].setPosition(390.0f, 148.0f);

			sf::Text err;
			//err.setString("fine");
			err.setCharacterSize(12);
			err.setPosition(15.0f, 110.0f);
			err.setFillColor(sf::Color(231, 76, 60));
			err.setFont(stdFont);


			while (jail.isOpen()) {
			

				sf::Event evt;
				while (jail.pollEvent(evt)) {

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

						sf::Vector2f mousePos = jail.mapPixelToCoords(sf::Mouse::getPosition(jail));

						sf::FloatRect btnBound[4];
						for (int i = 0; i < 4; i++) {

							btnBound[i] = btn[i].getGlobalBounds();


							if (btnBound[i].contains(mousePos)) {


								// options
								// try to roll doubles
								// use "get out of jail card"
								// pay fine
								// buy "get out of jail card"



								if (i == 0) {

									player->setIsInJail(true);
									player->setIsInJailCount(2);

									jail.close();

								}
								else if (i == 1) {

									if (player->getHasJailRescueCard()) {

										player->setHasJailRescueCard(player->getHasJailRescueCard() - 1);
										player->setIsInJail(false);
										player->setIsInJailCount(0);

									}

									err.setString("You do not have a jail rescue card!");

								}
								else if (i == 2) {

									if (player->getCash() >= 400) {

										player->deductCash(400);
										player->setIsInJail(false);
										player->setIsInJailCount(0);
										playerPosition[playerID] = 30;
										player->setPlayerPosition(30);

										jail.close();

									}
									else {

										err.setString("You do not have any cash!    * ghamgeen lamha *");

									}

								}
								else if (i == 3) {

									if (player->getCash() >= 400) {

										int jailCardExists = -1;

										Player** allPlayers = board.getPlayers();

										for (int i = 0; i < board.getPlayerCount() && !jailCardExists; i++) {

											if (!allPlayers[i]->getIsBankrupt() && allPlayers[i]->getHasJailRescueCard()) {

												jailCardExists = i;

											}

										}

										if (jailCardExists != -1) {


											sf::RenderWindow bin(sf::VideoMode(250, 120), "YES OR NO?", sf::Style::Titlebar);



											sf::RectangleShape yn[2];
											sf::Text ynText[2];

											for (int i = 0; i < 2; i++) {

												yn[i].setFillColor(sf::Color(52, 73, 94));
												yn[i].setSize(sf::Vector2f(100.0f, 50.0f));
												yn[i].setPosition(12.0f + (i * 120.0f), 20.0f);

											}

											sf::Text note;
											note.setString("Do you want\nto sell your card?");
											note.setFont(cardFont);
											note.setFillColor(sf::Color(52, 73, 94));
											note.setPosition(12.0f, 80.0f);
											note.setCharacterSize(14);

											while (bin.isOpen()) {


												sf::Event bEvt;
												while (bin.pollEvent(bEvt)) {



													if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


														mousePos = jail.mapPixelToCoords(sf::Mouse::getPosition(bin));

														sf::FloatRect ynBounds[2];
														ynBounds[0] = yn[0].getGlobalBounds();
														ynBounds[1] = yn[1].getGlobalBounds();


														if (ynBounds[0].contains(mousePos)) {


															player->deductCash(400);
															allPlayers[jailCardExists]->addCash(400);
															allPlayers[jailCardExists]->setHasJailRescueCard(allPlayers[jailCardExists]->getHasJailRescueCard() - 1);

															bin.close();


														}
														else if (ynBounds[1].contains(mousePos)) {


															err.setString("Player refused to sell.");
															
															
															bin.close();


														}




													}



												}


												bin.clear(sf::Color(236, 240, 241));

												for (int i = 0; i < 2; i++) {

													bin.draw(yn[i]);
													bin.draw(ynText[i]);

												}

												bin.draw(note);

												bin.display();


											}




										}
										else {

											err.setString("No one owns a \"get out of jail card\" yet.");

										}


									}
									else {

										err.setString("You do not have any cash  * ghamgeen lamha *");

									}


								}


							}


						}

					}



				}


				jail.clear(sf::Color(236, 240, 241));
				jail.draw(cardTitle);
				jail.draw(cardText);
				

				for (int i = 0; i < 4; i++) {
					jail.draw(btn[i]);
					jail.draw(btnText[i]);
				}

				jail.draw(err);

				jail.display();
			
			}

			delete[] btn;
			delete[] btnText;




		}

		if (strcmp(board.getCells()[playerPosition[playerID]]->getSpaceType(), "PROPERTYTAX") == 0) {
		
			/*
			
			Pay 10% tax on land, 20% tax on houses and 30% on hotels
			and shops on each visit of this cell

			*/


			Space** cells = board.getCells();

			float totalTax = 0;


			for (int i = 0; i < 40; i++) {


				if (strcmp(cells[i]->getSpaceType(), "PRIVATE") == 0) {
				
					PrivateProperty* p = (PrivateProperty*) cells[i];


					totalTax += (
						
						(p->getPurchasePrice() * 0.10f) +
						(p->getHouseCount() * 20.0f) +
						(p->getHotelCount() * 210.0f) +
						(p->getShopCount() * 90.0f)

						);



				}
				else if (strcmp(cells[i]->getSpaceType(), "COMMERCIAL") == 0) {
				
					CommercialProperty* p = (CommercialProperty*)cells[i];

					totalTax += (

						(p->getPurchasePrice() * 0.10f)

						);


				}


			}


			player->deductCash(totalTax);



		}



	}
	else {


		// Check if the player has rolled doubles. If he does, the player gets out.

		int diceRoll[2];

		diceRoll[0] = board.getPrevTurns()[board.getPlayerCount() - 1][0];
		diceRoll[1] = board.getPrevTurns()[board.getPlayerCount() - 1][1];

		if (diceRoll[0] == diceRoll[1] && player->getIsInJailCount() == 2) {

			player->setIsInJail(false);
			player->setIsInJailCount(0);

			movePlayer(diceRoll[0] + diceRoll[1], playerID, window);

		}
		else {

			player->setIsInJailCount(player->getIsInJailCount() - 1);

			if (player->getIsInJailCount() == 0)
				player->setIsInJail(false);

		}


	}


	{


		if (toJail || player->getIsInJail()) {
			// also set the boolean to true
			// also set the inJailCount to 2
			playerPosition[playerID] = 10;
			player->setIsInJailCount(2);

		}


	}





}

void Monopoly::playDice(sf::RenderWindow& window,
	sf::RectangleShape* dice, sf::Texture* diceTexture, int dealChoice) {


	if (!gameWon) {

		if (board.getTurn() == 0) {


			checkBankruptcy();


		}



		int* diceNum = board.rollDice();

		//if (existsInProp) {

		//if (!bankruptPlayers[board.getTurn()]) {

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
		//else {

		//	board.setTurn(

		//		(board.getTurn() + 1)
		//		% board.getPlayerCount()

		//	);

		//}

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



void Monopoly::checkBankruptcy() {


	Player** player = board.getPlayers();


	for (int i = 0; i < board.getPlayerCount(); i++) {
	
		bool isBankrupt = false;

		if (player[i]->getCash() <= 0) {

			Space** cells = board.getCells();


			int propertiesOwned = 0;


			for (int j = 0; j < 40; j++) {


				if (strcmp(cells[j]->getSpaceType(), "PRIVATE") == 0 && strcmp(cells[j]->getSpaceType(), "COMMERCIAL") == 0) {
				

					Property* p = (Property*) cells[j];


					if (p->getOwnerID() == player[i]->getPlayerID()) {
					
						propertiesOwned++;


					}


				}


			}


			// cout << "Properties owned by " << i << propertiesOwned << endl;


			isBankrupt = (propertiesOwned <= 0);


			if (isBankrupt) {
				
				player[i]->setIsBankrupt(true);
				bankruptPlayers[player[i]->getPlayerID()] = true;
			
			}
			else {


				int deficit = abs(player[i]->getCash());
				int minDiff = INT_MAX;
				int propertyInd = -1;


				for (int j = 0; j < 40; j++) {


					if (strcmp(cells[j]->getSpaceType(), "PRIVATE") == 0 && strcmp(cells[j]->getSpaceType(), "COMMERCIAL")) {


						Property* p = (Property*)cells[j];

						if (p->getOwnerID() == player[i]->getPlayerID() && abs(deficit - p->getPurchasePrice()) < minDiff && !p->getMortgaged()) {

							propertyInd = j;

						}
						else if (p->getOwnerID() == player[i]->getPlayerID() && abs(deficit - (p->getPurchasePrice() / 2)) < minDiff && p->getMortgaged()) {

							propertyInd = j;

						}


					}


				}



				Property* p = (Property*)cells[propertyInd];

				player[i]->addCash(

					(!p->getMortgaged()) ?
					p->getPurchasePrice() :
					(p->getPurchasePrice() / 2) - (0.2f * p->getPurchasePrice())

				);

				p->setOwnerID(-1);


			}

		}
		else {

			player[i]->setIsBankrupt(false);
			bankruptPlayers[player[i]->getPlayerID()] = false;

		}



	}


	int playersLeft = 0;

	for (int i = 0; i < board.getPlayerCount(); i++) {

		playersLeft += !bankruptPlayers[i];

	}

	gameWon = (playersLeft == 1);

	if (gameWon) cout << "Game Won!" << endl;


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