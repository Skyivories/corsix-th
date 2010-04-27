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

Language("portuguese", "pt", "pt")
Inherit("english")
Inherit("original_strings", 0)

-- override
adviser.warnings.money_low = "Est�s a ficar sem dinheiro!" -- Funny. Exists in German translation, but not existent in english?
-- TODO: tooltip.graphs.reputation -- this tooltip talks about hospital value. Actually it should say reputation.
-- TODO: tooltip.status.close -- it's called status window, not overview window.

-- The originals of these two contain one space too much
fax.emergency.cure_not_possible_build = "Vais precisar de construir %s"
fax.emergency.cure_not_possible_build_and_employ = "Vais precisar de construir um %s e empregar um %s"

-- new strings
object.litter = "Lixo"
tooltip.objects.litter = "Lixo: Deitado fora por um paciente porque n�o encontrou um caixote do lixo onde o colocar."

menu_options.lock_windows = "  BLOQUEAR JANELAS  "
menu_options_game_speed.pause = "  PAUSA  "

menu_debug = {
  transparent_walls           = "  PAREDES TRANSPARENTES  ",
  limit_camera                = "  LIMITAR C�MARA  ",
  disable_salary_raise        = "  DESACTIVAR AUMENTO DOS SAL�RIOS  ",
  make_debug_patient          = "  MAKE DEBUG PATIENT  ",
  spawn_patient               = "  GERAR PACIENTE  ",
  make_adviser_talk           = "  MAKE ADVISER TALK  ",
  show_watch                  = "  MOSTRAR REL�GIO  ",
  create_emergency            = "  CRIAR EMERG�NCIA  ",
  place_objects               = "  COLOCAR OBJECTOS  ",
  dump_strings                = "  DUMP DAS STRINGS  ",
  map_overlay                 = "  OVERLAY DO MAPA  ",
  sprite_viewer               = "  VISUALIZAR SPRITES  ",
}
menu_debug_overlay = {
  none                        = "  NENHUM  ",
  flags                       = "  FLAGS  ",
  positions                   = "  POSI��ES  ",
  byte_0_1                    = "  BYTE 0 & 1  ",
  byte_floor                  = "  BYTE FLOOR  ",
  byte_n_wall                 = "  BYTE N WALL  ",
  byte_w_wall                 = "  BYTE W WALL  ",
  byte_5                      = "  BYTE 5  ",
  byte_6                      = "  BYTE 6  ",
  byte_7                      = "  BYTE 7  ",
  parcel                      = "  PARCEL  ",
}
adviser.room_forbidden_non_reachable_parts = "Colocar o espa�o neste s�tio bloquearia o acesso a zonas do hospital."

dynamic_info.patient.actions.no_gp_available = "� espera que seja construidos um consult�rio de CG."
dynamic_info.staff.actions.heading_for = "Indo para %s"

fax = {
  welcome = {
    beta1 = {
      "Bem-vinda(o) ao CorsixTH, um clone opensource do cl�ssico Theme Hospital da Bullfrog!",
      "Esta � a vers�o jog�vel beta 1 do CorsixTH. Muitos espa�os, doen�as e outras funcionalidades foram implementadas, mas ainda falta muito para terminar.",
      "Se gostas deste projecto, podes ajudar-nos no desenvolvimento, relatando bugs por exemplo, ou contribuindo com c�digo.",
      "Mas por agora, diverte-te! Para os que n�o conhecem o Theme Hospital: come�a por construir uma recep��o (a partir do menu dos Objectos) e um consult�rio de CG (zonas de Diagn�stico). Zonas de Tratamento tamb�m v�o ser necess�rias.",
      "-- A equipa do CorsixTH, th.corsix.org",
      "PS: Consegues encontrar os Easter Eggs :-) ?",
    },
    beta2 = {
      "Bem-vinda(o) � beta 2 do CorsixTH, um clone opensource do cl�ssico Theme Hospital da Bullfrog!s",
      "Muitas funcionalidades foram adicionadas desde a �ltima vers�o. D� uma espreitadela ao changelog para uma lista incompleta.",
      "Mas primeiro que tudo, jogar! Ao que parece, tens uma mensagem � tua espera. Fecha esta janela e clica no ponto de interroga��o, pr�ximo do painel do fundo.",
      "-- A equipa do CorsixTH, th.corsix.org",
    },
  },
  tutorial = {
    "Bem-vinda(o) ao teu primeiro Hospital!",
    "Gostavas de aprender mais?",
    "Sim, mostra-me como �.",
    "N�o, j� sei tudo de tr�s para a frente.",
  },
}

