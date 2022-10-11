-- querys input state and quits the game
if isKeyDown(KEYBOARD.Q) then
	quit()
end

--loading anything through scripts is broken?

--loadSound("moyai", "sounds/moyai.wav")
--loadImage("closed", "textures/closed.png")
--loadImage("open", "textures/open.png")
--loadImage("rock", "textures/rock.png")
--loadImage("rock_closed", "textures/rock_closed.png")

--anything to do with images is broken

--local closedID = createEntity("ip")
--local closedSprite = getSprite(closedID)
--getPosition(closedID) = vec2(0, 0)
--closedSprite.name = "closed"
--closedSprite.translate = vec3(0, 0, 0)
--closedSprite.scale = vec3(150, 150, 1)
--closedSprite.rotateAxis = vec3(0, 0, 1)
--closedSprite.rotateAngle = 180.0

-- querys input state and plays sound
if isKeyDown(KEYBOARD.F) then
	playSound("moyai")
end