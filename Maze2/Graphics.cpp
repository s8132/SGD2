#include "Graphics.h"

//Konstruktor
Graphics::Graphics(){
	
}

//Inicjalizacja biblioteki
void Graphics::initGraph(int width, int height, char *title){

	this->setWidth(width);
	this->setHeight(height);

	tile.setWidth(width);
	tile.setHeight(height);

	if(!al_init()){
		cout << "Problem z inicjalizacja biblioteki allegro!" << endl;
		return;
	}

	this->display = al_create_display(width*SIZE_SQUARE+1, height*SIZE_SQUARE+1);

	if(!display){
		cout << "Utworzenie okna sie nie powiodlo! :(" << endl;
		return;
	}

	
	
	al_set_window_title(this->display, title);
	al_set_window_position(this->display, 0, 0);

	//al_clear_to_color(al_map_rgb(57, 10, 70));

	

	//Inicjalizacje dodatków
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	
	
	this->font = al_load_ttf_font("pirulen.ttf", 12, 0);

	if(!font){
		cout << "Error z font" << endl;
	}

	this->point = al_load_bitmap("point09.bmp");

	if(!this->point){
		cout << "problem z pointem" << endl;
	}

	al_convert_mask_to_alpha(point, al_map_rgb(255, 255, 255));

	this->finish = al_load_bitmap("meta.gif");
	al_convert_mask_to_alpha(this->finish, al_map_rgb(255, 255, 255));

	if(!this->finish){
		cout << "problem z meta" << endl;
	}

	

	this->buff = al_create_bitmap(this->width*SIZE_SQUARE+1, this->height*SIZE_SQUARE+1);
	this->map = al_create_bitmap(this->width*SIZE_SQUARE+1, this->height*SIZE_SQUARE+1);

	al_get_keyboard_state(&this->keyboard_state);

}

//Dekonstruktor
Graphics::~Graphics(){

	//al_flip_display();
	
	//al_rest(10.0);
	
	//al_destroy_display(this->display);
}

//Operacje na szerokoœci
void Graphics::setWidth(int width){
	this->width = width;
}

int Graphics::getWidth(){
	return this->width;
}

//Operacje na wysokoœci
void Graphics::setHeight(int height){
	this->height = height;
}

int Graphics::getHeight(){
	return this->height;
}

//Rysowanie siatki
void Graphics::drawLine(){
	int i=0, j=0;
	int x=1, y=1;

	al_set_target_bitmap(this->map);

	//Rysuj poziom
	for(i; i<=(this->getHeight()*SIZE_SQUARE); i=i+15){
		al_draw_line(x, y, x+this->getWidth()*SIZE_SQUARE, y, al_map_rgb(255, 255, 255), 1);
		y=y+15;
	}
	x=1, y=1;
	//Rysuj pion
	for(j; j<=(this->getWidth()*SIZE_SQUARE); j++){
		al_draw_line(x, y, x, y+this->height*SIZE_SQUARE, al_map_rgb(255, 255, 255), 1);
		x=x+15;
	}

	
}

void Graphics::drawRedPixel(int x, int y){
	al_draw_pixel(x*SIZE_SQUARE+1, y*SIZE_SQUARE+1, al_map_rgb(255, 0, 0));
}

void Graphics::deleteLine(int way, int index){
	int x=0, y=0, row=0, col=0;
	row = index/this->width;
	col = index%this->width;
	x=col*SIZE_SQUARE+1;
	y=row*SIZE_SQUARE+1;

	//cout << "row = " << row << "\t col = " << col << endl;
	//cout << "Grafika, punkty (" << x <<", " << y << ")" << endl;

	al_set_target_bitmap(this->map);

	switch(way)
	{
	case 1:
		al_draw_line(x, y, x+SIZE_SQUARE-1, y, al_map_rgb(57, 10, 70), 1);
		//cout << "Ide do gory" << endl;
		break;
	case 2:
		al_draw_line(x+SIZE_SQUARE, y, x+SIZE_SQUARE, y+SIZE_SQUARE-1, al_map_rgb(57, 10, 70), 1);
		//cout << "Ide w prawo" << endl;
		break;
	case 3:
		al_draw_line(x, y+SIZE_SQUARE, x+SIZE_SQUARE-1, y+SIZE_SQUARE, al_map_rgb(57, 10, 70), 1);
		//cout << "Ide na dol" << endl;
		break;
	case 4:
		al_draw_line(x, y, x, y+SIZE_SQUARE-1, al_map_rgb(57, 10, 70), 1);
		//cout << "Ide w lewo" << endl;
		break;
	default:
		//cout << "UPS! Cos nie tak z losowanie kierunku!" << endl;
		break;
	}
}

