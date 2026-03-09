#pragma once
#include "raylib.h"
#include "Player.h"
#include "DungeonDoor.h"
#include "Enemy.h"


enum textureAsset {
	TEXTURE_TILEMAP = 0
};

enum tyleType {
	TILE_TYPE_DIRT,
	TILE_TYPE_GRASS,
	TILE_TYPE_TREE,
	TILE_TYPE_STONE,
};

struct sTile {
	int x;
	int y;
	int type;
};


class Game
{

public:

	void gameStartup();
	void gameUpdate();
	void gameRender();
	void drawTile(int x, int y, int tileX, int tileY);
	void gameShutdown();

private:

	Player* player = new Player();
	Enemy* orc = new Enemy();
	DungeonDoor* dungeonGate = new DungeonDoor();

	static constexpr int TILE_WIDTH = 8;
	static constexpr int TILE_HEIGHT = 8;
	
	static constexpr int MAX_TEXTURES = 1;

	static constexpr int WORLD_WIDTH = 20; // 20 * tileWidth
	static constexpr int WORLD_HEIGHT = 20; // 20 * tileHeight

	Texture2D textures[MAX_TEXTURES];
	
	sTile world[WORLD_WIDTH][WORLD_HEIGHT];
	sTile dungeon[WORLD_WIDTH][WORLD_HEIGHT];

	Camera2D camera = { 0 };

};

