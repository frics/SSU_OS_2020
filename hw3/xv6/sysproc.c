#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h"

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
int
sys_hello(void)
{

	cprintf("helloxv6\n");
	return 0;
}
int
sys_hello_name(void)
{
	char *name;
	//UserMode에서 전달한 인자 받아오기	
	if(argstr(0, &name) <0)
		return -1;
	cprintf("hello %s\n", name);

	return 0;
}

int
sys_get_num_proc(void)
{
	//proc.c의 get_num_proc()호출
	return get_num_proc();
}
int
sys_get_max_pid(void)
{
	//proc.c의 get_max_pid()호출
	return get_max_pid();
}
int
sys_get_proc_info(void)
{
	int pid;
	struct processInfo *procInfo;
	//UserMode에서 전달한 인자 받아오기
	if(argint(0, &pid) < 0 || argptr(1, (void*)&procInfo, sizeof(*procInfo)))
		return -1;

	//proc.c의 get_proc_info()호출
	return get_proc_info(pid, procInfo);
}

int 
sys_set_prio(void)
{
	int n;
	//UserMode에서 전달한 인자 받아오기
	if(argint(0, &n) <0)
		return -1;
	//proc.c의 set_prio(int n)호출
	return set_prio(n);
}

int 
sys_get_prio(void)
{
	//proc.c의 get_prio(void)호출
	return get_prio();
}

