include 'C:\FASM\MZERO.inc'
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;ВОССТАНОВЛЕНИЕ По Таблице Брадиса
 НАЧАЛО_Программы Форма=PE,Вывод=Console,Имя_Входа=start
				СЕКЦИЯ_ДАННЫХ Имя=data,Чтение=+,Запись=+
;************************  1 Константы  *****************
include 'C:\FASM\brad.inc'							;РАЗВЕРНУТАЯ ТАБЛИЦА БРАДИСА
include 'C:\FASM\UCABCJmp.inc'							;Сравнение переменных с переходом
include 'C:\FASM\OBIBLMCN\NCMP2.inc'
ISXDN	dbr	"Проверка получения амплитуд"			
		db	0ah,0dh
DLISXDN=Writed-ISXDN
Writed	dd	21										
;************************ 2 Рабочие ячейки **************
Hconsl	dd	0
Sa dd 41
Sb dd 101
N dd 9
water_key dw 255
MFen dd ?

;********************************************************
						СЕКЦИЯ_КОМАНД
;+++++++++++++++++++++++++     	1    ++++++++++++++++++++
;	STD_OUTPUT_HANDLE   ==>	[GetStdHandle]  ==>Hconsl	
;	1.«апрашиваем короткий ключ ( HANDLE)  консоли дл¤ использовани¤ в распечатках

	;invoke	GetStdHandle, STD_OUTPUT_HANDLE
		;mov	[Hconsl],eax				;handle консоли
;------------------------------------------- 1 -----------------------------------
;+++++++++++++++++++++++++     2    ++++++++ѕечать исходна¤ матрица ISXODN MATRIX+++++++++++
		;mov	eax,[Hconsl]		;handle console
		;mov	ECX,30				;ѕ≈„ј“№	
	;invoke	WriteConsole, eax,ISXDN, ecx,Writed, 0
;------------------------------------------- 2 -----------------------------------
;---------------------------- 3 ---------------------
			;stdcall	F@enik,[Sa],[Sb],[N],MFen  ;при отладке
;F@enik Sa, Sb, N, MFen
;+++++++++++++++++++++++++++++++++ќбщее окончание
	;invoke CloseHandle,[Hconsl]
	;invoke	ExitProcess, 2
