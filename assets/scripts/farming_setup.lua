-- Load in all assets
-- Player Sprite Assets
LoadImage("psf", "psf.png") -- psf = player standing front
LoadImage("psb", "psb.png") -- psb = player standing back
LoadImage("pmf1", "pmf1.png") -- pmf = player moving front
LoadImage("pmb1", "pmb1.png") -- pmb = player moving back
LoadImage("pl", "pl.png")   -- pl = player left
LoadImage("pr", "pr.png")   -- pr = player right

-- Tile Map Assets
LoadImage("grass_1", "grass_1.png");
LoadImage("grass_2", "grass_2.png");
LoadImage("grass_3", "grass_3.png");
LoadImage("grass_4", "grass_4.png");

-- Load in the tile map *** WORK IN PROGRESS ***
--tile_set = {"grass_1", "grass_2", "grass_3", "grass_4"}
--world_map = {1}
--LoadTileMap(tile_set, 10, world_map, 1, 1)

--LoadSound("bubbles", "bubbles.wav")

-- Create the ball game object and set up its components
player = CreateGameObject()

-- Player Sprite Component
player_sprite = GetSprite(player)
player_sprite.image_name = "player_front"
player_sprite.scale = vec3.new(10.0, 10.0, 0.0)
player_sprite.rotation_axis = vec3.new(0.0, 0.0, 0.0)
player_sprite.rotation_angle = 0
player_sprite.z = 0.0

-- Player Position Component
player_position = GetPosition(player)
player_position.x = 0.0
player_position.y = 0.0

-- Player Velocity Component
player_velocity = GetVelocity(player)
player_velocity.x = 0.0
player_velocity.y = 0.0

-- Player Hitbox
player_hitbox_width = 15.0
player_hitbox_height = 13.0

-- Player Movement Speed
player_movement_speed = 50 
player_direction = "Down"

-- Time
delta_time = 0.0