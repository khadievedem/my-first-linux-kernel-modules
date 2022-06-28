/*
 * hello_world.c - module that just says hello to the world
*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#define MODULE_NAME "hello_world"

static int __init hw_init(void)
{
	printk(KERN_INFO "[%s] Hello world! \n", MODULE_NAME);
	return 0;
}

static void __exit hw_exit(void)
{
	printk(KERN_INFO "[%s] Exit from the module. \n", MODULE_NAME);
	return;
}

module_init(hw_init);
module_exit(hw_exit);

MODULE_LICENSE("LGPL");
MODULE_AUTHOR("Khadiev Edem");