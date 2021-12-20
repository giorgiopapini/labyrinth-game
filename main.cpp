#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <chrono>
#include "constants.cpp"

// DA AGDOWNNGERE: 
// (2) Miglioramenti grafici
// (3) Fare in modo che ogni 10 livelli (ad esempio) vengano aumentate le dimensioni del labirinto di 1 --> qundi (h = h + 1) e (b = b + 1)

using namespace std;

class Labirinto {
	public:
		string playerName;
		string lab[DIM];
		char parz = ' ';
		int x = STARTX;
		int y = STARTY;
		int level;
		
		void startGame() {
			auto start = std::chrono::high_resolution_clock::now();
			this->level ++;
			this->createLabStd();
			this->createRoad();
			this->x = STARTX;
			this->y = STARTY;
			this->lab[this->y][this->x] = PLAYER;
			while (true) {
				this->printLab();
				if (this->getEndLine(PLAYER) == true) {break;}
				int dim;
				switch (dim = getch()) {
					case UP:
						if (this->checkMotion(this->y - 1, this->lab[this->y - 1][this->x], VERTICAL) == true) {
							this->lab[this->y][this->x] = parz;
							this->parz = this->lab[this->y - 1][this->x];
							this->y --;
						}
						break;
					case DOWN:
						if (this->checkMotion(this->y + 1, this->lab[this->y + 1][this->x], VERTICAL) == true) {
							this->lab[this->y][this->x] = parz;
							this->parz = this->lab[this->y + 1][this->x];
							this->y ++;
						}
						break;
						
					case LEFT:
						if (this->checkMotion(this->x - 1, this->lab[this->y][this->x - 1], HORIZONTAL) == true) {
							this->lab[this->y][this->x] = parz;
							this->parz = this->lab[this->y][this->x - 1];
							this->x --;
						}
						break;
					
					case RIGHT:
						if (this->checkMotion(this->x + 1, this->lab[this->y][this->x + 1], HORIZONTAL) == true) { 
							this->lab[this->y][this->x] = parz;
							this->parz = this->lab[this->y][this->x + 1];
							this->x ++;
						}
						break;
				}
				this->lab[this->y][this->x] = PLAYER;
			}
			auto finish = std::chrono::high_resolution_clock::now();
			chrono::duration<double> delta = finish - start;
			this->levelCompleted(delta);
		}

		void createRoad() {
			int xDelta = 3;  // Le - sono 3 da rimuovere, quindi deve esserci un ciclo che le rimuove tutte e 3
			bool done;
			while (done == false) {
				int dir = rand() % 3;
				switch(dir) { // IMPORTANTE!!! --> Verificare che il codice funzioni correttamente in tutte le direzioni, forse non va a sinistra e in UP?
					case 0:
						// UP
						if (this->checkRemoval(this->y - 2, VERTICAL)) {  // IMPORTANTE!!! --> Capire come rendere meno ridondante il codice all'interno dello switch
							for (int i = 0; i < 3; i ++) {
								this->lab[this->y - 1][this->x + i] = ' ';
							}
							this->y -= 2;
						}
						break;
					case 1:
						// DOWN
						if (this->checkRemoval(this->y + 2, VERTICAL)) {
							for (int i = 0; i < 3; i ++) {
								this->lab[this->y + 1][this->x + i] = ' ';
							}
							this->y += 2;
						}
						break;
					case 2:
						// RIGHT
						if (this->checkRemoval(this->x + xDelta, HORIZONTAL)) {
							for (int i = 0; i < 3; i ++) {
								this->lab[this->y][this->x + i + xDelta] = ' ';
							}
							this->x += xDelta + 1;  // Sistemare questa variabile in modo da renderla meno hardwritten
						}
						break;
					case 3:
						// LEFT
						/*
						if (this->checkRemoval(this->x - xDelta, HORIZONTAL)) {
							for (int i = 0; i < 3; i ++) {
								this->lab[this->y][this->x - i - xDelta] = ' ';
							}
							this->x -= xDelta - 1;  // sistemare questa variabile
							//done = true;  // IMPORTANTE!!! --> Rimuovere il done da qui
						}
						*/
						break;
				}
				done = this->getEndLine(' ');
			}
		}
		
