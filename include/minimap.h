#include<raylib.h>
#include<raymath.h>
#include<raygui.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;


class Minimap 
{
private:
	int dotX;
	int dotY;
	Color dotCol;
	int speed;

	float angle;
	int gap;
	int rows;
	string *map;
	int blockSize;

public:
	Minimap(Color col,int size,int spd);

	void read_Map(string mapname);

	void show_Tile();

	void find_Spawn();

	void show_Player();

	void check_player_Movement();
	

};

Minimap::Minimap(Color col, int size,int spd)
{
	dotCol = col;
	blockSize = size;
	dotX = blockSize/2;
	dotY = blockSize/2;
	gap = 1;

	angle = 0;
	rows = 0;
	map = nullptr;
	speed = spd;



}

void Minimap::read_Map(string mapname)
{
	ifstream filereader(mapname);
	if (!filereader.is_open())
	{
		cout << "Map opening failure!" << endl;
		exit(0);
	}

	string text;
	int cnt = 0;
	while (getline(filereader, text))
	{
		cnt++;
	}

	filereader.clear();
	filereader.seekg(0);

	rows = cnt;
	map = new string[rows];

	for (int i = 0; i < rows; i++)
	{
		getline(filereader, text);
		map[i] = text;
		//cout << map[i];
	}

}

void Minimap::show_Tile()
{
	string maprow;
	for (int i = 0; i < rows; i++)
	{
		maprow = map[i];
		for (int j = 0; j < maprow.length(); j++)
		{
			if (maprow[j] == '0')
			{
				DrawRectangle(j*(blockSize+gap), i*(blockSize+gap), blockSize, blockSize, BLACK);
			}
			else if (maprow[j] =='1')
			{
				DrawRectangle(j * (blockSize + gap), i * (blockSize + gap), blockSize, blockSize, RED);
			}
			else if (maprow[j] == '2')
			{
				DrawRectangle(j * (blockSize + gap), i * (blockSize + gap), blockSize, blockSize, BLUE);
			}
		}
	}
}

void Minimap::find_Spawn()
{
	string maprow;
	bool found = false;
	for (int i = 0; i < rows&&!found; i++)
	{
		maprow = map[i];
		for (int j = 0; j < maprow.length()&&!found; j++)
		{
			if (map[i][j] == '1')
			{
				dotX = (j * (blockSize + gap))+blockSize/2;
				dotY = (i * (blockSize + gap))+blockSize/2;
				found = true;
			}
		}
	}
}

void Minimap::show_Player()
{
	DrawCircle(dotX, dotY, 5, dotCol);
}

void Minimap::check_player_Movement()
{
	if (IsKeyDown(KEY_W)&&dotY > blockSize/2)
	{
		dotY -= speed;
	}
	else if (IsKeyDown(KEY_S)&& dotY<(rows * (blockSize + gap)) - blockSize/2)
	{
		dotY += speed;
	}
	else if (IsKeyDown(KEY_A) && dotX > blockSize/2)
	{
		dotX -= speed;
	}
	else if (IsKeyDown(KEY_D) && dotX<(rows * (blockSize + gap)) - blockSize/2)
	{
		dotX += speed;
	}

}