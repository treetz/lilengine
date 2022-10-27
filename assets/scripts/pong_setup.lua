LoadSound("bubbles", "bubbles.wav")
LoadImage("spongebob", "spongebob.png")

ball = CreateGameObject()

ball_sprite = Sprite.new()
ball_sprite.image_name = "spongebob"
ball_sprite.scale = vec3(100, 100, 100)
ball_sprite.rotation_axis = vec3(0, 0, 0)
ball_sprite.rotation_angle = 0
ball_sprite.z = 1.0
GetSprite(ball) = ball_sprite