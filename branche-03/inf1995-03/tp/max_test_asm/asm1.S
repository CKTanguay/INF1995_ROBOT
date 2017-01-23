.text
add:
    push %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    add 12(%ebp), %eax  
    pop %ebp
    ret
    
    
.global max
max:
.equ a, 5
.equ b, 4
pushl	$a
pushl	$b
call	add
popl	%ecx
popl	%ecx
end:
ret

##debut if
#cmp %eax, b
#jnle IF
#movl $4, %eax
#jmp end
#IF:
#movl $5, %eax
#jmp end


