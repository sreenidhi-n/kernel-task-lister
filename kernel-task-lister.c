/*
Write a kernel module that lists all current tasks in a Linux system beginning from the init task. Output the task name, state and process id of each task in a tree structure.
*/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched/task.h>

void traverse(struct task_struct *task)
{
	struct task_struct *next;  // included under sched/task.h. Helps contain all the information required by the kernel and has a store of info the kernel already has.
    struct list_head *list;    // used for implementing large lists of like structures. Included under list.h
	list_for_each(list, &task->children) {  // iterates the list until no more children (list end is reached)
		next = list_entry(list, struct task_struct, sibling); //connects several elements of the list. 
		/* 
		list_entry(pointer, type, member)
		helps convert list pointer to a task_struct value that holds the list value, pointed to by the value at pointer.
		IT computes the offset of the member (here sibling) and subtracting that many bytes from the list pointer.
		
		Why sibling?
		-Used to check what sibling is a list entry. Per linux kernel lists API, list pointers are initialised to the siblings for linkage purposes (to link a given list entry with other entries).
		- Address of parent task/current task is known. Address of child tasks is unknown. Address of 
		*/
		printk(KERN_INFO "pid: %d | pname: %s | state: %u\n", next->pid, next->comm, next->__state);
		traverse(next);  // recursive call to continue DFS traversal.
	}  
}

int __init taskInit(void)   // __init macro causes init function to be discarded and its memory freed once init function is fully executed.
{
	printk(KERN_INFO "Loading module...\n");
	traverse(&init_task);
	printk(KERN_INFO "Module loaded.\n");
	return 0;
}

void __exit taskExit(void) // __exit is a cleanup macro for once the module is done executing. 
{
  	return;
}

module_init(taskInit);  //Module entry point macro
module_exit(taskExit);  //mODULE exit macro
//Licensing
MODULE_VERSION("0.1");
MODULE_DESCRIPTION("Test MOdule");
MODULE_AUTHOR("sreenidhi");
MODULE_LICENSE("GPL");