int Graphics::getFinishTile(){
	al_get_mouse_state(&this->mouse_state);
	int x=0, y=0, button=0, index=0, u=0, v=0;

		if(al_mouse_button_down(&this->mouse_state, 1)){
			x = mouse_state.x;
			y = mouse_state.y;
			u = (this->width*SIZE_SQUARE)/(x*SIZE_SQUARE);
			v = (this->height*SIZE_SQUARE)/(y*SIZE_SQUARE);
			index = u*SIZE_SQUARE+y;

		}

	return index;
}

void Graphics::generateLab(int index){


	int visted = 0, test=0;

	tile.pushCurrentTile(index);
	tile.pushVisted(index);
	while(visted<=height*width-1){
		if(tile.neightbor(index)){
			//cout << "Index: " << index << " jest sasiad" << endl;
			int size=0, way=0;
			size = tile.getSizeWay();
			if(size>0){
				way = tile.randomWay();
			}else{
				cout << "Cos jest nie tak :/" << endl;
			}
			this->deleteLine(way, index);
			test = tile.newIndex(index, way);
			tile.pushVisted(test);
			tile.pushCurrentTile(test);
			visted++;
		}else{
			//cout << "Index: " << index << " nie ma sasiada" << endl;
			tile.popCurrentTile();
			test=tile.topCurrentTile();
		}
		index = test;
	}

}

void Graphics::main(int index){
	/*
		DIRECTION:
		1 - UP
		2 - RIGHT
		3 - DOWN
		4 - LEFT
	*/
	int x=1, y=1, xpos=0, ypos=0, xf=0, yf=0, indexf=10, start=0, tmp, way, direction=0, button=0, h=0, u, v;
	double timer = al_current_time();
	int speed=0;
	bool draw=false, drawF=false, go=false, redraw=false, mouse=false, done=true;

	this->tiles.push(start);
	this->odwiedzone.insert(start);
	
	
	
	while(!al_key_down(&this->keyboard_state, ALLEGRO_KEY_ESCAPE)){

		
		
		

		al_set_target_bitmap(this->buff);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		//al_convert_mask_to_alpha(this->buff, al_map_rgb(0, 0, 0));

		al_draw_bitmap(this->map, 0, 0, 0);

		al_get_keyboard_state(&this->keyboard_state);
		al_get_mouse_state(&this->mouse_state);

		
		
		
		
		if(mouse){
			//cout << "Myszka x = " << mouse_state.x << ", y = " << mouse_state.y << endl;
			int kom;
			kom = (v*this->width)+u;
			xf=this->tile.indexToPixelY(kom)*SIZE_SQUARE;
			yf=this->tile.indexToPixelX(kom)*SIZE_SQUARE;
			//cout << "XF = " << xf << endl;
			//cout << "YF = " << yf << endl;
			drawF=true;
			go=true;
			indexf=kom;
		}

		mouse=false;

		if(drawF){
			al_draw_bitmap(this->finish, xf+1, yf+1, 0);
		}
		
		
		

		if(go){

				if(this->checkRoad(start)){
					//cout << "index: " << index << endl;
					if(this->checkUp(start)){
						cout << "\tide do gory" << endl;
						start = start-this->width;
						direction = 1;
					}else if(this->checkRight(start)){
						cout << "\tide w prawo" << endl;
						start = start+1;
						direction = 2;
					}else if(this->checkDown(start)){
						cout << "\tide na dol" << endl;
						start = start + this->width; 
						direction = 3;
					}else if(this->checkLeft(start)){
						cout << "\tide w lewo" << endl;
						start = start-1;
						direction = 4;
					}else{
						cout << "cos jest nie tak" << endl;
						break;
					}
					this->odwiedzone.insert(start);
					this->tiles.push(start);
					
					go=false;
				}else{
					tmp = start;
					this->tiles.pop();
					start = this->tiles.top();
					way = tmp - start;
					cout << "Way: " << way << endl;
					if(way==1){
						direction = 4;
					}else if(way==-1){
						direction = 2;
					}else if(way==this->width){
						direction = 1;
					}else if(way==-this->width){
						direction = 3;
					}else{
						//cout << "cos jest nie tak" << endl;
					}
					go=false;
				}
				
				//cout << "TEST" << endl;

		}

		if(start==indexf){
			//al_draw_text(this->font, al_map_rgb(255, 0, 0), (this->width*SIZE_SQUARE)/2, this->height*SIZE_SQUARE/2, 0, "THE END");
			//go=false;
			break;
		}

		

		if(al_current_time() >= timer+0.01){
			timer = al_current_time();
			
			if(direction==1){
				if(ypos!=tile.indexToPixelX(start)*SIZE_SQUARE+1){
					ypos--;
					go=false;
					//if(ypos==tile.indexToPixelX(indexf)*SIZE_SQUARE+1) direction=0;
			
				}else{
					go=true;
				}
			}

			if(direction==2){
				if(xpos!=tile.indexToPixelY(start)*SIZE_SQUARE+1){
					xpos++;
					go=false;
					//if(xpos==tile.indexToPixelY(indexf)*SIZE_SQUARE+1) direction=0;
				}else{
					go=true;
				}
			}

			if(direction==3){
				if(ypos!=tile.indexToPixelX(start)*SIZE_SQUARE+1){
					ypos++;
					go=false;
					//if(ypos==tile.indexToPixelX(indexf)*SIZE_SQUARE+1) direction=0;
				}else{
					go=true;
				}
			}

			if(direction==4){
				if(xpos!=tile.indexToPixelY(start)*SIZE_SQUARE+1){
					xpos--;
					go=false;
					//if(xpos==tile.indexToPixelY(indexf)*SIZE_SQUARE+1) direction=0;
				}else{
					go=true;
				}
			}

			
			
			draw=true;
		}


		al_draw_bitmap(this->point, xpos, ypos, NULL);

		al_set_target_bitmap(al_get_backbuffer(this->display));            
		//al_clear_to_color(al_map_rgb(57, 10, 70));
		al_draw_bitmap(this->buff, 0, 0, 0);
		
		al_flip_display();
			
		
		
	
		}
		
	
	
	}
	
}

