/* REFERENCES
 *  - Tiles and Tilemaps Overview Article 
 *	  https://developer.mozilla.org/en-US/docs/Games/Techniques/Tilemaps
 *  - How To Make A Game #18 : Tile Map & Tile Set implementation SDL2 Tutorial 
 *     https://www.youtube.com/watch?v=FQOiFUl93lI&t=405s&ab_channel=Let%27sMakeGames
 */

#pragma once

#include <vector>

#include "Types.h"
#include "Engine.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "ECS.h"
#include "ScriptingManager.h"

namespace lilengine {	
	class Tile {
	public:
		Tile();
		~Tile();
		Tile(EntityID id, int tile_size, int x, int y);

		EntityID id;
		int tile_size, x, y;
	};

	class TileMapManager {
	public:
		TileMapManager();
		~TileMapManager();

		bool LoadTileMap(std::vector<string> tile_set, int tile_size, std::vector<int> world_map, int cols, int rows);
		EntityID GetTile(int x, int y);

		void PrintHi();

	private:
		std::vector<Tile> tiles;
	};
}