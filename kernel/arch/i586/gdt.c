#include "gdt.h"

GDT_t create_gdt_record(uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags)
{
    GDT_t gdt_record = 0;
    GDT_t buffer;
    gdt_record |= limit                & 0x000000000000ffff; 
    gdt_record |= (base << 16)         & 0x000000ffffff0000; 
    buffer = access_byte;
    gdt_record |= (buffer << 41)       & 0x0000ff0000000000;
    buffer = limit;
    gdt_record |= (buffer << (49-16))  & 0x000f000000000000;
    buffer = flags;
    gdt_record |= (buffer << 53)       & 0x00f0000000000000;
    buffer = base ;
    gdt_record |= (buffer << (56-24))  & 0xff00000000000000;
    return gdt_record;
}

void set_up_gdt()
{
    
    GDT_t gdt[3];
    // Null descriptor - will never be used by processor
    gdt[0] = create_gdt_record(0,0,0,0);
    // Code segment, theoretically, really the flags are set to allow anything
    gdt[1] = create_gdt_record(0, 0xffffffff, 0xff, 0xff); 
    // Data segment, theoretically, really the flags are set to allow anything
    gdt[2] = create_gdt_record(0, 0xffffffff, 0xff, 0xff);
    gdt_ptr->table_start = gdt;
    gdt_ptr->table_size = 3 * 64 - 1;
    enter_protected_mode();
}

void enter_protected_mode()
{
    __asm__ __volatile__ (
    "cli\n"            // disable interrupts
    "lgdt gdt_ptr\n"   // load GDT register with start address of GDT
    "mov %cr0, %eax\n" // move the contents of the control register 0 to the
                       // eax register
    "or %al, 1\n"      // set PE (Protection Enable) bit in CR0 
                       // (Control Register 0)
    "mov %eax, %cr0\n" // Put the contents of eax back into the eax register
    );
}
