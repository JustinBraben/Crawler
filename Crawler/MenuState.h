#pragma once
#include "GameState.h"

class MenuState : public GameState {
public:
    void init() override {
        if (!m_font.loadFromFile("assets/arial.ttf")) {
            // Handle the error
        }

        m_gameStartButton.setFont(m_font);
        m_gameStartButton.setString("Start Game");
        m_gameStartButton.setCharacterSize(24);
        m_gameStartButton.setFillColor(sf::Color::White);

        // Center the text on the screen
        sf::FloatRect textBounds = m_gameStartButton.getLocalBounds();
        m_gameStartButton.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        m_gameStartButton.setPosition(sf::Vector2f(400, 300)); // Assuming a window size of 800x600
    };
    void handleInput(sf::Event event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window); // Assuming you have access to the window object
                sf::FloatRect textBounds = m_gameStartButton.getGlobalBounds();

                if (textBounds.contains(sf::Vector2f(mousePosition))) {
                    // Handle state change here, e.g., change to the main game state
                    // You might need to access the Game instance from here to call its state management methods.
                }
            }
        }
    };
    void update(float dt) override;
    void render() override {
        m_window->draw(m_gameStartButton);
    };

private:
    sf::Text m_gameStartButton;
    sf::Font m_font;
};