void Graphics::generateCycle(int number){
	srand(time(0));
	for(int i=0; i<number; i++)
	{
		
		int tile = rand()%(this->width*this->height-1), x, y;

		cout << "Tile: " << tile << endl;
		x=this->tile.indexToPixelY(tile)*SIZE_SQUARE+1;
		y=this->tile.indexToPixelX(tile)*SIZE_SQUARE+1;
		cout << "\t x = " << x << ", y = " << y << endl;
		al_set_target_bitmap(this->map);
		//al_draw_pixel(x, y, al_map_rgb(255, 0, 0));

		//al_draw_line(x+1, y+1, x+SIZE_SQUARE-1, y+SIZE_SQUARE-1, al_map_rgb(255, 0, 0), 1);

		int up, down, left, right;

		ALLEGRO_LOCKED_REGION *lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
		int r, g, b;
		ALLEGRO_COLOR color = al_get_pixel(this->map, x-1, y);
		al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
		int a, d, c;
		ALLEGRO_COLOR kolor = al_map_rgb(255, 255, 255);
		al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
		al_unlock_bitmap(this->map);
		//al_draw_filled_circle(x, y, 5, al_map_rgb(255, 0, 0));

		//al_draw_filled_rectangle(x, y, x+5, y+5, al_map_rgb(255, 0, 0));

		if(r==a && g==d && c==b){
			cout << "Moge usunac lewa krawedz" << endl;
			if(y+1<this->height*SIZE_SQUARE+1 && x>1 && x<this->width*SIZE_SQUARE){
				al_draw_line(x, y-1, x, y+SIZE_SQUARE, al_map_rgb(57, 10, 70), 1);
			}else{
				tile = rand()%(this->width*this->height-1);
			}
		}else{
			lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
			color = al_get_pixel(this->map, x+1, y-1);
			al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
			color = al_map_rgb(255, 255, 255);
			al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
			al_unlock_bitmap(this->map);
			cout << "\t x = " << x << ", y = " << y << endl;
			if(r==a && g==d && c==b){
				cout << "Moge usunac gorna krawedz" << endl;
				if(x+1<this->width*SIZE_SQUARE+1 && y>1 && y<this->height*SIZE_SQUARE){
					al_draw_line(x-1, y, x+SIZE_SQUARE, y, al_map_rgb(57, 10, 70), 1);
				}else{
					tile = rand()%(this->width*this->height-1);
				}
			}else{
				lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
				color = al_get_pixel(this->map, x+SIZE_SQUARE-1, y+1);
				al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
				color = al_map_rgb(255, 255, 255);
				al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
				al_unlock_bitmap(this->map);
				cout << "\t x = " << x << ", y = " << y << endl;
				if(r==a && g==d && c==b){
					cout << "Moge usunac prawa krawedz" << endl;
					if(y+1<this->height*SIZE_SQUARE+1 && x<this->height*SIZE_SQUARE+1){
						al_draw_line(x+SIZE_SQUARE, y-1, x+SIZE_SQUARE, y+SIZE_SQUARE, al_map_rgb(57, 10, 70), 1);
					}else{
						tile = rand()%(this->width*this->height-1);
					}
				}else{
					lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
					color = al_get_pixel(this->map, x+1, y+SIZE_SQUARE-1);
					al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
					color = al_map_rgb(255, 255, 255);
					al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
					al_unlock_bitmap(this->map);
					cout << "\t x = " << x << ", y = " << y << endl;

					if(r==a && g==d && c==b){
						cout << "Moge usunac dolna krawedz" << endl;
						if(x<this->width*SIZE_SQUARE+1 && y>this->height*SIZE_SQUARE+1){
							al_draw_line(x, y+SIZE_SQUARE, x+SIZE_SQUARE, y+SIZE_SQUARE, al_map_rgb(57, 10, 70), 1);
						}else{
							tile = rand()%(this->width*this->height-1);
						}
					}else{
						tile = rand()%(this->width*this->height-1);
					}
				}
			}
		}
	}
}

