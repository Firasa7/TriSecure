#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/sysinfo.h>

#define PROC_NAME "sys_health"
#define TIMER_INTERVAL (5 * HZ)  // 5 seconds

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CyberGuardians");
MODULE_DESCRIPTION("SCIA 360: Real-Time Health Monitoring Module");
MODULE_VERSION("0.1");

#define GROUP_NAME "TriSecure"
#define GROUP_MEMBERS "Firas Abdelgadir, Justin Duru, Sa'Niyah Council"

// Memory threshold parameter
static int mem_threshold = 100;  // in MB
module_param(mem_threshold, int, 0644);
MODULE_PARM_DESC(mem_threshold, "Memory usage threshold in MB");

static struct timer_list health_timer;
static struct proc_dir_entry *proc_entry;
static struct sysinfo info;

// Timer callback
static void monitor_callback(struct timer_list *t) {
    si_meminfo(&info);
    unsigned long total_mem = (info.totalram * info.mem_unit) >> 20;
    unsigned long free_mem = (info.freeram * info.mem_unit) >> 20;
    unsigned long used_mem = total_mem - free_mem;

    if (used_mem > mem_threshold) {
        printk(KERN_WARNING "[%s] Alert: Memory usage exceeded threshold (%luMB used)\n",
               GROUP_NAME, used_mem);
    }

    mod_timer(&health_timer, jiffies + TIMER_INTERVAL);
}

// /proc read handler
static ssize_t proc_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) {
    char buf[128];
    int len;

    si_meminfo(&info);
    len = snprintf(buf, sizeof(buf), "Free memory: %lu MB\n",
                   (info.freeram * info.mem_unit) >> 20);

    return simple_read_from_buffer(ubuf, count, ppos, buf, len);
}

static struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

static int __init sys_health_init(void) {
    printk(KERN_INFO "[%s] SCIA 360: Module loaded successfully. Team Members: %s\n",
           GROUP_NAME, GROUP_MEMBERS);

    proc_entry = proc_create(PROC_NAME, 0444, NULL, &proc_fops);
    if (!proc_entry) {
        printk(KERN_ERR "[%s] Failed to create /proc entry\n", GROUP_NAME);
        return -ENOMEM;
    }

    timer_setup(&health_timer, monitor_callback, 0);
    mod_timer(&health_timer, jiffies + TIMER_INTERVAL);

    return 0;
}

static void __exit sys_health_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    del_timer(&health_timer);
    printk(KERN_INFO "[%s] SCIA 360: Module unloaded. Team Members: %s\n",
           GROUP_NAME, GROUP_MEMBERS);
}

module_init(sys_health_init);
module_exit(sys_health_exit);
