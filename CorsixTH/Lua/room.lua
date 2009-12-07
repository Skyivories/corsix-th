--[[ Copyright (c) 2009 Peter "Corsix" Cawley

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

class "Room"

function Room:Room(x, y, w, h, id, room_info, world, hospital, door)
  self.id = id
  self.world = world
  self.hospital = hospital
  self.x = x
  self.y = y
  self.width = w
  self.height = h
  self.room_info = room_info
  self.maximum_patients = 1 -- A good default for most rooms
  door.room = self
  self.door = door
  
  self.world.map.th:markRoom(x, y, w, h, room_info.floor_tile, id)
  
  self.humanoids = {--[[a set rather than a list]]}
  
  self.objects_additional = {}
  if room_info.objects_additional then
    for i = 1, #room_info.objects_additional do
      self.objects_additional[i] = { object = TheApp.objects[room_info.objects_additional[i]], qty = 0 }
    end
  end

  self.objects_needed = {}
  if room_info.objects_needed then
    for i = 1, #room_info.objects_needed do
      self.objects_needed[i] = { object = TheApp.objects[room_info.objects_needed[i]], qty = 1, needed = true }
    end
  end
  -- TODO
end

function Room:getEntranceXY(inside)
  local door = self.door
  local x, y = door.tile_x, door.tile_y
  if (inside and self.world:getRoom(x, y) ~= self) or (not inside and self.world:getRoom(x, y) == self) then
    if door.direction == "north" then
      y = y - 1
    elseif door.direction == "west" then
      x = x - 1
    end
  end
  return x, y
end

function Room:createLeaveAction()
  local x, y = self:getEntranceXY(false)
  return {name = "walk", x = x, y = y, is_leaving = true}
end

function Room:createEnterAction()
  local x, y = self:getEntranceXY(true)
  return {name = "walk", x = x, y = y}
end

function Room:getPatient()
  for humanoid in pairs(self.humanoids) do
    if class.is(humanoid, Patient) then
      return humanoid
    end
  end
end

function Room:getPatientCount()
  local count = 0
  for humanoid in pairs(self.humanoids) do
    if class.is(humanoid, Patient) then
      count = count + 1
    end
  end
  return count
end

function Room:dealtWithPatient(patient)
  patient = patient or self:getPatient()
  patient:setNextAction(self:createLeaveAction())
  if patient.disease and not patient.diagnosed then
    -- Patient not yet diagnosed, hence just been in a diagnosis room.
    -- Increment diagnosis_progress, and send patient back to GP.
    -- TODO: Variate progress with respect to room type and staff skill, etc.
    patient.diagnosis_progress = patient.diagnosis_progress + 0.4
    if patient.diagnosis_progress >= 1.0 then
      patient.diagnosis_progress = 1.0
    end
    patient:queueAction{name = "seek_room", room_type = "gp"}
    self.hospital:receiveMoneyForTreatment(patient)
  elseif patient.disease and patient.diagnosed then
    -- Patient just been in a cure room, so either patient now cured, or needs
    -- to move onto next cure room.
    patient.cure_rooms_visited = patient.cure_rooms_visited + 1
    local next_room = patient.disease.treatment_rooms[patient.cure_rooms_visited + 1]
    if next_room then
      patient:queueAction{name = "seek_room", room_type = next_room}
    else
      self.hospital:receiveMoneyForTreatment(patient)
      patient:setMood "happy"
      patient:setHospital(nil)
    end
  else
    patient:queueAction{name = "meander", count = 2}
    patient:queueAction{name = "idle"}
  end
end

local profile_attributes = {
  Psychiatrist = "is_psychiatrist",
  Surgeon = "is_surgeon",
  Researcher = "is_researcher",
}

function Room:testStaffCritera(criteria, extra_humanoid)
  -- critera should be required_staff or maximum_staff table.
  -- if extra_humanoid is nil, then returns true if the humanoids in the room
  -- meet the given critera, and false otherwise.
  -- if extra_humanoid is not nil, then returns true if the given humanoid
  -- would assist in satisfying the given critera, and false if they would not.
  for attribute, count in pairs(criteria) do
    if attribute == "Nurse" then
      for humanoid in pairs(self.humanoids) do
        if humanoid.humanoid_class == "Nurse" then
          count = count - 1
        end
      end
      if extra_humanoid and count > 0 then
        local humanoid = extra_humanoid
        if humanoid.humanoid_class == "Nurse" then
          return true
        end
      end
    elseif attribute == "Doctor" then
      for humanoid in pairs(self.humanoids) do
        if humanoid.humanoid_class == "Doctor" or humanoid.humanoid_class == "Surgeon" then
          count = count - 1
        end
      end
      if extra_humanoid and count > 0 then
        local humanoid = extra_humanoid
        if humanoid.humanoid_class == "Doctor" or humanoid.humanoid_class == "Surgeon" then
          return true
        end
      end
    elseif attribute == "Psychiatrist" or attribute == "Surgeon" or attribute == "Researcher" then
      attribute = profile_attributes[attribute]
      for humanoid in pairs(self.humanoids) do
        if humanoid.profile and humanoid.profile[attribute] == 1.0 then
          count = count - 1
        end
      end
      if extra_humanoid and count > 0 then
        local humanoid = extra_humanoid
        print(humanoid.profile[attribute])
        if humanoid.profile and humanoid.profile[attribute] == 1.0 then
          return true
        end
      end
    end
    if not extra_humanoid and count > 0 then
      return false
    end
  end
  return not extra_humanoid
end

local no_staff = {}
function Room:getMaximumStaffCritera()
  -- Some rooms have dynamic criteria (i.e. dependent upon the number of items
  -- in the room), so this method is provided for such rooms to override it.
  return self.room_info.maximum_staff or self.room_info.required_staff or no_staff
end

function Room:getRequiredStaffCritera()
  return self.room_info.required_staff or no_staff
end

function Room:onHumanoidEnter(humanoid)
  assert(not self.humanoids[humanoid], "Humanoid entering a room that they are already in")
  if humanoid.humanoid_class == "Handyman" then
    -- Handymen can always enter a room (to repair stuff, water plants, etc.)
    self.humanoids[humanoid] = true
    return
  end
  if class.is(humanoid, Staff) then
    -- If the room is already full of staff, or the staff member isn't relevant
    -- to the room, then make them leave. Otherwise, take control of them.
    local critera = self:getMaximumStaffCritera()
    if self:testStaffCritera(critera) or not self:testStaffCritera(critera, humanoid) then
      self.humanoids[humanoid] = true
      humanoid:setNextAction(self:createLeaveAction())
      humanoid:queueAction{name = "meander"}
    else
      self.humanoids[humanoid] = true
      self:commandEnteringStaff(humanoid)
    end
    self:tryAdvanceQueue()
    return
  end
  self.humanoids[humanoid] = true
  self:tryAdvanceQueue()
  if class.is(humanoid, Patient) then
    -- Check if the staff requirements are still fulfilled (the staff might have left / been picked up meanwhile)
    if self:testStaffCritera(self:getRequiredStaffCritera()) then
      self:commandEnteringPatient(humanoid)
    else
      humanoid:setNextAction(self:createLeaveAction())
      humanoid:queueAction(self:createEnterAction())
    end
  end
end

function Room:commandEnteringStaff(humanoid)
  -- To be implemented in derived classes
end

function Room:commandEnteringPatient(humanoid)
  -- To be extended in derived classes
  self.door.queue.visitor_count = self.door.queue.visitor_count + 1
end

function Room:tryAdvanceQueue()
  if self.door.queue:size() > 0 then
    local front = self.door.queue:front()
    if self.humanoids[front] or self:canHumanoidEnter(front) then
      self.door.queue:pop()
    end
  end
end

function Room:onHumanoidLeave(humanoid)
  assert(self.humanoids[humanoid], "Humanoid leaving a room that they are not in")
  self.humanoids[humanoid] = nil
  self:tryAdvanceQueue()
  if class.is(humanoid, Staff) then
    -- Make patients leave the room if there are no longer enough staff
    if not self:testStaffCritera(self:getRequiredStaffCritera()) then
      for humanoid in pairs(self.humanoids) do
        if class.is(humanoid, Patient) then
          if not humanoid.action_queue[1].is_leaving then
            humanoid:setNextAction(self:createLeaveAction())
            humanoid:queueAction(self:createEnterAction())
          end
        end
      end
    end
  end
end

function Room:canHumanoidEnter(humanoid)
  -- By default, staff can always enter
  if class.is(humanoid, Staff) then
    return true
  end
  -- By default, patients can only enter if there are sufficient staff and not
  -- too many patients.
  if class.is(humanoid, Patient) then
    return self:testStaffCritera(self:getRequiredStaffCritera()) and self:getPatientCount() < self.maximum_patients
  end
  -- By default, other classes of humanoids cannot enter
  return false
end
