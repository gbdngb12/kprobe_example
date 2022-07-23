#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/kprobes.h>

static struct kprobe kp;

int pre_handler(struct kprobe *p, struct pt_regs *regs) {
        printk(KERN_INFO "instruction end");
        return 0;
}

void post_handler(struct kprobe *p, struct pt_regs *regs, unsigned long flags){
        printk(KERN_INFO "instruction start\n");
}


static struct kprobe kp = {
        //.symbol_name  = "__x64_sys_execve",
        //.addr = (kprobe_opcode_t *)0xffffffff810a3f00,
        .pre_handler    = pre_handler,
        .post_handler   = post_handler
};

int kprobe_init(void) {
        register_kprobe(&kp);
        printk(KERN_INFO "Planted kprobe at %p\n", kp.addr);
        return 0;
}

void kprobe_exit(void) {
        unregister_kprobe(&kp);
        printk(KERN_INFO "kprobe at %p unregistered\n", kp.addr);
}

module_init(kprobe_init);
module_exit(kprobe_exit);
MODULE_AUTHOR("Pr0ln");
MODULE_DESCRIPTION("kprobe example");
MODULE_LICENSE("GPL");

