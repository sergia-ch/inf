[BITS 16]
[ORG 0x7c00]
_start:	
	cli
	mov ax, cs
	mov ds, ax
	mov ss, ax
	mov sp, _start

	;; Загрузка регистра GDTR:	
	lgdt [gd_reg]

	;; Включение A20: 
	in al, 0x92
	or al, 2
	out 0x92, al

	;; Установка бита PE регистра CR0
	mov eax, cr0 
	or al, 1	
	mov cr0, eax  

	;; С помощью длинного прыжка мы загружаем
	;; селектор нужного сегмента в регистр CS
	;; (напрямую это сделать нельзя)
	;; 8 (1000b) - первый дескриптор в GDT, RPL=0
	jmp 0x8: _protected


[BITS 32]
_protected:	
	;; Загрузим регистры DS и SS селектором
	;; сегмента данных
	mov ax, 0x10
	mov ds, ax
	mov ss, ax

	call memtest

	;; Завесим процессор
	hlt
	jmp short $


cursor:	dd 0
%define VIDEO_RAM 0xB8000

memtest:
    pusha
    mov ecx, 1048576
    mov ebx, 0b10101010
;    mov edx, 1073741824
    mov edx, 67108964 ; not ok
;    mov edx, 67108764 ; ok
lLoop:
    mov dword [ecx], ebx
    mov eax, dword [ecx]
    cmp eax, ebx
    jne short lWrong
    inc ecx
    cmp ecx, edx
    jge lRight
    jmp lLoop
lWrong:
    mov esi, msg_notok
    jmp lEnd
lRight:
    mov esi, msg_ok
lEnd:
    call kputs
    popa
    ret

;; Функция выполняет прямой вывод в память видеоадаптера
;; которая находится в VGA-картах (и не только) по адресу 0xB8000
	
kputs:
	pusha
.loop:	
	lodsb 
	test al, al
	jz .quit
	mov ecx, [cursor]
	mov [VIDEO_RAM+ecx*2], al
    mov [VIDEO_RAM+ecx*2+1], byte 0b0010100
	inc dword [cursor]
	jmp short .loop



.quit:	
	popa
	ret
		

gdt:
	dw 0, 0, 0, 0	; Нулевой дескриптор

	db 0xFF		; Сегмент кода с DPL=0 
	db 0xFF		; Базой=0 и Лимитом=4 Гб 
	db 0x00
	db 0x00
	db 0x00
	db 10011010b
	db 0xCF
	db 0x00
	
	db 0xFF		; Сегмент данных с DPL=0
	db 0xFF		; Базой=0 и Лимитом=4Гб	
	db 0x00	
	db 0x00
	db 0x00
	db 10010010b
	db 0xCF
	db 0x00


	;; Значение, которое мы загрузим в GDTR:	
gd_reg:
	dw 8192
	dd gdt

msg_hello:	db "Hello from the world of 32-bit Protected Mode",0
msg_ok: db "Memory is ok!", 0
msg_notok: db "Memory is NOT ok!", 0

	times 510-($-$$) db 0
	db 0xaa, 0x55


