#pragma once

#include "TileMapManager.h"

#include "spdlog/spdlog.h"

namespace lilengine {
	TileMapManager::TileMapManager() {}
	TileMapManager::~TileMapManager() {}

	bool TileMapManager::LoadTileMap(std::vector<string> tile_set, int tile_size, std::vector<int> world_map, int cols, int rows) {
		ECS& ecs = gEngine.GetECS();
		GraphicsManager& graphics_manager = gEngine.GetGraphicsManager();
		
		for (int c = 0; c < cols; c++) {
			for (int r = 0; r < rows; r++) {
				int tile = world_map[r * cols + c];
				EntityID curr_id = ecs.Create();
				
				Sprite curr_sprite;
				curr_sprite.image_name = tile_set[tile - 1];
				curr_sprite.scale = vec3(tile_size, tile_size, 0.0f);
				curr_sprite.rotation_axis = vec3(0.0f, 0.0f, 0.0f);
				curr_sprite.rotation_angle = 0.0f;
				curr_sprite.z = 1.0f;

				Position curr_position;
				curr_position.x = (c * tile_size * 2) - 168; // Hard coded for default window size.
				curr_position.y = (r * tile_size * 2) - 90; // Hard coded for default window size.

				ecs.Get<Sprite>(curr_id) = curr_sprite;
				ecs.Get<Position>(curr_id) = curr_position;
			}
		}
		return true;
	}
}