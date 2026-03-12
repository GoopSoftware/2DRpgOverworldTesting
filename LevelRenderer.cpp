#include "LevelRenderer.h"
#include "Game.h"
#include "Constants.h"

void LevelRenderer::renderLevel(const Level& level) {
    int texture_index_x = 0;
    int texture_index_y = 0;

    for (int i = 0; i < Level::WORLD_WIDTH_; i++) {
        for (int j = 0; j < Level::WORLD_HEIGHT_; j++) {
            const Tile& tile = level.tiles[i][j];

            switch (tile.type) {
            case TILE_TYPE_DIRT:
                texture_index_x = 1;
                texture_index_y = 1;
                break;
            case TILE_TYPE_GRASS:
                texture_index_x = 5;
                texture_index_y = 4;
                break;
            case TILE_TYPE_TREE:
                texture_index_x = 5;
                texture_index_y = 5;
                break;
            case TILE_TYPE_STONE:
                texture_index_x = 4;
                texture_index_y = 4;
                break;
            default:
                texture_index_x = 1;
                texture_index_y = 1;
                break;
            }

            drawTile(tile.x * TILE_SIZE, tile.y * TILE_SIZE, texture_index_x, texture_index_y);
        }
    }
}


void LevelRenderer::drawTile(int posX, int posY, int texture_index_x, int texture_index_y) {

    Rectangle source = { static_cast<float>(texture_index_x * TILE_SIZE),
                                 static_cast<float>(texture_index_y * TILE_SIZE),
                                 static_cast<float>(TILE_SIZE),
                                 static_cast<float>(TILE_SIZE) };
    Rectangle dest = { static_cast<float>(posX),
                             static_cast<float>(posY),
                             static_cast<float>(TILE_SIZE),
                             static_cast<float>(TILE_SIZE) };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(textures_[0], source, dest, origin, 0.0f, WHITE);
}
