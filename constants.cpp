#include <iostream>
#include <string>

using namespace std;
// costanti per labirinto
const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;

const int STARTX = 1;
const int STARTY = 1;

char PLAYER = '@';
const string HORI1 = "+---+---+---+---+---+---+---+---+---+---+---+";  // IMPORTANTE!!! --> Controllare che non ci siano spazi vuoti in fondo a queste stringhe
const string HORI2 = "|   |   |   |   |   |   |   |   |   |   |   |";

const char HORIZONTAL = 'o';
const char VERTICAL = 'v';

const int DIM = 11;

// costanti per grafiche e gestione menu

const char EXIT = '0';
const char FIRSTOPTION = '1';
const char SECONDOPTION = '2';
const char THIRDOPTION = '3';

