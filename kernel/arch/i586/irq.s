.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15


irq0:
        cli
        push $0x0
        push $0x20
        jmp irq_common_stub

irq1:
        cli
        push $0x0
        push $0x21
        jmp irq_common_stub

irq2:
        cli
        push $0x0
        push $0x22
        jmp irq_common_stub

irq3:
        cli
        push $0x0
        push $0x23
        jmp irq_common_stub

irq4:
        cli
        push $0x0
        push $0x24
        jmp irq_common_stub

irq5:
        cli
        push $0x0
        push $0x25
        jmp irq_common_stub

irq6:
        cli
        push $0x0
        push $0x26
        jmp irq_common_stub

irq7:
        cli
        push $0x0
        push $0x27
        jmp irq_common_stub


irq8:
        cli
        push $0x0
        push $0x28
        jmp irq_common_stub

irq9:
        cli
        push $0x0
        push $0x29
        jmp irq_common_stub

irq10:
        cli
        push $0x0
        push $0x2a
        jmp irq_common_stub

irq11:
        cli
        push $0x0
        push $0x2b
        jmp irq_common_stub

irq12:
        cli
        push $0x0
        push $0x2c
        jmp irq_common_stub

irq13:
        cli
        push $0x0
        push $0x2d
        jmp irq_common_stub

irq14:
        cli
        push $0x0
        push $0x2e
        jmp irq_common_stub

irq15:
        cli
        push $0x0
        push $0x2f
        jmp irq_common_stub


.extern irq_handler

irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov  $0x10, %ax
    mov  %ax  , %ds
    mov  %ax  , %es
    mov  %ax  , %fs
    mov  %ax  , %gs
    mov %esp, %eax
    push %eax
    #mov irq_handler, %eax
    call irq_handler
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $0x08, %esp
    iret

