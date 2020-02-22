; File: src/template_lin.asm

; Just as in the Windows template - we tell the assembler which type 
; of output we expect. 
; In this case it is 32-bit executable ELF

format ELF executable

; Tell the assembler where the entry point is
entry _start

; On *nix based systems, when in memory, the space is arranged into 
; segments, rather than in sections, therefore, we define 
; two segments:
; Code segment (executable segment)
segment readable executable

include 'variable.inc'
include 'system.inc'
; Here is our entry point
_start:

    mov eax, 4
    mov ebx, 1
    mov ecx, message2
    mov edx, len2
    int 0x80 

	mov eax, 10
	call display_number 

   ; Set return value to 0
   xor ebx, ebx
   mov eax, ebx
 
   ; Set eax to 1 - 32-bit Linux SYS_exit system call number
   inc eax
 
   ; Call kernel
   int 0x80

segment readable writeable
   message2 db 'Hello from FASM on Linux!', 0x0a
   len2 = $ - message
   command_line dd ?
   memory_setting dd ?
   definitions_pointer dd ?
   environment dd ?
   timestamp dq ?
   start_time dd ?
   con_handle dd ?
   displayed_count dd ?
   last_displayed db ?
   character db ?
   preprocessing_done db ?



; As you see, there is no import/export segment here. The structure 
; of an ELF executable/object file will be covered in more detail 
; in chapters 8 and 9
