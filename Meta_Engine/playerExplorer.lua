-- Lista tiles adjacentes

local function listAdjacentTiles(target_x, target_y, no_diagonal, no_cardinal)
	local tiles = {}
	local x = target_x
	local y = target_y

	local left_okay = x > 0
	local right_okay = x < map.w - 1
	local lower_okay = y > 0
	local upper_okay = y < map.h - 1

	if not no_cardinal then
		if upper_okay then tiles[1]        = {x,     y + 1,                       2 } end
		if left_okay  then tiles[#tiles+1] = {x - 1, y,                           4 } end
		if right_okay then tiles[#tiles+1] = {x + 1, y,                           6 } end
		if lower_okay then tiles[#tiles+1] = {x,     y - 1,                       8 } end
	end
	if not no_diagonal then
		if left_okay  and upper_okay then tiles[#tiles+1] = {x - 1, y + 1,        1 } end
		if right_okay and upper_okay then tiles[#tiles+1] = {x + 1, y + 1,        3 } end
		if left_okay  and lower_okay then tiles[#tiles+1] = {x - 1, y - 1,        7 } end
		if right_okay and lower_okay then tiles[#tiles+1] = {x + 1, y - 1,        9 } end
	end
	return tiles
end

local moved = false
for _, node in ipairs(listAdjacentTiles(player.x, player.y,false, false)) do
  local tile = map:getTile(node[1], node[2])
  -- Se puder andar no tile, puder ver, e não tiver passado
  
  if tile.id ~= 0 and map:has_seens(node[1], node[2]) and map:has_passed(node[1], node[2]) == false then 
    print('movendo ' .. node[1] .. ',' .. node[2] .. ' para ' .. node[3])
    player:move(node[3])
    moved = true
    break
  end
end
if moved == false then
  local dir = math.random(8)
  if(dir == 5) then 
    dir = dir+1
  end
  player:move(dir);
end
