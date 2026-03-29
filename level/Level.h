#pragma once

#include <vector>

enum TileType {
	TILE_TYPE_GRASS,
	TILE_TYPE_TREE,
	TILE_TYPE_DIRT,
	TILE_TYPE_STONE,
};


struct Tile {
	int x;
	int y;
	int type;
};

struct worldDimensions{
	int width;
	int height;
};

class Level {
public:

	Level(int width, int height)
		: width_(width),
		height_(height),
		tiles_(height, std::vector<Tile>(width))
	{
	}

	int width_ = 0; // 20 * tileWidth
	int height_ = 0; // 20 * tileHeight
	std::vector<std::vector<Tile>> tiles_;

private:
	


};