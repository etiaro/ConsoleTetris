// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <string>
#include <sstream>

enum TypBloku {
	A = 0, //zamiast średników stosuje się przecinki
	B = 1,
	C = 2,
	D = 3,
	E = 4,
	F = 5,
	G = 6
};

class Blok {
public:
	TypBloku typ;
	int x, y;
	Blok() : x(20), y(0), typ(A) {};
	Blok(TypBloku t) : x(20), y(0), typ(t) {};
	Blok(int X, int Y, TypBloku t) : x(X), y(Y), typ(t) {};
	void wyswietl(HANDLE hOut) {
		switch (this->typ) {
		case A:
			SetConsoleTextAttribute(hOut, BACKGROUND_RED);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case B:
			SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case C:
			SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case D:
			SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case E:
			SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_GREEN);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case F:
			SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case G:
			SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
			std::cout << " ";
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		}
	}
	std::string str() {
		switch (this->typ) {
		case A:
			return "A";
			break;
		case B:
			return "B";
			break;
		case C:
			return "C";
			break;
		case D:
			return "D";
			break;
		case E:
			return "E";
			break;
		case F:
			return "F";
			break;
		case G:
			return "G";
			break;
		}
	}
	bool operator ==(const Blok b) {
		if (this->x == b.x&&this->y == b.y)
			return true;
		else
			return false;
	}
};
class lezace {
public:
	std::vector<Blok> bloki;
	void dodaj(std::vector<Blok> b) {
		for (size_t i = 0; i<b.size(); i++)
			this->bloki.push_back(b[i]);
	}
	void Usunlinie(int y) {
		for (size_t i = 0; i<this->bloki.size(); i++)
			if (this->bloki[i].y == y) {
				this->bloki.erase(this->bloki.begin() + i);
				i--;
			}
		for (size_t i = 0; i<this->bloki.size(); i++)
			if (this->bloki[i].y<y)
				this->bloki[i].y++;
	}
};

class nastepny {
public:
	std::vector<Blok> bloki;
	nastepny() {
		nast();
	}
	void nast() {
		this->bloki.clear();
		switch (rand() % 7 + 1) {								//x=10 y=50
		case 1:	//I-block
			this->bloki.push_back(Blok(50, 10, A));
			this->bloki.push_back(Blok(50, 11, A));
			this->bloki.push_back(Blok(50, 12, A));
			this->bloki.push_back(Blok(50, 13, A));
			break;
		case 2:	//J-block
			this->bloki.push_back(Blok(51, 10, B));
			this->bloki.push_back(Blok(51, 11, B));
			this->bloki.push_back(Blok(51, 12, B));
			this->bloki.push_back(Blok(50, 12, B));
			break;
		case 3:	//L-block
			this->bloki.push_back(Blok(50, 10, C));
			this->bloki.push_back(Blok(50, 11, C));
			this->bloki.push_back(Blok(50, 12, C));
			this->bloki.push_back(Blok(51, 12, C));
			break;
		case 4: //O-block
			this->bloki.push_back(Blok(50, 10, D));
			this->bloki.push_back(Blok(50, 11, D));
			this->bloki.push_back(Blok(51, 10, D));
			this->bloki.push_back(Blok(51, 11, D));
			break;
		case 5:	//S-block
			this->bloki.push_back(Blok(50, 10, E));
			this->bloki.push_back(Blok(50, 11, E));
			this->bloki.push_back(Blok(51, 10, E));
			this->bloki.push_back(Blok(49, 11, E));
			break;
		case 6:	//Z-block
			this->bloki.push_back(Blok(50, 10, F));
			this->bloki.push_back(Blok(50, 11, F));
			this->bloki.push_back(Blok(49, 10, F));
			this->bloki.push_back(Blok(51, 11, F));
			break;
		case 7:	//T-block
			this->bloki.push_back(Blok(50, 10, G));
			this->bloki.push_back(Blok(49, 10, G));
			this->bloki.push_back(Blok(51, 10, G));
			this->bloki.push_back(Blok(50, 11, G));
			break;
		}
	}
};

