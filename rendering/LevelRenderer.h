#pragma once
#include <raylib.h>

#include "../level/Level.h"
#include "../Constants.h"

class LevelRenderer {
public:
	LevelRenderer(Texture2D* textures) : 
		textures_(textures) 
	{}
	void renderLevel(const Level& level);

private:
	Texture2D* textures_;


	void drawTile(int posX, int posY, int texture_index_x, int texture_index_y);

};