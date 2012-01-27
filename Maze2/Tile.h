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
	//Szerokoœæ
	int width;

	//Wysokoœæ
	int height;

	map<int, int> visted;

	//Stos komórek indeksów
	stack<int> currentTile;

	//Stos mo¿liwych dróg do wylosowania
	stack<int> way;

public:
	//Konstruktor
	Tile();

	//Konwersja pixela na indeks komórki
	int pixelToIndex(int, int);

	//Konwersja indeksu na pixel x
	int indexToPixelX(int);
	
	//Konwersja indeksu na pixel y
	int indexToPixelY(int);

	//Ustawienie szerokoœci w tej klasie
	void setWidth(int);

	//Pobranie szerokoœæ 
	int getWidth();

	//Ustawienie wysokoœci w tej klasie
	void setHeight(int);

	//Pobranie wysokoœci
	int getHeight();

	//Sprawdzenie czy istnieje jaki kolwiek s¹siad (przy okazji jeœli mo¿na iœæ w jakimœ kierunku to wrzucenie go do stosu "way")
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
	//Wk³adanie na stos po za klas¹
	void pushCurrentTile(int);

	//Zdejmowanie z stosu po za klas¹
	void popCurrentTile();

	//Ostatni element stosu (stosowane po za klas¹)
	int topCurrentTile();

	int getSizeVurrentTile();

/*
	STOS WAY
*/

	//Wk³adanie na stos po za klas¹
	void pushWay(int);

	//Zdejmowanie stos po za klas¹
	void popWay();

	//Ostatni element stosu (stosowane po za kals¹)
	int topWay();

	//Pobranie rozmiaru stosu po za klas¹
	int getSizeWay();

	
/*
	Sprawdzanie w którym kierunku mo¿na iœæ
*/
	//Do góry?
	bool checkUp(int);

	//Na dó³?
	bool checkDown(int);

	//W prawo?
	bool checkRight(int);

	//W lewo?
	bool checkLeft(int);

	int randomWay();

	int newIndex(int, int);
};