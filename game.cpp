#include "game.hh"

using namespace std;

void Game::displayGame()
{
    cout << endl;
    int tmp = sqrt(size); // zwraca wymiar szerokosci tarczy

    for (int i = 0; i < size; i++)
    {

        cout << "  " << table[i] << "  "; 
        if ((i + 1) % tmp == 0 && (i + 1) != 1 && (i + 1) != size)
        {
            cout << endl;
            for (int j = 0; j < tmp - 1; j++)
            {
                cout << "_____.";
            }
            cout << "_____" << endl;
        }
        else if ((i + 1) % tmp != 0)
        {
            cout << "|";
        }
    }

    cout << endl;
}

bool Game::checkWinVertical(char symbol)
{
    int size = getSize();
    int win = sqrt(size); // jak tyle takich samych znakow w kolumnie to wygrana
    int tmp;     // liczy liczbe powtorzen symbolu

    for (int i = 0; i < win; i++)
    {
        tmp = 0;
        for (int j = i; j < size; j = j + win)
        {
            if ((j + win < size))
            {
                if (table[j] == symbol && table[j + win] == symbol)
                {
                    tmp++;
                }
                if (tmp == (win - 1))
                    break;
            }
        }
        if (tmp == (win - 1))
            break;
    }
    if (tmp == (win - 1))
        return true;

    return false;
}

bool Game::checkWinHorizontal(char symbol)
{
    int size = getSize();
    int win = sqrt(size); // jak tyle takich samych znakow w wierszu to wygrana
    int tmp;    // liczy liczbe powtorzen symbolu

    for (int i = 0; i < size; i = i + win)
    {
        tmp = 0;
        for (int j = i; j < i + win; j++)
        {
            if ((j + 1) < (i + win))
            {
                if (table[j] == symbol && table[j + 1] == symbol)
                {
                    tmp++;
                }
                if (tmp == (win - 1))
                    break;
            }
        }
        if (tmp == (win - 1))
            break;
    }

    if (tmp == (win - 1))
        return true;

    return false;
}

bool Game::checkWinDiagonal1(char symbol)
{
    int size = getSize();
    int win = sqrt(size); // jak tyle takich samych znakow po przekatnej to wygrana
    int tmp = 0;   // liczy liczbe powtorzen symbolu

    for (int i = 0; i < size; i = i + win + 1)
    {
        if ((i + win + 1) < size)
        {
            if (table[i] == symbol && table[i + win + 1] == symbol)
            {
                tmp++;
            }
            if (tmp == (win - 1))
                break;
        }
    }

    if (tmp == (win - 1))
        return true;

    return false;
}

bool Game::checkWinDiagonal2(char symbol)
{
    int size = getSize();
    int win = sqrt(size); // jak tyle takich samych znakow po przekatnej to wygrana
    int tmp = 0;   // liczy liczbe powtorzen symbolu

    for (int i = win - 1; i < size; i = i + win - 1)
    {
        if ((i + win - 1) < (size - 1) || (i + win - 1) == 0)
        {
            if (table[i] == symbol && table[i + (win - 1)] == symbol)
            {
                tmp++;

                if (tmp == (win - 1))
                    break;
            }
        }
    }

    if (tmp == (win - 1))
        return true;

    return false;
}

bool Game::win(char symbol)
{
    if (checkWinDiagonal1(symbol))
        return true;

    if (checkWinDiagonal2(symbol))
        return true;

    if (checkWinHorizontal(symbol))
        return true;

    if (checkWinVertical(symbol))
        return true;

    return false;
}

bool Game::endWithoutWin()
{
    int size = getSize();
    int tmp = 0;

    for (int i = 0; i < size; i++)
    {
        if (table[i] != ' ')
            tmp++;
    }

    if (tmp == size)
        return true;
   
    return false;
}

void Game::gameUser(char symbol_user)
{
    int position;
    cout << " TWOJ SYMBOL: " << symbol_user <<" . PODAJ POLE GDZIE WSTAWIC " << symbol_user <<" ?" ;
    cin >> position;
    position--;

    if (checkPosition(position))
        setPosition(position, symbol_user);
    else
    {
        while (true)
        {
            cout << "Pole jest zajete, podaj inne pole: ";
            cin >> position;
            position--;
            if (checkPosition(position))
            {
                setPosition(position, symbol_user);
                break;
            }
        }
    }
}

int Game::minMax(char user, char AI, int depth, bool player_AI, int alpha, int beta)
{
    /* Zasady algorytmu MinMax:
    - AI (komputer) wygrywa zwraca liczbe dodatnia
    - AI (komputer) przegrywa zwraca liczbe ujemna
    - remis zwraca 0 */

    if (win(AI)) // gdy AI wygrywa zwraca 1
        return 1;

    if (win(user)) // gdy AI przegra, czyli wygra gracz zwraca -1
        return -1;

    if (endWithoutWin()) // w przypadku remisu zwraca 0
        return 0;

    if (size < 20) // jesli wielkosc tarczy mniejsza niz 20 to maksymalna glebokosc rekurencji wynosi 10
    {
        if (depth == 10)
            return 0;
    }
    else // w przypadku innej wielkosci tarczy maksymalna glebokosc rekurencji wynosi 5
    {
        if (depth == 5)
        {
            return 0;
        }
    }

    if (player_AI == true)
    {
        int best = (-1) * _infinity;
        for (int i = 0; i < size; i++)
        {
            if (table[i] == ' ')
            {
                table[i] = AI;
                int value = minMax(user, AI, depth + 1, false, alpha, beta);
                table[i] = ' ';
                best = max(best, value);
                alpha=max(alpha,value);
                if(beta<=alpha) break;
            }
        }
        return best;
    }
    else
    {

        int best = _infinity;
        for (int i = 0; i < size; i++) 
        {
            if (table[i] == ' ')
            {
                table[i] = user;
                int value = minMax(user, AI, depth + 1,true, alpha, beta);
                table[i] = ' ';
                best = min(best, value);
                beta=min(beta,value);
                if(beta<=alpha) break;
            }
        }
        return best;
    }
}

void Game::gameAI(char user, char symbol_AI)
{
    int value = (-1)*_infinity;
    int best_AI = 0;  // najlepszy ruch dla AI

    for (int i = 0; i < size; i++)
    {
        if (table[i] == ' ')
        {
            table[i] = symbol_AI;
            int min_max = minMax(user, symbol_AI, 0, false, _alpha, _beta); // false bo nastepny ruch ma przeciwnik
            table[i] = ' ';
            if (min_max > value)
            {
                value = min_max;
                best_AI = i;
            }
        }
    }

    setPosition(best_AI,symbol_AI);

}