void Graphics::searchRoad(int index, int finish){
	this->tiles.push(index);
	this->odwiedzone.insert(index);

	int tmp, way;

	while(index!=finish){
		if(this->checkRoad(index)){
			cout << "index: " << index << endl;
			if(this->checkUp(index)){
				cout << "\tide do gory" << endl;
				index = index-this->width;
			}else if(this->checkRight(index)){
				cout << "\tide w prawo" << endl;
				index = index+1;
			}else if(this->checkDown(index)){
				cout << "\tide na dol" << endl;
				index = index + this->width; 
			}else if(this->checkLeft(index)){
				cout << "\tide w lewo" << endl;
				index = index-1;
			}else{
				cout << "cos jest nie tak" << endl;
				break;
			}
			this->odwiedzone.insert(index);
			this->tiles.push(index);
		}else{
			tmp=index;
			this->tiles.pop();
			index = this->tiles.top();
			this->porownanie.insert(index);
		}
	}
}

bool Graphics::checkRoad(int index){
	bool zwracana;
	int z=0;

	if(this->checkUp(index)){
		z++;
	}

	if(this->checkDown(index)){
		z++;
	}

	if(this->checkLeft(index)){
		z++;
	}

	if(this->checkRight(index)){
		z++;
	}

	if(z>0){
		//cout << "jest droga" << endl;
		zwracana = true;
	}else{
		//cout << "nie ma droga" << endl;
		zwracana = false;
	}
	return zwracana;
}

bool Graphics::checkUp(int index){
	int x, y;
	bool zwracana = false;
	x = this->tile.indexToPixelY(index)*SIZE_SQUARE+1;
	y = this->tile.indexToPixelX(index)*SIZE_SQUARE+1;

	ALLEGRO_LOCKED_REGION *lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	int r, g, b;
	ALLEGRO_COLOR color = al_get_pixel(this->map, x+SIZE_SQUARE/2, y-1);
	al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
	int a, d, c;
	ALLEGRO_COLOR kolor = al_map_rgb(57, 10, 70);
	al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
	al_unlock_bitmap(this->map);
	
	if(r==a && g==d && c==b){
		//cout << "jest przejscie" << endl;
		if(index-this->width>0){
				set<int>::iterator result;
		
				result = this->odwiedzone.find(index-this->width);
		
				if( result!=this->odwiedzone.end() ){
					zwracana = false;
				}else{
					zwracana = true;
				}
		}else{
			zwracana = false;
		}
	}else{
		//cout << "nie ma przejscie" << endl;
		zwracana = false;
	}

	return zwracana;
}

bool Graphics::checkDown(int index){
	int x, y;
	bool zwracana = false;
	x = this->tile.indexToPixelY(index)*SIZE_SQUARE+1;
	y = this->tile.indexToPixelX(index)*SIZE_SQUARE+1;

	ALLEGRO_LOCKED_REGION *lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	int r, g, b;
	ALLEGRO_COLOR color = al_get_pixel(this->map, x+SIZE_SQUARE/2, y+SIZE_SQUARE-1);
	al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
	int a, d, c;
	ALLEGRO_COLOR kolor = al_map_rgb(57, 10, 70);
	al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
	al_unlock_bitmap(this->map);
	
	//al_draw_pixel(x+SIZE_SQUARE/2, y*SIZE_SQUARE, al_map_rgb(255, 0, 0));
	//this->odwiedzone.insert(0);
	//cout << "index: " << index << endl;
	if(r==a && g==d && c==b){
		//cout << "jest przejscie" << endl;
		if(index+this->width<this->height*this->width-1){
				set<int>::iterator result;
				
				result = this->odwiedzone.find(index+this->width);
		
				if( result!=this->odwiedzone.end() ){
					zwracana = false;
					//cout << "nie ma przejscie bo juz odwiedzone" << endl;
				}else{
					zwracana = true;
					//cout << "jest przejscie bo nie odwiedzone" << endl;
				}
		}else{
			zwracana = false;
		}
	}else{
		zwracana = false;
		//cout << "nie ma przejscie" << endl;
	}

	return zwracana;
}

