#include <arch/x86/process.h>

extern uint32_t get_flags(void);
extern uint32_t get_page_dir(void);
extern void _process_handler(void);
extern void switch_task(uint32_t esp, uint32_t cr3, uint32_t *kernel_esp);


void process_handler();

uint32_t get_next_pid() {
    static uint32_t proc_count = 0;
    return proc_count++;
}

struct process *running_proc;

void proc_init() {
    struct process *kernel_proc = kmalloc(sizeof(struct process));
    kernel_proc->next = kernel_proc;
    kernel_proc->cr3 = get_page_dir();
    klogf("init physical paging address %p\n", kernel_proc->cr3);
    running_proc = kernel_proc;

    install_interrupt(32, process_handler);
    uint8_t current_mask = read_port(0x21);
    write_port(0x21 , current_mask & TIMER_INTERRUPT_MASK);
}

struct process *create_proc(void(*entrypoint)()) {
    uint32_t *link_loc = (uint32_t*)0x20000;
    uint32_t *stack_page = (uint32_t*)NEXT_PAGE(link_loc);
    uint32_t stack_addr = (uint32_t)stack_page + (PAGE_SIZE-1-44+5);
    struct process *proc = kmalloc(sizeof(struct process));

    proc->cr3 = create_page_dir(link_loc,
            stack_page, entrypoint, PAGE_USER_MODE | PAGE_WRITABLE);

    proc->kernel_esp = stack_addr;
    proc->id = get_next_pid();
    proc->next = 0;
    return proc;
}

void schedule_proc(struct process *proc) {
    proc->next = running_proc->next;
    running_proc->next = proc;
}

void preempt() {
    klog("preempt\n");
    struct process *last = running_proc;
    running_proc = running_proc->next;
    // switch_task does not behave properly when the last task and current
    // tasks are the same, especially if the state of the current task's
    // registers are not properly initialized.
    // If the next proc is the same as the current one then return.
    if (running_proc == last) {
        return;
    }
    klogf("\nEnabling paging %p\n", running_proc->cr3);
    //enable_paging(running_proc->cr3);
    klogf("\nSetting stack to %p\n", running_proc->kernel_esp);
    switch_task(running_proc->kernel_esp, running_proc->cr3, &last->kernel_esp);
}


void process_handler() {
    // End interrupt
    write_port(0x20, 0x20);
    preempt();
}
