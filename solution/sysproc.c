#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"  //TASK 4


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// TASK 3 //
/*
 * Allow a process to set its own number of tickets.
 * The max tickets allowed to be set for a process is 1<<5.
 * The minimum tickets allowed is 1. 
 * If a process sets a value lower than 1, set the number of tickets to default = 8.
 * This is also the number of tickets a new process in your system should have.
 * Returns 0 on success, -1 on failure
 */
int sys_settickets(void)
{
  // Fetch number of tickets from the syscall argument
  int n;
  if (argint(0, &n) < 0) return -1;
  else return settickets(n);
}


// TASK 4 //
int sys_getpinfo(void)
{
  struct pstat *procstat;
  if (argptr(0, (char**)&procstat, sizeof(struct pstat)) < 0) return -1;
  return getpinfo(procstat); 
}
