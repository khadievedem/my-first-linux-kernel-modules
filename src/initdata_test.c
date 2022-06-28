/*
 * initdata_test.c - 
*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#define MODULE_NAME "initdata_test"

static int initdata_num __initdata = 11;

static int __init initdata_init(void)
{
	printk(KERN_INFO "[%s] Here is __initdata data: %d\n", MODULE_NAME,
	       initdata_num);
	return 0;
}

static void __exit initdata_exit(void)
{
	printk(KERN_INFO "[%s] Exit from the module. \n", MODULE_NAME);
	return;
}

module_init(initdata_init);
module_exit(initdata_exit);

MODULE_LICENSE("LGPL");