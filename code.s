
.section .text

.globl _start

_start:

 movl $3, a
 pushl a
 call prnt_int
 movl $4, x
 pushl x
 call prnt_int
 pushl x
 call prnt_int
 jmp exit

prnt_int:

 pushl %ebp
 movl %esp, %ebp
 pushl %esi
 movl 8(%ebp), %eax
 movl %esp, %esi
 cmpl $0, %eax 
 jge prnt1
 imull $(-1), %eax
 movl %eax, 8(%ebp)
 movl $45, %edx
 movl %edx, group+400
 movl $4, %eax 
 movl $1, %ebx
 movl $group+400, %ecx
 movl $1, %edx
 int $0x80
 movl 8(%ebp), %eax

prnt1:

 cdq
 movl $10, %ebx
 idivl %ebx
 pushl %edx
 cmpl $0, %eax
 jne prnt1
 jmp prnt2

prnt2:

 popl %edx
 addl $48, %edx
 movl %edx, group+400
 movl $4, %eax 
 movl $1, %ebx
 movl $group+400, %ecx
 movl $1, %edx
 int $0x80
 cmp %esp, %esi
 jne prnt2

 movl $10, group+400
 movl $4, %eax 
 movl $1, %ebx
 movl $group+400, %ecx
 movl $1, %edx
 int $0x80
 popl %esi
 movl %ebp, %esp
 popl %ebp
 ret


exit: 

 movl $1, %eax
 movl $0, %ebx
 int $0x80
