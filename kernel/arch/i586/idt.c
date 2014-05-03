#include "idt.h"

//TODO: rewrite
struct IDT_t create_idt_record()
{
    struct IDT_t idt_record;
    idt_record.ptr_offset_lower = (int)&idt_record;
    idt_record.code_segment_selector =  0x9a;
    idt_record.zero = 0;
    idt_record.gate_type = 0xe; // 32 bit interrupt gate
    idt_record.ptr_offset_higher = (int)&idt_record >> 16;
    return idt_record;
}

void set_up_idt()
{
    int num_idt = 256;
    struct IDT_t idt[num_idt];
    for(int i = 0; i < num_idt; i++) {
        idt[i] = create_idt_record();
    }
    idt_ptr.size = num_idt;
    idt_ptr.offset = idt;
}

void load_idt()
{
    __asm__ __volatile__(
    "cli\n"
    "lidt idt_ptr\n"
    );
}

void interrupt()
{
    kputs("Interrupt fired!");
}
