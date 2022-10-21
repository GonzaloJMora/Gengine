if not fDownFlag and isKeyDown(KEYBOARD.F) then
	playSound("moyai")
	fDownFlag = true
	resetFlag = true

	for i = 0, 13 do
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

	for i = 0, 13 do
		if i == 0 then
			sprite = getSprite(ids[i])
			sprite.translate = vec3:new(0, 0, 0)
		
		elseif i == 1 then
			sprite = getSprite(ids[i])
			sprite.translate = vec3:new(0, 0, 0.9)

		else
			sprite = getSprite(ids[i])

			if resetFlag and sprite.translate.z > 0 and i == 2 or i == 3 or i == 6 or i == 7 or i == 10 or i == 11 then
				sprite.translate = sprite.translate - vec3:new(0, 0, 1)

			elseif resetFlag and sprite.translate.z < 1 and i == 4 or i == 5 or i == 8 or i == 9 or i == 12 or i == 13 then
				sprite.translate = sprite.translate + vec3:new(0, 0, 1)

			end

		end
	end

	resetFlag = false
end

--local id1, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11, id12, id13, id14 = ...

--[[s1 = getSprite(id1)
s2 = getSprite(id2)
s3 = getSprite(id3)
s4 = getSprite(id4)
s5 = getSprite(id5)
s6 = getSprite(id6)
s7 = getSprite(id7)
s8 = getSprite(id8)
s9 = getSprite(id9)
s10 = getSprite(id10)
s11 = getSprite(id11)
s12 = getSprite(id12)
s13 = getSprite(id13)
s14 = getSprite(id14)

if isKeyDown(KEYBOARD.F) then
	playSound("moyai")
	
	s1.translate = vec3:new(0, 0, 0.9)
	s2.translate = vec3:new(0, 0, 0)

	if s3.translate.z < 1 then
		s3.translate = s3.translate + vec3:new(0, 0, 1)
		s4.translate = s4.translate + vec3:new(0, 0, 1)
		s7.translate = s7.translate + vec3:new(0, 0, 1)
		s8.translate = s8.translate + vec3:new(0, 0, 1)
		s11.translate = s11.translate + vec3:new(0, 0, 1)
		s12.translate = s12.translate + vec3:new(0, 0, 1)
	end

	if s5.translate.z > 0 then
		s5.translate = s5.translate - vec3:new(0, 0, 1)
		s6.translate = s6.translate - vec3:new(0, 0, 1)
		s9.translate = s9.translate - vec3:new(0, 0, 1)
		s10.translate = s10.translate - vec3:new(0, 0, 1)
		s13.translate = s13.translate - vec3:new(0, 0, 1)
		s14.translate = s14.translate - vec3:new(0, 0, 1)
	end

else 
	s1.translate = vec3:new(0, 0, 0)
	s2.translate = vec3:new(0, 0, 0.9)

	if s3.translate.z > 0 and s4.translate.z > 0 then
		s3.translate = s3.translate - vec3:new(0, 0, 1)
		s4.translate = s4.translate - vec3:new(0, 0, 1)
		s7.translate = s7.translate - vec3:new(0, 0, 1)
		s8.translate = s8.translate - vec3:new(0, 0, 1)
		s11.translate = s11.translate - vec3:new(0, 0, 1)
		s12.translate = s12.translate - vec3:new(0, 0, 1)
	end

	if s5.translate.z < 1 and s6.translate.z < 1 then
		s5.translate = s5.translate + vec3:new(0, 0, 1)
		s6.translate = s6.translate + vec3:new(0, 0, 1)
		s9.translate = s9.translate + vec3:new(0, 0, 1)
		s10.translate = s10.translate + vec3:new(0, 0, 1)
		s13.translate = s13.translate + vec3:new(0, 0, 1)
		s14.translate = s14.translate + vec3:new(0, 0, 1)
	end

	s3.rotateAngle = s3.rotateAngle + 0.35
	s4.rotateAngle = s4.rotateAngle - 0.35
	s5.rotateAngle = s5.rotateAngle + 0.35
	s6.rotateAngle = s6.rotateAngle - 0.35
	s7.rotateAngle = s7.rotateAngle + 0.35
	s8.rotateAngle = s8.rotateAngle - 0.35
	s9.rotateAngle = s9.rotateAngle + 0.35
	s10.rotateAngle = s10.rotateAngle - 0.35
	s11.rotateAngle = s11.rotateAngle + 0.35
	s12.rotateAngle = s12.rotateAngle - 0.35
	s13.rotateAngle = s13.rotateAngle + 0.35
	s14.rotateAngle = s14.rotateAngle - 0.35

	if s3.translate.y == 50 and s3.translate.x > -100 then
		s3.translate = s3.translate + vec3:new(-0.25, 0, 0)
		s5.translate = s5.translate + vec3:new(-0.25, 0, 0)

	elseif s3.translate.x == -100 and s3.translate.y > -50 then
		s3.translate = s3.translate + vec3:new(0, -0.25, 0)
		s5.translate = s5.translate + vec3:new(0, -0.25, 0)

	elseif s3.translate.y == -50 and s3.translate.x < 100 then
		s3.translate = s3.translate + vec3:new(0.25, 0, 0)
		s5.translate = s5.translate + vec3:new(0.25, 0, 0)

	elseif s3.translate.x == 100 and s3.translate.y < 50 then
		s3.translate = s3.translate + vec3:new(0, 0.25, 0)
		s5.translate = s5.translate + vec3:new(0, 0.25, 0)

	end

	if s4.translate.y == 50 and s4.translate.x > -100 then
		s4.translate = s4.translate + vec3:new(-0.25, 0, 0)
		s6.translate = s6.translate + vec3:new(-0.25, 0, 0)

	elseif s4.translate.x == -100 and s4.translate.y > -50 then
		s4.translate = s4.translate + vec3:new(0, -0.25, 0)
		s6.translate = s6.translate + vec3:new(0, -0.25, 0)

	elseif s4.translate.y == -50 and s4.translate.x < 100 then
		s4.translate = s4.translate + vec3:new(0.25, 0, 0)
		s6.translate = s6.translate + vec3:new(0.25, 0, 0)

	elseif s4.translate.x == 100 and s4.translate.y < 50 then
		s4.translate = s4.translate + vec3:new(0, 0.25, 0)
		s6.translate = s6.translate + vec3:new(0, 0.25, 0)

	end

	if s7.translate.y == 50 and s7.translate.x > -100 then
		s7.translate = s7.translate + vec3:new(-0.25, 0, 0)
		s9.translate = s9.translate + vec3:new(-0.25, 0, 0)

	elseif s7.translate.x == -100 and s7.translate.y > -50 then
		s7.translate = s7.translate + vec3:new(0, -0.25, 0)
		s9.translate = s9.translate + vec3:new(0, -0.25, 0)

	elseif s7.translate.y == -50 and s7.translate.x < 100 then
		s7.translate = s7.translate + vec3:new(0.25, 0, 0)
		s9.translate = s9.translate + vec3:new(0.25, 0, 0)

	elseif s7.translate.x == 100 and s7.translate.y < 50 then
		s7.translate = s7.translate + vec3:new(0, 0.25, 0)
		s9.translate = s9.translate + vec3:new(0, 0.25, 0)

	end

	if s8.translate.y == 50 and s8.translate.x > -100 then
		s8.translate = s8.translate + vec3:new(-0.25, 0, 0)
		s10.translate = s10.translate + vec3:new(-0.25, 0, 0)

	elseif s8.translate.x == -100 and s8.translate.y > -50 then
		s8.translate = s8.translate + vec3:new(0, -0.25, 0)
		s10.translate = s10.translate + vec3:new(0, -0.25, 0)

	elseif s8.translate.y == -50 and s8.translate.x < 100 then
		s8.translate = s8.translate + vec3:new(0.25, 0, 0)
		s10.translate = s10.translate + vec3:new(0.25, 0, 0)

	elseif s8.translate.x == 100 and s8.translate.y < 50 then
		s8.translate = s8.translate + vec3:new(0, 0.25, 0)
		s10.translate = s10.translate + vec3:new(0, 0.25, 0)

	end

	if s11.translate.y == 50 and s11.translate.x > -100 then
		s11.translate = s11.translate + vec3:new(-0.25, 0, 0)
		s13.translate = s13.translate + vec3:new(-0.25, 0, 0)

	elseif s11.translate.x == -100 and s11.translate.y > -50 then
		s11.translate = s11.translate + vec3:new(0, -0.25, 0)
		s13.translate = s13.translate + vec3:new(0, -0.25, 0)

	elseif s11.translate.y == -50 and s11.translate.x < 100 then
		s11.translate = s11.translate + vec3:new(0.25, 0, 0)
		s13.translate = s13.translate + vec3:new(0.25, 0, 0)

	elseif s11.translate.x == 100 and s11.translate.y < 50 then
		s11.translate = s11.translate + vec3:new(0, 0.25, 0)
		s13.translate = s13.translate + vec3:new(0, 0.25, 0)

	end

	if s12.translate.y == 50 and s12.translate.x > -100 then
		s12.translate = s12.translate + vec3:new(-0.25, 0, 0)
		s14.translate = s14.translate + vec3:new(-0.25, 0, 0)

	elseif s12.translate.x == -100 and s12.translate.y > -50 then
		s12.translate = s12.translate + vec3:new(0, -0.25, 0)
		s14.translate = s14.translate + vec3:new(0, -0.25, 0)

	elseif s12.translate.y == -50 and s12.translate.x < 100 then
		s12.translate = s12.translate + vec3:new(0.25, 0, 0)
		s14.translate = s14.translate + vec3:new(0.25, 0, 0)

	elseif s12.translate.x == 100 and s12.translate.y < 50 then
		s12.translate = s12.translate + vec3:new(0, 0.25, 0)
		s14.translate = s14.translate + vec3:new(0, 0.25, 0)

	end
	
end]]