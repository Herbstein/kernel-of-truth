#ifndef IDT_H
#define IDT_H

struct idt_location {
    uint16_t size;
    uint32_t offset;
}__attribute__(packed);

typedef uint64_t IDT_t;

IDT_t create_idg_record(uint32_t offset, uint16_t selector, uint8_t type_attr);

void set_up_idt();

void load_idt();

#endif
