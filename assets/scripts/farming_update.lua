-- USER INPUT
-- PLAYER MOVEMENT
if KeyIsDown(KEYBOARD.W) then
	player_sprite.image_name = "pmb1"
	player_direction = "Up"
	player_velocity.x = 0
	player_velocity.y = player_movement_speed
elseif KeyIsDown(KEYBOARD.A) then
	player_sprite.image_name = "pl"
	player_direction = "Left"
	player_velocity.x = -player_movement_speed
	player_velocity.y = 0
elseif KeyIsDown(KEYBOARD.S) then
	player_sprite.image_name = "pmf1"
	player_direction = "Down"
	player_velocity.x = 0
	player_velocity.y = -player_movement_speed
elseif KeyIsDown(KEYBOARD.D) then
	player_sprite.image_name = "pr"
	player_direction = "Right"
	player_velocity.x = player_movement_speed
	player_velocity.y = 0
else
	if player_direction == "Up" then
		player_sprite.image_name = "psb"
	elseif player_direction == "Down" then
		player_sprite.image_name = "psf"
	end
	player_velocity.x = 0
	player_velocity.y = 0
end

-- PLAYER MOVEMENT UPDATE
player_position.x = player_position.x + (player_velocity.x / 60)
player_position.y = player_position.y + (player_velocity.y / 60)

delta_time = delta_time + (1 / 60)