class Lecacy {
public:
	std::vector<Blok> bloki;
	Lecacy(nastepny n) {
		nowy(n.bloki);
		n.nast();
	}
	void nowy(std::vector<Blok> bloki) {
		this->bloki.clear();
		std::vector<Blok> wzglBloki = bloki;
		for (size_t i = 1; i<wzglBloki.size(); i++) {
			wzglBloki[i].x -= wzglBloki[0].x;
			wzglBloki[i].y -= wzglBloki[0].y;
		}
		wzglBloki[0].x = 0;
		wzglBloki[0].y = 0;
		for (size_t i = 0; i<wzglBloki.size(); i++) {
			wzglBloki[i].x += 19;
		}
		this->bloki = wzglBloki;
	}
	void obroc(int kier) {
		std::vector<Blok> wzglBloki = this->bloki;
		for (size_t i = 1; i<wzglBloki.size(); i++) {
			wzglBloki[i].x -= wzglBloki[0].x;
			wzglBloki[i].y -= wzglBloki[0].y;
		}
		if (kier == 1) {
			for (size_t i = 1; i<wzglBloki.size(); i++) {
				int x = wzglBloki[i].x;
				wzglBloki[i].x = wzglBloki[i].y;
				wzglBloki[i].y = x*-1;
			}
		}
		else {
			for (size_t i = 1; i<wzglBloki.size(); i++) {
				int x = wzglBloki[i].x;
				wzglBloki[i].x = wzglBloki[i].y*-1;
				wzglBloki[i].y = x;
			}
		}
		for (size_t i = 1; i<wzglBloki.size(); i++) {
			wzglBloki[i].x += wzglBloki[0].x;
			wzglBloki[i].y += wzglBloki[0].y;
		}
		this->bloki = wzglBloki;
	}
	void przesun(int x, int y) {
		for (size_t i = 0; i<this->bloki.size(); i++) {
			this->bloki[i].x += x;
			this->bloki[i].y += y;
		}
	}
};

class Gra {
public:
	int wynik;
	nastepny nastepny;
	Lecacy lecacy;
	lezace lezace;
	Gra() : wynik(0), lecacy(nastepny) {}
	std::vector<Blok> wszystkieBloki() {
		std::vector<Blok> w;
		for (size_t i = 0; i<this->lezace.bloki.size(); i++)
			w.push_back(this->lezace.bloki[i]);
		for (size_t i = 0; i<this->lecacy.bloki.size(); i++)
			w.push_back(this->lecacy.bloki[i]);
		for (size_t i = 0; i<this->nastepny.bloki.size(); i++)
			w.push_back(this->nastepny.bloki[i]);
		return w;
	}
	void sprawdzKompletnosc() {
		bool kompletnosc[22][40] = { false };
		std::vector<Blok> l = this->lezace.bloki;
		for (size_t i = 0; i<l.size(); i++) {
			kompletnosc[l[i].y][l[i].x] = true;
		}
		for (int i = 0; i<22; i++) {
			bool kompl = true;
			for (int j = 0; j<39; j++) {
				if (!kompletnosc[i][j]) {
					kompl = false;
					break;
				}
			}
			if (kompl) {
				this->lezace.Usunlinie(i);
				this->wynik += 1;
			}
		}
	}

	bool moznaObrocic(int kier) {
		Lecacy l = this->lecacy;
		l.obroc(kier);
		for (size_t j = 0; j<l.bloki.size(); j++)
			if (l.bloki[j].x<0 || l.bloki[j].x>39 || l.bloki[j].y>21)
				return false;
		for (size_t i = 0; i<this->lezace.bloki.size(); i++)
			for (size_t j = 0; j<l.bloki.size(); j++)
				if (this->lezace.bloki[i] == l.bloki[j])
					return false;
		return true;
	}

	bool moznaPrzesunac(int x) {
		std::vector<Blok> b = lecacy.bloki;
		for (size_t i = 0; i<b.size(); i++) {
			b[i].x += x;
		}
		std::vector<Blok> l = this->lezace.bloki;
		for (size_t i = 0; i<b.size(); i++) {
			if (b[i].x>39 || b[i].x<0)
				return false;
			for (size_t j = 0; j<l.size(); j++) {
				if (b[i].x == l[j].x&&b[i].y == l[j].y)
					return false;
			}
		}
		return true;
	}

	bool spadl(int y) {
		std::vector<Blok> b = lecacy.bloki;
		for (size_t i = 0; i<b.size(); i++) {
			b[i].y += y;
		}
		std::vector<Blok> l = this->lezace.bloki;
		for (size_t i = 0; i<b.size(); i++) {
			if (b[i].y>21)
				return true;
			for (size_t j = 0; j<l.size(); j++) {
				if (b[i].x == l[j].x&&b[i].y == l[j].y)
					return true;
			}
		}
		return false;
	}
	void wyswietl(HANDLE hOut) {
		std::stringstream ss;
		ss << this->wynik;
		std::string s = "                                     TETRIS\n";
		s += "_______________________________________________________________________________\n";
		for (int y = 0; y<22; y++) {
			s += "|";
			for (int x = 0; x<77; x++) {
				if (x == 40) {
					s += "|";
				}
				else {
					if (y == 6 && x == 42) {
						std::stringstream ss;
						ss << this->wynik;
						s += "    YOUR SCORE: ";
						s += ss.str();
						for (int i = 0; i<19 - ss.str().length(); i++)
							s += " ";
						break;
					}
					else if (y == 8 && x == 42) {
						s += "    NEXT FIGURE:                   ";
						break;
					}
					else {
						bool b = false;
						std::vector<Blok> w = this->wszystkieBloki();
						for (size_t i = 0; i<w.size(); i++)
							if (x == w[i].x&&y == w[i].y) {
								std::cout << s;
								w[i].wyswietl(hOut);
								b = true;
								s.clear();
							}
						if (!b)
							s += " ";
					}
				}
			}
			s += "|\n";
		}
		s += "|-----------------------------------------------------------------------------|";
		std::cout << s;
	}
	void KoniecGry();
};

