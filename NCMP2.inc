;********************************************************************
;в файле NCMP2.inc
;1	N!bCMPabJm	GA,GB,Pr,СБОЙ				переходы для байтовых размеров
;2	СучетомОтношенийbПерейти				синтаксическая форма ~ 1
;3	C!MPABop								переходы для любых размеров =<32 рр
;4	СучетомОтношений_A?B_Перейти			синтаксическая форма	3
;5	xA?xBJmp								переходы  для AX  и  BX
;6	eA?eBJmp								переходы  для 32 разрядных
;
;в файле \NCMP2\NCMPabPr.inc
;7	N!bCMPabPr	GA,GB,Pr,СБОЙ			
;8	СравнитьA_B_b_Дать_признак				синтаксическая форма ~ 7
;9	N!bCMPabPrJm							признак и переход
;10	СучетомОтношенийb_ДатьПризнак_Перейти	синтаксическая форма ~ 9
;11	N!bCMPabPRiJm							признакИ и переход
;12	СучетомОтношенийb_ДатьПризнаки_Перейти	синтаксическая форма ~ 11
;********************************************************************
;C!MPABop  RGA,RGB,Pr0,Pr1,Pr2,MISTEK		(Определение размерности операндов)	
;eA?eBJmp  EGA,EGB,Pr0,Pr1,Pr2,MISTEK		для 32 разрядных
;xA?xBJmp  GA,GB,Pr0,Pr1,Pr2,MISTEK			для 16 разрядных		
;N!bCMPabJm	GA,GB,Pr0,Pr1,Pr2,MISTEK		для 8 разрядных
;************************************
;if A=B then Pr0 v if A>B then Pr1  v if A<B then Pr2;  if Pri(i=0,1,2) then go MEXI
;2.C!MPabJm	al,bl,Pr0,Pr1, 	if A<B then MEXI
;3.C!MPabJm	al,bl,Pr0,,Pr2	if A>B then MEXI
;4.C!MPabJm	al,bl,,,Pr2		if A=B then MEXI  v	if A<B then MEXI
;5.C!MPabJm	al,bl,Pr0,,		if A=B then Pr0  v	if A<B v A<B then MEXI     равно не равно 0



;*****************Описатель интерфейса NCMP2.inc
;*****************Оператор установления отношения и перехода, 
;*					в зависимости от установленного класса отношений (для 8 разрядных)
;*	Версия:
;*	Описатель интерфейса:  
;*		N!bCMPabJm	al,bl,Pr0,Pr1,Pr2,MISTEK
;*			Где al, bl - сравниваемые операнды,
;*				Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений,
;*				MISTEK - адрес передачи управления, в случае ошибки
;*
;***************************************************************
MACRO	N!bCMPabJm  GA,GB,T1,T2,T3,SBOY	
{	
		 dispDescr	'Оператор установления отношения и перехода, в зависимости от установленного класса отношений (для 8 разрядных)',\
				'Версия','Описатель интерфейса',\
				'N!bCMPabJm	al,bl,Pr0,Pr1,Pr2,MISTEK',\
				'	Где al, bl - сравниваемые операнды',\
				'	Где al, bl - сравниваемые операнды',\
				'	Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений',\
				'	MISTEK - адрес передачи управления, в случае ошибки'
					
	LOCAL	MEXI,JmJ,JgJ,JeJ
		УпряталиРегистры	EAX,EBX
			mov	BL,GB			
			mov	AL,GA				
		and	AL,0FFh
	jne	@F
		and	BL,0FFh
	jne	JmJ							
	jmp	JeJ							
@@:			
		and	BL,0FFh
	je	JgJ	

		mov	BH,AL  					
		mov	AH,AL			
		xor	AH,BL					
	je	JeJ							
		and	BL,AH					
	jne	@F							
	jmp	JgJ 						
@@:
		and	BH,AH					
	je	JmJ							

		mov	AX,08080h				
		and	AX,BX					
	jne	@F							
		mov	AX,04040h				
		and	AX,BX					
	jne	@F
		mov	AX,02020h				
		and	AX,BX					
	jne	@F
		mov	AX,01010h				
		and	AX,BX					
	jne	@F	
		mov	AX,0808h				
		and	AX,BX					
	jne	@F
		mov	AX,0404h				
		and	AX,BX					
	jne	@F
		mov	AX,0202h				
		and	AX,BX					
	jne	@F
	jmp	SBOY						
@@:									
		and	AL,0FFh					
	jne	JmJ							

JgJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~T2 eq
	JMP	T2								
			else
	JMP	MEXI
			end if
JeJ:	
	ВосстановилиРегистры	EAX,EBX
			if   ~T1 eq
	JMP	T1								
			else
	JMP	MEXI
			end if						
JmJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~T3 eq
	JMP	T3								
			else
			end if					
MEXI:								
}
;****************Конец оператора



