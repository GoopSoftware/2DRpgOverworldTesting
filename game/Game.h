#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"

#include "../entities/Player.h"
#include "../input/InputHandler.h"
#include "../entities/Enemy.h"
#include "../commands/Command.h"
#include "../level/LevelManager.h"
#include "../rendering/LevelRenderer.h"
#include "../interaction/InteractionSystem.h"
#include "../interaction/TargetSystem.h"



enum textureAsset {
	TEXTURE_TILEMAP = 0
};

struct Timer {
	double startTime;
	double lifeTime;
	bool isActive;
};

struct FloatingText {
	std::string text;
	float x;
	float y;
	float lifetime;
	float elapsed;
	bool active;
};

class Game
{

public:

	void gameStartup();
	void gameUpdate();
	void gameRender();
	void gameShutdown();
	void drawTile(int posX, int posY, int texture_index_x, int texture_index_y, Color color);

	/*void updateSprite();
	void drawSprite();*/

	void startTimer(Timer* timer, double lifetime);
	bool isTimerDone(Timer timer);
	double getElapsed(Timer timer);


	// Timer struct code
	// TODO move into its own system


private:

	Texture2D overWorld;


	LevelManager* levelManager;
	LevelRenderer* levelRenderer = nullptr;
	InteractionSystem* interactionSystem = nullptr;

	Entity* interactTarget;
	Player* player;

	static constexpr int MAX_TEXTURES = 1;

	Texture2D textures[MAX_TEXTURES];

	Level worldLevel;
	Level dungeonLevel;

	Camera2D camera = { 0 };
	Timer combatTextTimer;

	TargetSystem* targetSystem = nullptr;

	
	// Timer struct code
	// TODO move into its own system
	std::vector<FloatingText> floatingTexts;

	// Sprite animation code
	// TODO move into its own system
	Texture2D playerTexture;
	int frame = 0;
	float timer = 0.0f;
	float speed = 0.1f;
	int frameWidth = playerTexture.width / 6;


};