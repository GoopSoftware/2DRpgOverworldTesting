#pragma once
#include "raylib.h"
#include "Player.h"
#include "DungeonDoor.h"
#include "Enemy.h"
#include "LevelGenerator.h"
#include "LevelRenderer.h"


enum textureAsset {
	TEXTURE_TILEMAP = 0
};

struct Timer {
	double startTime;
	double lifeTime;
	bool isActive;
};


class Game
{

public:

	void gameStartup();
	void gameUpdate();
	void gameRender();
	void gameShutdown();
	void drawTile(int posX, int posY, int texture_index_x, int texture_index_y);

	void startTimer(Timer* timer, double lifetime);
	bool isTimerDone(Timer timer);
	double getElapsed(Timer timer);

private:

	Entity* interactTarget;

	Player* player = new Player();
	Enemy* orc = new Enemy();
	DungeonDoor* dungeonGate = new DungeonDoor();

	static constexpr int TILE_WIDTH = 8;
	static constexpr int TILE_HEIGHT = 8;
	
	static constexpr int MAX_TEXTURES = 1;

	Texture2D textures[MAX_TEXTURES];

	Level worldLevel;
	Level dungeonLevel;
	Level* currentLevel = nullptr;

	LevelGenerator* levelGenerator = new LevelGenerator();
	LevelRenderer* levelRenderer = nullptr;

	Camera2D camera = { 0 };
	Timer combatTextTimer;

};

