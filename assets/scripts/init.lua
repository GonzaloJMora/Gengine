loadSound("moyai", "sounds/moyai.wav")
loadImage("closed", "textures/closed.png")
loadImage("open", "textures/open.png")
loadImage("rock", "textures/rock.png")
loadImage("rock_closed", "textures/rock_closed.png")


id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, 0)
sprite.name = "closed"
sprite.translate = vec3:new(0, 0, 0)
sprite.scale = vec3:new(150, 150, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 180.0

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, 0)
sprite.name = "open"
sprite.translate = vec3:new(0, 0, 0.9)
sprite.scale = vec3:new(150, 150, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 180.0

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, 50)
sprite.name = "rock_closed"
sprite.translate = vec3:new(100, 50, 0)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, -50)
sprite.name = "rock_closed"
sprite.translate = vec3:new(-100, -50, 0)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, 50)
sprite.name = "rock"
sprite.translate = vec3:new(100, 50, 1)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, -50)
sprite.name = "rock"
sprite.translate = vec3:new(-100, -50, 1)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0

