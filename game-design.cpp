#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(480, 520), "Number Guesser");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    // Game state
    int answer = rand() % 100 + 1;
    int attempts = 0;
    int maxAttempts = 10;
    int bestScore = 999;
    std::string inputText = "";
    std::string hintText = "Guess a number between 1 and 100!";
    sf::Color hintColor = sf::Color(126, 232, 162);
    bool gameOver = false;
    bool won = false;

    // --- UI Elements ---

    // Background
    sf::RectangleShape bg(sf::Vector2f(480, 520));
    bg.setFillColor(sf::Color(26, 26, 46));

    // Title
    sf::Text title("NUMBER GUESSER", font, 24);
    title.setFillColor(sf::Color(224, 224, 255));
    title.setPosition(480/2 - title.getLocalBounds().width/2, 30);

    sf::Text subtitle("Guess the number between 1 and 100", font, 13);
    subtitle.setFillColor(sf::Color(123, 123, 157));
    subtitle.setPosition(480/2 - subtitle.getLocalBounds().width/2, 65);

    // Attempts box
    sf::RectangleShape attBox(sf::Vector2f(120, 60));
    attBox.setFillColor(sf::Color(22, 33, 62));
    attBox.setOutlineColor(sf::Color(80, 80, 80));
    attBox.setOutlineThickness(1);
    attBox.setPosition(80, 110);

    sf::Text attLabel("ATTEMPTS", font, 11);
    attLabel.setFillColor(sf::Color(123, 123, 157));
    attLabel.setPosition(88, 118);

    sf::Text attValue("0 / 10", font, 20);
    attValue.setFillColor(sf::Color(167, 139, 250));
    attValue.setPosition(88, 138);

    // Best score box
    sf::RectangleShape bestBox(sf::Vector2f(120, 60));
    bestBox.setFillColor(sf::Color(22, 33, 62));
    bestBox.setOutlineColor(sf::Color(80, 80, 80));
    bestBox.setOutlineThickness(1);
    bestBox.setPosition(280, 110);

    sf::Text bestLabel("BEST", font, 11);
    bestLabel.setFillColor(sf::Color(123, 123, 157));
    bestLabel.setPosition(288, 118);

    sf::Text bestValue("---", font, 20);
    bestValue.setFillColor(sf::Color(167, 139, 250));
    bestValue.setPosition(288, 138);

    // Hint box
    sf::RectangleShape hintBox(sf::Vector2f(360, 50));
    hintBox.setFillColor(sf::Color(22, 33, 62));
    hintBox.setOutlineColor(sf::Color(61, 61, 107));
    hintBox.setOutlineThickness(1);
    hintBox.setPosition(60, 200);

    sf::Text hint(hintText, font, 13);
    hint.setFillColor(hintColor);
    hint.setPosition(70, 220);

    // Input box
    sf::RectangleShape inputBox(sf::Vector2f(160, 44));
    inputBox.setFillColor(sf::Color(22, 33, 62));
    inputBox.setOutlineColor(sf::Color(79, 79, 143));
    inputBox.setOutlineThickness(1);
    inputBox.setPosition(80, 285);

    sf::Text inputDisplay("", font, 20);
    inputDisplay.setFillColor(sf::Color(224, 224, 255));
    inputDisplay.setPosition(92, 295);

    // Guess button
    sf::RectangleShape guessBtn(sf::Vector2f(120, 44));
    guessBtn.setFillColor(sf::Color(91, 79, 207));
    guessBtn.setPosition(260, 285);

    sf::Text guessBtnText("GUESS", font, 14);
    guessBtnText.setFillColor(sf::Color::White);
    guessBtnText.setPosition(285, 298);

    // Progress bar
    sf::RectangleShape progressBg(sf::Vector2f(360, 8));
    progressBg.setFillColor(sf::Color(22, 33, 62));
    progressBg.setPosition(60, 365);

    sf::RectangleShape progressFill(sf::Vector2f(0, 8));
    progressFill.setFillColor(sf::Color(91, 79, 207));
    progressFill.setPosition(60, 365);

    // Play again button (hidden until game over)
    sf::RectangleShape replayBtn(sf::Vector2f(180, 44));
    replayBtn.setFillColor(sf::Color(91, 79, 207));
    replayBtn.setPosition(150, 430);

    sf::Text replayText("PLAY AGAIN", font, 14);
    replayText.setFillColor(sf::Color::White);
    replayText.setPosition(175, 443);

    auto updateHint = [&](int guess) {
        int diff = abs(guess - answer);
        if (guess == answer) {
            hintText = "Correct! You got it!";
            hintColor = sf::Color(167, 139, 250);
            won = true;
            gameOver = true;
            if (attempts < bestScore) bestScore = attempts;
            bestValue.setString(std::to_string(bestScore));
        } else if (diff <= 5) {
            hintText = guess < answer ? "So close! Go higher!" : "So close! Go lower!";
            hintColor = sf::Color(239, 68, 68);
        } else if (diff <= 15) {
            hintText = guess < answer ? "Warm! Try higher." : "Warm! Try lower.";
            hintColor = sf::Color(251, 191, 36);
        } else {
            hintText = guess < answer ? "Cold. Go much higher." : "Cold. Go much lower.";
            hintColor = sf::Color(126, 232, 162);
        }
        if (attempts >= maxAttempts && !won) {
            hintText = "Game over! Answer: " + std::to_string(answer);
            hintColor = sf::Color(239, 68, 68);
            gameOver = true;
        }
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (!gameOver) {
                if (event.type == sf::Event::TextEntered) {
                    char c = static_cast<char>(event.text.unicode);
                    if (isdigit(c) && inputText.size() < 3)
                        inputText += c;
                    else if (event.text.unicode == 8 && !inputText.empty())
                        inputText.pop_back();
                    else if (event.text.unicode == 13 && !inputText.empty()) {
                        int guess = std::stoi(inputText);
                        attempts++;
                        attValue.setString(std::to_string(attempts) + " / 10");
                        float fillW = (float)attempts / maxAttempts * 360;
                        progressFill.setSize(sf::Vector2f(fillW, 8));
                        updateHint(guess);
                        inputText = "";
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mp = sf::Mouse::getPosition(window);
                    if (guessBtn.getGlobalBounds().contains(mp.x, mp.y) && !inputText.empty()) {
                        int guess = std::stoi(inputText);
                        attempts++;
                        attValue.setString(std::to_string(attempts) + " / 10");
                        float fillW = (float)attempts / maxAttempts * 360;
                        progressFill.setSize(sf::Vector2f(fillW, 8));
                        updateHint(guess);
                        inputText = "";
                    }
                }
            } else {
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mp = sf::Mouse::getPosition(window);
                    if (replayBtn.getGlobalBounds().contains(mp.x, mp.y)) {
                        answer = rand() % 100 + 1;
                        attempts = 0;
                        inputText = "";
                        hintText = "Guess a number between 1 and 100!";
                        hintColor = sf::Color(126, 232, 162);
                        attValue.setString("0 / 10");
                        progressFill.setSize(sf::Vector2f(0, 8));
                        gameOver = false;
                        won = false;
                    }
                }
            }
        }

        hint.setString(hintText);
        hint.setFillColor(hintColor);
        hint.setPosition(480/2 - hint.getLocalBounds().width/2, 220);
        inputDisplay.setString(inputText);

        window.clear();
        window.draw(bg);
        window.draw(title);
        window.draw(subtitle);
        window.draw(attBox);
        window.draw(attLabel);
        window.draw(attValue);
        window.draw(bestBox);
        window.draw(bestLabel);
        window.draw(bestValue);
        window.draw(hintBox);
        window.draw(hint);
        window.draw(inputBox);
        window.draw(inputDisplay);
        window.draw(guessBtn);
        window.draw(guessBtnText);
        window.draw(progressBg);
        window.draw(progressFill);
        if (gameOver) {
            window.draw(replayBtn);
            window.draw(replayText);
        }
        window.display();
    }
    return 0;
}