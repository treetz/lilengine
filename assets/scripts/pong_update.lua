-- Clamp the speed of the ball.
if clamp_ball_speed then
	if ball_velocity.x > 10 then
		ball_velocity.x = 10
	end 
	if ball_velocity.y > 10 then
		ball_velocity.y = 10
	end
end

-- Update the location of the ball and player hitboxes.
ball_hitbox_right = ball_position.x + (ball_hitbox_width / 2)
ball_hitbox_left = ball_position.x - (ball_hitbox_width / 2)
ball_hitbox_top = ball_position.y + (ball_hitbox_height / 2)
ball_hitbox_bottom = ball_position.y - (ball_hitbox_height / 2)

player_1_hitbox_right = player_1_position.x + (player_1_hitbox_width / 2)
player_1_hitbox_left = player_1_position.x - (player_1_hitbox_width / 2)
player_1_hitbox_top = player_1_position.y + (player_1_hitbox_height / 2)
player_1_hitbox_bottom = player_1_position.y - (player_1_hitbox_height / 2)

player_2_hitbox_right = player_2_position.x + (player_2_hitbox_width / 2)
player_2_hitbox_left = player_2_position.x - (player_2_hitbox_width / 2)
player_2_hitbox_top = player_2_position.y + (player_2_hitbox_height / 2)
player_2_hitbox_bottom = player_2_position.y - (player_2_hitbox_height / 2)

-- GAME STATES
-- If the ball is ready for the start of the put it at the center of 
-- the screen
if ball_status == "ready" then 
	ball_position.x = 0.0
	ball_position.y = 0.0
	ball_velocity.x = 0.0
	ball_velocity.y = 0.0
end

-- If it is the start of the game then give the ball a random initial
-- velocity.
if ball_status == "start" then
	if math.random(0, 1) == 0 then
		ball_velocity.x = 50.0
		ball_velocity.y = math.random(-50.0, 50.0)
	else
		ball_velocity.x = -50.0
		ball_velocity.y = math.random(-50.0, 50.0)
	end
	ball_status = "play"
end

-- PLAYER INPUT
-- Start the game if the spacebar is pressed.
if KeyIsDown(KEYBOARD.SPACE) and (ball_status == "ready") then
	ball_status = "start"
end

-- Reset the ball if the R key is pressed.
if KeyIsDown(KEYBOARD.R) and (ball_status == "play") then 
	ball_status = "ready"
end

-- Move player 1 up and down based on if the user presses the up or
-- down arrow key.
if KeyIsDown(KEYBOARD.UP) then
	player_1_velocity.y = 150
elseif KeyIsDown(KEYBOARD.DOWN) then
	player_1_velocity.y = -150
else
	player_1_velocity.y = 0
end

-- Move player 2 up and down based on if the user presses the W or S
-- key.
if KeyIsDown(KEYBOARD.W) then
	player_2_velocity.y = 150
elseif KeyIsDown(KEYBOARD.S) then
	player_2_velocity.y = -150
else
	player_2_velocity.y = 0
end

-- HITBOXES
-- Collision between the ball and the left side of player 1.
if (ball_hitbox_right > player_1_hitbox_left) and ( ( (ball_hitbox_top <= player_1_hitbox_top) and (ball_hitbox_bottom >= player_1_hitbox_bottom) ) or ( (ball_hitbox_top > player_1_hitbox_top) and (ball_hitbox_bottom < player_1_hitbox_top) ) or ( (ball_hitbox_bottom < player_1_hitbox_bottom) and (ball_hitbox_top > player_1_hitbox_bottom) ) ) then 
	ball_velocity.x = ball_velocity.x * -1 * ball_speed_multiplier
	PlaySound("bubbles")

-- Collision between the ball and the right side of player 2.
elseif (ball_hitbox_left < player_2_hitbox_right) and ( ( (ball_hitbox_top <= player_2_hitbox_top) and (ball_hitbox_bottom >= player_2_hitbox_bottom) ) or ( (ball_hitbox_top > player_2_hitbox_top) and (ball_hitbox_bottom < player_2_hitbox_top) ) or ( (ball_hitbox_bottom < player_2_hitbox_bottom) and (ball_hitbox_top > player_2_hitbox_bottom) ) ) then 
	ball_velocity.x = ball_velocity.x * -1 * ball_speed_multiplier
	PlaySound("bubbles")

-- Collision between the ball and the right side of the screen.
elseif (ball_position.x + (ball_hitbox_width / 2)) > (GetWindowWidth() / 4.5) then
	ball_status = "ready"
	player_2_score = player_2_score + 1
	print("\nPlayer 2 scored!\nThe score is now " .. player_2_score .. " to " .. player_1_score)
	PlaySound("score")

-- Collision between the ball and the left side of the screen.
elseif (ball_position.x - (ball_hitbox_width / 2)) < ((GetWindowWidth() / 4.5) * -1) then
	ball_status = "ready"
	player_1_score = player_1_score + 1
	print("\nPlayer 2 scored!\nThe score is now " .. player_2_score .. " to " .. player_1_score)
	PlaySound("bubbles")

-- Collision between the ball and the top and bottom sides of the 
-- screen.
elseif (ball_position.y + (ball_hitbox_height / 2)) > (GetWindowHeight() / 4.5) then
	ball_velocity.y = ball_velocity.y * -1 --* ball_speed_multiplier
	PlaySound("bubbles")

elseif (ball_position.y - (ball_hitbox_height / 2)) < ((GetWindowHeight() / 4.5) * -1) then
	ball_velocity.y = ball_velocity.y * -1 --* ball_speed_multiplier
	PlaySound("bubbles")
end

-- BALL AND PLAYER MOVEMENT
-- Move the ball according to its velocity.
ball_position.x = ball_position.x + (ball_velocity.x / 60)
ball_position.y = ball_position.y + (ball_velocity.y / 60)

player_1_position.y = player_1_position.y + (player_1_velocity.y / 60)
player_2_position.y = player_2_position.y + (player_2_velocity.y / 60)