;************************************************
	;proc	F@enik (EDI=[EBP+20]),(ECX=[EBP+16]),(EBX=[EBP+12]), (EAX=[EBP+8]) ;
	;macro	F@enik posFst, posSec, samples, finalAmp
	;{
		lea edi, [MFen]
		mov ecx, [N]
		inc ecx
		mov ebx, [Sb]
		mov eax, [Sa]
		xor edx, edx
		push ecx
		mov	ebp, ecx
		shr ebp, 1
		pop ecx
		mov ebp, ecx
		push ecx
		mov ecx, ebp
		УпряталиРегистры eax, ebx
		jc step1_odd
		jmp step1_even
		
		
		step1_even:
		shr ecx, 1
		mov ebp, ecx
		push eax
		push edx
		loopa_step1_even:
			mov edx, eax
			mov eax, 5401
			УпряталиРегистры edx
			xor edx, edx
			mul cx
			xor edx, edx
			div bp
			xor edx, edx
			mov bx, 2
			mul bx
			mov ax, [Bradis + eax]
			pop edx
			mul edx
			mov ebx, 10000
			div ebx
			mov ebx, 2
			xor edx, edx
			div ebx
			pop ebx
			pop edx
			УпряталиРегистры ebx, ecx, edx
			mov ecx, eax
			mov eax, edx
			mov ebx, 2
			xor edx, edx
			div ebx
			add eax, ecx
			
			ВосстановилиРегистры edx, ecx, ebx
			mov [edi + edx], eax
			mov eax, ebx
			inc edx
			УпряталиРегистры eax, edx
		loop loopa_step1_even
		ВосстановилиРегистры ebx, eax, ecx
		
		push eax
		shr eax, 1
		mov [edi + edx], ax
		pop eax
		inc edx
		
		jmp step2_even
		
		
		step2_even:
		УпряталиРегистры ecx, ebx, eax
		mov ebp, eax
		mov ebx, ecx
		loopa_step2_even:
			mov eax, ebx
			sub eax, ecx
			push edx
			mov edx, 2
			mul edx
			pop edx
			push edx
			sub edx, eax
			sub edx, 2
			mov al, [edi + edx]
			mov edx, ebp
			sub edx, eax
			mov eax, edx
			pop edx
			mov [edi + edx], eax
			inc edx
		loop loopa_step2_even
		ВосстановилиРегистры ecx, ebx, eax
		jmp step3_even
		
		
		step3_even:
		УпряталиРегистры eax, edx
		mov ebp, ecx
		loopa_step3_even:
			mov eax, 5401
			mul ecx
			div ebp
			mov edx, 2
			mul edx
			mov ax, [Bradis + eax]
			mul ebx
			push ecx
			xor edx, edx
			mov ecx, 2
			div ecx
			mov ecx, 10000
			xor edx, edx
			div ecx
			pop ecx
			
			mov edx, ebx
			shr edx, 1
			sub edx, eax
			mov eax, edx
			
			pop edx
			;sub edx, ebp
			;add edx, ecx
			;add edx, ecx
			;sub edx, 1
			mov [edi + edx], al
			inc edx
			УпряталиРегистры edx
		loop loopa_step3_even
		ВосстановилиРегистры eax, eax
		mov ecx, ebp
		
		push ebx
		shr ebx, 1
		mov [edi + edx], bx
		pop ebx
		inc edx
		
		jmp step4_even
		
		
		step4_even:
		УпряталиРегистры ecx, eax, ebx
		mov ebp, ecx
		loopa_step4_even:
			mov eax, edx
			sub eax, 2
			sub eax, ebp
			sub eax, ebp
			add eax, ecx
			add eax, ecx
			mov eax, [edi + eax]
			push ebx
			sub ebx, eax
			mov [edi + edx], bl
			pop ebx
			inc edx
		loop loopa_step4_even
		ВосстановилиРегистры ecx, eax, ebx
		ВосстановилиРегистры ecx, eax
		jmp water
		
		
		step1_odd:
		ВосстановилиРегистры ecx, eax, ebx
		push ebx
		push ecx
		shr ecx, 1
		add ecx, 1
		mov ebp, ecx
		loopa_step1_odd:
			push edx
			
			push eax
			mov eax, 5401
			mov ebx, ebp
			sub ebx, ecx
			xor edx, edx
			mul ebx
			mov ebx, ebp
			sub ebx, 1
			xor edx, edx
			div ebx
			xor edx, edx
			mov ebx, 2
			mul ebx
			mov ebx, eax
			mov eax, 10802
			sub eax, ebx
			mov ax, [Bradis + eax]
			pop ebx
			push ebx
			xor edx, edx
			mul ebx
			xor edx, edx
			mov ebx, 2
			div ebx
			xor edx, edx
			mov ebx, 10000
			div ebx
			xor edx, edx
			pop ebx
			push ebx
			shr ebx, 1
			add eax, ebx
			
			pop ebx
			pop edx
			mov [edi + edx], ax
			mov eax, ebx
			inc edx
		loop loopa_step1_odd
		ВосстановилиРегистры ebx, ecx
		jmp step2_odd
		
		
		step2_odd:
		УпряталиРегистры eax, ecx, ebx
		mov ecx, ebp
		sub ecx, 1
		loopa_step2_odd:
			mov eax, ebp
			add eax, ebp
			sub eax, edx
			sub eax, 2
			mov ax, [edi + eax]
			mov ebx, [edi]
			sub ebx, eax
			mov eax, ebx
			
			mov [edi + edx], al
			inc edx
		loop loopa_step2_odd
		ВосстановилиРегистры eax, ecx, ebx
		dec edx
		jmp step3_odd
		
		
		step3_odd:
		push eax
		push ecx
		shr ecx, 1
		add ecx, 1
		mov ebp, ecx
		loopa_step3_odd:
			push edx
			
			push ebx
			mov eax, 5401
			mov ebx, ebp
			sub ebx, ecx
			xor edx, edx
			mul ebx
			mov ebx, ebp
			sub ebx, 1
			xor edx, edx
			div ebx
			xor edx, edx
			mov ebx, 2
			mul ebx
			mov ebx, eax
			mov eax, 10802
			sub eax, ebx
			mov ax, [Bradis + eax]
			pop ebx
			push ebx
			xor edx, edx
			mul ebx
			xor edx, edx
			mov ebx, 2
			div ebx
			xor edx, edx
			mov ebx, 10000
			div ebx
			xor edx, edx
			pop ebx
			push ebx
			shr ebx, 1
			add eax, ebx
			
			pop ebx
			push ebx
			sub ebx, 1
			sub ebx, eax
			mov eax, ebx
			
			pop ebx
			pop edx
			mov [edi + edx], ax
			inc edx
		loop loopa_step3_odd
		ВосстановилиРегистры eax, ecx
		jmp step4_odd
		
		
		step4_odd:
		УпряталиРегистры eax, ecx
		mov ecx, ebp
		sub ecx, 1
		loopa_step4_odd:
			push edx
			push ebp
			push ebx
			
			mov ebx, ebp
			dec ebx
			dec ebp
			add ebx, ebp
			add ebx, ebp
			add ebx, ebp
			add ebx, ebp
			add ebx, ebp
			sub ebx, edx
			xor eax, eax
			mov al, [edi + ebx]
			pop ebx
			push ebx
			sub ebx, eax
			mov eax, ebx
			
			pop ebx
			pop ebp
			pop edx
			mov [edi + edx], ax
			inc edx
		loop loopa_step4_odd
		ВосстановилиРегистры eax, ecx
		jmp water
		
		
		water:
		push ecx
		shr ecx, 1
		push edx
		mov edx, 255
		mov [edi + ecx], dl
		pop edx
		pop ecx
		
		push ecx
		push edx
		mov edx, ecx
		shr ecx, 1
		add ecx, edx
		inc ecx
		mov edx, 255
		mov [edi + ecx], dl
		pop edx
		pop ecx
		jmp EXI
		
		
		;water:
		;mov ebp, ecx
		;mov [edi + ebp], 255
		;inc ebp
		;add ebp, ecx
		;mov [edi + ebp], 25
		;jmp EXI
	
	EXI:
		invoke	ExitProcess, 0
;---------------------------- 1,2,3,4 -------------------
;ret
;-	 Процедура 1. F@enik восстановления амплитуд	
;}

