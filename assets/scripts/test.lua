if not fDownFlag and isKeyDown(KEYBOARD.F) then
	playSound("moyai")
	fDownFlag = true
	resetFlag = true

	for i = 0, 17 do
		if i == 0 then
			sprite = getSprite(ids[i])
			sprite.translate = vec3:new(0, 0, 0.9)
		
		elseif i == 1 then
			sprite = getSprite(ids[i])
			sprite.translate = vec3:new(0, 0, 0)

		else
			sprite = getSprite(ids[i])

			if sprite.translate.z > 0 then
				sprite.translate = sprite.translate - vec3:new(0, 0, 1)

			elseif sprite.translate.z < 1 then
				sprite.translate = sprite.translate + vec3:new(0, 0, 1)

			end

		end
	end

elseif not isKeyDown(KEYBOARD.F) then
	fDownFlag = false

	for i = 0, 17 do
		if i == 0 then
			sprite = getSprite(ids[i])
			sprite.translate = vec3:new(0, 0, 0)
		
		elseif i == 1 then
			sprite = getSprite(ids[i])
			sprite.translate = vec3:new(0, 0, 0.9)

		else
			sprite = getSprite(ids[i])
			vel = getVelocity(ids[i])

			if sprite.translate.y == 75 and sprite.translate.x <= -100 then
				vel.vel = vec2:new(0, -0.25)

			elseif sprite.translate.x == -100 and sprite.translate.y <= -75 then
				vel.vel = vec2:new(0.25, 0)

			elseif sprite.translate.y == -75 and sprite.translate.x >= 100 then
				vel.vel = vec2:new(0, 0.25)

			elseif sprite.translate.x == 100 and sprite.translate.y >= 75 then
				vel.vel = vec2:new(-0.25, 0)
				
			end

			sprite.translate = sprite.translate + vec3:new(vel.vel.x, vel.vel.y, 0)

			sprite.rotateAngle = sprite.rotateAngle - 0.35

			if resetFlag and sprite.translate.z > 0 then
				sprite.translate = vec3:new(sprite.translate.x, sprite.translate.y, 0)

			elseif resetFlag and sprite.translate.z < 1 then
				sprite.translate = vec3:new(sprite.translate.x, sprite.translate.y, 1)

			end

		end
	end

	resetFlag = false
end