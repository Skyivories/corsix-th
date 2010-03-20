--[[ Copyright (c) 2010 Manuel "Roujin" Wolf

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

Language("swedish", "sv", "swe")
Inherit("english")
Inherit("original_strings", 5)

-- override
object.reception_desk = "Reception"
-- TODO? Any more original strings that are off in swedish translation?

-- new strings
object.litter = utf8 "Skräp"
tooltip.objects.litter = utf8 "Skräp: Lämnat åt sitt öde eftersom patienten inte kunde hitta någon papperskorg."

menu_options.lock_windows = utf8 "  LÅS FÖNSTER  "
menu_options_game_speed.pause = "  PAUSA  "

menu_debug = {
  transparent_walls           = utf8 "  TRANSPARENTA VÄGGAR  ",
  limit_camera                = utf8 "  BEGRÄNSA KAMERAN  ",
  disable_salary_raise        = utf8 "  STÄNG AV LÖNEÖKNINGAR  ",
  make_debug_patient          = "  SKAPA DEBUGPATIENT  ",
  spawn_patient               = "  GENERERA VANLIG PATIENT  ",
  make_adviser_talk           = utf8 "  LÅT RÅDGIVAREN PRATA  ",
  show_watch                  = "  VISA KLOCKA  ",
  create_emergency            = "  SKAPA AKUTFALL  ",
  place_objects               = "  PLACERA OBJEKT  ",
  dump_strings                = "  SKAPA TEXTFILER  ",
  map_overlay                 = utf8 "  KARTÖVERSIKT  ",
  sprite_viewer               = "  GRAFIKVISARE  ",
}
menu_debug_overlay = {
  none                        = "  INGET  ",
  flags                       = "  FLAGGOR  ",
  positions                   = "  KOORDINATER  ",
  byte_0_1                    = "  BYTE 0 & 1  ",
  byte_floor                  = "  BYTE GOLV  ",
  byte_n_wall                 = utf8 "  BYTE N VÄGG  ",
  byte_w_wall                 = utf8 "  BYTE W VÄGG  ",
  byte_5                      = "  BYTE 5  ",
  byte_6                      = "  BYTE 6  ",
  byte_7                      = "  BYTE 7  ",
  parcel                      = "  TOMT  ",
}

adviser.room_forbidden_non_reachable_parts = utf8 "Rummet kan inte placeras här eftersom delar av sjukhuset då blir oåtkomliga."

dynamic_info.patient.actions.no_gp_available = utf8 "Väntar på att du ska bygga en allmänpraktik"
dynamic_info.staff.actions.heading_for = utf8 "På väg till %s"

fax = {
  welcome = {
    beta1 = {
      utf8 "Välkommen till CorsixTH, en klon i öppen källkod av det klassiska spelet Theme Hospital av Bullfrog!",
      utf8 "Detta är den första spelbara betan av CorsixTH. Även om många rum, sjukdomar och funktioner implementerats saknas fortfarande mycket.",
      utf8 "Om du gillar projektet kanske du vill hjälpa oss? Till exempel genom att rapportera buggar eller rentav börja koda något själv.",
      utf8 "Hur som helst, börja med att njuta av spelet! Här är några starttips: Bygg en reception (korridorsutrustning) och en allmänpraktik (diagnosrum). Diverse kliniker kommer också att behövas.",
      "-- Gruppen bakom CorsixTH, th.corsix.org",
      utf8 "PS: Kan du hitta påskäggen?",
    },
    beta2 = {
      utf8 "Välkommen till den andra betan av CorsixTH, det klassiska spelet Theme Hospital av Bullfrog i ny förpackning!",
      utf8 "Många funktioner har lagts till sen förra betan. Kolla in ändringsloggen för en nästan komplett lista.",
      utf8 "Men innan dess är det dags att spela! Det verkar som att ett meddelande väntar. Stäng detta fönster och klicka på frågetecknet nere till vänster.",
      "-- Gruppen bakom CorsixTH, th.corsix.org",
    },
  },
  tutorial = {
    utf8 "Välkommen till ditt första Sjukhus!",
    utf8 "Vill du ha hjälp att komma igång?",
    utf8 "Ja, det behövs.",
    utf8 "Det är lugnt, jag kan sånt här.",
  },
}

misc.not_yet_implemented = utf8 "(ej tillgänglig ännu)"
misc.no_heliport = utf8 "Antingen har inga sjukdomar upptäckts ännu, eller så finns det ingen helikopterplatta på den här banan."

main_menu = {
  new_game = "Nytt spel",
  custom_level = utf8 "Specialnivå",
  load_game = "Ladda spel",
  options = "Alternativ",
  exit = "Avsluta",
}

tooltip.main_menu = {
  new_game = utf8 "Starta ett helt nytt spel från början",
  custom_level = utf8 "Bygg ditt sjukhus i en specialnivå",
  load_game = "Ladda ett sparat spel",
  options = utf8 "Fixa till dina inställningar",
  exit = utf8 "Nej! Du vill väl inte sluta redan?",
}
