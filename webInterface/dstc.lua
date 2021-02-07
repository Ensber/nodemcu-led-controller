-- deathstar trashcompactor
-- compacts a folder into a c headder filename

require("lfs")

specialHandler = {}
function specialHandler.html(data)
  -- trim data
  data:gsub("    ","\t")
  repeat
    data, n1 = data:gsub(" \n","\n")
    data, n2 = data:gsub("\n ","\n")
  until n1+n2 == 0
  data = data:gsub("\n","\\n")
  data = data:gsub("\r","")
  data = '"' .. data:gsub("\"","\\\"") .. '"'
  return data
end
specialHandler.css = specialHandler.html

function specialHandler.png(data)
  local t0 = os.clock()
  local out = 'string()'
  local outTab = {}
  local dLen = #data
  for i=1,dLen do
    out = out .. '+(char)' .. tostring(string.byte(data, i))
    if i%100000 == 1 then
      io.write("\r"..math.floor(i/dLen*100).."%  ")
    end
    if i%40 == 1 then
      table.insert(outTab, out)
      out = ""
    end
  end
  table.insert(outTab, out)
  print("\r100% time: "..(os.clock()-t0).."s")
  return table.concat( outTab )
end

fileCount = 0
function compact(base,path)
  path = path or ""
  local out = ""
  for file in lfs.dir("webContent") do
    if file ~= "." and file ~= ".." then
      print(base..path.."/"..file)
      f = io.open(base..path.."/"..file,"rb")
      if not f then
        out = out .. compact(base,path.."/"..file)
      else
        fileCount = fileCount + 1
        local data = f:read("*all")
        f:close()

        local ending = file
        x = ending:find("%.")
        while x do
          ending = ending:sub(x+1,-1)
          x = ending:find("%.")
        end
        
        if specialHandler[ending] then
          data = specialHandler[ending](data)
        else -- default handler
          data = data:gsub("\n","\\n")
          data = data:gsub("\r","")
          data = '"' .. data:gsub("\"","\\\"") .. '"'
        end

        out = out .. 'webContent("' .. path..'/'..file .. '",' .. data .. ');\n'
      end
    end
  end
  return out
end

folder = "webContent"

print("generating headder file...")
local timer = os.clock()

hData2 = compact(folder):sub(1,-3) .. "\n;"
hData1 = [[
#include "includes/Dictionary/Dictionary.h"

using namespace std;

Dictionary &webContent = *(new Dictionary(]]..fileCount..[[));
]]

f = io.open(folder..".hpp","w")
f:write(hData1)
f:write(hData2)
f:close()
print("\n------------------------------\nfinished combining "..fileCount.." files in "..(os.clock()-timer).."s")