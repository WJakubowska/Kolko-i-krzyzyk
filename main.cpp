#include <iostream>

#include "game.hh"

using namespace std;

int sizeGame()
{
  int size_x, size_y;
  for (;;)
  {
    cout << " Podaj rozmiar pola ( kwadratowego ) w formacie liczba x liczba (na przyklad 3x3):  " << endl;
    cin >> size_x;
    cout << " x " << endl;
    cin >> size_y;
    if (size_x != 1 || size_y != 1)
      break;
    cout << "Rozmiar nie moze byc 1. Podaj wiekszy rozmiar planszy. " << endl;
  }

  while (size_x != size_y)
  {
    for (;;)
    {
      cout << " Podano inny niz kwadratowy rozmiar pola. Podaj JESZCZE RAZ rozmiar pola ( kwadratowego ) w formacie  liczba x liczba:   " << endl;
      cin >> size_x;
      cout << "x" << endl;
      cin >> size_y;
      if (size_x != 1 && size_y != 1)
        break;
      cout << "Rozmiar nie moze byc 1. Podaj wiekszy rozmiar planszy. " << endl;
    }
  }

  return size_x * size_y;
}

int main()
{
  char symbol_user;
  char symbol_AI;
  int size = 0;
  

  cout << "   GRA W KOLKO I KRZYZYK  " << endl;
  size = sizeGame();
  
  cout << "   Zasady gry:        " << endl;
  cout << "1) Pola sa numerowe od 1. Pole 1 jest w lewym gornym rogu." << endl;
  cout << "2) Ruchy wykonuja na przemian gracz i komputer." << endl;
  cout << "3) Wygrywa gracz ktory pierwszy zdobedzie wszystkie takie same znaki" << endl;
  cout << "   w pionie, poziomie lub po przekatnej " << endl;

  cout << "WPISZ X GDY CHCESZ GRAC JAKO X, WPISZ O GDY CHCESZ GRAC JAKO 0 : " << endl;
  cin >> symbol_user;
  while (symbol_user != 'X' && symbol_user != 'O')
  {
    cout << " Podano bledny znak, podaj jeszcze raz X lub O :";
    cin >> symbol_user;
    if (symbol_user == 'X' || symbol_user == 'O')
      break;
  }

  if (symbol_user == 'X')
    symbol_AI = 'O';
  else
    symbol_AI = 'X';

  Game game(size);
  game.setSize(size);
  game.displayGame();

  // najpierw ruch wykonuje użytkownik

  while (true)
  {

    game.gameUser(symbol_user);
    game.displayGame();

    if (game.win(symbol_user))
    {
      cout << " WYGRALES !!!!!!! GRATULACJE " << endl;
      break;
    }

    if (game.endWithoutWin())
    {
      cout << " NIE MOZNA ROZSTRZYGNAC WYGRANEJ " << endl;
      break;
    }

    cout << endl;
    cout << "RUCH PRZECIWNIKA :" << endl;

    game.gameAI(symbol_user, symbol_AI);
    game.displayGame();

    if (game.win(symbol_AI))
    {
      cout << " PRZEGRALES :( . WYGRAL: " << symbol_AI << endl;
      break;
    }

    if (game.endWithoutWin())
    {
      cout << " NIE MOZNA ROZSTRZYGNAC WYGRANEJ " << endl;
      break;
    }
  }

  return 0;
}