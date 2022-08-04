;1.	dbr			8		-формирование русского текста в нужной кодировке для печати
;2 	Print!afall
;3 	Print!Rfall			Печать в русской кодировке
;4	spibefor	183
;5	spiafter	193
;6	spiszero	202
;7	spisoutone	212
;8	spinumb		228
;9	MINC		240
;10	MDEC		260
;11	!			294
;12	PrList		329
;13	PrLista		340
;14	!_			352
;15	!_v			364
;16	!_n			378
;17	!_Pr		390
;18	!_Pro		410
;19	?_V			430
;20	?_N			437
;21	?_N			438
;22	?_Vd		444
;23	!_!			472					добавление(включение) библиотеки
;24	НАЧАЛО_Программы	500
;*********1***********
macro dbr arg
{ 
 ;local offset,char,offsetw		;,Z_MET
   offset = $-$$
   offsetw = offset						;$-$$
   db arg
   FLEG=0
if arg eqtype ''
offs=offset										;для подсчета окончания записи основных символов
nsimv=0
    repeat ($-offset-$$)
     load char byte from $$+offset+(%-1)
      if char > 07Fh					;>127
	    if ~char=0D1h												;FLEG=2
		  if ~char=0D0h												;FLEG=1
									if FLEG=1						;Был 0D0		  
				if char > 090h				;090h=192   A  русские символы
					if char < 0C0h			;от 090 до 0С0  русские А,Б,...,н,о,п		
					char =char-10h
							;display char
							;display '\'
					store byte char at $$+offsetw+(%-1)
					offs=offs+1
									FLEG=0
					else
					Print!afall 'Ошибка '
					display char
					;store byte char at $$+offsetw+(%-1)
									FLEG=0
					end if
				else						;07Fh <char< 090h
					store byte char at $$+offsetw+(%-1)
					offs=offs+1
									FLEG=0
				end if
									else
;************************************************* char=0D0h**************
									if FLEG=2
				if char > 07Fh			
					if char < 090h							;128 русские  p,с,т..,я  +060h
								char =char+60h
								;display char
								store byte char at $$+offsetw+(%-1)
								offs=offs+1
									FLEG=0
					else
								Print!afall 'Ошибка '
								display char
								store byte char at $$+offsetw+(%-1)
								offs=offs+1
								FLEG=0
					end if
				else										;< = 07Fh
								Print!afall 'Ошибка '
								display char
						store byte char at $$+offsetw+(%-1)
						offs=offs+1
				end if
									else					; ~FLEG=1     ~FLEG=2
									store byte char at $$+offsetw+(%-1)
									offs=offs+1
									end if					;FLEG=2
									end if					;FLEG=1
		  else
			offsetw=offsetw-1								;char=0D0h
			FLEG=1
			nsimv=nsimv+1
		  end if
	    else												;char=0D1h
	    offsetw=offsetw-1
		nsimv=nsimv+1
	    FLEG=2
	    end if
      else													;char<07Fh
	  ;display char
	  ;display 0Dh,0ah
		store byte char at $$+offsetw+(%-1)
		offs=offs+1
		FLEG=0
	  end if  
    end repeat
		repeat nsimv
		load char byte from $$+offs+(%-1)
		char =020h   
		store byte	char at $$+offs+(%-1)
		end repeat
end if
 }