;*****************Оператор установления отношения и перехода, 
;*					в зависимости от установленного класса отношений (для 8 разрядных, синтаксическая форма)
;*	Версия:
;*	Описатель интерфейса:  
;*		СучетомОтношенийbПерейти\
;*			A=?B\
;*			==Pr0 =>Pr1  =< Pr2\
;*			ПриСбое=>M!ISTEK
;*			Где A, B - сравниваемые операнды,
;*				Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений,
;*				MISTEK - адрес передачи управления, в случае ошибки
;*
;***************************************************************
	MACRO	СучетомОтношенийbПерейти	arg
{
		 dispDescr	'Оператор установления отношения и перехода, в зависимости от установленного класса отношений (для 8 разрядных, синтаксическая форма)',\
				'Версия','Описатель интерфейса',\
				'СучетомОтношенийbПерейти',\
				'	A=?B',\
				'	==Pr0 =>Pr1  =< Pr2',\
				'	ПриСбое=>M!ISTEK',\
				'	Где A, B - сравниваемые операнды',\
				'	Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений',\
				'	MISTEK - адрес передачи управления, в случае ошибки'
				
common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =< Pr2 ==>Er,arg
		\{\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =<  ==Er,arg
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<  ==Er,arg
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<Pr2  ==Er,arg	
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<Pr2  ==Er,arg	
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<  ==Er,arg
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<Pr2  ==Er,arg
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<  ==Er,arg	
		\{
			\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
}
;****************Конец оператора



;*****************Оператор определения размерности операндов al - AX - EAX в пределах 32 рр (EAX)
;*	Версия:
;*	Описатель интерфейса:  
;*		C!MPABop  EAX,EBX,Pr0,Pr1,Pr2,MISTEK
;*		C!MPABopDescription   AX,BX,Pr0,Pr1,Pr2,MISTEK
;*		C!MPABopDescription   al,bl,Pr0,Pr1,Pr2,MISTEK
;*			Где EAX,EBX или AX,BX или al,bl - имена регистров (с 8 рр до 32 рр)
;*				со значениями переменных у которых требуется определить размерность
;*				и произвести сравнение с последующей классификацией.
;*				Pr0, Pr1, Pr2 - адреса для перехода, в зависимости от определенного класса
;*				MISTEK - адрес для перехода в случае ошибки.
;*
;***************************************************************
	MACRO	C!MPABop  RGA,RGB,Pr0,Pr1,Pr2,MISTEK	
{
			 dispDescr	'Оператор определения размерности операндов al - AX - EAX в пределах 32 рр (EAX)',\
				'Версия','Описатель интерфейса',\
				'C!MPABop  EAX,EBX,Pr0,Pr1,Pr2,MISTEK',\
				'C!MPABopDescription   AX,BX,Pr0,Pr1,Pr2,MISTEK',\
				'C!MPABopDescription   al,bl,Pr0,Pr1,Pr2,MISTEK',\
				'	Где EAX,EBX или AX,BX или al,bl - имена регистров (с 8 рр до 32 рр)',\
				'	со значениями переменных у которых требуется определить размерность',\
				'	и произвести сравнение с последующей классификацией.',\
				'	Pr0, Pr1, Pr2 - адреса для перехода, в зависимости от определенного класса',\
				'	MISTEK - адрес для перехода в случае ошибки'

	if  RGA   in  <al,ah,bl,bh,cl,ch,dl,dh>
		N!bCMPabJm RGA,RGB,Pr0,Pr1,Pr2,MISTEK
	else
		 if  RGB   in  <al,ah,bl,bh,cl,ch,dl,dh>
			N!bCMPabJm RGA,RGB,Pr0,Pr1,Pr2,MISTEK
		else
		end if
	end if


 	if  RGA   in  <AX,BX,CX,DX,BP,SI,DI>
		xA?xBJmp  RGA,RGB,Pr0,Pr1,Pr2,MISTEK
	else	
		 if  RGB   in  <AX,BX,CX,DX,BP,SI,DI>
			xA?xBJmp RGA,RGB,Pr0,Pr1,Pr2,MISTEK
		else
			
		end if
	end if


	if  RGA   in  <EAX,EBX,ECX,EDX,EBP,ESI,EDI>
		eA?eBJmp  RGA,RGB,Pr0,Pr1,Pr2,MISTEK
	else	
		if  RGB   in  <EAX,EBX,ECX,EDX,EBP,ESI,EDI>
			eA?eBJmp RGA,RGB,Pr0,Pr1,Pr2,MISTEK
		else
			
		end if
	end if
}
;****************Конец оператора



;*****************Оператор определения размерности операндов 
;*						al - AX - EAX в пределах 32 рр (EAX) (синтаксическая форма)
;*	Версия:
;*	Описатель интерфейса:  
;*				 СучетомОтношений_A?B_Перейти\
;*					al ? bl\
;*						= P6 >P7 <P8\	
;*							=>MEXIT
;*			Где EAX,EBX или AX,BX или al,bl - имена регистров (с 8 рр до 32 рр)
;*			со значениями переменных у которых требуется определить размерность
;*			и произвести сравнение с последующей классификацией.
;*			P6, P7, P8 - адреса для перехода, в зависимости от определенного класса
;*			MEXIT - адрес для перехода в случае ошибки.
;*
;***************************************************************
MACRO	СучетомОтношений_A?B_Перейти	arg
{
			 dispDescr	'Оператор определения размерности операндов al - AX - EAX в пределах 32 рр (EAX) (синтаксическая форма)',\
				'Версия','Описатель интерфейса',\
				'СучетомОтношений_A?B_Перейти',\
				'	al ? b',\
				'	= P6 >P7 <P8',\
				'	=>MEXIT',\
				'		Где EAX,EBX или AX,BX или al,bl - имена регистров (с 8 рр до 32 рр)',\
				'		со значениями переменных у которых требуется определить размерность',\
				'		и произвести сравнение с последующей классификацией.',\
				'		P6, P7, P8 - адреса для перехода, в зависимости от определенного класса',\
				'		MEXIT - адрес для перехода в случае ошибки.'

common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =< Pr2 ==>Er,arg
		\{			\C!MPABop  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er	
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =<  ==Er,arg		
		\{			\C!MPABop  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<  ==Er,arg		
		\{			\C!MPABop  \OP1,\OP2,\Pr0,,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<Pr2  ==Er,arg		
		\{			\C!MPABop  \OP1,\OP2,\Pr0,,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<Pr2  ==Er,arg		
		\{			\C!MPABop  \OP1,\OP2,,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<  ==Er,arg		
		\{														
			\C!MPABop  \OP1,\OP2,,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<Pr2  ==Er,arg		
		\{			\C!MPABop  \OP1,\OP2,,,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<  ==Er,arg		
		\{		\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
}
;****************Конец оператора



;*****************Оператор установления отношения и перехода, 
;*					в зависимости от установленного класса отношений (для 16 разрядных)
;*	Версия:
;*	Описатель интерфейса:  
;*		xA?xBJmp_Description	AX,BX,Pr0,Pr1,Pr2,MISTEK
;*			Где AX, BX - сравниваемые операнды,
;*				Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений,
;*				MISTEK - адрес передачи управления, в случае ошибки
;*
;***************************************************************
	MACRO	xA?xBJmp  GA,GB,Pr0,Pr1,Pr2,MISTEK	;=, >, <
{	
			 dispDescr	'Оператор установления отношения и перехода, в зависимости от установленного класса отношений (для 16 разрядных)',\
				'Версия','Описатель интерфейса',\
				'xA?xBJmp_Description	AX,BX,Pr0,Pr1,Pr2,MISTEK',\
				'	Где AX, BX - сравниваемые операнды',\
				'		Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений',\
				'		MISTEK - адрес передачи управления, в случае ошибки'

	LOCAL	MEXI,JmJ,JgJ,NBloc0
	if  GA  in  <AX,BX>
	else
	УпряталиРегистры	EAX,EBX
		mov AX,GA						
		mov BX,GB						
	end if	
	
		ror	AX,8			
		ror	BX,8
		and	al,0FFh
	jne	@F
		and	bl,0FFh
	jne	JmJ								
	jmp	NBloc0							
@@:			
		and	bl,0FFh
	je	JgJ								
		push	CX
		mov	cl,al
		xor	cl,bl						
		pop		cx
	je	NBloc0	
	
CMPab:
  N!bCMPabJm  al,bl,Pr0,Pr1,Pr2,MISTEK	
NBloc0:
		ror	AX,8						
		ror	EBX,8
	jmp	CMPab


JgJ:
			if  GA  in  <AX,BX>
			else
	ВосстановилиРегистры	EAX,EBX
			end if
			if   ~Pr1 eq
	JMP	Pr1								
			else
	JMP	MEXI
			end if
JmJ:
			if  GA  in  <AX,BX>
			else
	ВосстановилиРегистры	EAX,EBX
			end if
			if   ~Pr2 eq
	JMP	Pr2								
			else
			end if						
MEXI:									
}
;****************Конец оператора



;*****************Оператор установления отношения и перехода, 
;*					в зависимости от установленного класса отношений (для 32 разрядных)
;*	Версия:
;*	Описатель интерфейса:  
;*		eA?eBJmp_Description	EAX,EBX,Pr0,Pr1,Pr2,MISTEK
;*			Где EAX, EBX - сравниваемые операнды,
;*				Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений,
;*				MISTEK - адрес передачи управления, в случае ошибки
;*
;***************************************************************
	MACRO	eA?eBJmp  EGA,EGB,Pr0,Pr1,Pr2,MISTEK	
{
		dispDescr	'Оператор установления отношения и перехода, в зависимости от установленного класса отношений (для 32 разрядных)',\
		'Версия','Описатель интерфейса',\
		'eA?eBJmp_Description	EAX,EBX,Pr0,Pr1,Pr2,MISTEK',\
		'	Где EAX, EBX - сравниваемые операнды',\
		'		Pr0, Pr1, Pr2 - адреса передачи управления, взависимости от установленного класса отношений',\
		'		MISTEK - адрес передачи управления, в случае ошибки'
	LOCAL	MEXI,JmJ,JgJ,JeJ,NBloc2,CMPab
	if  EGA  in  <EAX,EBX>
	else
		УпряталиРегистры	EAX,EBX
			mov	EBX,EGB				
			mov	EAX,EGA				
	end if
	ror	EAX,24
	ror	EBX,24
		and	AX,0FFFFh
	jne	@F
		and	BX,0FFFFh
	jne	JmJ			
	jmp	NBloc2			
@@:			
		and	BX,0FFFFh
	je	JgJ			
		push	ecx
		mov		CX,AX
		xor		CX,BX
		pop		ECX
	je	NBloc2					
CMPab:
  xA?xBJmp  AX,BX,Pr0,Pr1,Pr2,MISTEK	
NBloc2: 
		ror	EAX,24
		ror	EBX,24
	jmp	CMPab
	
JgJ:
			if  EGA  in  <EAX,EBX>
			else
	ВосстановилиРегистры	EAX,EBX
			end if
			if   ~Pr1 eq
	JMP	Pr1								
			else
	JMP	MEXI
			end if
JmJ:
			if  EGA  in  <EAX,EBX>
			else
	ВосстановилиРегистры	EAX,EBX
			end if
			if   ~Pr2 eq
	JMP	Pr2						
			else
			end if
MEXI:
}
;****************Конец оператора