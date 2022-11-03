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

-- KEYBOARD INPUT
-- Start the game if the spacebar is pressed.
if KeyIsDown(KEYBOARD.SPACE) and (ball_status == "ready") then
	ball_status = "start"
end

-- Reset the ball if the R key is pressed.
if KeyIsDown(KEYBOARD.R) and (ball_status == "play") then 
	ball_status = "ready"
end

-- HITBOXES
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

-- BALL MOVEMENT
-- Move the ball according to its velocity.
ball_position.x = ball_position.x + (ball_velocity.x / 60)
ball_position.y = ball_position.y + (ball_velocity.y / 60)

print(ball_position.x)
print(ball_position.y)