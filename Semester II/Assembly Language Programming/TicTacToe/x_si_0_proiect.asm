.386
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc
extern malloc: proc
extern memset: proc
extern printf: proc

includelib canvas.lib
extern BeginDrawing: proc

public start

.data
;;;;;;;;note: atunci cand dai click pe tabla si vezi ca a castigat cineva, mai dai un click din nou pe acelasi patrat
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; pentru ca altfel nu se va afisa castigatorul
include digits.inc
include letters.inc
include X_O.inc

format db "%d" ,13, 10 , 0
window_title DB "X si 0", 0

area DD 0
counter DD 0
matrice DD 9 dup(0)

area_width EQU 500 
area_height EQU 300

X_matrice DD 0
Y_matrice DD 0
X0 DD 100 
Y0 DD 100 
X_O_height EQU 39 

verifica_afara DD 0 
culoare_simb DD 0

verificare_X_O DD 0
numarator DD 9 
constanta_patru DD 4   
constanta_zero EQU 0

arg1 EQU 8
arg2 EQU 12
arg3 EQU 16
arg4 EQU 20

symbol_width EQU 10
symbol_height EQU 20

.code

make_text proc
	push ebp
	mov ebp, esp
	pusha
	
	mov eax, [ebp+arg1]
	cmp eax, 'A'
	jl make_digit
	cmp eax, 'Z'
	jg make_digit
	sub eax, 'A'
	lea esi, letters
	jmp draw_text
make_digit:
	cmp eax, '0'
	jl make_space
	cmp eax, '9'
	jg make_space
	sub eax, '0'
	lea esi, digits
	jmp draw_text
make_space:	
	mov eax, 26 
	lea esi, letters
	
draw_text:
	mov ebx, symbol_width
	mul ebx
	mov ebx, symbol_height
	mul ebx
	add esi, eax
	mov ecx, symbol_height
bucla_simbol_linii:
	mov edi, [ebp+arg2] 
	mov eax, [ebp+arg4] 
	add eax, symbol_height
	sub eax, ecx
	mov ebx, area_width
	mul ebx
	add eax, [ebp+arg3] 
	shl eax, 2 
	add edi, eax
	push ecx
	mov ecx, symbol_width
bucla_simbol_coloane:
	cmp byte ptr [esi], 0
	je simbol_pixel_alb
	mov dword ptr [edi], 0000000h ;culoare scris
	jmp simbol_pixel_next
simbol_pixel_alb:
simbol_pixel_next:
	inc esi
	add edi, 4
	loop bucla_simbol_coloane
	pop ecx
	loop bucla_simbol_linii
	popa
	mov esp, ebp
	pop ebp
	ret
make_text endp

; un macro ca sa apelam mai usor desenarea simbolului
make_text_macro macro symbol, drawArea, x, y
	push y
	push x
	push drawArea
	push symbol
	call make_text
	add esp, 16
endm

afisareXsau0 proc   
	push ebp
	mov ebp,esp
	pusha
punex:
	;desenam pe X in roz
	mov eax, [ebp + arg1]  
	cmp eax, 'X'
	jne pune0;daca s a pus deja x, vom pune 0
	sub eax, 'X'
	lea esi, X_O
	mov culoare_simb, 0FF00FFh 
	jmp deseneaza_X_O
pune0:
;desenam pe O in mov
	mov eax, 1  
	mov culoare_simb, 09932CCh 
	lea esi, X_O
deseneaza_X_O:
	mov ebx, 39
	mul ebx
	mov ebx, 39
	mul ebx
	add esi, eax
	mov ecx, 39
linie_X_O:
	mov edi, [ebp+arg2] 
	mov eax, [ebp+arg4] 
	add eax, 39
	sub eax, ecx
	mov ebx, area_width
	mul ebx
	add eax, [ebp+arg3] 
	shl eax, 2 
	add edi, eax
	push ecx
	mov ecx, X_O_height
coloana_X_O:
	cmp byte ptr [esi], 0
	je simbol_pixel_alb_X_O
	mov edx, culoare_simb
	mov dword ptr [edi], edx
	jmp simbol_pixel_next_X_O
simbol_pixel_alb_X_O:
	mov dword ptr [edi], 0FFFFFFh ;coloreaza 0-urile in alb
simbol_pixel_next_X_O:
	inc esi
	add edi, 4
	loop coloana_X_O
	pop ecx
	loop linie_X_O
	popa
	mov esp, ebp
	pop ebp
	ret
afisarexsau0 endp

make_text_macro_X_O macro symbol, drawArea, x, y
	push y
	push x
	push drawArea
	push symbol
	call afisareXsau0
	add esp, 16
