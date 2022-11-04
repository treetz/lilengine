-- Load in all assets
LoadSound("bubbles", "bubbles.wav")
LoadSound("score", "score.wav")
LoadImage("spongebob", "spongebob.png")
LoadImage("paddle", "paddle.png")

-- Create the ball game object and set up its components
ball = CreateGameObject()

ball_sprite = GetSprite(ball)
ball_sprite.image_name = "spongebob"
ball_sprite.scale = vec3.new(10.0, 10.0, 0.0)
ball_sprite.rotation_axis = vec3.new(0.0, 0.0, 0.0)
ball_sprite.rotation_angle = 0
ball_sprite.z = 0.0

ball_position = GetPosition(ball)
ball_position.x = 0.0
ball_position.y = 0.0

ball_velocity = GetVelocity(ball)
ball_velocity.x = 0.0
ball_velocity.y = 0.0

ball_hitbox_width = 15.0
ball_hitbox_height = 13.0

-- Create the player game objects and set up their components.
-- Player 1
player_1 = CreateGameObject()

player_1_sprite = GetSprite(player_1)
player_1_sprite.image_name = "paddle"
player_1_sprite.scale = vec3.new(15.0, 15.0, 0.0)
player_1_sprite.rotation_axis = vec3.new(0.0, 0.0, 0.0)
player_1_sprite.rotation_angle = 0
player_1_sprite.z = 0.1

player_1_position = GetPosition(player_1)
player_1_position.x = 165.0
player_1_position.y = 0.0

player_1_velocity = GetVelocity(player_1)
player_1_velocity.x = 0.0
player_1_velocity.y = 0.0

player_1_hitbox_width = 5.0
player_1_hitbox_height = 4.0

-- Player 2
player_2 = CreateGameObject()

player_2_sprite = GetSprite(player_2)
player_2_sprite.image_name = "paddle"
player_2_sprite.scale = vec3.new(15.0, 15.0, 0.0)
player_2_sprite.rotation_axis = vec3.new(0.0, 0.0, 0.0)
player_2_sprite.rotation_angle = 0
player_2_sprite.z = 0.1

player_2_position = GetPosition(player_2)
player_2_position.x = -165.0
player_2_position.y = 0.0

player_2_velocity = GetVelocity(player_2)
player_2_velocity.x = 0.0
player_2_velocity.y = 0.0

player_2_hitbox_width = 4.25
player_2_hitbox_height = 4.25

player_1_score = 0
player_2_score = 0

ball_status = "ready"
ball_speed_multiplier = 1.5 
clamp_ball_speed = false

print("\nWelcome to Pong!")