int main() {
	srand(time(NULL));
	Gra gra;

	HANDLE hOut;//uchwyt do okienka konsoli
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::ios::sync_with_stdio(false);

	int sleep = 50;
	bool koniec = false;
	int przejscie = 0;
	int ilPrzejsc = 5;
	bool pierwszy = false;
	while (koniec == false) {
		unsigned char znak = 0;
		while (_kbhit()) {
			znak = _getch();
			switch (znak) {
			case 0: //klawisze specjalne (czasem zero czasem 224 - zależne od pc'ta chyba)
			case 224: //klawisze specjalne
				if (_kbhit())
					znak = _getch();
				switch (znak) {
				case 72: //strzałka w górę
					if (gra.moznaObrocic(-1))
						gra.lecacy.obroc(-1);
					gra.wyswietl(hOut);
					break;
				case 80: //strzałka w dół
					if (gra.moznaObrocic(1))
						gra.lecacy.obroc(1);
					gra.wyswietl(hOut);
					break;
				case 75: //strzałka w lewo
					if (gra.moznaPrzesunac(-1))
						gra.lecacy.przesun(-1, 0);
					gra.wyswietl(hOut);
					break;
				case 77: //strzałka w prawo
					if (gra.moznaPrzesunac(1))
						gra.lecacy.przesun(1, 0);
					gra.wyswietl(hOut);
					break;
				}
				break;
			case 13: //ENTER
				if (ilPrzejsc == 5) {
					ilPrzejsc = 2;
					przejscie = 2;
				}
				else {
					przejscie = 5;
					ilPrzejsc = 5;
				}
				break;
			}
		}
		if (przejscie == ilPrzejsc) {
			if (!(gra.spadl(1))) {
				if (ilPrzejsc == 5)
					gra.lecacy.przesun(0, 1);
				else
					if (!(gra.spadl(2)))
						gra.lecacy.przesun(0, 2);
					else
						gra.lecacy.przesun(0, 1);
				pierwszy = false;
			}
			else {
				if (pierwszy) {
					gra.KoniecGry();
					break;
				}
				else {
					gra.lezace.dodaj(gra.lecacy.bloki);
					gra.lecacy.nowy(gra.nastepny.bloki);
					gra.nastepny.nast();
					ilPrzejsc = 5;
					pierwszy = true;
				}
			}
			gra.sprawdzKompletnosc();
			gra.wyswietl(hOut);
			przejscie = 0;
		}
		Sleep(sleep);
		przejscie++;
	}
	return 0;
}

void Gra::KoniecGry() {
	std::cout << "                                    \n";
	std::cout << "XXX###XX XXX###XXX XXX#XxX#XXX XX###\n";
	std::cout << "XX    XX XX     XX XX   X   XX XX   \n";
	std::cout << "XX   xxx XXxxxxxXX XX   #   XX XX###\n";
	std::cout << "XX    XX XX     XX XX       XX XX   \n";
	std::cout << "XXXxxxXX XX     XX XX       XX XXxxx\n";
	std::cout << "                                    \n";
	std::cout << "XXX###XXX #XXX  XX# XX### XX####XXx \n";
	std::cout << "XX     XX   XX  XX  XX    XX     XX \n";
	std::cout << "XX     XX   XX  XX  XX### XXxxxxx## \n";
	std::cout << "XX     XX   XX  X#  XX    XX     XX \n";
	std::cout << "XXXxxxXXX   ─#X#  ─ XXxxx XX     XXx\n";
	std::cout << "                                    \n";
	std::cout << "        XX               XX         \n";
	std::cout << "      XXXXx   xxxxxxx   xXXXX       \n";
	std::cout << "         ##XxXXXXXXXXXxX##          \n";
	std::cout << "           XXXXXXXXXXXXX            \n";
	std::cout << "           XX###XXX###XX            \n";
	std::cout << "           XX   XXX   XX            \n";
	std::cout << "           XXXXX#x#XXXXX            \n";
	std::cout << "            XXXXXXXXXXX             \n";
	std::cout << "        xxxXX  X#X#X  XXxxx         \n";
	std::cout << "        ##XX           XX##         \n";
	std::cout << "          ##           ##           \n";
	std::cout << "                                    ";
	_getch();
}
//problem ze znikaniem
//nie da sie zginac
//zabezp przed obracaniem