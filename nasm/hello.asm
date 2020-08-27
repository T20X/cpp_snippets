global _start

section .data
message:
	 db 'hello, world!', 10
lessthen:
	 db 'less then', 10

section .text
_start:
    mov     rax, 1           ;system call number should be stored in rax
    mov     rdi, 1           ; argument #1 in rdi: where to write (descriptor)?
    mov     rsi, message     ; argument #2 in rsi: where does the string start?
    mov     rdx, 14          ; argument #3 in rdx: how many bytes to write?
    syscall                  ; this instruction invokes a system call

    push 1 
	mov rax, gs
    cmp rax, 10
    je yes
    mov rbx, 0
    jmp ex
yes:
    mov rbx, 1
    mov     rax, 1           ;system call number should be stored in rax
    mov     rdi, 1           ; argument #1 in rdi: where to write (descriptor)?
    mov     rsi, lessthen      ; argument #2 in rsi: where does the string start?
    mov     rdx, 14          ; argument #3 in rdx: how many bytes to write?
    syscall                  ; this instruction invokes a system call 

ex:

    mov     rax, 60          ; 'exit' syscall number
    xor     rdi, rdi
    syscall 


