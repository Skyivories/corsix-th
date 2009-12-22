--[[ Copyright (c) 2009 Edvin "Lego3" Linge

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

local disease = {}
disease.name = _S(4, 10)
disease.id = "fractured_bones"
disease.cause = _S(44, 83)
disease.symptoms = _S(44, 84)
disease.cure = _S(44, 85)
disease.cure_price = 450 -- http://www.eudoxus.demon.co.uk/thc/tech.htm
disease.initPatient = function(patient)
  if 1 == 2 then -- Right now the female animation in the cast remover is bad
    patient:setType("Standard Female Patient")
    patient:setLayer(0, math.random(1, 4) * 2)
    local num1 = math.random(0, 1) -- The first bandage yes/no
    patient:setLayer(2, num1 * 2)
    -- There needs to be at least one bandage on the patient
    patient:setLayer(3, (num1 == 0 and 1 or math.random(0, 1)) * 2)
    patient:setLayer(4, 0)
  else
    patient:setType("Alternate Male Patient")
    patient:setLayer(0, math.random(1, 5) * 2)
    -- Some bandage types may be duplicated, then it shall be so
    local num1 = math.random(0, 2) -- The first bandage yes/no
    patient:setLayer(2, num1 * 2)
    local num2 = math.random(0, 5) -- The second bandage yes/no
    -- 6 does not exist, a few more arm bandages instead
    if num2 == 3 then num2 = 4 end 
    patient:setLayer(3, num2 * 2)
    -- There needs to be at least one bandage on the patient
    local num3 = math.random(0, 5)
    if num3 == 3 then num3 = 4 end
    patient:setLayer(4, ((num1 == 0 and num2 == 0) and 1 or num3) * 2)
  end
  patient:setLayer(1, math.random(0, 3) * 2)
end
-- Diagnosis rooms are the rooms other than the GPs office which can be visited
-- to aid in diagnosis. The need not be visited, and if they are visited, the
-- order in which they are visited is not fixed.
disease.diagnosis_rooms = {
  -- TODO
}
-- Treatment rooms are the rooms which must be visited, in the given order, to
-- cure the disease.
disease.treatment_rooms = {
  "fracture_clinic",
}
-- Diagnosis difficulty: a value between 0 (instant diagnosis in GP's office) and 1.
disease.diagnosis_difficulty = 0.5

return disease
