#ifndef IDT_H
#define IDT_H
#include "../../kernel-functions/kputs.h"

struct idt_location {
    uint16_t size;
    uint32_t offset;
}__attribute__((packed));

struct idt_location idt_ptr;

struct IDT_t {
    uint16_t ptr_offset_lower;
    uint16_t code_segment_selector;
    uint8_t zero;
    uint8_t gate_type;
    uint16_t ptr_offset_higher;
};


struct IDT_t create_idg_record();

void set_up_idt();

void load_idt();

void interrupt();

#endif