;***********************
; Windows 1251 ==> OEM 866
struc dbr arg
{ 
 ;local offset,char,offsetw		;,Z_MET
   offset = $-$$
   offsetw = offset						;$-$$
   db arg
   FLEG=0
if arg eqtype ''
offs=offset										;для подсчета окончания записи основных символов
nsimv=0
    repeat ($-offset-$$)
     load char byte from $$+offset+(%-1)
      if char > 07Fh					;>127
	    if ~char=0D1h												;FLEG=2
		  if ~char=0D0h												;FLEG=1
									if FLEG=1						;Был 0D0		  
				if char > 090h				;090h=192   A  русские символы
					if char < 0C0h			;от 090 до 0С0  русские А,Б,...,н,о,п		
					char =char-10h
							;display char
							;display '\'
					store byte char at $$+offsetw+(%-1)
					offs=offs+1
									FLEG=0
					else
					Print!afall 'Ошибка '
					display char
					;store byte char at $$+offsetw+(%-1)
									FLEG=0
					end if
				else						;07Fh <char< 090h
					store byte char at $$+offsetw+(%-1)
					offs=offs+1
									FLEG=0
				end if
									else
;************************************************* char=0D0h**************
									if FLEG=2
				if char > 07Fh			
					if char < 090h							;128 русские  p,с,т..,я  +060h
								char =char+60h
								;display char
								store byte char at $$+offsetw+(%-1)
								offs=offs+1
									FLEG=0
					else
								Print!afall 'Ошибка '
								display char
								store byte char at $$+offsetw+(%-1)
								offs=offs+1
								FLEG=0
					end if
				else										;< = 07Fh
								Print!afall 'Ошибка '
								display char
						store byte char at $$+offsetw+(%-1)
						offs=offs+1
				end if
									else					; ~FLEG=1     ~FLEG=2
									store byte char at $$+offsetw+(%-1)
									offs=offs+1
									end if					;FLEG=2
									end if					;FLEG=1
		  else
			offsetw=offsetw-1								;char=0D0h
			FLEG=1
			nsimv=nsimv+1
		  end if
	    else												;char=0D1h
	    offsetw=offsetw-1
		nsimv=nsimv+1
	    FLEG=2
	    end if
      else													;char<07Fh
	  ;display char
	  ;display 0Dh,0ah
		store byte char at $$+offsetw+(%-1)
		offs=offs+1
		FLEG=0
	  end if  
    end repeat
		repeat nsimv
		load char byte from $$+offs+(%-1)
		char =020h   
		store byte	char at $$+offs+(%-1)
		end repeat
end if
 }
;***************************************	 
struc du [args]
 { common label . word
  du args }
