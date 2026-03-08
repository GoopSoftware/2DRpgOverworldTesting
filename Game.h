#pragma once
#include "raylib.h"
#include "Player.h"



enum textureAsset {
	TEXTURE_TILEMAP = 0
};



struct sTile {
	int x;
	int y;
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

	Player player;

	static constexpr int TILE_WIDTH = 8;
	static constexpr int TILE_HEIGHT = 8;
	
	static constexpr int MAX_TEXTURES = 1;

	static constexpr int WORLD_WIDTH = 20; // 20 * tileWidth
	static constexpr int WORLD_HEIGHT = 20; // 20 * tileHeight

	Texture2D textures[MAX_TEXTURES];
	
	sTile world[WORLD_WIDTH][WORLD_HEIGHT];

	Camera2D camera = { 0 };

};

