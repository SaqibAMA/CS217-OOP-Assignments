
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

#include <Monopoly.h>

using namespace std;


int main()
{

    // Monopoly object to run the entire
    // gameplay

    Monopoly game;

    // Creating an SFML window
    sf::RenderWindow window(sf::VideoMode(1280, 720),
        "Monopoly by Saqib, Nabeel, Abdur Rehman, & Salman",
        sf::Style::Close | sf::Style::Titlebar);

    // Standard Font
    sf::Font stdFont;
    stdFont.loadFromFile("fonts/Montserrat-Black.ttf");


    // Implementing the favicon
    sf::Image favicon;
    favicon.loadFromFile("assets/favicon.png");
    window.setIcon(314, 229, favicon.getPixelsPtr());

    // Intro screen
    sf::RectangleShape introScreen(sf::Vector2f(1280.0f, 720.0f));
    sf::Texture introScreenTexture;
    introScreenTexture.loadFromFile("assets/intro-splash-screen.png");
    introScreen.setTexture(&introScreenTexture);

    window.draw(introScreen);

    bool gameStarted = false;

    while (!gameStarted) {

        sf::Event evt;
        while (window.pollEvent(evt)) {

            if (evt.type == evt.Closed) {

                window.close();

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {


                /*

                Play button bounds

                485, 505
                795, 505
                485, 592
                795, 592

                */

                int mouseX = sf::Mouse::getPosition(window).x;
                int mouseY = sf::Mouse::getPosition(window).y;

                if ((mouseX >= 485 && mouseX <= 795) && (mouseY >= 505 && mouseY <= 592)) {
                    gameStarted = true;
                }


            }

        }

        window.draw(introScreen);
        window.display();

    }


    // Selection screen to get the user choice
    // for either new game or load game

    // Creating in-game assets for screen rendering

    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("assets/selection-screen.png");
    sf::RectangleShape selectionScreen(sf::Vector2f(1280.0f, 720.0f));
    selectionScreen.setTexture(&selectionScreenTexture);

    // New game button
    sf::Texture newGameButtonTexture;
    newGameButtonTexture.loadFromFile("assets/new-game-button.png");
    sf::RectangleShape newGameButton(sf::Vector2f(316.0f, 94.0f));
    newGameButton.setTexture(&newGameButtonTexture);

    newGameButton.setPosition(sf::Vector2f(480.0f, 210.0f));

    // Load game button
    sf::Texture loadGameButtonTexture;
    loadGameButtonTexture.loadFromFile("assets/load-game-button.png");
    sf::RectangleShape loadGameButton(sf::Vector2f(316.0f, 94.0f));
    loadGameButton.setTexture(&loadGameButtonTexture);

    loadGameButton.setPosition(sf::Vector2f(newGameButton.getPosition().x,
        newGameButton.getPosition().y + 114.0f));


    // Keeps the choice that the user has made.
    // 1 --> New Game
    // 2 --> Load Game
    int choice = -1;


    while (window.isOpen() && gameStarted && choice == -1) {

        sf::Event evt;
        while (window.pollEvent(evt)) {


            if (evt.type == evt.Closed) {

                window.close();

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                sf::FloatRect newGameButtonBounds = newGameButton.getGlobalBounds();
                sf::FloatRect loadGameButtonBounds = loadGameButton.getGlobalBounds();

                if (newGameButtonBounds.contains(mousePos)) {

                    choice = 1;

                }

                if (loadGameButtonBounds.contains(mousePos)) {

                    choice = 2;

                }


            }

            window.draw(selectionScreen);
            window.draw(newGameButton);
            window.draw(loadGameButton);
            window.display();

        }

    }

    gameStarted = false;

    while (!gameStarted) {

        if (choice == 1) {

            gameStarted = true;

            // Keeps the total number of players
            // that the user has asked for
            // the game supports 3 - 5 players.
            int totalPlayers = -1;

            // Background screen
            sf::Texture playerNumberScreenTexture;
            playerNumberScreenTexture.loadFromFile("assets/player-number-selection-screen.png");
            sf::RectangleShape playerNumberScreen(sf::Vector2f(1280.0f, 720.0f));
            playerNumberScreen.setTexture(&playerNumberScreenTexture);


            // Card that shows 3 players
            sf::Texture threePlayerTexture;
            threePlayerTexture.loadFromFile("assets/3-player-card.png");
            sf::RectangleShape threePlayerCard(sf::Vector2f(251.0f, 272.0f));
            threePlayerCard.setTexture(&threePlayerTexture);
            threePlayerCard.setPosition(sf::Vector2f(250.0f, 200.0f));

            // Card that shows 4 players
            sf::Texture fourPlayerTexture;
            fourPlayerTexture.loadFromFile("assets/4-player-card.png");
            sf::RectangleShape fourPlayerCard(sf::Vector2f(251.0f, 272.0f));
            fourPlayerCard.setTexture(&fourPlayerTexture);
            fourPlayerCard.setPosition(sf::Vector2f(
                threePlayerCard.getPosition().x + 260, threePlayerCard.getPosition().y));

            // Card that shows 5 players
            sf::Texture fivePlayerTexture;
            fivePlayerTexture.loadFromFile("assets/5-player-card.png");
            sf::RectangleShape fivePlayerCard(sf::Vector2f(251.0f, 272.0f));
            fivePlayerCard.setTexture(&fivePlayerTexture);
            fivePlayerCard.setPosition(sf::Vector2f(
                fourPlayerCard.getPosition().x + 260, threePlayerCard.getPosition().y));

            while (totalPlayers == -1) {


                sf::Event evt;
                while (window.pollEvent(evt)) {


                    if (evt.type == evt.Closed) {

                        window.close();

                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // Checks if any of the cards have been clicked

                        sf::FloatRect threeCardBound = threePlayerCard.getGlobalBounds();
                        sf::FloatRect fourCardBound = fourPlayerCard.getGlobalBounds();
                        sf::FloatRect fiveCardBound = fivePlayerCard.getGlobalBounds();

                        if (threeCardBound.contains(mousePos)) totalPlayers = 3;
                        if (fourCardBound.contains(mousePos)) totalPlayers = 4;
                        if (fiveCardBound.contains(mousePos)) totalPlayers = 5;


                    }


                }

                window.draw(playerNumberScreen);
                window.draw(threePlayerCard);
                window.draw(fourPlayerCard);
                window.draw(fivePlayerCard);
                window.display();

            }

            game.setTotalPlayers(totalPlayers);


        }
        else {

            window.clear();

            ifstream fin;
            fin.open("savedGames/savedGamesList.txt");


            // Getting the total number of games
            // that is written on top

            int totalGames = -1;

            if (!fin.eof())
                fin >> totalGames;

            fin.ignore();


            // Reading all the saved games
            // from the savedGamesList.txt file

            char** list = nullptr;

            if (totalGames > 0) {
                list = new char* [totalGames];

                int i = 0;

                while (!fin.eof()) {

                    char buff[100];

                    fin.getline(buff, 100);

                    list[i] = new char[strlen(buff) + 1];
                    strcpy_s(list[i], strlen(buff) + 1, buff);

                    i++;


                }


            }

            fin.close();

            // Background screen
            sf::Texture playerNumberScreenTexture;
            playerNumberScreenTexture.loadFromFile("assets/player-number-selection-screen.png");
            sf::RectangleShape playerNumberScreen(sf::Vector2f(1280.0f, 720.0f));
            playerNumberScreen.setTexture(&playerNumberScreenTexture);


            // New game button
            sf::Texture newGameButtonTexture;
            newGameButtonTexture.loadFromFile("assets/new-game-button.png");
            sf::RectangleShape newGameButton(sf::Vector2f(316.0f, 94.0f));
            newGameButton.setTexture(&newGameButtonTexture);

            newGameButton.setPosition(sf::Vector2f(480.0f, 400.0f));



            if (!list) {

                sf::Text noGamesTxt;
                noGamesTxt.setString("No games saved previously!");
                noGamesTxt.setFillColor(sf::Color::Red);  // Setting the text color to cream
                noGamesTxt.setFont(stdFont);

                noGamesTxt.setPosition(sf::Vector2f(400.0f, 250.0f));

                while (choice != 1) {

                    sf::Event evt;
                    while (window.pollEvent(evt)) {

                        if (evt.type == evt.Closed) {

                            window.close();

                        }

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


                            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                            // Checking if the new button has been clicked.

                            sf::FloatRect newGameButtonBounds = newGameButton.getGlobalBounds();


                            if (newGameButtonBounds.contains(mousePos)) {

                                choice = 1;

                            }



                        }

                    }

                    window.draw(playerNumberScreen);
                    window.draw(noGamesTxt);
                    window.draw(newGameButton);
                    window.display();

                }


            }
            else {

                sf::Text totalGamesText;
                totalGamesText.setString("~ SAVED GAMES ~");

                totalGamesText.setCharacterSize(35);
                totalGamesText.setFont(stdFont);
                totalGamesText.setFillColor(sf::Color(163, 191, 46));
                totalGamesText.setPosition(sf::Vector2f(470.0f, 130.0f));

                sf::Text* gamesListText = new sf::Text[totalGames];

                for (int i = 0; i < totalGames; i++) {

                    gamesListText[i].setCharacterSize(30);
                    gamesListText[i].setFont(stdFont);
                    gamesListText[i].setFillColor(sf::Color(94, 60, 54));
                    gamesListText[i].setString(list[i]);
                    gamesListText[i].setPosition(sf::Vector2f(500.0f, 220.0f + ((float)i * 50.0f)));

                }


                int gameChoiceSelected = -1;

                while (!gameStarted) {

                    sf::Event evt;
                    while (window.pollEvent(evt)) {

                        if (evt.type == evt.Closed) {

                            window.close();

                        }

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                            // Checking if any of the game selections were used.

                            for (int i = 0; i < totalGames; i++) {

                                sf::FloatRect gamesListTextBound = gamesListText[i].getGlobalBounds();

                                if (gamesListTextBound.contains(mousePos)) {
                                    gameChoiceSelected = i;
                                    gameStarted = true;
                                }


                            }


                        }

                    }

                    window.draw(playerNumberScreen);

                    window.draw(totalGamesText);

                    for (int i = 0; i < totalGames; i++) {

                        window.draw(gamesListText[i]);

                    }

                    window.display();

                }

            }




        }

    }


    // Main game loop

    //window.close();


    // Creating a window that is resizable
    //window.create(sf::VideoMode(1280, 720), "Monopoly by Saqib, Nabeel, Abdur Rehman, & Salman",
    //    sf::Style::Close | sf::Style::Resize);

    // Setting up the favicon for that window again
    window.setIcon(314, 229, favicon.getPixelsPtr());

    sf::Texture gameScreenTexture;
    gameScreenTexture.loadFromFile("assets/game-screen.png");
    sf::RectangleShape gameScreen(sf::Vector2f(1280.0f, 720.0f));
    gameScreen.setTexture(&gameScreenTexture);

    gameScreenTexture.setSmooth(true);



    // ****** PRIMARY GAME LOGIC ******


    // Files names for all the player pieces

    const char* playerPieceFileName[5] = {

        "assets/player1.png",
        "assets/player2.png",
        "assets/player3.png",
        "assets/player4.png",
        "assets/player5.png"

    };

    // Initializing all of the pieces

    //int totalPlayers = game.getTotalPlayers();

    int totalPlayers = game.getTotalPlayers();
    game.initializePositions();

    sf::Texture* playerTextures = new sf::Texture[totalPlayers];
    sf::RectangleShape* playerPieces = new sf::RectangleShape[totalPlayers];

    // Setting up all of the textures

    for (int i = 0; i < totalPlayers; i++) {

        playerTextures[i].loadFromFile(playerPieceFileName[i]);
        playerPieces[i].setTexture(&playerTextures[i]);
        playerPieces[i].setSize(sf::Vector2f(20.0f, 20.0f));

        playerTextures[i].setSmooth(true);

    }

    // Camera button for Screenshot

    sf::Texture cameraButtonTexture;
    cameraButtonTexture.loadFromFile("assets/camera.png");
    sf::RectangleShape cameraButton(sf::Vector2f(106.5f, 80.25f));
    cameraButton.setTexture(&cameraButtonTexture);
    cameraButton.setPosition(1150.0f, 620.0f);
    cameraButtonTexture.setSmooth(true);


    // Dice button for Dice

    sf::Texture diceButtonTexture;
    diceButtonTexture.loadFromFile("assets/diceButton.png");
    sf::RectangleShape diceButton(sf::Vector2f(111.0f, 111.0f));
    diceButton.setPosition(750.0f, 600.0f);
    diceButton.setTexture(&diceButtonTexture);


    // Player Icons

    const char* playerIconTextureImg[5] = {
        "assets/player_icon_1.png",
        "assets/player_icon_2.png",
        "assets/player_icon_3.png",
        "assets/player_icon_4.png",
        "assets/player_icon_5.png"
    };

    sf::Texture* playerIconTexture = new sf::Texture[totalPlayers];
    sf::RectangleShape* playerIcon = new sf::RectangleShape[totalPlayers];
    for (int i = 0; i < totalPlayers; i++) {

        playerIconTexture[i].loadFromFile(playerIconTextureImg[i]);
        playerIcon[i].setTexture(&playerIconTexture[i]);
        playerIcon[i].setPosition(720.0f + (i * 100), 20.0f);
        playerIcon[i].setSize(sf::Vector2f(120.5f, 155.0f));

    }


    // Two dices

    const char* diceTextureImg[6] =
    {
        "assets/dice_1.png",
        "assets/dice_2.png",
        "assets/dice_3.png",
        "assets/dice_4.png",
        "assets/dice_5.png",
        "assets/dice_6.png"

    };


    sf::Texture* diceTexture = new sf::Texture[2];
    diceTexture[0].loadFromFile(diceTextureImg[0]);
    diceTexture[1].loadFromFile(diceTextureImg[1]);

    sf::RectangleShape* dice = new sf::RectangleShape[2];
    for (int i = 0; i < 2; i++) {
        dice[i].setSize(sf::Vector2f(80.0f, 80.f));
        dice[i].setPosition(120.0f + (i * 75), 520.0f);
        dice[i].setTexture(&diceTexture[i]);
        diceTexture[i].setSmooth(true);
    }

    // To handle animation times
    sf::Clock clk;
    sf::Time animInt = sf::seconds(0.5f);
    sf::Time pieceMvtTime = sf::milliseconds(100);

    bool diceAnim = false;

    // To handle pieces movement delay

    int* playerPrevPos = new int[totalPlayers];
    for (int i = 0; i < totalPlayers; i++)
        playerPrevPos[i] = 0;


    // Property Cards Assets (Private)

    sf::Texture cardPanelTexture;
    cardPanelTexture.loadFromFile("assets/prop_cards.png");
    sf::RectangleShape cardPanel(sf::Vector2f(448.0f, 166.0f));
    cardPanel.setPosition(760.0f, 200.0f);
    cardPanel.setTexture(&cardPanelTexture);

    sf::Texture* navButtonTexture = new sf::Texture[2];
    navButtonTexture[0].loadFromFile("assets/float_left_btn.png");
    navButtonTexture[1].loadFromFile("assets/float_right_btn.png");

    sf::RectangleShape* navButton = new sf::RectangleShape[2];
    for (int i = 0; i < 2; i++) {

        navButton[i].setSize(sf::Vector2f(88.0f, 88.0f));
        navButton[i].setTexture(&navButtonTexture[i]);
        navButton[i].setPosition(725.0f + (i * 425.0f), 240.0f);

    }


    // Property Card Assets (Commercial)

    sf::RectangleShape commercialCardPanel(cardPanel);
    commercialCardPanel.setPosition(760.0f, 350.0f);

    sf::RectangleShape* commercialNavButton = new sf::RectangleShape[2];
    for (int i = 0; i < 2; i++) {

        commercialNavButton[i].setSize(sf::Vector2f(88.0f, 88.0f));
        commercialNavButton[i].setTexture(&navButtonTexture[i]);
        commercialNavButton[i].setPosition(725.0f + (i * 425.0f), 390.0f);

    }


    // Private Property Names to iterate through, on cards

    int privatePropertyCardScroll = 0;
    int commercialPropertyCardScroll = 0;

    const char* privatePropertyNames[20] = {

        "IQBAL TOWN A",
        "IQBAL TOWN B",
        "IQBAL TOWN C",

        "JOHAR TOWN A",
        "JOHAR TOWN B",

        "FAISAL TOWN A",
        "FAISAL TOWN B",
        "FAISAL TOWN C",

        "MODEL TOWN A",
        "MODEL TOWN B",
        "MODEL TOWN C",

        "GULBERG II A",
        "GULBERG II B",
        "GULBERG II C",

        "DHA A",
        "DHA B",
        "DHA Y",

        "BAHRIA TOWN A",
        "BAHRIA TOWN B",
        "BAHRIA TOWN C"

    };

    const char* privatePropertyPrices[20] = {

        "250", "300", "400",
        "200", "250",
        "300", "400", "400",
        "800", "850", "2000",
        "1000", "1200", "2500",
        "2500", "3000", "3000",
        "2500", "3000", "3000"

    };

    const char* privatePropertyRents[20] = {

        "60", "70", "100",
        "80", "90",
        "100", "130", "130",
        "200", "250", "500",
        "300", "350", "600",
        "500", "500", "1000",
        "800", "900", "1000"

    };

    int privatePropertySpaces[20] = {

        1, 3, 6, 8,
        9, 11, 13, 14,
        16, 18, 19, 21,
        23, 24, 26, 27,
        29, 31, 32, 34,

    };


    const char* commercialPropertyNames[8] = {

        "METRO ST.",
        "LESCO",
        "BUS ST.",
        "RAILWAY ST.",
        "WASA",
        "ORANGE TRAIN",
        "PTCL",
        "SUI"

    };

    const char* commercialPropertyPrices[8] = {

        "2000",
        "5000",
        "2000",
        "2500",
        "4000",
        "2500",
        "8000",
        "2500"

    };

    const char* commercialPropertyRents[8] = {

        "200",
        "450",
        "200",
        "350",
        "400",
        "350",
        "500",
        "350"

    };

    // Text for Private Properties

    sf::Font cardFont;
    cardFont.loadFromFile("fonts/Nexa-Light.otf");

    sf::Text* cardTitle = new sf::Text[3];
    for (int i = 0; i < 3; i++) {

        cardTitle[i].setFillColor(sf::Color::Black);
        cardTitle[i].setFont(cardFont);
        cardTitle[i].setCharacterSize(12);
        cardTitle[i].setString(privatePropertyNames[i]);

    }

    cardTitle[0].setPosition(785.0f, 250.0f);
    cardTitle[1].setPosition(925.0f, 250.0f);
    cardTitle[2].setPosition(1070.0f, 250.0f);


    sf::Text* cardPrice = new sf::Text[3];

    for (int i = 0; i < 3; i++) {

        cardPrice[i].setFillColor(sf::Color(26, 188, 156));
        cardPrice[i].setFont(stdFont);
        cardPrice[i].setCharacterSize(12);
        cardTitle[i].setString(privatePropertyPrices[i]);

    }

    cardPrice[0].setPosition(785.0f, cardTitle[0].getPosition().y + 20.0f);
    cardPrice[1].setPosition(925.0f, cardTitle[0].getPosition().y + 20.0f);
    cardPrice[2].setPosition(1070.0f, cardTitle[0].getPosition().y + 20.0f);


    sf::Text* cardRent = new sf::Text[3];
    for (int i = 0; i < 3; i++) {

        cardRent[i].setFillColor(sf::Color(52, 152, 219));
        cardRent[i].setFont(stdFont);
        cardRent[i].setCharacterSize(10);
        cardRent[i].setString(privatePropertyRents[i]);

    }

    cardRent[0].setPosition(785.0f, cardTitle[0].getPosition().y + 40.0f);
    cardRent[1].setPosition(925.0f, cardTitle[0].getPosition().y + 40.0f);
    cardRent[2].setPosition(1070.0f, cardTitle[0].getPosition().y + 40.0f);



    // Text for commercial properties

    sf::Text* commercialCardTitle = new sf::Text[3];
    for (int i = 0; i < 3; i++) {
        commercialCardTitle[i].setFillColor(sf::Color::Black);
        commercialCardTitle[i].setFont(cardFont);
        commercialCardTitle[i].setCharacterSize(12);
        commercialCardTitle[i].setString(commercialPropertyNames[i]);
    }

    commercialCardTitle[0].setPosition(785.0f, 400.0f);
    commercialCardTitle[1].setPosition(925.0f, 400.0f);
    commercialCardTitle[2].setPosition(1070.0f, 400.0f);


    sf::Text* commercialCardPrice = new sf::Text[3];

    for (int i = 0; i < 3; i++) {

        commercialCardPrice[i].setFillColor(sf::Color(230, 126, 34));
        commercialCardPrice[i].setFont(stdFont);
        commercialCardPrice[i].setCharacterSize(12);
        commercialCardPrice[i].setString(commercialPropertyPrices[i]);

    }

    commercialCardPrice[0].setPosition(785.0f, commercialCardTitle[0].getPosition().y + 20.0f);
    commercialCardPrice[1].setPosition(925.0f, commercialCardTitle[0].getPosition().y + 20.0f);
    commercialCardPrice[2].setPosition(1070.0f, commercialCardTitle[0].getPosition().y + 20.0f);


    sf::Text* commercialCardRent = new sf::Text[3];
    for (int i = 0; i < 3; i++) {

        commercialCardRent[i].setFillColor(sf::Color(211, 84, 0));
        commercialCardRent[i].setFont(stdFont);
        commercialCardRent[i].setCharacterSize(10);
        commercialCardRent[i].setString(commercialPropertyRents[i]);

    }

    commercialCardRent[0].setPosition(785.0f, commercialCardTitle[0].getPosition().y + 40.0f);
    commercialCardRent[1].setPosition(925.0f, commercialCardTitle[0].getPosition().y + 40.0f);
    commercialCardRent[2].setPosition(1070.0f, commercialCardTitle[0].getPosition().y + 40.0f);


    // Player Cash Text setup


    sf::Text* playerCash = new sf::Text[totalPlayers];
    for (int i = 0; i < totalPlayers; i++) {

        playerCash[i].setFillColor(sf::Color(26, 188, 156));
        playerCash[i].setFont(stdFont);
        playerCash[i].setCharacterSize(11);

        float playerMoney = (float)game.getBoard().getPlayers()[i]->getCash();
        char* playerMoneyChar = new char[10];


        if (playerMoney >= 1000) {

            float flPointPart = (playerMoney / 1000) - (int)(playerMoney / 1000);
            flPointPart *= 100;


            char* flPointPartChar = new char[10];



            _itoa((int)(playerMoney / 1000), playerMoneyChar, 10);
            _itoa((int)(flPointPart), flPointPartChar, 10);

            strcat(playerMoneyChar, ".");
            strcat(playerMoneyChar, flPointPartChar);
            strcat(playerMoneyChar, "K");

            //_itoa_s(playerMoney, playerMoneyChar, 10);

            playerCash[i].setString(playerMoneyChar);

        }
        else {

            _itoa((int)playerMoney, playerMoneyChar, 10);

            playerCash[i].setString(playerMoneyChar);

        }

        playerCash[i].setPosition(735.f + (i * 100.0f), 125.0f);

    }


    // Turn Display Assets

    sf::Text turnText;
    turnText.setFont(stdFont);
    turnText.setFillColor(sf::Color::Black);
    turnText.setCharacterSize(10);
    turnText.setString("TURN");
    turnText.setPosition(141.0f, 460.0f);

    sf::Texture turnDisplayTexture;
    turnDisplayTexture.loadFromFile("assets/turn_display.png");

    sf::RectangleShape turnDisplay(sf::Vector2f(80.0f, 80.f));
    turnDisplay.setPosition(120.0f, 450.0f);
    turnDisplay.setTexture(&turnDisplayTexture);

    sf::Texture turnDisplayPieceTexture;
    turnDisplayPieceTexture.loadFromFile("assets/player1.png");

    sf::RectangleShape turnDisplayPiece(sf::Vector2f(30.0f, 30.0f));
    turnDisplayPiece.setTexture(&turnDisplayPieceTexture);
    turnDisplayPiece.setPosition(142.0f, 480.0f);
    turnDisplayPieceTexture.setSmooth(true);



    // Card Upgrades Assets

    sf::Texture** upgradeIconTexture = new sf::Texture * [3];
    for (int i = 0; i < 3; i++)
        upgradeIconTexture[i] = new sf::Texture[2];

    const char* upgradeIconImg[6] = {

        "assets/wifi.png", "assets/wifi_en.png",
        "assets/elec.png", "assets/elec_en.png",
        "assets/gas.png", "assets/gas_en.png"

    };

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 2; j++) {

            upgradeIconTexture[i][j].loadFromFile(upgradeIconImg[(2 * i) + j]);

        }

    }

    sf::RectangleShape** upgradeIcon = new sf::RectangleShape*[3];
    
    for (int i = 0; i < 3; i++) {

        upgradeIcon[i] = new sf::RectangleShape[3];

        for (int j = 0; j < 3; j++) {

            upgradeIcon[i][j].setTexture(&upgradeIconTexture[j][0]);
            
            
            upgradeIcon[i][j].setSize(sf::Vector2f(13.0f, 15.0f));

        }

    }

    for (int i = 0; i < 3; i++)
        upgradeIcon[0][i].setPosition(785.f + (i * 20), 315.0f);

    for (int i = 0; i < 3; i++)
        upgradeIcon[1][i].setPosition(785.f + (i * 20) + 140, 315.0f);
    
    for (int i = 0; i < 3; i++)
        upgradeIcon[2][i].setPosition(785.f + (i * 20) + 285, 315.0f);


    {
        PrivateProperty* propertyCell = (PrivateProperty*)game.getBoard().getCells()[privatePropertySpaces[5]];

        propertyCell->setHasGas(true);
        propertyCell->setHasElectricity(true);
        propertyCell->setHasWifi(true);

    }

    while (window.isOpen()) {

        sf::Event evt;
        while (window.pollEvent(evt)) {
        

            if (evt.type == evt.Closed) {
            
                // game.saveGame(0);
                window.close();

            }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                sf::FloatRect cameraButtonBounds = cameraButton.getGlobalBounds();
                sf::FloatRect diceButtonBounds = diceButton.getGlobalBounds();

                sf::FloatRect navBtnLeftBounds = navButton[0].getGlobalBounds();
                sf::FloatRect navBtnRightBounds = navButton[1].getGlobalBounds();

                sf::FloatRect commercialNavBtnLeftBounds = commercialNavButton[0].getGlobalBounds();
                sf::FloatRect commercialNavBtnRightBounds = commercialNavButton[1].getGlobalBounds();


                // Screenshot function

                if (cameraButtonBounds.contains(mousePos)) {


                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    texture.copyToImage().saveToFile("screenshot.png");


                }

                if (diceButtonBounds.contains(mousePos)) {

                    clk.restart();
                    diceAnim = true;

                    game.playDice(window, dice, diceTexture);


                }


                if (navBtnLeftBounds.contains(mousePos)) {

                    if (privatePropertyCardScroll) {

                        privatePropertyCardScroll--;

                    }

                }

                if (navBtnRightBounds.contains(mousePos)) {

                    if (privatePropertyCardScroll < 17) {

                        privatePropertyCardScroll++;

                    }


                }

                if (commercialNavBtnLeftBounds.contains(mousePos)) {

                    if (commercialPropertyCardScroll) {

                        commercialPropertyCardScroll--;

                    }

                }

                if (commercialNavBtnRightBounds.contains(mousePos)) {

                    if (commercialPropertyCardScroll < 5) {

                        commercialPropertyCardScroll++;

                    }


                }


                int currTurnOnBoard = game.getBoard().getTurn();
                turnDisplayPieceTexture.loadFromFile(playerPieceFileName[currTurnOnBoard]);



                // game.updatePositions();


            }

            if (evt.type == sf::Event::MouseWheelScrolled) {

                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                sf::FloatRect cardBound = cardPanel.getGlobalBounds();
                sf::FloatRect commercialCardBound = commercialCardPanel.getGlobalBounds();

                if (evt.mouseWheelScroll.delta > 0) // moving up
                {
                    if (privatePropertyCardScroll && cardBound.contains(mousePos)) {

                        privatePropertyCardScroll--;

                    }

                    if (commercialPropertyCardScroll && commercialCardBound.contains(mousePos)) {

                        commercialPropertyCardScroll--;

                    }

                }
                else if (evt.mouseWheelScroll.delta < 0) // moving down
                {

                    if (privatePropertyCardScroll < 17 && cardBound.contains(mousePos)) {

                        privatePropertyCardScroll++;

                    }

                    if (commercialPropertyCardScroll < 5 && commercialCardBound.contains(mousePos)) {

                        commercialPropertyCardScroll++;

                    }


                }

            }


        }

        window.draw(gameScreen);
        window.draw(cameraButton);
        window.draw(diceButton);
        window.draw(cardPanel);
        window.draw(commercialCardPanel);
        window.draw(turnDisplay);
        window.draw(turnText);
        window.draw(turnDisplayPiece);
        



        // Prints card texts

        for (int i = 0; i < 3; i++) {

            cardTitle[i].setString(privatePropertyNames[i + privatePropertyCardScroll]);
            cardPrice[i].setString(privatePropertyPrices[i + privatePropertyCardScroll]);
            cardRent[i].setString(privatePropertyRents[i + privatePropertyCardScroll]);

            commercialCardTitle[i].setString(commercialPropertyNames[i + commercialPropertyCardScroll]);
            commercialCardPrice[i].setString(commercialPropertyPrices[i + commercialPropertyCardScroll]);
            commercialCardRent[i].setString(commercialPropertyRents[i + commercialPropertyCardScroll]);

            window.draw(cardTitle[i]);
            window.draw(cardPrice[i]);
            window.draw(cardRent[i]);
            

            window.draw(commercialCardTitle[i]);
            window.draw(commercialCardPrice[i]);
            window.draw(commercialCardRent[i]);


            // enable switching based on connection
            for (int j = 0; j < 3; j++) {

                PrivateProperty* propertyCell = (PrivateProperty*)game.getBoard().getCells()[privatePropertySpaces[i + privatePropertyCardScroll]];

                upgradeIcon[i][0].setTexture(&upgradeIconTexture[j][propertyCell->getHasWifi()]);
                upgradeIcon[i][1].setTexture(&upgradeIconTexture[j][propertyCell->getHasElectricity()]);
                upgradeIcon[i][2].setTexture(&upgradeIconTexture[j][propertyCell->getHasGas()]);

                window.draw(upgradeIcon[i][j]);
            
            }

        }


        // Prints all the player icons on the screen
        for (int i = 0; i < totalPlayers; i++) {
            window.draw(playerIcon[i]);
            window.draw(playerCash[i]);
        }

        // Prints the dices on the board

        if (clk.getElapsedTime().asMilliseconds() < animInt.asMilliseconds() && diceAnim) {

            diceTexture[0].loadFromFile(diceTextureImg[rand() % 6]);
            diceTexture[1].loadFromFile(diceTextureImg[rand() % 6]);

        }
        else {
            
            diceAnim = false;
            clk.restart();
            game.updateDiceTextures(diceTexture);

        }


        for (int i = 0; i < 2; i++) {
            window.draw(dice[i]);
            window.draw(navButton[i]);
            window.draw(commercialNavButton[i]);
        }

        // Prints players when the dice animation
        // is going on.

        for (int i = 0; i < totalPlayers && diceAnim; i++) {

            game.printPlayerOnCell(window, playerPieces[i],
                playerPrevPos[i], i);

        }

        // Prints all the player pieces on the board
        // after the dice has been rolled completely
        for (int i = 0; i < totalPlayers && !diceAnim; i++) {

            game.printPlayerOnCell(window, playerPieces[i],
                game.getPlayerPosition(i), i);


            playerPrevPos[i] = game.getPlayerPosition(i);

        }

        window.display();


    }

    delete[] playerPrevPos;


    return 0;
}