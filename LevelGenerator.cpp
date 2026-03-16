#include "LevelGenerator.h"
#include "raylib.h"
#include <iostream>

void LevelGenerator::generateOverWorld(Level& level) {
    for (int i = 0; i < Level::WORLD_WIDTH_; i++) {
        for (int j = 0; j < Level::WORLD_HEIGHT_; j++) {
            level.tiles[i][j] = Tile{
                i,
                j,
                static_cast<TileType>(GetRandomValue(TILE_TYPE_DIRT, TILE_TYPE_DIRT))
            };
        }
    }
}

void LevelGenerator::generateWorld(Level& level) {
    int dungeonI = 10;
    int dungeonJ = 10;
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

std::vector<SpawnPoint> LevelGenerator::generateMonsterSpawns(int monsterCount, Zone zone) {
    std::vector<SpawnPoint> spawns;

    for (int i = 0; i < monsterCount; i++) {
        int attempts = 0;
        const int maxAttempts = 10;

        while (attempts < maxAttempts) {
            int iPos = GetRandomValue(0, 19);
            int jPos = GetRandomValue(0, 19);
            

            if (iPos == 10 && jPos == 10) {
                attempts++;
                continue;
            }

            if (tileIsTakenByEnemy(iPos, jPos, spawns)) {
                attempts++;
                continue;
            }

            spawns.push_back(SpawnPoint(iPos, jPos));
            break;
        }
    }

    int iteration = 1;
    for (const SpawnPoint& spawn : spawns) {
        std::string zoneText;
        if (zone == 2) {
            zoneText = "World ";
        }
        else if (zone == 3) {
            zoneText = "Dungeon ";
        }
        
        std::cout << "Enemy: " << iteration << " Zone: " << zoneText << "i:" << spawn.i << " | j:" << spawn.j << std::endl;
        iteration++;
    }
    return spawns;
}


bool LevelGenerator::tileIsTakenByEnemy(int i, int j, const std::vector<SpawnPoint>& spawns) {
    for (const SpawnPoint& spawn : spawns) {
		if (spawn.i == i && spawn.j == j) {
			return true;
		}
	}
	return false;
}
