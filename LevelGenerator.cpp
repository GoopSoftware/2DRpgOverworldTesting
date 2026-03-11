#include "LevelGenerator.h"
#include "raylib.h"

void LevelGenerator::generateWorld(Level& level) {
    for (int i = 0; i < Level::WORLD_WIDTH_; i++) {
        for (int j = 0; j < Level::WORLD_HEIGHT_; j++) {
            level.tiles[i][j] = Tile{
                i,
                j,
                static_cast<TileType>(GetRandomValue(TILE_TYPE_GRASS, TILE_TYPE_STONE))
            };
        }
    }
}

void LevelGenerator::generateDungeon(Level& level) {
    for (int i = 0; i < Level::WORLD_WIDTH_; i++) {
        for (int j = 0; j < Level::WORLD_HEIGHT_; j++) {
            level.tiles[i][j] = Tile{
                i,
                j,
                static_cast<TileType>(GetRandomValue(TILE_TYPE_DIRT, TILE_TYPE_STONE))
            };
        }
    }
}

