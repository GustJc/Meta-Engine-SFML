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


-- Itera tiles adjacentes, pulando a abertura dos tiles que originaram o movimento
local adjacentTiles = {
  --Dir 1
  function(target_x, target_y, cardinal_tiles, diagonal_tiles)
    local x = target_x
    local y = target_y
    
    if y < map.h - 1 then
      if isOpenTiles(x,y+1) then cardinal_tiles[#cardinal_tiles+1]         = {x,     y + 1,                2 } end
			if isOpenTiles(x+1,y+1) then diagonal_tiles[#diagonal_tiles+1]         = {x + 1, y + 1,                3 } end
			if x > 0 then
			  if isOpenTiles(x-1,y+1) then diagonal_tiles[#diagonal_tiles+1] = {x - 1,  y + 1,                     1 } end
			  if isOpenTiles(x-1,y) then cardinal_tiles[#cardinal_tiles+1] = {x - 1,  y,                         4 } end
			  if isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1] = {x - 1,  y - 1,                     7 } end
			end
		elseif x > 0 then
			if isOpenTiles(x-1,y) then cardinal_tiles[#cardinal_tiles+1]         = {x - 1, y,                    4 } end
			if isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1]         = {x - 1, y - 1,                7 } end
		end
	end,
	--Dir 2
	function(target_x, target_y, cardinal_tiles, diagonal_tiles)
	  local x = target_x
	  local y = target_y
	  
	  if y > map.h - 2 then return end
	  
    if x > 0 and isOpenTiles(x-1,y+1) then diagonal_tiles[#diagonal_tiles+1]         = {x-1, y+1,        1} end
	  if isOpenTiles(x,y+1) then cardinal_tiles[#cardinal_tiles+1]      = {x,   y+1,        2} end
	  if x < map.w -1 and isOpenTiles(x+1,y+1) then diagonal_tiles[#diagonal_tiles+1]  = {x+1, y+1,       3} end
	end,
	--Dir 3
	function(target_x, target_y, cardinal_tiles, diagonal_tiles)
	  local x = target_x
	  local y = target_y
	  
	  if y < map.h - 1 then 
      if isOpenTiles(x-1,y+1) then diagonal_tiles[#diagonal_tiles+1]         = {x-1, y+1,        1} end
      if isOpenTiles(x,y+1) then cardinal_tiles[#cardinal_tiles+1]                       = {x,   y+1,        2} end
      if x < map.w - 1 then
        if isOpenTiles(x+1,y+1) then diagonal_tiles[#diagonal_tiles+1]                     = {x+1, y+1,        3} end
        if isOpenTiles(x+1,y) then cardinal_tiles[#cardinal_tiles+1]                     = {x+1, y,          6} end
        if isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1]                     = {x+1, y-1,        9} end
      end
    elseif x < map.w - 1 then
      if isOpenTiles(x+1,y) then cardinal_tiles[#cardinal_tiles+1]                     = {x+1, y,          6} end
      if isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1]       = {x+1, y-1,        9} end
      end
    end,
    --Dir 4
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
      if x < 1 then return end
      
      if y < map.h -1 and isOpenTiles(x-1,y+1) then diagonal_tiles[#diagonal_tiles+1] = {x-1, y+1,         1} end
      if isOpenTiles(x-1,y) then cardinal_tiles[#cardinal_tiles+1]                      = {x-1, y,           4} end
      if y > 0 and isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1]        = {x-1, y-1,         7} end
    end,
    --Dir 5
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
	    local y = target_y

	    local left_okay = x > 0
	    local right_okay = x < map.w - 1
	    local lower_okay = y > 0
	    local upper_okay = y < map.h - 1


	    if upper_okay and isOpenTiles(x,y+1) then cardinal_tiles[#cardinal_tiles+1]                = {x,     y + 1,        2 } end
	    if left_okay  and isOpenTiles(x-1,y) then cardinal_tiles[#cardinal_tiles+1]                = {x - 1, y,            4 } end
	    if right_okay and isOpenTiles(x+1,y) then cardinal_tiles[#cardinal_tiles+1]                = {x + 1, y,            6 } end
	    if lower_okay and isOpenTiles(x,y-1) then cardinal_tiles[#cardinal_tiles+1]                = {x,     y - 1,        8 } end


	    if left_okay  and upper_okay and isOpenTiles(x-1,y+1)  then diagonal_tiles[#diagonal_tiles+1] = {x - 1, y + 1,        1 } end
	    if right_okay and upper_okay and isOpenTiles(x+1,y+1) then diagonal_tiles[#diagonal_tiles+1] = {x + 1, y + 1,        3 } end
	    if left_okay  and lower_okay and isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1] = {x - 1, y - 1,        7 } end
	    if right_okay and lower_okay and isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1] = {x + 1, y - 1,        9 } end

    end,
    --Dir 6
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
      if x > map.w -2 then return end
      
      if y < map.h - 1 and isOpenTiles(x+1,y+1) then diagonal_tiles[#diagonal_tiles+1]             = {x+1, y+1,            3} end
      if isOpenTiles(x+1,y) then cardinal_tiles[#cardinal_tiles+1]                                   = {x+1, y,              6} end
      if y > 0 and isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1]                     = {x+1, y-1,            9} end
    end,
    --Dir 7
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
      if x > 0 then
        if isOpenTiles(x-1,y+1) then diagonal_tiles[#diagonal_tiles+1]                                 = {x-1, y+1,            1} end
        if isOpenTiles(x-1,y) then cardinal_tiles[#cardinal_tiles+1]                                   = {x-1, y,              4} end
        if y > 0 then
          if isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1]                               = {x-1, y-1,            7} end
          if isOpenTiles(x,y-1) then cardinal_tiles[#cardinal_tiles+1]                                 = {x,   y-1,            8} end
          if isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1]                               = {x+1,   y-1,          9} end
        end
      elseif y > 0 then
          if isOpenTiles(x,y-1) then cardinal_tiles[#cardinal_tiles+1]                                 = {x,   y-1,            8} end
          if isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1]                               = {x+1,   y-1,          9} end
      end
    end,
    --Dir 8
	  function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
		  if y < 1 then return end

		  if x > 0 and isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1]                    = {x - 1, y - 1, 7 } end
		  if isOpenTiles(x,y-1) then cardinal_tiles[#cardinal_tiles+1]                                  = {x,     y - 1, 8 } end
		  if x < map.w - 1 and isOpenTiles(x+1,y-11) then diagonal_tiles[#diagonal_tiles+1]            = {x + 1, y - 1, 9 } end
	  end,
	  -- Dir 9
	  function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      

		  if x < map.w - 1 then
			  if isOpenTiles(x+1,y+1) then diagonal_tiles[#diagonal_tiles+1]         = {x + 1, y + 1, 3 } end
			  if isOpenTiles(x+1,y) then cardinal_tiles[#cardinal_tiles+1]           = {x + 1, y    , 6 } end
			  if y > 0 then
				  if isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1]       = {x - 1, y - 1    , 7 } end
				  if isOpenTiles(x,y-1) then cardinal_tiles[#cardinal_tiles+1]         = {x,     y - 1    , 8 } end
				  if isOpenTiles(x+1,y-1) then diagonal_tiles[#diagonal_tiles+1]       = {x + 1, y - 1    , 9 } end
			  end
		  elseif y > 0 then
			  if isOpenTiles(x-1,y-1) then diagonal_tiles[#diagonal_tiles+1]         = {x - 1, y - 1, 7 } end
			  if isOpenTiles(x,y-1) then cardinal_tiles[#cardinal_tiles+1]           = {x,     y - 1, 8 } end
      end
	  end
}

function isOpenTiles(target_x, target_y)
  --print("doing " .. target_x ..','..target_y)
  local tile = map:getTile(target_x,target_y)
  if openTiles[target_x+1][target_y+1] == false and tile.id ~= 0 then
    openTiles[target_x+1][target_y+1] = true
    return true
  end
  return false
end

function clearOpenTiles() 
  openTiles = {}
  for x=1, map.w do
    openTiles[x] = {}
    for y=1, map.h do
      openTiles[x][y] = false    
      --print('open: ' .. x .. ',' .. y)
    end
  end  

end

clearOpenTiles()

running = true
iter = 1;
node = { player.x, player.y, 5 }
print('player, ' .. player.x ..',' .. player.y)
current_tiles = { node }
while running do
  local cardinal_tiles = {}
  local diagonal_tiles = {}	
  local current_tiles_next = {}

  for _, node in ipairs(current_tiles) do
			  adjacentTiles[node[3]](node[1],node[2], cardinal_tiles, diagonal_tiles)
			  --print(_)
  end
  
  --os.execute("sleep 0.8")
  --map:forceShowMap()

  for id_Tipes, tile_list in ipairs({cardinal_tiles, diagonal_tiles}) do
  
      for id_Tile, node in ipairs(tile_list) do
          local x = node[1]
          local y = node[2]
          local from = node[3]
          --print('pos['.. id_Tipes .. ',' .. id_Tile .. '] is: ' .. x .. ',' .. y .. ' number: ' .. from)
          local tile = map:getTile(x,y)
          --if(tile) then print('tileID = ' .. tile.id) end
            map:setTile(x,y,1,1)
          if tile.id ~= 0 then
            current_tiles_next[#current_tiles_next+1] = node
          end
          if id_Tile > 2000 then
           print('2000 PLUS')
           break 
          end
          
      end
  end
  
  iter = iter + 1
  if iter > 7 then 
    print('Breaking')
    break 
  end
  
  running = running and #current_tiles_next > 0
	current_tiles = current_tiles_next
	
  
  
end