bool Graphics::checkLeft(int index){
	int x, y;
	bool zwracana = false;
	x = this->tile.indexToPixelY(index)*SIZE_SQUARE+1;
	y = this->tile.indexToPixelX(index)*SIZE_SQUARE+1;

	ALLEGRO_LOCKED_REGION *lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	int r, g, b;
	ALLEGRO_COLOR color = al_get_pixel(this->map, x-1, y+SIZE_SQUARE/2);
	al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
	int a, d, c;
	ALLEGRO_COLOR kolor = al_map_rgb(57, 10, 70);
	al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
	al_unlock_bitmap(this->map);
	
	//al_draw_pixel(x*SIZE_SQUARE+1, y*SIZE_SQUARE+5, al_map_rgb(255, 0, 0));
	//this->odwiedzone.insert(0);

	if(r==a && g==d && c==b){
		//cout << "jest przejscie" << endl;
		if(index/this->width==((index-1)/this->width)){
			if(index>0){
				set<int>::iterator result;
				
				result = this->odwiedzone.find(index-1);
		
				if( result!=this->odwiedzone.end() ){
					zwracana = false;
					//cout << "nie ma przejscie bo juz odwiedzone" << endl;
				}else{
					zwracana = true;
					//cout << "jest przejscie bo nie odwiedzone" << endl;
				}
			}else{
				zwracana = false;
			}
		}else{
			zwracana = false;
		}
	}else{
		zwracana = false;
		//cout << "nie ma przejscie" << endl;
	}

	return zwracana;
}

bool Graphics::checkRight(int index){
	int x, y;
	bool zwracana = false;
	x = this->tile.indexToPixelY(index)*SIZE_SQUARE+1;
	y = this->tile.indexToPixelX(index)*SIZE_SQUARE+1;

	ALLEGRO_LOCKED_REGION *lock = al_lock_bitmap(this->map, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	int r, g, b;
	ALLEGRO_COLOR color = al_get_pixel(this->map, x-1+SIZE_SQUARE, y+SIZE_SQUARE/2);
	al_unmap_rgb( color,( unsigned char * ) & r,( unsigned char * ) & g,( unsigned char * ) & b );
	int a, d, c;
	ALLEGRO_COLOR kolor = al_map_rgb(57, 10, 70);
	al_unmap_rgb(kolor,( unsigned char * ) & a,( unsigned char * ) & d,( unsigned char * ) & c );
	al_unlock_bitmap(this->map);
	
	//al_draw_pixel(x*SIZE_SQUARE+1, y*SIZE_SQUARE+5, al_map_rgb(255, 0, 0));
	//this->odwiedzone.insert(0);

	if(r==a && g==d && c==b){
		//cout << "jest przejscie" << endl;
		if(index/this->width==((index+1)/this->width)){
			if(index<((this->width*this->height)-1)){
				set<int>::iterator result;
				
				result = this->odwiedzone.find(index+1);
		
				if( result!=this->odwiedzone.end() ){
					zwracana = false;
					//cout << "nie ma przejscie bo juz odwiedzone" << endl;
				}else{
					zwracana = true;
					//cout << "jest przejscie bo nie odwiedzone" << endl;
				}
			}else{
				zwracana = false;
			}
		}else{
			zwracana = false;
		}
	}else{
		zwracana = false;
		//cout << "nie ma przejscie" << endl;
	}

	return zwracana;
}

void Graphics::writeStos(){

	for(int i=0; i<this->tiles.size(); i++){
		cout << this->tiles.top() << ", ";
		this->tiles.pop();
	}

	cout << endl;

}

void Graphics::writeSet(){

	set<int>::iterator it;

	for(it=this->odwiedzone.begin(); it!=this->odwiedzone.end(); ++it){
		cout << *it << ",";
	}

	cout << endl;
}

void Graphics::writePorow(){

	set<int>::iterator it;

	for(it=this->porownanie.begin(); it!=this->porownanie.end(); ++it){
		cout << *it << ",";
	}

	cout << endl;
}