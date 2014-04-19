#ifndef GDT_H
#define GDT_H
#include <stdint.h>
#include "../../kernel-functions/kassert.h"

/*
    The Global Descriptor Table, or GDT, is a table in memory which describes
    to the processor how memory will be divided. For instance, memory may be
    divided into code and data segments, and elsewhere space may be reserved
    for additional tables such as the Interrupt Descriptor Table.
    In order to enter protected mode, where the CPU will throw interrupts and
    prevent unauthorized access to segments of memory, the GDT must be loaded
    with the `lgdt` instruction. The `lgdt` instruction takes a pointer to
    a field of memory with two parts, first the size of the GDT minus one
    and second, the pointer to the beginning of the GDT itself.

    The GDT is composed of a series of records, each 64 bits long. The portions
    of these records will be described later.
    For a thorough explanation of gdts go here:
    http://wiki.osdev.org/Global_Descriptor_Table
    http://wiki.osdev.org/GDT
*/

/*
    Use an unsigned 64 bit integer as a single GDT type. This is easier to 
    do bit twiddling on than a similarly sized struct.
*/
typedef uint64_t GDT_t;

/*
    This struct represents the location of the GDT. It will be used by the
    `lgdt` instruction. The first field is the size of the GDT - 1. The second
    is a pointer to where the GDT begins.
*/
struct gdt_location {
    uint16_t table_size;
    GDT_t* table_start;
}__attribute__((packed));

/* a pointer to the location of the gdt, used by the lgdt instruction */
struct gdt_location* gdt_ptr;

/* 
    Creates a gdt record with the specified settings. Returns the record as a
    GDT_t. Takes the following arguments:
        uint32_t base:
            I'm not 100% what this field is, but what I've read reccomends
            setting it to 0.
        uint32_t limit (actual max size of 20 bytes):
            Set the size of the segments described. My reading suggests 0xFFFFF
            is best.
        uint8_t  access_byte:
            Indicates access permissions for the segment of memory.
            This will determine whether this part of memory is readable,
            writable, etc. My reading suggests that I should have a 0x9A for a
            code segment and a 0x92 for data.
        uint8_t  flags (actual max size of 4 bytes):
            My reading suggests 5 as the magic number for flags.
            The top bit represents granularity with 1 indicating the limit is
            expressed in units of 4kb (as opposed to 1 byte granularity)
            The size bits enable 16 or 32 bit protected mode.
        
 */
GDT_t create_gdt_record(uint32_t base, uint32_t limit, uint8_t access_byte,
                           uint8_t flags);

/* sets up the kernel's gdt */
void set_up_gdt();

/* call the lgdt instruction and enter protected mode */
void enter_protected_mode();

#endif
