#include<raylib.h>
#include<raymath.h>
#include<raygui.h>
#include"minimap.h"
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

//Initializing environment grid

const char* title = "Raycaster";

int main()
{
//Initializing display windows
InitWindow(800,600, title);

SetTargetFPS(30);

//Spawn location
Minimap map(GREEN, 20,3);
map.read_Map("C:\\Project\\Engine\\assets\\map1.txt");
map.find_Spawn();

while (!WindowShouldClose())
{
	//Update
	map.check_player_Movement();


	//Draw
	ClearBackground(RAYWHITE);
	map.show_Tile();
	map.show_Player();
	EndDrawing();
}

CloseWindow();

return 0;

}