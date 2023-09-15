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

	// The Tile class is used by the Tile Map Manager to create tile maps - whats put into the Entity Component System
	class Tile {
	public:
		// Constructors/Destructor
		Tile();
		~Tile();
		Tile(EntityID id, int tile_size, int x, int y);

		EntityID id;
		int tile_size, x, y;
	};

	// The Tile Map Manager class is in charge of 
	class TileMapManager {
	public:
		// Constructor/Destructor
		TileMapManager();
		~TileMapManager();

		// Creates a tilemap given a vector of image names (tile_set), the tiles' sizes, a vector of integers describing a grid of tiles (world_map), and the number of columns and rows in
		// the tile map
		bool LoadTileMap(std::vector<string> tile_set, int tile_size, std::vector<int> world_map, int cols, int rows);

		// Returns the tile object at the inputted coordinates
		EntityID GetTile(int x, int y);

		void PrintHi(); // For testing

	private:
		std::vector<Tile> tiles;
	};
}