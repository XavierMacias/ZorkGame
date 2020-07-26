// main.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "world.h";

using namespace std;

vector<string> splitString(string str)
{
    vector<string> words;
    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    words.push_back(word);
    return words;
}

int main()
{
    string instruction;

    World* world = new World();

    cout << "Welcome to Zork! This is a fantastic adventure. Use the command 'help' if you don't know how to play.\n";
    cout << "Use the command 'exit' to exit the game.\n";
    cout << "-----------------------------------------------\n";
    world->LookInitialMap();

    while (1) {
        getline(cin, instruction);
        if (instruction == "exit") {
            break;
        }
        vector<string> words = splitString(instruction);
        if (!world->CheckInstruction(words)) {
            cout << "I don't understand you\n";
        }
    }

    cout << "See you!";
    return 0;
}
