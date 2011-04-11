--[[ Copyright (c) 2011 <Zbyněk "teh humble with big ego :D" Schwarz>

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

Font("unicode")
Language("Čeština", "Czech", "cs", "cze")
Inherit("English")
Encoding(utf8)

high_score = {
  player = "HRÁČ",
  pos = "POZ",
  best_scores = "SÍŇ SLÁVY",
  killed = "Zabil",
  categories = {
    salary = "NEJVYŠŠÍ VÝPLATA",
    total_value = "CELKOVÁ HODNOTA",
    money = "NEJBOHATŠÍ",
    clean = "ČISTOTA",
    cures = "POČET VYLÉČENÍ",
    patient_happiness = "USPOKOJENÍ ZÁKAZNÍKŮ",
    deaths = "POČET ÚMRTÍ",
    cure_death_ratio = "POMĚR VYLÉČENÍ ÚMRTÍ",
    staff_happiness = "USPOKOJENÍ ZAMĚSTNANCŮ",
    visitors = "NEJVÍCE NÁVŠTĚVNÍKŮ",
    staff_number = "NEJVÍCE ZAMĚSTNANCŮ",
  },
  worst_scores = "SÍŇ HANBY",
  score = "SKÓRE",
}
menu_display = {
  shadows = "  STÍNY  ",
  mcga_lo_res = "  MCGA NÍZKÉ ROZ  ",
  high_res = "  VYSOKÉ ROZ  ",
}
rooms_long = {
  dna_fixer = "Spravovač DNA",
  psychiatric = "Psychiatrie",
  corridors = "Chodby",
  gps_office = "Kancelář Praktického Lékaře",
  general = "Všeobecné",
  emergency = "Pohotovost",
  general_diag = "Obecná Diagnóza",
  hair_restoration = "Obnovovač vlasů",
  scanner = "Skener",
  research_room = "Výzkumné Odd.",
  cardiogram = "Kardiogram",
  toilets = "Toaleta",
  decontamination = "Dekontaminace",
  staffroom = "Místnost pro Zaměstnance",
  ward = "Nemocniční pokoj",
  jelly_vat = "Želé Nádrž",
  x_ray = "Rentgen",
  inflation = "Nafukovárna",
  ultrascan = "Ultraskener",
  blood_machine = "Krevní Stroj",
  tongue_clinic = "Oddělení Ochablého Jazyka",
  fracture_clinic = "Oddělení Zlomenin",
  training_room = "Výuková Místnost",
  electrolysis = "Oddělení Elektrolýzy",
  pharmacy = "Lékárna",
  operating_theatre = "Operační Sál",
}
menu_file_load = {
  [1] = "  HRA 1  ",
  [2] = "  HRA 2  ",
  [3] = "  HRA 3  ",
  [4] = "  HRA 4  ",
  [5] = "  HRA 5  ",
  [6] = "  HRA 6  ",
  [7] = "  HRA 7  ",
  [8] = "  HRA 8  ",
}
cheats_window = {
  warning = "Varování: Pokud budete podvádět, nedostanete na konci úrovně žádné bonusové body!",
  caption = "Číty",
  cheated = {
    no = "Číty použity: Ne",
    yes = "Číty použity: Ano",
  },
  close = "Zavřít",
  cheats = {
    lose_level = "Prohrát Úroveň",
    emergency = "Vytvořit Havárii",
    end_year = "Konec Roku",
    money = "Peníze",
    win_level = "Vyhrát Úroveň",
    all_research = "Všechen Výzkum",
    create_patient = "Vytvořit Pacienta",
    end_month = "Konec Měsíce",
  },
}
menu_file_save = {
  [1] = "  HRA 1  ",
  [2] = "  HRA 2  ",
  [3] = "  HRA 3  ",
  [4] = "  HRA 4  ",
  [5] = "  HRA 5  ",
  [6] = "  HRA 6  ",
  [7] = "  HRA 7  ",
  [8] = "  HRA 8  ",
}
level_names = {
  [1] = "ToxiMěsto",
  [2] = "Ospalá Díra",
  [3] = "Velkýčestr",
  [4] = "Frimpton na Moři",
  [5] = "Prosťáčkov",
  [6] = "Hnisání na Pláni",
  [7] = "Zelená Kaluž",
  [8] = "Lidské přístaviště",
  [9] = "Východní město",
  [10] = "Vejceseslaninou",
  [11] = "Skřehotálkov",
  [12] = "Vykrmené město",
  [13] = "Chumleigh",
  [14] = "Malé Ztlouknutí",
  [15] = "Zakopej Pohřbi",
}
custom_game_window = {
  caption = "Vlastní Hra",
}
menu_debug_overlay = {
  positions = "  POZICE  ",
  parcel = "  PARCELA  ",
  byte_6 = "  BAJT 6  ",
  byte_floor = "  BAJT PODLAHY  ",
  none = "  ŽÁDNÝ  ",
  flags = "  PŘÍZNAKY  ",
  byte_0_1 = "  BAJT 0 a 1  ",
  byte_n_wall = "  BAJT S ZDI  ",
  byte_w_wall = "  BAJT Z ZDI  ",
  byte_5 = "  BAJT 5  ",
  byte_7 = "  BAJT 7  ",
  heat = "  TEPLOTA  ",
}
newspaper = {
  [1] = {
    [1] = "HOROR DR ŠOKA",
    [2] = "DIVNÝ OBECNÝ LÉKAŘ SI HRAJE NA BOHA",
    [3] = "ŠOK ŠPRÝMOŠTAINA",
    [4] = "CO BYLO NA LABORATORNÍM STOLE?",
    [5] = "RAZIE ZASTAVILA RISKANTNÍ VÝZKUM",
  },
  [2] = {
    [1] = "OPILÝ DO NĚMOTY",
    [2] = "OPILÝ CHIRURG",
    [3] = "HÝŘIVÝ KONZULTANT",
    [4] = "CHIRURGICKÁ ŠTAMPRLE",
    [5] = "CHIRURG NASÁVÁ",
    [6] = "CHIRURGICKÉ DUŠIČKY",
  },
  [3] = {
    [1] = "CHTIVÝ CHIRURG",
    [2] = "DOKTOR KALHOTYDOLŮ",
    [3] = "DOKTOR MÍŘÍ DOLŮ",
    [4] = "NEUSPOKOJITELNÝ CHIRURG",
  },
  [4] = {
    [1] = "DOKTOR UPRAVUJE ČÍSLA",
    [2] = "ORGÁN-IZOVANÝ ZLOČIN",
    [3] = "OPERACE PŘEKLENUTÍ BANKY",
    [4] = "LÉKAŘ DRŽÍ FONDY",
  },
  [5] = {
    [1] = "ZDRAVOTNÍ VÝZKUMNÍK LOUPÍ HROBY",
    [2] = "DOKTOR VYPRAZDŇUJE HROBY",
    [3] = "PŘICHYCEN S MRTVOLOU",
    [4] = "DEN ZÚČTOVÁNÍ DR SMRTKY",
    [5] = "SMRTELNÁ NEDBALOST",
    [6] = "DOKTOROVO NALEZIŠTĚ ODHALENO",
  },
  [6] = {
    [1] = "DOKTOROVA TAJNÁ DOHODA!",
    [2] = "NEPOZORNÝ MASTIČKÁŘ",
    [3] = "ZNIČUJÍCÍ DIAGNÓZA",
    [4] = "NEŠIKOVNÝ KONZULTANT",
  },
  [7] = {
    [1] = "DOKTOR NEMÁ CO DĚLAT",
    [2] = "CHIRURG 'OPERUJE' SÁM SEBE",
    [3] = "MASTURBACE NA HAJZLU",
    [4] = "DOCTOR'S HANDLE SCANDAL",
    [5] = "MEDIK DĚLÁ BORDEL",
  },
}
months = {
  [1] = "Led",
  [2] = "Úno",
  [3] = "Bře",
  [4] = "Dub",
  [5] = "Kvě",
  [6] = "Čer",
  [7] = "Čvc",
  [8] = "Srp",
  [9] = "Zář",
  [10] = "Říj",
  [11] = "Lis",
  [12] = "Pro",
}
dynamic_info = {
  object = {
    strength = "Síla %d",
    queue_size = "Velikost Fronty %d",
    times_used = "Kolikrát Použito %d",
    queue_expected = "Očekávaná Fronta %d",
  },
  patient = {
    diagnosed = "Diagnostikovaný: %s ",
    diagnosis_progress = "Průběh Diagnózy",
    guessed_diagnosis = "Odhadnutá diagnóza: %s ",
    actions = {
      no_diagnoses_available = "Nemáte pro mě žádné další diagnózy - Jdu domů",
      no_gp_available = "Čekám až postavíte kancelář praktického lékaře",
      cured = "Vyléčen!",
      waiting_for_treatment_rooms = "Čekám, až pro mě vybudujete místnost k léčení",
      fed_up = "Naštvaný a odchází",
      prices_too_high = "Vaše ceny jsou příliš vysoké - Jdu domů",
      on_my_way_to = "Na cestě do %s",
      sent_home = "Poslán Domů",
      dying = "Umírá!",
      no_treatment_available = "Není pro mě diagnóza - Jdu domů",
      epidemic_contagious = "Jsem nakažlivý",
      waiting_for_diagnosis_rooms = "Čekám, až postavíte další diagnostická oddělení",
      queueing_for = "Ve frontě pro %s",
      awaiting_decision = "Čekám na Vaše rozhodnutí",
      sent_to_other_hospital = "Odkázán jinam",
      epidemic_sent_home = "Poslán domů Inspektorem",
    },
    emergency = "Havárie: %s",
  },
  staff = {
    psychiatrist_abbrev = "Psych.",
    tiredness = "Unavenost",
    actions = {
      heading_for = "Mířím do %s",
      fired = "Propuštěn",
      wandering = "Jen se tak potuluji",
      waiting_for_patient = "Čekám na pacienta",
      going_to_repair = "Jdu opravit %s",
    },
    ability = "Dovednost",
  },
  vip = "VIP Návštěvník",
  health_inspector = "Hygienický Inspektor",
}
calls_dispatcher = {
  summary = "%d volání; %d přiřazeno",
  watering = "Zalévám @ %d,%d",
  repair = "Opravit %s",
  staff = "%s - %s",
  close = "Zavřít",
}
town_map = {
  number = "Číslo Pozemku",
  area = "Oblast Pozemku",
  not_for_sale = "Nelze Vlastnit",
  owner = "Vlastník Pozemku",
  chat = "Chat Podrobností Města",
  for_sale = "Na prodej",
  price = "Cena Pozemku",
}
confirmation = {
  replace_machine = "Jste si jisti, že chcete nahradit %s za $%d?",
  abort_edit_room = "Právě stavíte nebo upravujete místnost. Pokud jsou všechny povinné objekty umístěny, bude dokončena, ale jinak bude smazána. Pokračovat?",
  quit = "Zvolili jste, že chete Odejít. Opravdu chcete hru opustit?",
  needs_restart = "Změna tohoto nastavení vyžaduje restart CorsixTH. Jakýkoli neuložený postup bude ztracen. Jste si jiti, že to chcete udělat?",
  delete_room = "Opravdu chcete tuto místnost smazat?",
  sack_staff = "Jste si jisti, že chcete tohoto zaměstnance vykopnout?",
  restart_level = "Jste si jisti, že chcete úroveň restartovat?",
  overwrite_save = "Hra už byla do této pozice uložena. Jste si jisti, že ji chcete přepsat?",
  return_to_blueprint = "Jste si jisti, že se chcete vrátit do režimu Návrhu?",
}
adviser = {
  goals = {
    win = {
      reputation = "Zvyšte Vaši reputaci na %d ke splnění kritéria pro výhru úrovně",
      money = "Potřebujete dalších %d ke splnění finančního kritéria v této úrovni.",
      cure = "Vylečte dalších %d pacientů a budete mít dostatek k výhře v této úrovni.",
      value = "Musíte zvýšit Vaši hodnotu nemocnice na %d",
    },
    lose = {
      kill = "Zabijte dalších %d pacientů a úroveň prohrajete!",
    },
  },
  competitors = {
    staff_poached = "Jeden z Vašich zaměstnanců byl ukraden jinou nemocnicí.",
    land_purchased = "%s právě koupil pozemek.",
    hospital_opened = "%s otevřel v oblasti konkurenční nemocnici.",
  },
  information = {
    promotion_to_doctor = "One of your JUNIORS has become a DOCTOR.",
    pay_rise = "Jeden z Vašich zaměstnanců vyhrožuje výpovědí. Zvolte, jestli s jejich požadavky souhlasíte nebo je vykopnete. Klikněte na ikonu vlevo, abyste viděli, který zaměstnanec hrozí výpovědí.",
    handyman_adjust = "Údržbáři můžou čistit účiněji tím, že jim zadáte priority.",
    emergency = "Je tu pohotovost! Pohyb! Pohyb! POHYB!",
    epidemic_health_inspector = "Zprávy o Vaší epidemii se donesly na Ministerstvo Zdravotnictví. Připravte se na návštěvu Hygienického Inspektora.",
    fax_received = "Ikona která vyskočila vlevo dole na obrazovce Vás upozorňuje na důležitou informaci nebo rozhodnutí, které musíte udělat.",
    larger_rooms = "Větší místnosti dávájí zaměstnancům pocit důležitosti a zlepšují jejich výkon.",
    first_cure = "Výborně! Právě jste vyléčili Vašeho prvního Pacienta.",
    promotion_to_specialist = "Jeden z Vašich Doktorů byl povýšen na %s.",
    initial_general_advice = {
      psychiatric_symbol = "Doktoři kvalifikování v Psychiatrických záležitostech mají symbol: |",
      research_symbol = "Doktoři schopní výzkumu mají symbol: }",
      surgeon_symbol = "Doktoři, kteří mohou provádět operace mají symbol: {",
      epidemic_spreading = "Ve Vaší nemocnici je nákaza. Zkuste nakažené lidi vyléčit dřív, než odejdou.",
      first_epidemic = "Ve Vaší nemocnici je epidemie! Rozhodněte, zda-li to chcete ututlat nebo přiznat barvu.",
      autopsy_available = "Auto-Pitevní stroj byl vynalezen. Tímto se můžete zbavit problémových a nevítaných pacientů a udělat na jejich zbytcích výzkum. Berte na vědomí, že použití tohoto přístroje je vysoce kontroverzní.",
      first_VIP = "Chystáte se pořádat Vaši první návštěvu VIP. Snažte se zajistit, aby VIP neviděl nic nehygienického, nebo nějaké nešťastné pacienty.",
      place_radiators = "Lidem ve Vaší nemocnici je zima - můžete umístit více radiátorů tím, že je vyberete z menu Položek Chodby.",
      first_emergency = "Urgentní pacienti mají nad svými hlavami blikající modré světlo. Vylečte je předtím, než zemřou nebo vyprší čas.",
      research_now_available = "Vybudovali jste Vaši první Výzkumnou místnost. Nyní můžete vstoupit do obrazovky Výzkumu.",
      taking_your_staff = "Někdo krade Váš personál. Budete muset bojovat, aby tu zůstali.",
      first_patients_thirsty = "Lidé mají ve Vaší nemocnici žízeň. Umistěte pro ně automat na nápoje.",
      machine_needs_repair = "Máte stroj, který potřebuje opravit. Nalezněte tento stroj - bude se z něho kouřit - a klikněte na něj. Pak klikněte na tlačítko údržbáře.",
      decrease_heating = "Lidem ve Vaší nemocnici je horko. Snižte úroveň vytápění. To se provádí v Obrazovce Města.",
      increase_heating = "Lidem je zima. Zvyšte teplotu vytápění v Obrazovce Města.",
      rats_have_arrived = "Vaši nemocnici zamořily krysy. Zkuste je myší zastřelit.",
    },
    place_windows = "Umístěním oken bude místnost jasnější a zlepší náladu Vašich zaměstnanců.",
    patient_leaving_too_expensive = "Pacient odchází, aniž by zaplatil za %s. Je to příliš drahé.",
    vip_arrived = "Pozor! - %s právě přijel na obhlídku Vaší nemocnice! Ujistěte se, že vše běží hladce, abyste ho potěšily.",
    epidemic = "Ve Vaší nemocnici máte nakažlivou chorobu. Musíte s tím okamžitě něco dělat!",
    first_death = "Právě jste zabili svého prvního pacienta. Jaký je to pocit?",
    extra_items = "Dodatečné věci v místnostech Vaše zaměstnance uklidňuje a zlepšuje jejich výkon.",
    promotion_to_consultant = "Jeden z Vašich DOKTORŮ se stal KONZULTANTEM.",
    patient_abducted = "Jednoho z Vašich pacientů unášejí mimozemšťani.",
  },
  praise = {
    many_plants = "Jak milé. Máte spousty rostlin. Vaši Pacienti to jistě ocení.",
    few_have_to_stand = "Jen málokdo musí ve Vaší nemocnici stát. To pacienty potěší.",
    plenty_of_benches = "Je tu spousta míst k sezení, takže to není problém.",
    many_benches = "Pacienti teď mají dostatek míst k sezení. Bod pro Vás.",
    plants_thriving = "Velmi dobře. Vaše rostliny přímo vzkvétají. Vypadají úžasně. Jen tak dál a možná za ně vyhrajete ocenění.",
    plants_are_well = "To je hezké. Dobře se staráte o Vaše rostliny. Milé.",
    patients_cured = "%d Pacientů vyléčeno.",
  },
  placement_info = {
    reception_can_place = "Tuto recepci můžete umístit zde.",
    window_can_place = "Toto okno můžete umístit zde. Je to v pořádku.",
    door_can_place = "Pokud chcete, můžete tyto dveře umístit zde.",
    reception_cannot_place = "Zde nemůžete tuto Recepci umístit.",
    object_can_place = "Zde můžete umístit tento objekt.",
    room_cannot_place = "Zde nemůžete tuto místnost umístit.",
    room_cannot_place_2 = "Zde nemůžete tuto místnost umístit.",
    window_cannot_place = "Aha. Zde vlastně okno umístit nemůžete.",
    staff_cannot_place = "Zde nemůžete zaměstnance umístit. Je mi líto.",
    staff_can_place = "Zde můžete zaměstnance umístit. ",
    door_cannot_place = "Je mi líto, ale zde nemůžete dveře umístit.",
    object_cannot_place = "Hej, zde tento objekt umístit nemůžete.",
  },
  surgery_requirements = {
    need_surgeons_ward_op = "Musíte zaměstnat dva Chirurgy a postavit Nemocniční Pokoj a také Operační Sál k provedení Operace.",
    need_surgeon_ward = "Stále potřebujete zaměstnat dalšího Chirurga a postavit Nemocniční Pokoj, abyste mohli provádět Operace.",
  },
  build_advice = {
    placing_object_blocks_door = "Umístěním tohoto objektu zde by zabránil lidem dostat se k dveřím.",
    door_not_reachable = "Lidé by nebyli schopni se ke dveřím dostat. Přemýšlejte o tom.",
    blueprint_would_block = "Tento návrh by bránil ostatním místnostem. Zkuste změnit její velikost, nebo ji přesunout jinam!",
    blueprint_invalid = "To není platný návrh.",
  },
  multiplayer = {
    poaching = {
      not_interested = "Ha! Nemají zájem pro Vás pracovat - jsou spokojeni tam, kde jsou.",
      already_poached_by_someone = "To snad ne! Někdo se už snaží tuto osobu ukrást.",
      in_progress = "Dám Vám vědět, zda-li tato osoba bude chtít jít pro Vás pracovat.",
    },
    everyone_failed = "Všichni nedokázali splnit poslední úkol. Takže všichni budou hrát dál !",
    players_failed = "Následující hráč(i) nedokázal(i) splnit poslední úkol : ",
    objective_completed = "Splnili jste úkol. Blahopřeji!",
    objective_failed = "Nedokázali jste splnit úkol.",
  },
  staff_place_advice = {
    only_doctors_in_room = "Pouze Doktoři mohou v %s pracovat",
    only_nurses_in_room = "Pouze Sestry mohou v %s pracovat",
    receptionists_only_at_desk = "Recepční mohou pracovat pouze v Recepci.",
    nurses_cannot_work_in_room = "Sestry nemohou v %s pracovat",
    only_researchers = "Doktoři mohou ve Výzkumném Oddělení pracovat pouze, pokud mají Výzkumnou odbornost.",
    only_surgeons = "Doktoři mohou na Operačním Sále pracovat pouze, pokud mají Chirurgickou odbornost.",
    only_psychiatrists = "Doktoři mohou na Psychiatrii pracovat pouze, pokud mají Psychiatrickou odbornost.",
    doctors_cannot_work_in_room = "Doktoři nemohou v %s pracovat",
  },
  tutorial = {
    start_tutorial = "Přečtěte si Úvod do Mise, pak klikněte levým tlačítkem myši ke spuštění výuky.",
    room_too_small_and_invalid = "Návrh je příliš malý a na neplatném místě. Tak jen do toho.",
    place_receptionist = "Přesuňte Recepční a umistěte ji kamkoliv. Chytře se přesune ke svému stolu.",
    next_receptionist = "Toto je první Recepční v seznamu. Klikněte lavým tlačítkem na blikajicí ikonku k zobrazení další dostupné.",
    build_reception = "Dobrý den. Nejdříve potřebuje Vaše nemocnice Recepci. Vyberte jednu z menu Položek Chodby.",
    accept_purchase = "Klikněte levým tlačítkem, abyste ji zakoupili.",
    window_in_invalid_position = "Toto okno je v neplatné pozici. Zkuste ho umístit někde jinde na zdi, pokud byste byli tak laskavi.",
    order_one_reception = "Klikněte jednou na blikající řádek levým tlačítkem myši k objednání jedné Recepce.",
    place_door = "Pohybujte myší okolo zdí návrhu, abyste umístili dveře tam, kam je chcete.",
    object_in_invalid_position = "Tato položka je v neplatné pozici. Prosím, buď ji umístěte někam jinam, nebo ji otočte tak, aby se vešla.",
    click_and_drag_to_build = "Pro vybudování kanceláře Praktického Lékaře si nejdříve musíte promyslet, jak bude velká. Klikněte a držte levé tlačítko, při držení Vaší místnosti, pro změnu velikosti.",
    doctor_in_invalid_position = "Hej! Zde Doktora dát nemůžete.",
    build_gps_office = "Abyste mohli začit vyšetřovat nemoci pacientů musíte postavit kancelář praktického lékaře.",
    prev_receptionist = "Klikněte levým tlačítkem na blikajicí ikonu k zobrazení předchozí dostupné Recepční.",
    door_in_invalid_position = "Ah! Snažili jste se umístit dveře do neplatné polohy. Zkuste někde jinde na zdech návrhu.",
    room_big_enough = "Návrh je nyní dostatečně velký. Když uvolníte tlačítko myši, tak bude umístěna. Stále ji můžete přemisťovat, nebo měnit její velikost.",
    select_receptionists = "Klikněte levým tlačítkem na blikající ikonu, pro zobrazení, které Recepční jsou nyní k dispozici pro práci. To číslo na ikoně označuje, z kolika si musíte vybrat.",
    hire_doctor = "Potřebujete Dokotra, který bude vyšetřovat a léčit nemocné lidi.",
    place_doctor = "Umístěte Doktora kdekoliv v nemocnici. Jakmile v kanceláři bude někdo k vyšetření, tak tam vyrazí.",
    choose_doctor = "Dobře se podívejte na dovednosti každého Doktora, než si jednoho zvolíte.",
    click_gps_office = "Klikněte levým tlačítkem na řádek pro vybrání kanceláře praktického lékaře.",
    choose_receptionist = "Rozhodněte, která Recepční má dobré dovednosti a spravedlivou mzdu a pak klikněte levým tlačítkem na blikající ikonu, abyste ji zaměstnali.",
    hire_receptionist = "Budete také potřebovat Recepční, aby se postarala o pacienty.",
    reception_invalid_position = "Recepce je zašedivělá protože je v neplatné pozici. Zkuste ji posunout nebo otočit.",
    rotate_and_place_reception = "Klikněte pravým tlačítkem myši k otočení Recepce a umístěte ji ve Vaší nemocnici levým tlačítkem myši.",
    place_windows = "Okna umístěte stejným způsobem jako dveře. Okna sice nepotřebujete, ale Vaši zaměstnanci jsou šťastnější, když se mají z čeho koukat ven.",
    room_too_small = "Tento návrh místnosti je červený, protože je moc malý. Roztáhněte ho více, aby byl větší.",
    build_pharmacy = "Blahopřeji! Nyní vybudujte Lékárnu a zaměstnejte Sestru, abyste dostali fungující nemocnici.",
    room_in_invalid_position = "Jejda! Tento návrh je neplatný - červené oblasti označují kde jste překrývá s jinou místností nebo zdmi nemocnice.",
    select_doctors = "Klikněte levým tlačítkem na blikající ikonu, abyste se podívali na Doktory, dostupné k najmutí.",
    place_objects = "Pravým tlačítkem otáčíte položky místnosti, a levým tlačítkem je umisťujete.",
    receptionist_invalid_position = "Zde nemůžete Recepční umístit.",
    select_diagnosis_rooms = "Klikněte levým tlačítkem na blikající ikonu pro zobrazení seznamu dostupných diagnostických místností.",
    information_window = "Rámeček Nápovědy Vám říká vše o té hezké kanceláři, kterou jste právě vybudovali.",
    confirm_room = "Klikněte levým tlačítkem na blikající ikonu k otevření Vaší místnosti pro činnost nebo klikněte na ikonku X, abyste šli o krok zpět.",
  },
  room_requirements = {
    op_need_two_surgeons = "Zaměstnejte dva Chirurgy, k provádění operací na Operačním Sále.",
    op_need_ward = "Musíte vybudovat Nemocniční Pokoj k Předoperačnímu Vyšetření pacientů, než budou moci jít na zákrok.",
    research_room_need_researcher = "K použití Výzkumné Místnosti musíte zaměstnat Doktora s Výzkumnou odborností.",
    training_room_need_consultant = "Musíte zaměstnat Konzultanta, který bude ve Výukové Místnosti učit.",
    pharmacy_need_nurse = "Pro tuto Lékárnu musíte zaměstnat Sestru.",
    reception_need_receptionist = "Musíte zaměstnat Recepční, abyste mohli vidět Vaše pacienty.",
    op_need_another_surgeon = "Stále musíte ještě zaměstnat jednoho Chirurga, aby Operační Sál mohl být použitelný.",
    psychiatry_need_psychiatrist = "Když jste nyní postavili Psychiatrii, musíte také zaměstnat Psychiatra.",
    ward_need_nurse = "Pro tento Nemocniční Pokoj musíte zaměstnat Sestru.",
    gps_office_need_doctor = "Potřebujete zaměstnat Doktora, aby v této kanceláři pracoval.",
  },
  research = {
    new_available = "Nový %s je dostupný.",
    drug_fully_researched = "%s jste vyzkoumali na 100%.",
    new_drug_researched = "Nový lék pro léčbu %s byl vynalezen.",
    drug_improved = "Lék %s byl vylepšen Vašim Výzkumným Oddělením.",
    autopsy_discovered_rep_loss = "Váš stroj Auto-Pitvy byl objeven. Očekávejte zápornou reakci obecné veřejnosti.",
    new_machine_researched = "Nový %s byl právě úspěšně vynalezen.",
    machine_improved = "%s byl vylepšen Vašim Výzkumným Oddělením.",
  },
  cheats = {
    bloaty_cheat = "Čít Nafouknuté Hlavy aktivován!",
    th_cheat = "Blahopřejeme, právě jste odemkli číty!",
    hairyitis_cheat = "Čít Vlasoitidy aktivován!",
    crazy_on_cheat = "Ale ne! Všichni doktoři se zbláznili!",
    roujin_off_cheat = "Roujinova výzva deaktivována.",
    crazy_off_cheat = "Uf... doktoři znovu získali svou příčetnost.",
    hairyitis_off_cheat = "Čít Vlasoitidy deaktivován.",
    roujin_on_cheat = "Roujinova výzva aktivována! Hodně štěstí...",
    bloaty_off_cheat = "Čít Nafouknuté Hlavy deaktivován.",
  },
  room_forbidden_non_reachable_parts = "Umístěním místnosti zde by zapříčinilo, že části nemocnice by byly nedostupné.",
  level_progress = {
    improve_reputation = "Potřebujete svoji reputaci zlepšit o %d, abyste vůbec měli šanci tuto úroveň vyhrát.",
    three_quarters_lost = "Jste na tři čtvrtě cesty k prohře v této úrovni.",
    another_patient_cured = "Výborně - další pacient vyléčen. To je teď %d.",
    three_quarters_won = "Jste na tři čtvrtě cesty k výhře této úrovně.",
    nearly_lost = "Dostáváte se velmi blízko k prohře této úrovně.",
    halfway_won = "Jste tak na půli cesty k výhře v této úrovni.",
    another_patient_killed = "Ale ne! Zabili jste dalšího pacienta. To teď dělá %d úmrtí.",
    dont_kill_more_patients = "Vážně si nemůžete dovolit nechat zemřít další pacienty!",
    reputation_good_enough = "Dobře, Vaše reputace je dost vysoká na výhru této úrovně. Udržujte ji nad %d a vyřešte jiné problémy, abyste ji dokončili.",
    nearly_won = "Jste velmi blízko k výhře v této úrovni.",
    hospital_value_enough = "Udržte hodnotu své nemocnice nad %d a věnujte se Vašim ostatním problémům, abyste úroveň vyhráli.",
    close_to_win_increase_value = "Dostáváte se velmi blízko k výhře. Zvyšte hodnotu Vaší nemocnice o %d.",
    cured_enough_patients = "Sice jste vyléčili dostatek pacientů, ale budete muset udělat ve Vaší nemocnici lepší pořádek, abyste úroveň vyhráli.",
    financial_criteria_met = "Splnili jste finanční kritéria pro tuto úroveň. Nyní udržujte Vaši bilanci nad %d a zároveň se ujistěte, že Vaše nemocnice dobře beží.",
    halfway_lost = "Jste na půl cesty k prohře v této úrovni.",
  },
  warnings = {
    litter_catastrophy = "Situace s odpadky je bezútěšná. Ať na tom hned začne pracovat tým Údržbářů!",
    financial_trouble = "Jste ve vážných finančních potížích. Hned si zorganizujte své finance! Pokud ztratíte dalších %d, tak zahodíte celou tuto úroveň!",
    need_toilets = "Pacienti potřebují toalety. Vybudujte je na snadno přístupném místě.",
    many_epidemics = "Vypadá to, že u Vás propukla více než jedna epidemie najednou. To by mohla být obrovská katastrofa, takže rychle s tím něco dělejte.",
    need_staffroom = "Postavte Místnost pro Zaměstnance, aby si Vaši zaměstnanci mohly kde odpočinout.",
    nobody_cured_last_month = "Minulý měsíc nebyl vůbec nikdo vyléčen.",
    charges_too_high = "Vaše poplatky jsou vysoké. Sice budete mít krátkodobě vysoké příjmy, ale nakonec začnete odhánět lidi pryč.",
    patient_stuck = "Někdo uváznul. Plánujte Vaši nemocnici lépe.",
    build_staffroom = "Okamžitě postavte Místnost pro Zaměstnance. Vaši zaměstnanci pracují příliš tvrdě a jsou napokraji zhroucení. No tak - mějte rozum!",
    machinery_very_damaged = "Nalehávé! Řekněte Vašemu Údržbáři, aby okamžitě opravil Vaše přístroje! Chystají se vybouchnout!",
    nurses_tired2 = "Vaše Sestry jsou velmi unavené. Hned jim dejte odpočinout.",
    patients_very_thirsty = "Pacienti opravdu trpí žízní. Pokud brzo neumístíte automaty na nápoje, budete čelit velkému odcházení, jak všichni lidé odejdou domů pro kolu.",
    machinery_deteriorating = "Vaše přístroje začali chátrat kvůli nadměrnému užívání. Tak je hlídejte.",
    machine_severely_damaged = "%s je velmi blízko k nenapravitelné škodě.",
    people_have_to_stand = "Trpící lid musí stát. Hned umistěte další sezení.",
    machinery_damaged2 = "Musíte brzo zaměstnat Údržbáře, aby opravil Vaše přístroje.",
    deal_with_epidemic_now = "Pokud se s touto epidemií brzo něco neprovede, budete až po oči v průšvihu. Tak pohyb!",
    too_many_plants = "Máte až příliš mnoho kytek. Je to tam jako v džungli.",
    patients_thirsty = "People are getting thirsty. Perhaps you should provide them with drinks machines.",
    machinery_slightly_damaged = "Vaše přistroje v nemocnici jsou lehce poškozené. Nezapomeňte, abyste je všechny někdy udržovali.",
    change_priorities_to_plants = "Musíte změnit priority Vašich Údržbářů, aby trávili více času zaléváním rostlin.",
    queue_too_long_send_doctor = "Vaše fronty %s jsou příliš dlouhé. Ujistěte se, že v místnosti je doktor.",
    too_much_litter = "Máte problém s odpadky. Více údržbářů by mohla být odpověď.",
    place_plants_to_keep_people = "Lidé odcházejí. Umístěním kytek je může přesvědčit, aby zůstali.",
    queue_too_long_at_reception = "Máte příliš mnoho pacientů, čekajících na přidělení místnosti v recepci. Umístěte další Recepci a zaměstnejte další Recepční.",
    machines_falling_apart = "Vaše přístroje se začínají rozpadat. Okamžitě k nim pošlete Údržbáře!",
    patients_too_hot = "Pacientům začíná být velké horko. Buď nějaké radiátory odstraňte, snižte teplotu nebo umístěte pro ně víc automatů na nápoje.",
    staff_tired = "Vaši zaměstnanci začínají být pěkně unavení. Pokud je nenecháte trochu si odpočinout v Místnosti pro Zaměstnance, někteří by mohli pod tlakem zešílet.",
    cash_low_consider_loan = "Vaše peněžní situace je velmi vážná. Přemýšleli jste o půjčce?",
    patient_leaving = "Pacient odchází. Důvod? Vaše mizerně spravovaná a špatně zaměstnaná i vybavená nemocnice.",
    build_toilet_now = "Hned vybudujte toaletu. Lidé už to nemůžou vydržet. Nesmějte se - tohle je vážné.",
    epidemic_getting_serious = "Ta Nakažlivá Choroba se stává vážnou. Musíte brzo něco udělat!",
    money_very_low_take_loan = "Vaše Bankovní Bilance je strašlivě nízká. Mohli byste si vzít půjčku, víte.",
    more_benches = "Promyslete si umístění více laviček. Nemocní lidé nenávidí, když musejí vstávat.",
    some_litter = "Údržbáři se mohou odpadků zbavit dřív. než se z toho stane vážný problém.",
    patients_very_cold = "Pacientům je velmi zima. Zkuste zvýšit vytápění, nebo umístěte více radiátorů ve Vaší nemocnici.",
    receptionists_tired2 = "Vaše Recepční jsou velmi vyčerpané. Hned je nechte odpočinout.",
    patients_getting_hot = "Pacientům začíná být velké horko. Zkuste snížit vytápění, nebo dokonce odstraňte některé radiátory.",
    people_did_it_on_the_floor = "Někteří pacienti to nemohli vydržet. Čištění bude pro někoho velká práce.",
    patients_really_thirsty = "Pacienti mají velkou žízeň. Umístěte více automatů na nápoje, nebo přemistěte existující blízko k největším frontám.",
    doctors_tired = "Vaši Doktoři jsou velmi unavení. Hned je nechte odpočinout.",
    financial_trouble3 = "Vaše bankovní bilance vypadá trochu znepokojivě. Přemýšlejte o vydělávání více peněz. Jste %d vzdáleni od katastrofy.",
    handymen_tired2 = "Vaši Údržbáři jsou naprosto zničení. Okamžitě jim dejte odpočinout.",
    patients_thirsty2 = "Lidé si stěžují na žízeň. Měli byste umístit další Automaty na nápoje, nebo existující přesuňte blíže k nim.",
    people_freezing = "Neuvěřitelné, v této době centrálního vytápění, někteří Vaši pacienti mrznou zimou. Postavte radiátory, aby jim bylo teplo a zvyšte vytápění.",
    staff_too_hot = "Vaši zaměstnanci se přehřívají. Snižte teplotu, nebo odstraňte radiátory z jejich místností.",
    staff_unhappy2 = "Vaši zaměstnanci jsou obecně neštastní. Také budou brzo chtít více peněz.",
    charges_too_low = "Účtujete si příliš málo. Sice to přinese více lidí do nemocnice, ale z každého nebudete mít moc velký výdělek.",
    staff_very_cold = "Zaměstnanci si stěžují na zimu. Zvyšte vytápění, nebo umistěte více radiátorů.",
    place_plants4 = "Utěšte Pacienty pomocí více rostlin v prostředí.",
    nurses_tired = "Vaše sestry jsou unavené. Hned jim dejte odpočinout.",
    bankruptcy_imminent = "Hej! Míříte směrem k bankrotu. Buďte opatrní!",
    handymen_tired = "Vaši Údržbáři jsou unavení. Dejte jim odpočinout.",
    finanical_trouble2 = "Zařiďte, aby Vám přicházeli peníze nebo budete na dlažbě. Úroveň prohrajete, jestli přijdete o dalších %d.",
    desperate_need_for_watering = "Zoufale potřebujete zaměstnat Údržbáře, aby se staral o Vaše rostliny.",
    machinery_damaged = "Hned opravte Vaše přístroje. Nebude dlouho trvat a začnou se rozpadat.",
    many_killed = "Nyní jste zabili %d lidí. Víte, že jim máte pomáhat.",
    litter_everywhere = "Všude jsou odpadky. Pošlete na tento problém pár Údržbářů.",
    no_patients_last_month = "Minulý měsíc nepřišli do Vaší nemocnice žádní noví pacienti. Šokující!",
    receptionists_tired = "Vaše Recepční jsou vážně unavené. Hned jim dejte odpočinout.",
    more_toilets = "Potřebujete více toalet. Lidem se u zadku dělají podezřelé objekty.",
    plants_thirsty = "Potřebujete se starat o Vaše rostliny. Začínají mít žízeň.",
    doctors_tired2 = "Vaši Doktoři jsou neuvěřitelně unavení. Potřebují okamžitý odpočinek.",
    staff_overworked = "Vaši zaměstnanci jsou strašně přepracovaní. Stávají se neschopnými a začnou dělat katastrofické chyby.",
    patients_annoyed = "Lidé jsou strašně naštvaní na způsob, jak vedete nemocnici. A já se jim nemůžu divit. Vzpamatujte se, nebo čelte následkům!",
    hospital_is_rubbish = "Lidé otevřeně říkají, že Vaše nemocnice je příšerná. Než se nadáte, vezmou si jejich nemoci jinam.",
    pay_back_loan = "Máte dostatek peněz. Co takhle pomyslet na splacení půjčky?",
    plants_dying = "Vaše rostliny umírají. Zoufale touží po vodě. Ať na tomto pracuje více Údržbářů. Pacienti nemají rádi mrtvé rostliny.",
    patients_unhappy = "Pacienti nemají rádi Vaši nemocnici. Měli byste něco udělat pro zlepšení jejich prostředí.",
    queues_too_long = "Vaše fronty jsou příliš dlouhé.",
    place_plants2 = "Lidé odcházejí. Trochu více rostlin by je mohlo zde déle udržet.",
    patients_leaving = "Pacienti odcházejí. Zlepšete nemocnici pro Vaše návštěvníky umístěním rostlin, laviček, Automatů na nápoje a tak dále.",
    money_low = "Docházejí Vám peníze!",
    reception_bottleneck = "V Recepci je zácpa. Zaměstnejte další Recepční.",
    staff_unhappy = "Vaši zaměstnanci jsou nešťastní. Zkuste jim dát příplatek, nebo ještě lépe, postavte jim Místnost pro Zaměstnance. Také byste mohli změnit zásady odpočinku Vašich zaměstnanců na obrazovce Zásady.",
    reduce_staff_rest_threshold = "Zkuste snížit práh Odpočinku Zaměstnanců ve Vaší obrazovce Zásad tak, aby Vaši zaměstnanci častěji odpočívají. Jen takový nápad.",
    place_plants3 = "Pacienti začínají být nešťastní. Umístěte více rostlin, abyste je utěšili.",
    build_toilets = "Hned teď vybudujte Toaletu nebo uvidíte něco velmi nepěkného. A představte si, jak Vaše nemocnice bude smrdět.",
    }}