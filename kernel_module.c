#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Adithya S");

void print_process_tree(struct task_struct *task, int depth) {
    struct task_struct *child_task;
    struct list_head *list;

    printk(KERN_INFO "%*sPID: %d, Name: %s\n", depth * 10, "", task->pid, task->comm);

    list_for_each(list, &task->children) {
        child_task = list_entry(list, struct task_struct, sibling);
        print_process_tree(child_task, depth + 1);
    }
}

static int __init proc_tree_init(void) {
    printk(KERN_INFO "Process Tree Module Loaded\n");

    print_process_tree(&init_task, 0);

    return 0; 
}

static void __exit proc_tree_exit(void) {
    printk(KERN_INFO "Process Tree Module Unloaded\n");
}

module_init(proc_tree_init);
module_exit(proc_tree_exit);