x_min = -3.1415 * 2
x_max = 3.1415 * 2
y_min = -2 
y_max = 2

max_n = 10000
min_dist = 1
thickness = 1
color = 0xFFFFFF00 -- ABGR

f = function (x)
	if (x > -3.1415 and x < 3.1415)
	then
		result = math.sin(x)
	elseif (x > 3.1415)
	then
		result = 3.1415 - x
	elseif (x < -3.1415)
	then
		result = -3.1415 - x
	end

	return result
end

