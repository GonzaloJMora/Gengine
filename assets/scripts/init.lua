loadSound("moyai", "sounds/moyai.wav")
loadImage("closed", "textures/closed.png")
loadImage("open", "textures/open.png")
loadImage("rock", "textures/rock.png")
loadImage("rock_closed", "textures/rock_closed.png")

fDownFlag = false
resetFlag = false

ids = {}
for i = 0, 17 do
	ids[i] = 0
end

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, 0)
sprite.name = "closed"
sprite.translate = vec3:new(0, 0, 0)
sprite.scale = vec3:new(150, 150, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 180.0
ids[0] = id

id = createEntity("ip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, 0)
sprite.name = "open"
sprite.translate = vec3:new(0, 0, 0.9)
sprite.scale = vec3:new(150, 150, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 180.0
ids[1] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, 75)
sprite.name = "rock_closed"
sprite.translate = vec3:new(100, 75, 0)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(0, -0.25)
ids[2] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, 75)
sprite.name = "rock"
sprite.translate = vec3:new(100, 75, 1)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(0, 0.25)
ids[3] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, -75)
sprite.name = "rock_closed"
sprite.translate = vec3:new(-100, -75, 0)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(0, 0.25)
ids[4] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, -75)
sprite.name = "rock"
sprite.translate = vec3:new(-100, -75, 1)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(0, 0.25)
ids[5] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, 75)
sprite.name = "rock_closed"
sprite.translate = vec3:new(-100, 75, 0)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(0.25, 0)
ids[6] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, 75)
sprite.name = "rock"
sprite.translate = vec3:new(-100, 75, 1)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(0.25, 0)
ids[7] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, -75)
sprite.name = "rock_closed"
sprite.translate = vec3:new(100, -75, 0)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(-0.25, 0)
ids[8] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, -75)
sprite.name = "rock"
sprite.translate = vec3:new(100, -75, 1)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 170.0
getVelocity(id).vel = vec2:new(-0.25, 0)
ids[9] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, -75)
sprite.name = "rock_closed"
sprite.translate = vec3:new(0, -75, 0)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(0.25, 0)
ids[10] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, -75)
sprite.name = "rock"
sprite.translate = vec3:new(0, -75, 1)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(0.25, 0)
ids[11] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, 75)
sprite.name = "rock_closed"
sprite.translate = vec3:new(0, 75, 0)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
getVelocity(id).vel = vec2:new(-0.25, 0)
sprite.rotateAngle = 190.0
ids[12] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(0, 75)
sprite.name = "rock"
sprite.translate = vec3:new(0, 75, 1)
sprite.scale = vec3:new(-20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(-0.25, 0)
ids[13] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, 0)
sprite.name = "rock_closed"
sprite.translate = vec3:new(-100, 0, 0)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(0, -0.25)
ids[14] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(-100, 0)
sprite.name = "rock"
sprite.translate = vec3:new(-100, 0, 1)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(0, -0.25)
ids[15] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, 0)
sprite.name = "rock_closed"
sprite.translate = vec3:new(100, 0, 0)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(0, 0.25)
ids[16] = id

id = createEntity("vip")
sprite = getSprite(id)
getPosition(id).pos = vec2:new(100, 0)
sprite.name = "rock"
sprite.translate = vec3:new(100, 0, 1)
sprite.scale = vec3:new(20, 20, 1)
sprite.rotateAxis = vec3:new(0, 0, 1)
sprite.rotateAngle = 190.0
getVelocity(id).vel = vec2:new(0, 0.25)
ids[17] = id