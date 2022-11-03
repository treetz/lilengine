-- Load in all assets
LoadSound("bubbles", "bubbles.wav")
LoadImage("spongebob", "spongebob.png")

-- Create the ball game object and set up its components
ball = CreateGameObject()

ball_sprite = GetSprite(ball)
ball_sprite.image_name = "spongebob"
ball_sprite.scale = vec3.new(10.0, 10.0, 10.0)
ball_sprite.rotation_axis = vec3.new(0.0, 0.0, 0.0)
ball_sprite.rotation_angle = 0
ball_sprite.z = 1.0

ball_position = GetPosition(ball)
ball_position.x = 0.0
ball_position.y = 0.0

ball_velocity = GetVelocity(ball)
ball_velocity.x = 0.0
ball_velocity.y = 0.0

ball_hitbox_right = 10.0
ball_hitbox_left = 10.0
ball_hitbox_top = 5.0
ball_hitbox_bottom = 5.0

-- Create the player game objects and set up their components
player_1 = CreateGameObject()



ball_status = "ready"