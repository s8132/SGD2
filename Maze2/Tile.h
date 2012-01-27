#include <iostream>
#include <stack>
#include <time.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;

class Tile{
private:
	//Szeroko��
	int width;

	//Wysoko��
	int height;

	map<int, int> visted;

	//Stos kom�rek indeks�w
	stack<int> currentTile;

	//Stos mo�liwych dr�g do wylosowania
	stack<int> way;

public:
	//Konstruktor
	Tile();

	//Konwersja pixela na indeks kom�rki
	int pixelToIndex(int, int);

	//Konwersja indeksu na pixel x
	int indexToPixelX(int);
	
	//Konwersja indeksu na pixel y
	int indexToPixelY(int);

	//Ustawienie szeroko�ci w tej klasie
	void setWidth(int);

	//Pobranie szeroko�� 
	int getWidth();

	//Ustawienie wysoko�ci w tej klasie
	void setHeight(int);

	//Pobranie wysoko�ci
	int getHeight();

	//Sprawdzenie czy istnieje jaki kolwiek s�siad (przy okazji je�li mo�na i�� w jakim� kierunku to wrzucenie go do stosu "way")
	bool neightbor(int);

/*
	MAPA VISTED
*/
	void pushVisted(int);
	int getSizeVisted();
	void checkVisted(int);
	void coutVisted();

/*
	STOS CURRENTTILE
*/
	//Wk�adanie na stos po za klas�
	void pushCurrentTile(int);

	//Zdejmowanie z stosu po za klas�
	void popCurrentTile();

	//Ostatni element stosu (stosowane po za klas�)
	int topCurrentTile();

	int getSizeVurrentTile();

/*
	STOS WAY
*/

	//Wk�adanie na stos po za klas�
	void pushWay(int);

	//Zdejmowanie stos po za klas�
	void popWay();

	//Ostatni element stosu (stosowane po za kals�)
	int topWay();

	//Pobranie rozmiaru stosu po za klas�
	int getSizeWay();

	
/*
	Sprawdzanie w kt�rym kierunku mo�na i��
*/
	//Do g�ry?
	bool checkUp(int);

	//Na d�?
	bool checkDown(int);

	//W prawo?
	bool checkRight(int);

	//W lewo?
	bool checkLeft(int);

	int randomWay();

	int newIndex(int, int);
};