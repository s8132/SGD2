#include "Graphics.h"
#include <iostream>
#include <conio.h>
//#include "Tile.h"
#include <stack>

using namespace std;


int main(int argc, char* args[]){

	Graphics Graphics;

	int width=0, height;
	//bool up=false, down=false, left=false, right=false;
	
	cout << "Podaj szerokosc labiryntu: ";
	cin >> width;
	cout << "Podaj wysokosc labiryntu: ";
	cin >> height;
	

	int size = height*width;
	int *map = new int[size-1];
	

	for(int i=0; i<height*width; i++)
	{
		map[i] = 0;
	}

	cout << "Wynik dzielenia 14/15 = " << 14/15 << endl;

	//Inincjalizacja biblioteki graficznej allegro
	Graphics.initGraph(width, height, "Labirynt - Projekt na SGD");

	//Wyrysowanie kratek
	Graphics.drawLine();

	//Graphics.drawRedPixel(Tile.indexToPixelY(898), Tile.indexToPixelX(898));

	//Graphics.deleteLine(1, 33);

	srand(time(NULL));
	//int index=rand()%(height*width-1);
	
	int index = (height*width-1)/2;

	/*
	Tile.pushVisted(71);
	Tile.pushVisted(79);

	if(Tile.neightbor(index)){
		cout << "jest sasiada" << endl;

	}else{
		cout << "nie sasiada" << endl;
	}
	
	
	cout << "Way size: " << Tile.getSizeWay() << endl;
	cout << "Pierwszy element way: " << Tile.topWay() << endl;

	int cos = Tile.randomWay();

	cout << "Kierunek: " << cos << endl;
	
	*/
	//generuj(index, Tile, Graphics);
	
	Graphics.generateLab(index);
	Graphics.generateCycle(4);
	//Graphics.searchRoad(0, 25);
	//Graphics.writeSet();
	//Graphics.writePorow();
	//int bladf=0;
	//Graphics.checkDown(bladf+1);
	//Graphics.writeStos();
	//Graphics.writeSet();
	//Graphics.checkRoad(0);
	Graphics.main(index);
	
	//Generuj przejscia - labirynt
	/*
		KIERUNKI:
			1 - góra
			2 - prawo
			3 - dó³
			4 - lewo

	*/

	

	//getch();
	//system("PAUSE");
	return 0;
}


