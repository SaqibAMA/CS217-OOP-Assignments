#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


int main()
{
    
    // Creating an SFML window
    sf::RenderWindow window(sf::VideoMode(1280, 720),
        "Monopoly by Saqib, Nabeel, Abdur Rehman, & Salman",
        sf::Style::Close | sf::Style::Resize);


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
        
            if(evt.type == evt.Closed) {

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


    if (choice == 1) {
    

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


    }



    return 0;
}