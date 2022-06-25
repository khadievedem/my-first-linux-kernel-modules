#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

static int my_init(void)
{
	return 0;
}

static void my_exit(void)
{
	return;
}

ssize_t device_file_read(struct file *, char *, size_t, loff_t *);

static struct file_operations simple_driver_fops = {
	.owner = THIS_MODULE,
	.read = device_file_read,
};


module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("LGPL");
