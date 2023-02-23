#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/ktime.h>
MODULE_LICENSE("Dual BSD/GPL");

unsigned long hz_config= 250;
unsigned long jiffies_start;
unsigned long jiffies_exit;
unsigned long difference;
unsigned long difference_k;
ktime_t time_start;
ktime_t time_exit;

static int hello_init(void){
unsigned long tick_time = (1000/hz_config);
jiffies_start = jiffies;
time_start = ktime_get_boottime();
printk(KERN_ALERT "Hello, world\n");
printk("The tick time in milliseconds is %ld\n",tick_time);
return 0;
}

static void hello_exit(void){
jiffies_exit = jiffies;
time_exit = ktime_get_boottime();
difference = ((jiffies_exit - jiffies_start) / hz_config) *1000;
difference_k = (time_exit - time_start) / 1000000;
printk("The time difference found using the jiffies metric is %ld milliseconds\n", difference);
printk("The time difference found using the ktime_t metric is %ld milliseconds\n", difference_k);
printk(KERN_ALERT "Goodbye,cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