misc.not_yet_implemented = "(not yet implemented)"
misc.no_heliport = "Hm... Ou n�o foram desocbertas novas doen�as ou n�o existe um heliporto neste mapa."

main_menu = {
  new_game = "Novo jogo",
  custom_level = "N�vel Personalizado",
  load_game = "Carregar Jogo",
  options = "Op��es",
  exit = "Sair",
}

tooltip.main_menu = {
  new_game = "Come�ar um jogo de ra�z",
  custom_level = "Construir o meu hospital",
  load_game = "Carregar um jogo",
  options = "Ajustar prefer�ncias",
  exit = "N�o, por favor, n�o saias!",
}

load_game_window = {
  back = "Voltar",
}

tooltip.load_game_window = {
  load_game_number = "Carregar o jogo %d",
  load_autosave = "Carregar o jogo gravado automaticamente",
  back = "Fechar a janela de carregamento",
}

errors = {
  dialog_missing_graphics = "Desculpa, mas a vers�o de demonstra��o n�o tem este di�logo!",
  save_prefix = "Erro durante a grava��o do jogo: ",
  load_prefix = "Erro durante o carregamento do jogos: ",
}

totd_window = {
  tips = {
    "Todos os hospitais precisam de uma recep��o e de um consult�rio de CG para come�ar. Depois disso, depende do tipo de pacientes que recebes. Uma farm�cia � sempre uma boa escolha, no entanto.",
    "M�quinas como a Bomba de Encher Cabe�as precisam de manuten��o. Contrata um ou dois funcion�rios para reparar as tuas m�quinas, ou arriscas-te a que o pessoal ou os pacientes se aleijem quando elas avariarem.",
    "Ap�s algum tempo, o teu pessoal vai ficar cansado. Constr�i um Quarto do Pessoal, para que eles possam relaxar.",
    "Coloca radiadores em quantidade suficiente para que o teu pessoal e pacientes estejam quentinhos... caso contr�rio ir�o ficar aborrecidos!",
    "O n�vel de per�cia de um m�dico influencia a qualidade e velocidade do seu diagn�stico. Coloca um m�dico com per�cia nas salas de CGs, e n�o precisar�s de tantas salas de diagn�stico.",
    "M�dicos j�niores e regulares podem aumentar a sua per�cia se aprenderem com um consultante numa Sala de Treino. Se o consultante for especialista (cirurgi�o, psiquiatra ou investigador), tamb�m ensinar� a sua especializa��o aos seus pupilos.s",
    "J� tentaste escrever o n�mero de emerg�ncia (112) no fax? N�o te esque�as de ligar as colunas!",
    "O menu de op��es ainda n�o est� implementado, mas podes ajustar algumas prefer�ncias tais como resolu��o e lingua no ficheiro config.txt na pasta do jogo.",
    "Seleccionaste outra linguagem al�m do Ingl�s, mas v�s Ingl�s em todo o lado? Ajuda-nos a traduzir esse texto!",
    "A equipa do CorsixTH est� � procura de refor�os! Est�s interessado em programar, traduzir ou criar arte gr�fica para o CorsixTH? Contacta-nos no f�rum, IRC (corsix-th no freenode) ou via Mailing List.",
    "Se encontrares um bug, diz-nos em: th-issues.corsix.org",
    "O CorsixTH foi tornado p�blico a 24 de Julho de 2009. A primeira beta jog�vel (beta 1) foi lan�ada a 24 de Dezembro de 2009. Ap�s tr�s meses, temos o orgulho de apresentar a beta 2 (24 de Mar�o de 2010)!",
  },
  previous = "Dica anterior",
  next = "Pr�xima dica",
}

tooltip.totd_window = {
  previous = "Mostrar dica anterior",
  next = "Mostrar a pr�xima dica",
}
