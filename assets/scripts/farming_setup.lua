-- Load in all assets
--LoadSound("bubbles", "bubbles.wav")
LoadImage("psf", "psf.png") -- psf = player standing front
LoadImage("psb", "psb.png") -- psb = player standing back
LoadImage("pmf1", "pmf1.png") -- pmf = player moving front
LoadImage("pmb1", "pmb1.png") -- pmb = player moving back
LoadImage("pl", "pl.png")   -- pl = player left
LoadImage("pr", "pr.png")   -- pr = player right

-- Create the ball game object and set up its components
player = CreateGameObject()

-- Player Sprite Component
player_sprite = GetSprite(player)
player_sprite.image_name = "player_front"
player_sprite.scale = vec3.new(5.0, 5.0, 0.0)
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

delta_time = 0.0