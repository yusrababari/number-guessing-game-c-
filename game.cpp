#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Function to clear invalid input
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Difficulty settings
void setDifficulty(int &maxNumber, int &maxAttempts, int choice) {
    switch(choice) {
        case 1:
            maxNumber = 50;
            maxAttempts = 10;
            break;

        case 2:
            maxNumber = 100;
            maxAttempts = 7;
            break;

        case 3:
            maxNumber = 500;
            maxAttempts = 5;
            break;

        default:
            maxNumber = 100;
            maxAttempts = 7;
    }
}

int main() {

    srand(time(0));

    char playAgain = 'y';

    cout << "==============================" << endl;
    cout << "     NUMBER GUESSER GAME      " << endl;
    cout << "==============================" << endl;

    int bestScore = 9999;

    while(playAgain == 'y' || playAgain == 'Y') {

        int difficulty;
        int maxNumber;
        int maxAttempts;

        cout << "\nChoose Difficulty:" << endl;
        cout << "1. Easy   (1 - 50, 10 attempts)" << endl;
        cout << "2. Medium (1 - 100, 7 attempts)" << endl;
        cout << "3. Hard   (1 - 500, 5 attempts)" << endl;
        cout << "Choice: ";

        cin >> difficulty;

        if(cin.fail()) {
            clearInput();
            cout << "Invalid input!" << endl;
            continue;
        }

        setDifficulty(maxNumber, maxAttempts, difficulty);

        int answer = rand() % maxNumber + 1;
        int guess;
        bool guessedCorrectly = false;

        cout << "\nI picked a number between 1 and "
             << maxNumber << "!" << endl;

        for(int attempt = 1; attempt <= maxAttempts; attempt++) {

            cout << "\nAttempt "
                 << attempt
                 << "/"
                 << maxAttempts
                 << endl;

            cout << "Enter your guess: ";
            cin >> guess;

            if(cin.fail()) {
                clearInput();
                cout << "Please enter a valid number!" << endl;
                attempt--;
                continue;
            }

            if(guess < 1 || guess > maxNumber) {
                cout << "Number out of range!" << endl;
                attempt--;
                continue;
            }

            // Correct guess
            if(guess == answer) {

                cout << "\nCorrect! You guessed the number!" << endl;

                guessedCorrectly = true;

                // Score system
                int score = (maxAttempts - attempt + 1) * 100;

                cout << "Your score: " << score << endl;

                if(attempt < bestScore) {
                    bestScore = attempt;
                    cout << "NEW BEST SCORE!" << endl;
                }

                cout << "Best score: "
                     << bestScore
                     << " attempts" << endl;

                break;
            }

            // Hint system
            int difference = abs(guess - answer);

            if(guess < answer) {

                if(difference <= 5)
                    cout << "Very close! Try HIGHER!" << endl;

                else if(difference <= 15)
                    cout << "Warm... go HIGHER!" << endl;

                else
                    cout << "Cold! Much HIGHER!" << endl;

            } else {

                if(difference <= 5)
                    cout << "Very close! Try LOWER!" << endl;

                else if(difference <= 15)
                    cout << "Warm... go LOWER!" << endl;

                else
                    cout << "Cold! Much LOWER!" << endl;
            }

            // Attempts left
            cout << "Attempts remaining: "
                 << maxAttempts - attempt
                 << endl;
        }

        // Lost game
        if(!guessedCorrectly) {
            cout << "\nGame Over!" << endl;
            cout << "The correct answer was: "
                 << answer
                 << endl;
        }

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
    }

    cout << "\nThanks for playing!" << endl;

    return 0;
}