endm

in_tabla proc   
	mov esi, edx
	cmp ebx, 100
	jl fals
	mov eax, 4
	mov ecx, 40
	mul ecx
	add eax, 100
	cmp ebx, eax
	jge fals
	mov edx, esi
	cmp edx, 100
	jl fals
	mov eax, 4
	mov ecx, 40
	mul ecx
	add eax, Y0
	mov edx, esi
	cmp edx, eax
	jge fals
	mov eax, 1
	mov verifica_afara, eax   
	jmp afara
fals:
	mov eax, 0
	mov verifica_afara, eax
afara:
	ret
in_tabla endp

petabla proc
	push ebp
	mov ebp, esp
	push ebx
	push ecx
	mov eax, [ebp+arg1]
	mov ebx, 4
	mul ebx
	mov esi, eax			
	mov eax, [ebp+arg2]
	mul ebx
	mov ebx, eax
	mov eax, 3				
	mul ebx
	mov ebx, eax
	mov eax, matrice[ebx+esi]	
	cmp eax, 0 
	jne iesire_transpunere_in_matrice
	mov ecx, [ebp+arg3] 
	cmp ecx, 0 
	jne este_X
este_0:
	mov eax, 2
	mov matrice[ebx+esi], eax
	mov eax, 0
	jmp aici
este_X:
	mov eax, 1
	mov matrice[ebx+esi], eax
	mov eax, 0
	jmp aici
iesire_transpunere_in_matrice:
	mov edx, 1				
	sub edx, verificare_X_O
	mov verificare_X_O, edx
aici:
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret
petabla endp	

verificare_castigator_linie proc
	push ebp
	mov ecx, 3				
	primul_for:
		mov ebp, ecx
		mov ebx, ecx	
		dec ebx
		mov eax, 4
		mul ebx
		mov ebx, 3
		mul ebx
		mov ebx, eax
		mov ecx, 2
		mov edi, matrice[ebx + 8]
	al_doilea_forlinie:
			mov eax, 4		
			dec ecx
			mul ecx
			inc ecx
			mov esi, eax
			mov edx, matrice[ebx + esi]
			cmp edi, edx
			jne remiza
			loop al_doilea_forlinie
		cmp edi, 0
		je remiza
		cmp edi, 1
		je castiga_X
castiga_O:
		mov eax, 2
		jmp final_verificare
castiga_X:
		mov eax, 1
		jmp final_verificare
remiza:
		mov ecx, ebp
		loop primul_for
		mov eax, 0
final_verificare:
	pop ebp
	ret
verificare_castigator_linie endp

verificare_castigator_coloana proc
	push ebp
	mov ecx, 3					
	primul_for:
		mov ebp, ecx
		mov ebx, ecx
		dec ebx
		mov eax, 4
		mul ebx
		add eax, 24
		mov ecx, 2
		mov edi, matrice[eax]
	al_doilea_for_coloana:
			sub eax, 12
			mov edx, matrice[eax]
			cmp edi, edx
			jne remiza
			loop al_doilea_for_coloana
		cmp edi, 0
		je remiza
		cmp edi, 1
		je castiga_X
castiga_O:
		mov eax, 2
		jmp final_verificare
castiga_X:
		mov eax, 1
		jmp final_verificare
remiza:
		mov ecx, ebp
		loop primul_for
		mov eax, 0
final_verificare:
	pop ebp
	ret
verificare_castigator_coloana endp

verificare_castigator_diagonala1 proc
	mov edi, matrice[0]
	cmp edi, matrice[16]
	jne remiza
	cmp edi, matrice[32]
	jne remiza
		cmp edi, 0
		je remiza
		cmp edi, 1
		je castiga_X
castiga_O:
		mov eax, 2
		jmp final_verificare
castiga_X:
		mov eax, 1
		jmp final_verificare
remiza:
		mov eax, 0
final_verificare:
	ret
verificare_castigator_diagonala1 endp

verificare_castigator_diagonala2 proc
	mov edi, matrice[8]
	cmp edi, matrice[16]
	jne remiza
	cmp edi, matrice[24]
	jne remiza
		cmp edi, 0
		je remiza
		cmp edi, 1
		je castiga_X
castiga_O:
		mov eax, 2
		jmp final_verificare
castiga_X:
		mov eax, 1
		jmp final_verificare
remiza:
		mov eax, 0
final_verificare:
	ret
verificare_castigator_diagonala2 endp