;F@enik Sa, Sb, N, MFen
;endp
						СЕГМЕНТ_ИМПОРТА
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				;					           •  S   BEBX=[EBP+12]
				;				            •
				;				        •	------ 0 -------
				;				      •
				;			   SA  •	EAX=[EBP+8]
				;Дано: Sa<Sb
				;Дано: N число отсчетов для полуволны	между A и  B ECX=[EBP+16]
				;DeltaS = Sa - Sb – ? фрагмента соответствующего ?  цикла волны
				;MFen   EDI=[EBP+20] адрес массива куда записываем промежуточные значения
;********************** Процедура 1. F@enik восстановления значения амплитуд до 21600 отсчетов на волну
; Если больше 21600 , то ECX = -1
; Обращение		stdcall	F@enik,[ Sa], [Sb],[N], MFen  при отладке
;			 invoke	F@enik,[ Sa], [Sb],[N], MFen
;  	Sa 1-e значение амплитуды	(EAX=[EBP+8]
;	Sb 2-e значение амплитуды	EBX=[EBP+12]
;	N -  количество отсчетов	ECX=[EBP+16]
;	MFen  -  Адрес массива куда положить значения амплитуд кроме Sa, Sb 	EDI=[EBP+20]
;********************************************
;****SIN***********************************************************************
;FINIT
;mov	 [Rab],EBX
;FILD	[Rab]			;St[0]
;FSIN
;FISTP	[Rab]	;результат
;mov	EDX,[Rab]
;FWAIT
;*************************************  другой способ вычисления  функции   