;***************************************
;*********2************	Print!afall	expr
	macro Print!afall nlist1
{	common match nlist,nlist1
	\{	common  irps token,nlist
	\\{
	common	display	\\`token
	\\}
	\}
}
;
;1**********3***********	Print!afall	expr
	macro Print!Rfall [arg]
{	;local o$set,char,							;Z_ME1
virtual at 0
    o$set = $-$$
	FLEG=0											;label Z_ME1  
   db arg    
if arg eqtype ''
    repeat ($-o$set-$$)
     load char byte from $$+o$set+(%-1)
	IF	char=020h
	display	 char
	FLEG=0
	else
      if char > 07Fh							;>127
	    if ~char=0D1h							;FLEG=2
		  if ~char=0D0h							;FLEG=1
									if FLEG=1	;Был 0D0		  
				if char > 08Fh					;192   A
					if char < 0C0h
					char =char-10h
					display	 char
									FLEG=0
					else
					end if
				else
				end if
									else
;***************************************************************
									if FLEG=2
				if char > 07Fh					;128   p    +030h
					if char < 090h
								char =char+60h
								display	 char
									FLEG=0
					else
					end if
				else
				end if
									else
									end if
;*********************************************											
									end if
		  else
			FLEG=1								;~char=0D0h
		  end if
	    else
	    FLEG=2									;~char=0D1h
	    end if
      else
					if FLEG=0
					display	 char
					else
					end if				;char < 7Fh	
	  end if
	end if 										;020h 
    end repeat
end if
	end virtual
}
;******************************************************
;2 spibefor ********4************ Дополнение списка спереди  item + List
  macro spibefor	item,list
     {
	match ane,item				
\{
       match any,list \\{ list equ item,list \\}
       match ,list \\{ list equ item \\}			;при пустом списке
\}
     }
;3 spiafter *********5***********Дополнение списка сзади  List+item
  macro spiafter	list,item
     {
	match ane,item				
\{
       match any,list \\{ list equ list,item \\}
       match ,list \\{ list equ item \\}			;Первый в списке
\}
     }
;4	spiszero ***********6*********Заверщение списка 0
	macro	spiszero vlis
{
		match ,vlis 
	\{			Print!afall vlis
				display "  Список пустой",0Dh,0ah
	\}			
	match any,list \{ vlis equ vlis,0 \}
}
;**********************7*********	
;5 spisoutone **********Из listua по разделителю =, изымается 1 в tema элемент в list остаток
macro spisoutone	tema,list,listua
     {common	match an1 =,an2,listua
				\{
				tema	equ	\an1
				list 	equ	\an2
				\}
				;match an1,listua 			\{ listua equ 0,an1 \}
				;match =0,listua 			\{ Print!afall listua\}
				;assert listua, 'File is too small.'
												;Print!Rfall " СПИСОК ИСЧЕРПАН"
												;display 0Dh,0ah			
     }
;*********************8*********	 
;6 spinumb **spinumb tema,list,listua **Из listua добав.в список list с фиксацией номера впереди
	macro spinumb	tema,list,listua
{		common	match an1 =,an2,listua
				\{
				MINC Nom,\an1
				list equ	Nom,\an2,tema
				\}
				match ,list 			\{ list equ 1,tema \}
}
;******************** 9
;7 MINC **   MINC Nom,\an1 ***** Увеличение счетчика _A,вначале, на 1 и фиксация N_A
	macro MINC	N_A,_A
	{
 MINCd	N_A,_A,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,\
 17,17,18,18,19,19,20, 20,21, 21,22, 22,23, 23,24, 24,25, 25,26, 26,27, 27,28, 28,29, 29,30,\
 30,31
	}
;********************* 9
	macro MINCd	N_A,_A,[P1,P2]
{FORWARD
		match =P1,_A
	 \{ define _PPT P2
		N_A equ	_PPT
								;Print!afall _A 
								;display " _A  63",0Dh,0ah 
	 \}
common
							;Print!afall N_A 
							;display " N_A 64",0Dh,0ah
}
;******************** 10
;8 MDEC **  MDEC Nom,\an1 ***** Уменьшение счетчика MDEC Nom,\an1 NOM по содержимомму \an1
	macro MDEC	N_A,_A
	{
 MDECd	N_A,_A,1,0,2,1,3,2,4,3,5,4,6,5,7,6,8,7,9,8,10,9,11,10,12,11,13,12,14,13,15,14,16,15,\
 17,16,18,17,19,18,20,19,21,20, 22,21, 23,22, 24,23, 25,24, 26,25, 27,26, 28,27, 29,28, 30,29,\
 31,30, 32,31, 33,32, 34,33, 35,34, 36,35, 37,36, 38,37, 39,38, 40,39, 41,40, 42,41, 43,42,\
 44,43
	}
;*******
	macro MDECd	N_A,_A,[P1,P2]
{FORWARD
		match =P1,_A
	 \{ define _PPT P2
		N_A equ	_PPT
								;Print!afall _A 
								;display " _A  63",0Dh,0ah 
	 \}
common
							;Print!afall N_A 
							;display " N_A 64",0Dh,0ah
}
;*******************************************
_vlista	equ			;Список включенных
_nlista	equ			;Список включенных
_slista	equ			;Список не требуюших подключения так уже включены через другой	 ОПЕРАТОР
_lista equ			;Весь список ОПЕРАТОРОВ

_listDllOn equ
_listDllOff equ
;***************************************************************
;***************************************************************
;N имя		Способ обращения                                   *
;        имя     Имя макроса  n выкл/вкд  Путь к билиотеке     *
;9  !   * !   УпряталРегистры 4   -/+    'C:\FASM\BIBLMC\Rpushpop.inc' 
;        *** Включение/выключение макроопределения при трансляции программы
;********************* 11 ******************************************

MACRO ! arg
{
common match ar1 ar2 =- ar3,arg
\{
 ;match params,\ar1 \\{ \\params 0 \\}				;маркировка для отключения 
	\spiafter \_lista,\ar1
	\spiafter \_lista,"		-"
	\spiafter	\_nlista,\ar1
	\spiafter \_nlista,\ar3
\}
common match ar1 ar2 =+ ar3,arg
\{
	\spinumb \ar1,\_vlista,\_vlista		;Запись очередного имени  с изменением номера
	\spiafter \_vlista,\ar2				;номер библиотеки
	\spiafter \_lista,\ar1				;В общий список всех опреаторов подключенных и не
	\spiafter \_lista,"		+"
	include \ar3
\}
common match ar1 ar2 =* ar3,arg			;Библиотека подключена через другой оператор
\{
	\spiafter \_lista,\ar1
	\spiafter \_lista,"		*"			;В общий список операторов
	\spiafter \_slista,\ar1				;имя оператора в список под одним номером
	\spiafter \_slista,\ar2				; общий номер библиотеки
	\niki equ	ON
 \}
}

MACRO !O arg
{
common match ar1 ar2 =+ ar3,arg
	\{
		\spinumb \ar1,\_vlista,\_vlista		;Запись очередного имени  с изменением номера
		\spiafter \_vlista,\ar2				;номер библиотеки
		\spiafter \_lista,\ar1				;В общий список всех опреаторов подключенных и не
		\spiafter \_lista,"		+"
		include \ar3 
	\}
common match ar1 ar2 =* ar3,arg			;Библиотека подключена через другой оператор
	\{
		\spiafter \_lista,\ar1
		\spiafter \_lista,"		*"			;В общий список операторов
		\spiafter \_slista,\ar1				;имя оператора в список под одним номером
		\spiafter \_slista,\ar2				; общий номер библиотеки
		\niki equ	ON
	\}	
}

;********************   Из listua по разделителю -, изымается 1 элемент в tema в list остпток
;10 PrList  ********  12  ***   Печать по одному списка в arge
MACRO PrList [arge]
{
FORWARD
Print!afall	arge

display 0Dh,0ah
}
;*****
;11 PrLista *********  13 ***Печать 2-х из списка в arge YN***************
MACRO PrLista [arge,YN]
{
FORWARD
Print!Rfall	""#`arge
display	"      "
Print!afall	YN 
display 0Dh,0ah
}
;*****
;*********************** 14  *******************************************
;12 !_	Печать Полная_библиотека_Операторов с включенной, выключенной библиотеки 
	MACRO		!_
{
	display	"+*-*+-+*-*+-+*+-+*-*+-+*-*+-+*-*+-+*-+*-*+-+*-*+-+*-"
	display 0Dh,0ah
!_Pr	"     Полная библиотека Операторов" _lista
	display	"+*-*+-+*-*+-+*+-+*-*+-+*-*+-+*-*+-+*-+*-*+-+*-*+-+*-"
	display 0Dh,0ah
}
;************************** 15 ************************************************
;13 !_v  ***********Включенные операторы
	MACRO		!_v
{
tema	equ
	spisoutone	tema,_list,_vlista
	display	"+++++++++++++++++++++++++++++++++++++++++++"
	display 0Dh,0ah
	!_Pr	"        Включенные операторы"  _list
	display	"..................................."
	display 0Dh,0ah
	!_Pr	"        Уже включенные операторы" _slista
	display	"+++++++++++++++++++++++++++++++++++++++++++"
	display 0Dh,0ah	
}
;14!_n  **********		16	**Выключенные операторы
	MACRO		!_n
{
	display	"-----------------------------------------------"
	display 0Dh,0ah
	!_Pro	"          Выключенные операторы" _nlista
	display	"-----------------------------------------------"
	display 0Dh,0ah
}
;***********************    17 **по двум параметрам******************
;							Заголовок					Список полной библиотеки
;15  !_Pr   *****!_Pr	<Полная_библиотека_Операторов> _lista ****************
	MACRO	!_Pr	arg						;служебная для печати библиотека
{
	common match  ogl Nspis,arg
	\{							Print!Rfall \ogl
								display 0Dh,0ah
	display	"     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	display 0Dh,0ah
	common match  params,\Nspis
	\\{
						\\PrLista \\params  ;к двум параметрам
								\\}
	;display	"***********************************"
	;display 0Dh,0ah
	\}
}
;********************по одному параметру******************
;16 !_Pro *****			18 ****************************
; Печать библиотеки включенной + , выключенной библиотеки
	MACRO	!_Pro		arg
{
	common match  ogl Nspis,arg
	\{							Print!Rfall \ogl
								display 0Dh,0ah
	display	"     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	display 0Dh,0ah
	common match  params,\Nspis
	\\{
						\\PrLista \\params		;ОБРАЩЕНИЕ К ОДНОМУ ПАРАМЕТРУ 
	\\}
	display	"..................................."
	display 0Dh,0ah
	\}
}
;*************************** 19 **************
;17 ?_V*****   ?_V		УпряталиРегистры  *******
; Проверка Включен ли оператор arg в списке Операторов  Name
;
	MACRO	?_V			arg
{
	match _vlis,_vlista	\{?_Vd	arg,\_vlis	\}
}
;*************************** 20 **************
;18 ?_N ************?_N УпряталиРегистры************
; Проверка Отключен ли оператор
MACRO	?_N			arg
{
	match _vlis,_nlista	\{?_Nd	arg,\_vlis	\}
}
;*************************** 21 **************
;19 ?_Vd ***довавление ?_V *********************
	MACRO	?_Vd		arg,[_vlis]
	{common
									;Print!afall arg 
									;display " arg",0Dh,0ah 
FORWARD
									;Print!afall _vlis 
									;display " _vlis",0Dh,0ah 
		match =arg,_vlis
	 \{ 						Print!afall arg 
								display " включен",0Dh,0ah 
	 \}
	}
;***********	
;*************************** 22 **************
;20 ?_Nd ********довавление ?_N***********
	MACRO	?_Nd		arg,[_vlis]
	{common
FORWARD
		match =arg,_vlis
	 \{ 						Print!afall arg 
								display " выключен",0Dh,0ah 
	 \}
	}
;*************************** 23 **************
;21 !_! ***************включение библиотеки соотвествующего макроса*********
;*************  !_! УпряталиРегистры   ****************
MACRO	!_!			arg
{
common	match _vlis,_nlista	\{!_!d	arg,\_vlis	\}
}
;*************************** 23 **************
;22 !_!d *******добавление к !_!*****************
	MACRO	!_!d		arg,[_nm,_bib]
	{common
									;Print!afall arg 
									;display " arg",0Dh,0ah 
FORWARD
									;Print!afall _vlis 
									;display " _vlis",0Dh,0ah 
		match =arg,_nm
	 \{ 
				include `_bib#'   ' 
								Print!afall _bib 
								display " включили",0Dh,0ah 
	 \}
	}
;*************************** 24 **************	
	MACRO	dispDescr [strings]
{common
	display 0Dh,0ah
	display 0Dh,0ah 	
	display '*******************************************'
	display 0Dh,0ah
	Print!Rfall 'Описание выбранных операторов'
	display 0Dh,0ah 
	display '*******************************************'
		forward
			display 0Dh,0ah 
			Print!Rfall strings,0Dh,0ah 
	common
	display 0Dh,0ah 
	display '*******************************************'
}	
;*********************************************************
; ВЫЗОВ НЕОБХОДИМЫХ БИБЛИОТЕК МАКРОСОВ
; include 'C:\FASM\BIBLMCN\INCALL_NTERFACE.inc'	;Включение Библиотеки ОПЕРАТОРОВ по имени (ИНТЕРФЕЙС)
include 'C:\FASM\BIBLMCN\INCALL.inc'			;Включение Библиотеки ОПЕРАТОРОВ по имени
include 'C:\FASM\BIBLMCN\SYSALL.inc'			;Включение Библиотеки СИСТЕМНЫХ ОПЕРАТОРОВ по имени
;include 'C:\FASM\INCLUDE\win32a.inc'	;Билиотека системных ОПЕРАТОРОВ
;****************************************************