player_vs_player proc
	push ecx
	mov ebx,[ebp+arg2]		
	mov edx,[ebp+arg3]
	push edx
	push ebx
	call in_tabla  
	add esp, 8
	cmp eax, 0
	je final_player
	mov edx, 1				
	;;verificare x sau 0
	sub edx, verificare_X_O
	mov verificare_X_O, edx 
	xor edx, edx
	mov ecx, 40
	mov eax, [ebp+arg2]		
	sub eax, X0
	div ecx
	mov X_matrice, eax
	mov ecx, 40
	mul ecx
	mov ebx, eax
	add ebx, X0
	add ebx, 1
	xor edx, edx
	mov eax, [ebp+arg3]
	sub eax, Y0
	div ecx
	mov Y_matrice, eax
	mov ecx, 40
	mul ecx
	add eax, Y0
	add eax, 1
	mov ecx, eax			
	push verificare_X_O
	push Y_matrice
	push X_matrice
	call petabla
	add esp, 12
	cmp eax, 0				
	jne final_player
	cmp verificare_X_O, 1 ;1-deseneaza X, 0-deseneaza 0
	jne draw_0
	make_text_macro_X_O 'X', area, ebx, ecx 
	jmp final_player
draw_0:
	make_text_macro_X_O 'O', area, ebx, ecx
final_player:
	pop ecx
	ret
player_vs_player endp

;;;;;;;;;;;;;;;;;;;;linii orizontale si verticale
linie_orizontala macro x, y, len, color
local bucla_linie
	mov eax, y
	mov ebx, area_width
	mul ebx
	add eax, x
	shl eax, 2
	add eax, area
	mov ecx, len
bucla_linie:
	mov dword ptr[eax], color
	add eax, 4
	loop bucla_linie
endm 

linie_verticala macro x, y, len, color
local bucla_linie
	mov eax, y
	mov ebx, area_width
	mul ebx
	add eax, x
	shl eax, 2
	add eax, area
	mov ecx, len
bucla_linie:
	mov dword ptr[eax], color
	add eax, area_width * 4
	loop bucla_linie
endm 

draw proc
	push ebp
	mov ebp, esp
	pusha
	mov eax, [ebp+arg1]
	cmp eax, 1
	jz evt_click
	cmp eax, 2
	jz afisare_litere 
clear:
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	push 0FFFFFFh   ;culoare fundal
	push area
	call memset
	add esp, 12
	linie_orizontala 100, 139, 40, 09932CCh
	linie_orizontala 100, 140, 40, 0000000h
	linie_orizontala 100, 141, 40, 09932CCh
	linie_orizontala 140, 139, 40, 09932CCh
	linie_orizontala 140, 140, 40, 0000000h
	linie_orizontala 140, 141, 40, 09932CCh
	linie_orizontala 180, 139, 40, 09932CCh
	linie_orizontala 180, 140, 40, 0000000h
	linie_orizontala 180, 141, 40, 09932CCh
	linie_orizontala 100, 179, 40, 09932CCh
	linie_orizontala 100, 180, 40, 0000000h
	linie_orizontala 100, 181, 40, 09932CCh
	linie_orizontala 140, 179, 40, 09932CCh
	linie_orizontala 140, 180, 40, 0000000h
	linie_orizontala 140, 181, 40, 09932CCh
	linie_orizontala 180, 179, 40, 09932CCh
	linie_orizontala 180, 180, 40, 0000000h
	linie_orizontala 180, 181, 40, 09932CCh
	linie_verticala 139, 100, 40, 09932CCh
	linie_verticala 140, 100, 40, 0000000h
	linie_verticala 141, 100, 40, 09932CCh
	linie_verticala 139, 140, 40, 09932CCh
	linie_verticala 140, 140, 40, 0000000h
	linie_verticala 141, 140, 40, 09932CCh
	linie_verticala 139, 180, 40, 09932CCh
	linie_verticala 140, 180, 40, 0000000h
	linie_verticala 141, 180, 40, 09932CCh
	linie_verticala 179, 100, 40, 09932CCh
	linie_verticala 180, 100, 40, 0000000h
	linie_verticala 181, 100, 40, 09932CCh
	linie_verticala 179, 140, 40, 09932CCh
	linie_verticala 180, 140, 40, 0000000h
	linie_verticala 181, 140, 40, 09932CCh
	linie_verticala 179, 180, 40, 09932CCh
	linie_verticala 180, 180, 40, 0000000h
	linie_verticala 181, 180, 40, 09932CCh
	jmp afisare_litere
	
