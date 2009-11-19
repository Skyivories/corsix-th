--[[ Copyright (c) 2009 Manuel K�nig

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. --]]

local object = {}
object.id = "x_ray"
object.thob = 27
object.name = _S(2, 28)
object.ticks = false
object.build_cost = 4000
object.build_preview_animation = 5076
object.idle_animations = {
  north = 1988,
  south = 1988,
}
object.orientations = {
  north = {
    footprint_origin = {-1, -1},
    footprint = { {-2, -2}, {-1, -2},
                  {-2, -1}, {-1, -1}, {0, -1}, {1, -1, only_passable = true},
                  {-2, 0}, {-1, 0}, {0, 0} }
  },
  east = {
    footprint_origin = {-1, -1},
    footprint = { {-2, -2}, {-1, -2}, {0, -2},
                  {-2, -1}, {-1, -1}, {0, -1},
                  {-1, 0}, {0, 0},
                  {-1, 1, only_passable = true} }
  },
}

return object