		void setPlayer() {
			system("cls");
			cout << endl << "====================== Set your avatar ======================" << endl << endl;
			cout << "- Insert a character as your active avatar (current avatar = " << PLAYER << "): ";
			cin >> PLAYER;
		}
	
	private:
	
		bool getEndLine(char param) {
			for (int i = 0; i < DIM; i ++) {
				if (this->lab[i].back() == param) {
					return true;
				}
			}
			return false;
		}
		
		void createLabStd() {
			this->x = STARTX;
			this->y = STARTY;
			for (int i = 0; i < DIM; i ++) {
				if ((i % 2) == 0) {
					this->lab[i] = HORI1;
				}
				else {
					this->lab[i] = HORI2;
				}
			}
		}
		
		void printLab() {
			system("cls");
			cout << endl << "====================== " << this->level << char(248) << " LEVEL ======================" << endl << endl;
			for (int i = 0; i < DIM; i ++) {
				cout << this->lab[i] << endl;
			}
		}
		
		int ottieniLunghezza(char ori) {
			if (ori == HORIZONTAL) {
				return HORI1.length();
			}
			else {
				return DIM - 1;  // Dato che DIM uguale ad altezza del labirinto (n di righe orizzontali) 
			}
		}
		
		bool checkMotion(int val, char carUPcc, char ori) {
			int len = this->ottieniLunghezza(ori);
			if (val > 0 && val < len) {
				if (carUPcc != '-' && carUPcc != '+' && carUPcc != '|') {  // IMPORTANTE!!! --> Scrivere questi ostacoli attraverso delle variabili, magari un array di caratteri
					return true;
				}
			}
			return false;
		}
	
		bool checkRemoval(int val, char ori) {
			if (ori == HORIZONTAL) {
				if (val > 0) {
					return true;
				}
				return false;
			}
			else if (ori == VERTICAL) {
				if (val > 0 && val < (DIM - 1)) {
					return true;
				}
				return false;
			}
		}
		
		void levelCompleted(chrono::duration<double> delta) {
			char choice;
			system("cls");
			cout << endl << endl << "====================== Level " << this->level <<" Completed! ======================" << endl;
			cout << "- Time elapsed: " << delta.count() << " seconds"<< endl;
			cout << endl;
			cout << "- Insert " << EXIT << " to return to the main menu" << endl;
			cout << "- Insert " << FIRSTOPTION << " to go to the next level" << endl;
			cin >> choice;
			switch(choice) {
				case EXIT:
					break;
				case FIRSTOPTION:
					this->startGame();
					break;
				default:
					this->levelCompleted(delta);
					break;
			}
		}
	
};

char menu() {
	system("cls");
	char choice;
	cout << " __________________________________________" << endl;
	cout << "|                                          |" << endl;
	cout << "|               The Labyrinth              |" << endl;
	cout << "|__________________________________________|" << endl;
	cout << endl;
	cout << "- Insert " << EXIT << " to end the program" << endl;
	cout << "- Insert " << FIRSTOPTION << " to start the labyrinth" << endl;
	cout << "- Insert " << SECONDOPTION << " to set your avatar" << endl;
	cin >> choice;
	return choice;
}

string getName() {
	string name;
	do {
		cout << " - Insert your name or nickname: ";
		cin >> name;
	}
	while (name.empty());
	return name;
}

int main() {
	
	// LABIRINTO
	
	srand(time(NULL));
	
	string playerName = getName();
	
	while(true) {
		Labirinto labirinto;
		char choice = menu();
		switch(choice) {
			case FIRSTOPTION:
				labirinto.playerName = playerName;
				labirinto.startGame();  // IMPORTANTE!!! --> Passare informazioni come (numero di level, name del giocatore) dentro questo metodo qui
				break;
			case SECONDOPTION:
				labirinto.setPlayer();
				break;
			
			case EXIT:
				system("cls");
				cout << endl << "================= PROGRAM FINISHED =================" << endl;
				cout << "- Thanks for playing!" << endl;
				return 0;
		
			}
	
		}
	
	return 0;
}

