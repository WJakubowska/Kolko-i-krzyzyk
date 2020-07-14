#pragma once
#include <cmath>
#include <iostream>
#include <vector>

const int _alpha = -2147483647;  // alpha to -nieskonczonsc
const int _beta = 2147483647; // beta to nieskonczonosc
const int _infinity = 2147483647; // nieskonczonosc

class Game
{
private:
    std::vector<char> table; // vector przechpwujacy X i O 
    int size; // rozmiar pola gry 

public:
    void setSize(int set_size) { size = set_size; } // ustawia rozmiar pola gry
    int getSize() { return size; } // zwraca rozmiar pola gra
    void displayGame(); // wyswietla pole gry
    void setPosition(int index, char symbol) { table[index] = symbol; } // ustawia na wyznaczona pozycje w polu gry odpowiedni symbol
    bool checkPosition(int index) // sprawdza czy na wyznaczonej pozycji w polu gry jest puste miejsce
    {
        if (table[index] == ' ')
            return true;
        return false;
    }
    bool checkWinVertical(char symbol);   //sprawdza czy wystapila wygrana w kolumnie
    bool checkWinDiagonal1(char symbol);  //sprawdza czy wystapila wygrana po jednej z przekatnych
    bool checkWinDiagonal2(char symbol);  //sprawdza czy wystapila wygrana po drugiej z przekatnych
    bool checkWinHorizontal(char symbol); //sprawdza czy wystapila wygrana w wierszu 
    bool win(char symbol);  // sprawdza czy w programie wystapila jakakolwiek wygrana
    bool endWithoutWin(); // sprawdza remis (jesli nie ma wygranej ani zadne pole nie jest puste zwraca true)
    void gameUser(char symbol_user); // odpowiada za ruch gracza w grze
    void gameAI(char user, char symbol_AI); // odpowiada za ruch AI (komputera) w grze
    int minMax(char user, char AI, int depth, bool player_AI, int alpha, int beta); // implementacja algorytmu minimax wraz z cieciami beta i alpha

    Game(int set_size) // konstuktor tworzacy gre, nadajacy jej rozmiar i wypelniajacy jej pole pustymi miejscami
    {
        table.reserve(set_size);
        size = set_size;
        for (int i = 0; i < size; i++)
        {
            table[i] = ' ';
        }
    }
    ~Game() 
    {
        table.clear();
    };
};
