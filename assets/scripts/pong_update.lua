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
-- Make the ball bounce off the four "walls" of the screen.
if (ball_position.x + ball_hitbox_right) > (GetWindowWidth() / 4.5) then
	ball_velocity.x = ball_velocity.x * -1.1
	PlaySound("bubbles")
end

if (ball_position.x - ball_hitbox_left) < ((GetWindowWidth() / 4.5) * -1) then
	ball_velocity.x = ball_velocity.x * -1.1
	PlaySound("bubbles")
end

if (ball_position.y + ball_hitbox_top) > (GetWindowHeight() / 4.5) then
	ball_velocity.y = ball_velocity.y * -1.1
	PlaySound("bubbles")
end

if (ball_position.y - ball_hitbox_bottom) < ((GetWindowHeight() / 4.5) * -1) then
	ball_velocity.y = ball_velocity.y * -1.1
	PlaySound("bubbles")
end

-- Make the ball bounce off the players.
--if ((ball_position.x - ball_hitbox_left) < (player_2_position.x + player_2_hitbox_right)) then
--	if (ball_position.y < player_2_position.y + player_2_hitbox_top) then
--		if (ball_position.y > player_2_position.y - player_2_hitbox_bottom) then
--			ball_velocity.x = ball_velocity.x * -1.1
--			PlaySound("bubbles")
--		end
--	end
--end


-- Bound the players so they cannot move off the screen
--if (player_1_position.y + player_1_hitbox_top) > (GetWindowHeight() / 4.5) then
-- 	player_1_velocity.y = ball_velocity.y * -1.0
--end

-- BALL AND PLAYER MOVEMENT
-- Move the ball according to its velocity.
ball_position.x = ball_position.x + (ball_velocity.x / 60)
ball_position.y = ball_position.y + (ball_velocity.y / 60)

player_1_position.y = player_1_position.y + (player_1_velocity.y / 60)
player_2_position.y = player_2_position.y + (player_2_velocity.y / 60)