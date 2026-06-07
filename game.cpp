//Number Guesser Game
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0)); // seed random number generator

    cout << "Number Guesser Game:" << endl;
    int answer = rand() % 100 + 1; // random number between 1-100
    int numberEntered;

    cout << "Type a number: ";
    cin >> numberEntered;

    if (numberEntered == answer){
        cout << "You have guessed correctly!" << endl;
    } else {
        cout << "Incorrect! The answer was " << answer << endl;
    }

    return 0;
}