evt_click:
	mov ebx,[ebp+arg2]
	mov edx,[ebp+arg3]	
	push edx
	push ebx
	add esp, 8
	mov eax, 99
	cmp eax, 99
	jne clear
	buclisoara:
		call player_vs_player 
		cmp eax, 0
		jne pastram_numarator				
		cmp verifica_afara, constanta_zero	
		je pastram_numarator
		dec numarator
		jmp verifica_castigator
	pastram_numarator:
		mov ecx, numarator
	verifica_castigator:
		cmp eax, 1
		je castiga_X
		cmp eax ,2
		je castiga_O
		cmp numarator, constanta_zero
		je egalitate
	iesi:	
		jmp afisare_litere
	 
	egalitate:
		make_text_macro 'E', area, 260, 190
		make_text_macro 'G', area, 270, 190
		make_text_macro 'A', area, 280, 190
		make_text_macro 'L', area, 290, 190
		make_text_macro 'I', area, 300, 190
		make_text_macro 'T', area, 310, 190
		make_text_macro 'A', area, 320, 190
		make_text_macro 'T', area, 330, 190
		make_text_macro 'E', area, 340, 190
		jmp afisare_litere
			
	castiga_O:
		;castiga O
		make_text_macro 'O', area, 280, 190
		make_text_macro ' ', area, 290, 190
		make_text_macro 'C', area, 300, 190
		make_text_macro 'A', area, 310, 190
		make_text_macro 'S', area, 320, 190
		make_text_macro 'T', area, 330, 190
		make_text_macro 'I', area, 340, 190
		make_text_macro 'G', area, 350, 190
		make_text_macro 'A', area, 360, 190
		mov numarator, constanta_zero
		jmp afisare_litere
	
	castiga_X:
	;castiga X 
		make_text_macro 'X', area, 280, 190
		make_text_macro ' ', area, 290, 190
		make_text_macro 'C', area, 300, 190
		make_text_macro 'A', area, 310, 190
		make_text_macro 'S', area, 320, 190
		make_text_macro 'T', area, 330, 190
		make_text_macro 'I', area, 340, 190
		make_text_macro 'G', area, 350, 190
		make_text_macro 'A', area, 360, 190
		mov numarator, constanta_zero

afisare_litere:	
	make_text_macro 'J', area, 190, 40
	make_text_macro 'O', area, 200, 40
	make_text_macro 'A', area, 210, 40
	make_text_macro 'C', area, 220, 40
	make_text_macro 'A', area, 230, 40
	make_text_macro ' ', area, 240, 40
	make_text_macro 'X', area, 250, 40
	make_text_macro ' ', area, 260, 40
	make_text_macro 'S', area, 270, 40
	make_text_macro 'I', area, 280, 40
	make_text_macro ' ', area, 290, 40
	make_text_macro '0', area, 300, 40
	
	make_text_macro 'D', area, 290, 80
	make_text_macro 'A', area, 300, 80
	make_text_macro ' ', area, 310, 80
	make_text_macro 'C', area, 320, 80
	make_text_macro 'L', area, 330, 80
	make_text_macro 'I', area, 340, 80
	make_text_macro 'C', area, 350, 80
	make_text_macro 'K', area, 360, 80
	make_text_macro ' ', area, 370, 80
	make_text_macro 'P', area, 380, 80
	make_text_macro 'E', area, 390, 80
	make_text_macro ' ', area, 400, 80
	make_text_macro 'P', area, 410, 80
	make_text_macro 'A', area, 420, 80
	make_text_macro 'T', area, 430, 80
	make_text_macro 'R', area, 440, 80
	make_text_macro 'A', area, 450, 80
	make_text_macro 'T', area, 460, 80
	make_text_macro 'E', area, 470, 80
	make_text_macro ' ', area, 480, 80
	make_text_macro 'S', area, 320, 100
	make_text_macro 'I', area, 330, 100
	make_text_macro ' ', area, 340, 100
	make_text_macro 'V', area, 350, 100
	make_text_macro 'E', area, 360, 100
	make_text_macro 'Z', area, 370, 100
	make_text_macro 'I', area, 380, 100
	make_text_macro ' ', area, 390, 100
	make_text_macro 'C', area, 400, 100
	make_text_macro 'I', area, 410, 100
	make_text_macro 'N', area, 420, 100
	make_text_macro 'E', area, 430, 100
	make_text_macro ' ', area, 440, 100
	make_text_macro 'C', area, 350, 120
	make_text_macro 'A', area, 360, 120
	make_text_macro 'S', area, 370, 120
	make_text_macro 'T', area, 380, 120
	make_text_macro 'I', area, 390, 120
	make_text_macro 'G', area, 400, 120
	make_text_macro 'A', area, 410, 120

	
	popa
	mov esp, ebp
	pop ebp
	ret
draw endp

start:
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov area, eax
	push offset draw
	push area
	push area_height
	push area_width
	push offset window_title
	call BeginDrawing
	add esp, 20
	push 0
	call exit
end start