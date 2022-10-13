local id1, id2, id3, id4, id5, id6 = ...

s1 = getSprite(id1)
s2 = getSprite(id2)
s3 = getSprite(id3)
s4 = getSprite(id4)
s5 = getSprite(id5)
s6 = getSprite(id6)

if isKeyDown(KEYBOARD.F) then
	playSound("moyai")
	
	s1.translate = vec3:new(0, 0, 0.9)
	s2.translate = vec3:new(0, 0, 0)

	if s3.translate.z < 1 and s4.translate.z < 1 then
		s3.translate = s3.translate + vec3:new(0, 0, 1)
		s4.translate = s4.translate + vec3:new(0, 0, 1)
	end

	if s5.translate.z > 0 and s6.translate.z > 0 then
		s5.translate = s5.translate - vec3:new(0, 0, 1)
		s6.translate = s6.translate - vec3:new(0, 0, 1)
	end

else 
	s1.translate = vec3:new(0, 0, 0)
	s2.translate = vec3:new(0, 0, 0.9)

	if s3.translate.z > 0 and s4.translate.z > 0 then
		s3.translate = s3.translate - vec3:new(0, 0, 1)
		s4.translate = s4.translate - vec3:new(0, 0, 1)
	end

	if s5.translate.z < 1 and s6.translate.z < 1 then
		s5.translate = s5.translate + vec3:new(0, 0, 1)
		s6.translate = s6.translate + vec3:new(0, 0, 1)
	end

	s3.rotateAngle = s3.rotateAngle + 0.35
	s4.rotateAngle = s4.rotateAngle - 0.35
	s5.rotateAngle = s5.rotateAngle + 0.35
	s6.rotateAngle = s6.rotateAngle - 0.35

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


end