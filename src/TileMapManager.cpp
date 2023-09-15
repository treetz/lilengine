#pragma once

#include "TileMapManager.h"

#include "spdlog/spdlog.h"

namespace lilengine {
	Tile::Tile() {}
	Tile::~Tile() {}
	Tile::Tile(EntityID id, int tile_size, int x, int y) {
		this->id = id;
		this->tile_size = tile_size;
		this->x = x;
		this->y = y;
	}

	TileMapManager::TileMapManager() {}
	TileMapManager::~TileMapManager() {}

	bool TileMapManager::LoadTileMap(std::vector<string> tile_set, int tile_size, std::vector<int> world_map, int cols, int rows) {
		ECS& ecs = gEngine.GetECS();
		GraphicsManager& graphics_manager = gEngine.GetGraphicsManager();
		
		// For each column in the tile map...
		for (int c = 0; c < cols; c++) {
			// For each row in the tile map
			for (int r = 0; r < rows; r++) {
				// Get the sprite's id from the world_map vector
				int sprite_id = world_map[r * cols + c]; // world_map is a vector representing a grid of tiles

				// Add the tile to the Entity Component System
				EntityID tile_id = ecs.Create();

				// Get the tile's sprite information
				Sprite curr_sprite;
				curr_sprite.image_name = tile_set[sprite_id - 1];
				curr_sprite.scale = vec3(tile_size, tile_size, 0.0f);
				curr_sprite.rotation_axis = vec3(0.0f, 0.0f, 0.0f);
				curr_sprite.rotation_angle = 0.0f;
				curr_sprite.z = 1.0f;

				// Calculate the tile's x and y coordinates
				int x = (c * tile_size * 2) - 168; // Hard coded for default window size.
				int y = (r * tile_size * 2) - 90; // Hard coded for default window size.

				// Set the tile's x and y coordinates
				Position curr_position;
				curr_position.x = x;
				curr_position.y = y;

				// Assign the sprite and position to the tile within the Entity Component System
				ecs.Get<Sprite>(tile_id) = curr_sprite;
				ecs.Get<Position>(tile_id) = curr_position;

				Tile tile(tile_id, tile_size, x, y);
				tiles.push_back(tile);
			}
		}
		return true;
	}

	// Returns the tile object at the inputted coordinates
	EntityID TileMapManager::GetTile(int x, int y) {
		spdlog::info("Hi from GetTile()"); // For Testing
		for (Tile t : tiles) {
			int x1 = t.x - (t.tile_size / 2);
			int y1 = t.y - (t.tile_size / 2);
			int x2 = t.x + (t.tile_size / 2);
			int y2 = t.y + (t.tile_size / 2);
			if (x > x1 && x < x2 && y > y1 && y < y2) {
				return t.id;
			}
		}
		return -1;
	}

	// For testing
	void TileMapManager::PrintHi() {
		spdlog::info("hi");
	}
}