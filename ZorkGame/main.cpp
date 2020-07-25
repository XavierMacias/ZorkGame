// main.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

using namespace std;

int main()
{
    string instruction;

    cout << "Welcome to Zork! This is a fantastic adventure.\n";
    cout << "-----------------------------------------------\n";

    while (instruction != "exit") {
        cin >> instruction;
    }

    cout << "See you!";
    return 0;
}
