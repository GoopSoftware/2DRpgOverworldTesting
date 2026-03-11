#pragma once


enum TileType {
	TILE_TYPE_DIRT,
	TILE_TYPE_GRASS,
	TILE_TYPE_TREE,
	TILE_TYPE_STONE,
};


struct Tile {
	int x;
	int y;
	int type;
};


class Level {
public:
	static constexpr int WORLD_WIDTH_ = 20; // 20 * tileWidth
	static constexpr int WORLD_HEIGHT_ = 20; // 20 * tileHeight
	static constexpr int TILE_SIZE_ = 8;
	
	Tile tiles[WORLD_WIDTH_][WORLD_WIDTH_];

private:
	


};