LoadSound("bubbles", "bubbles.wav")
LoadImage("spongebob", "spongebob.png")

ball = CreateGameObject()

ball_sprite = GetSprite(ball)
ball_sprite.image_name = "spongebob"
ball_sprite.scale = vec3(100.0, 100.0, 0.0)
ball_sprite.rotation_axis = vec3(0, 0, 0)
ball_sprite.rotation_angle = 0.0
ball_sprite.z = 1.0

-- Things that do not work:

--GetSprite(ball)= ball_sprite
--GetSprite(ball) = Sprite.new()

--ball_sprite = GetSprite(ball)
--ball_sprite.image_name = "spongebob"

--GetSprite(ball).image_name = "spongebob"
--GetSprite(ball).scale = vec3(100.0, 100.0, 0.0)
--GetSprite(ball).rotation_axis = vec3(0, 0, 0)
--GetSprite(ball).rotation_angle = 0.0
--GetSprite(ball).z = 1.0

--GetPosition(ball).x = 50.0
--GetPosition(ball).y = 0.0