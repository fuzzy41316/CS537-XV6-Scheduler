#define STRIDE1 1<<10        // STRIDE1 is a constant (for this project: 1<<10).

// Per-CPU state
struct cpu {
  uchar apicid;                // Local APIC ID
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table
  volatile uint started;       // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.
  int intena;                  // Were interrupts enabled before pushcli?
  struct proc *proc;           // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)


  // TASK 1 // 
  int tickets;                  // A value assigned upon process creation.  It can be modified by a system call.  It should default to 8
  int stride;                   // A value that is inversely proportional to a process' tickets. stride = STRIDE1 / tickets
  int pass;                     // Initially set to 0.  This gets updated every time the process runs
  int remain;                   // Represents the number of passes that are left before a process' next selection. When a process leaves the scheduler queue, remain is computed as the difference between the process' pass and the global_pass
  int rtime;                    // Total runtime, used for tie-breaking, process with lower number of ticks spent running is scheduled first, if equal, fall back on lower PID going first
};

// TASK 1 //
extern int global_tickets;             // The sum of all runnable process's tickets.
extern int global_stride;              // Inversely proportional to the global_tickets, specifically STRIDE1 / global_tickets
extern int global_pass;                // Incremented by the current global_stride at every tick.

// TASK 4 //
struct pstat;
extern int getpinfo(struct pstat * procstat);
extern int settickets(int n);

// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap
