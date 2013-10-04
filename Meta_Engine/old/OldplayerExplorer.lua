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
      cardinal_tiles[#cardinal_tiles+1]         = {x,     y + 1,                2 }
			diagonal_tiles[#diagonal_tiles+1]         = {x + 1, y + 1,                3 }
			if x > 0 then
			  diagonal_tiles[#diagonal_tiles+1] = {x - 1,  y + 1,                     1 }
			  cardinal_tiles[#cardinal_tiles+1] = {x - 1,  y,                         4 }
			  diagonal_tiles[#diagonal_tiles+1] = {x - 1,  y - 1,                     7 }
			end
		elseif x > 0 then
			cardinal_tiles[#cardinal_tiles+1]         = {x - 1, y,     c - 1,                    4 }
			diagonal_tiles[#diagonal_tiles+1]         = {x - 1, y - 1, c - 1 - game.level.map.w, 7 }
		end
	end,
	--Dir 2
	function(target_x, target_y, cardinal_tiles, diagonal_tiles)
	  local x = target_x
	  local y = target_y
	  
	  if y > map.h - 2 then return end
	  
    if x > 0 then diagonal_tiles[#diagonal_tiles+1]         = {x-1, y+1,        1} end
	  cardinal_tiles[#cardinal_tiles+1]                       = {x,   y+1,        2}
	  if x > map.w -1 then diagonal_tiles[#diagonal_tiles+1]  = {x+11, y+1,       3} end
	end,
	--Dir 3
	function(target_x, target_y, cardinal_tiles, diagonal_tiles)
	  local x = target_x
	  local y = target_y
	  
	  if y > map.h - 1 then
      if x > 0 then diagonal_tiles[#diagonal_tiles]         = {x-1, y+1,        1} end
      cardinal_tiles[#cardinal_tiles]                       = {x,   y+1,        2}
      if x < map.w - 1 then
        diagonal_tiles[#diagonal_tiles]                     = {x+1, y+1,        3}
        cardinal_tiles[#cardinal_tiles]                     = {x+1, y,          6}
        diagonal_tiles[#diagonal_tiles]                     = {x+1, y+1,        9}
      end
    elseif x < map.w - 1 then
      cardinal_tiles[#cardinal_tiles+1]                     = {x+1, y,          6}
      if y > 0 then diagonal_tiles[#diagonal_tiles+1]                     = {x+1, y+1,        9} end
      end
    end,
    --Dir 4
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
      if x < 1 then return end
      
      if y < map.h -1 then diagonal_tiles[#diagonal_tiles] = {x-1, y+1,         1} end
      cardinal_tiles[#cardinal_tiles]                      = {x-1, y,           4}
      if y > 0 then diagonal_tiles[#diagonal_tiles]        = {x-1, y-1,         7} end
    end,
    --Dir 5
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
	    local y = target_y

	    local left_okay = x > 0
	    local right_okay = x < map.w - 1
	    local lower_okay = y > 0
	    local upper_okay = y < map.h - 1

		if upper_okay then cardinal_tiles[#cardinal_tiles+1]                = {x,     y + 1,        2 } end
		if left_okay  then cardinal_tiles[#cardinal_tiles+1]                = {x - 1, y,            4 } end
		if right_okay then cardinal_tiles[#cardinal_tiles+1]                = {x + 1, y,            6 } end
		if lower_okay then cardinal_tiles[#cardinal_tiles+1]                = {x,     y - 1,        8 } end
	    
		if left_okay  and upper_okay then diagonal_tiles[#diagonal_tiles+1] = {x - 1, y + 1,        1 } end
		if right_okay and upper_okay then diagonal_tiles[#diagonal_tiles+1] = {x + 1, y + 1,        3 } end
		if left_okay  and lower_okay then diagonal_tiles[#diagonal_tiles+1] = {x - 1, y - 1,        7 } end
		if right_okay and lower_okay then diagonal_tiles[#diagonal_tiles+1] = {x + 1, y - 1,        9 } end      
    end,
    --Dir 6
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
      if x < map.w -2 then return end
      
      if y < map.h - 1 then diagonal_tiles[#diagonal_tiles+1]             = {x+1, y+1,            3} end
      cardinal_tiles[#cardinal_tiles+1]                                   = {x+1, y,              6} 
      if y > 0 then diagonal_tiles[#diagonal_tiles+1]                     = {x+1, y-1,            9} end
    end,
    --Dir 7
    function(target_x, target_y, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
      if x > 0 then
        diagonal_tiles[#diagonal_tiles+1]                                 = {x-1, y+1,            1} 
        cardinal_tiles[#cardinal_tiles+1]                                 = {x-1, y,              4}
        if y > 0 then
          diagonal_tiles[#diagonal_tiles+1]                               = {x-1, y-1,            7}
          cardinal_tiles[#cardinal_tiles+1]                               = {x,   y-1,            8}
          diagonal_tiles[#diagonal_tiles+1]                               = {x+1,   y-1,          9}
        end
      elseif y > 0 then
          cardinal_tiles[#cardinal_tiles+1]                               = {x,   y-1,            8}
          diagonal_tiles[#diagonal_tiles+1]                               = {x+1,   y-1,          9}
      end
    end,
    --Dir 8
	  function(node, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      
		  if y < 1 then return end

		  if x > 0 then diagonal_tiles[#diagonal_tiles+1]                    = {x - 1, y - 1, 7 } end
		  cardinal_tiles[#cardinal_tiles+1]                                  = {x,     y - 1, 8 }
		  if x < game.level.map.w - 1 then diagonal_tiles[#diagonal_tiles+1] = {x + 1, y - 1, 9 } end
	  end,
	  -- Dir 9
	  function(node, cardinal_tiles, diagonal_tiles)
      local x = target_x
      local y = target_y
      

		  if x < game.level.map.w - 1 then
			  diagonal_tiles[#diagonal_tiles+1]         = {x + 1, y + 1, c + 1 + game.level.map.w, 3 }
			  cardinal_tiles[#cardinal_tiles+1]         = {x + 1, y,     c + 1,                    6 }
			  if y > 0 then
				  diagonal_tiles[#diagonal_tiles+1] = {x - 1, y - 1, c - 1 - game.level.map.w, 7 }
				  cardinal_tiles[#cardinal_tiles+1] = {x,     y - 1, c     - game.level.map.w, 8 }
				  diagonal_tiles[#diagonal_tiles+1] = {x + 1, y - 1, c + 1 - game.level.map.w, 9 }
			  end
		  elseif y > 0 then
			  diagonal_tiles[#diagonal_tiles+1]         = {x - 1, y - 1, c - 1 - game.level.map.w, 7 }
			  cardinal_tiles[#cardinal_tiles+1]         = {x,     y - 1, c     - game.level.map.w, 8 }
		  end
	  end
}




function autoExplore()
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
end
