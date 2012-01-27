#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\mouse.h>
#include <allegro5\keyboard.h>
#include <allegro5\bitmap.h>
#include <allegro5\bitmap_io.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <map>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <set>
#include "Tile.h"
#include <Windows.h>

using namespace std;

const int SIZE_SQUARE=15;

class Graphics{
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *point;
	ALLEGRO_BITMAP *buff;
	ALLEGRO_BITMAP *map;
	ALLEGRO_FONT *font;
	ALLEGRO_BITMAP *finish;
	ALLEGRO_MOUSE_STATE mouse_state;
	ALLEGRO_KEYBOARD_STATE keyboard_state;
	set<int> odwiedzone;
	set<int> porownanie;
	stack<int> tiles;
	Tile tile;
	int width;
	int height;
public:
	Graphics();
	~Graphics();
	void initGraph(int, int, char*);
	void setWidth(int);
	void setHeight(int);
	int getWidth();
	int getHeight();
	void drawLine();
	void drawRedPixel(int, int);
	void deleteLine(int, int);
	void generateLab(int);
	int getFinishTile();
	void main(int);
	void generateCycle(int);
	void searchRoad(int, int);
	bool checkRoad(int);
	bool checkUp(int);
	bool checkDown(int);
	bool checkLeft(int);
	bool checkRight(int);
	void writeStos();
	void writeSet();
	void writePorow();
};