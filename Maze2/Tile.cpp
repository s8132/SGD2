#include "Tile.h"
#include <iostream>
#include <time.h>

Tile::Tile(){
	
}

int Tile::indexToPixelX(int index){
	return index/this->width;
}

int Tile::indexToPixelY(int index){
	return index%width;
}

void Tile::setWidth(int width){
	this->width = width;
}

int Tile::getWidth(){
	return this->width;
}

void Tile::setHeight(int height){
	this->height = height;
}

int Tile::getHeight(){
	return this->height;
}

bool Tile::neightbor(int index){
	int z=0, x=0, u=0;

	//Sprawdü gÛrÍ
	if(this->checkUp(index)){
		z++;
		//cout << "Jest sasiad na gorze" << endl;
	}

	//Sprawdü dÛ≥
	if(this->checkDown(index)){
		z++;
		//cout << "Jest sasiad na dole" << endl;
	}

	//Sprawdü lewo
	if(this->checkLeft(index)){
		z++;
		//cout << "Jest sasiad na lewo" << endl;
	}

	//Sprawdü prawo
	if(this->checkRight(index)){
		z++;
		//cout << "Jest sasiad na prawo" << endl;
	}

	if(z>0){
		return true;
	}else{
		return false;
	}
}

//Sprawdü czy moøna iúÊ do gÛry
bool Tile::checkUp(int index){
	int z=0;
	bool zwracana = false;

	if(index-this->width > 0){
		//sprawdü na stosie
		for(map<int, int>::const_iterator i=this->visted.begin(); i!=this->visted.end(); i++){
			if(i->second==index-this->width){
					z++;
			}
		}
		if(z<=0){
			//Jeúli moøna iúÊ to wrzuÊ na stos "way" 1 (1 -> kierunek gÛra)
			this->way.push(1);
			zwracana = true;
		}else{
			zwracana = false;
		}
	}
	return zwracana;
}

//Sprawdü czy moøna iúÊ w dÛ≥
bool Tile::checkDown(int index){
	int z=0;
	bool zwracana = false;
	if(index+this->width < this->height*this->width-1){
		//sprawdü na stosie
		for(map<int, int>::const_iterator i=this->visted.begin(); i!=this->visted.end(); i++){
			if(i->second==index+this->width){
					z++;
			}
		}
		if(z<=0){
			//Jeúli moøna iúÊ to wrzuÊ na stos "way" 2 (2 -> kierunek dÛ≥)
			this->way.push(3);
			zwracana = true;
		}else{
			zwracana = false;
		}
	}
	return zwracana;
}

//Sprawdü czy moøna iúÊ w prawo
bool Tile::checkRight(int index){
	int x=0, u=0, z=0;
	x=index/this->width;
	u=index+1;
	bool zwracana = false;

	if(x==(u/this->width)){
		if(u<((this->width*this->height)-1)){
			//sprawdü na stosie
			for(map<int, int>::const_iterator i=this->visted.begin(); i!=this->visted.end(); i++){
				if(i->second==u){
					z++;
				}
			}
		}
		if(z<=0){
			//Jeúli moøna iúÊ to wrzuÊ na stos "way" 3 (3 -> kierunek prawo)
			this->way.push(2);
			zwracana = true;
		}else{
			zwracana = false;
		}
	}
	return zwracana;
}

//Sprawdü czy moøna iúÊ w lewo
bool Tile::checkLeft(int index){
	int x=0, u=0, z=0;
	x=index/this->width;
	u=index-1;
	bool zwracana = false;

	if(x==(u/this->width)){
		if(index>0){
			//sprawdü na stosie
			for(map<int, int>::const_iterator i=this->visted.begin(); i!=this->visted.end(); i++){
				if(i->second==u){
					z++;
				}
			}
			
			if(z<=0){
				//Jeúli moøna iúÊ to wrzuÊ na stos "way" 4 (4 -> kierunek lewo)
				this->way.push(4);
				zwracana = true;
			}else{
				zwracana = false;
			}
		}
	}
	return zwracana;
}

void Tile::pushVisted(int index){
	int size=this->visted.size()+1;
	this->visted[size]=index;
}

int Tile::getSizeVisted(){
	return this->visted.size();
}

void Tile::checkVisted(int value){
	map<int, int>::iterator abc;

	for(abc=this->visted.begin(); abc!=this->visted.end(); abc++){
		if(abc->second == value){
			cout << "Element jest w mapie!" << endl;
		}
	}
}

/*OBSU£GA STOSU "CurrentTile"*/
void Tile::pushCurrentTile(int value){
	this->currentTile.push(value);
}
void Tile::popCurrentTile(){
	this->currentTile.pop();
}	
int Tile::topCurrentTile(){
	return this->currentTile.top();
}

int Tile::getSizeVurrentTile(){
	return this->currentTile.size();
}


void Tile::coutVisted(){
	map<int, int>::iterator I;

	for(I=this->visted.begin(); I!=this->visted.end(); I++)
	{
		cout << I->second << ", ";
	}

}
/*OBSU£GA STOSU "way"*/
void Tile::pushWay(int value){
	this->way.push(value);
}
void Tile::popWay(){
	this->way.pop();
}
int Tile::topWay(){
	return this->way.top();
}
int Tile::getSizeWay(){
	return this->way.size();
}


int Tile::randomWay(){
	int size=0, random=0, way=0;

	size = this->way.size();
	srand((unsigned)time(0));
	random = (rand()%size)+1;

	for(int i=1; i<=size; i++){
		if(i==random){
			way=this->way.top();
			break;
		}
		this->way.pop();
	}


	//Czyszczenie dla nastÍpnego ruchu
	while(this->way.empty()==false){
		this->way.pop();
	}

	return way;
}


int Tile::newIndex(int index, int way){
	int newindex=0;

	switch(way)
	{
	case 1:
		newindex = index-this->width;
		break;
	case 2:
		newindex = index+1;
		break;
	case 3:
		newindex = index+this->width;
		break;
	case 4:
		newindex = index-1;
		break;
	default:
		cout << "UPS! Cos nie tak z losowanie kierunku!" << endl;
		break;
	}

	return newindex;
}
