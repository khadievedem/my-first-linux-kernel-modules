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

static unsigned int device_file_major_number;
static const char device_name[] = "Simple-driver";
int register_device(void)
{
	int result = 0;
	printk(KERN_NOTICE "[%s] register_device() is called.\n", device_name);
	if ((result = register_chrdev(device_file_major_number, device_name,
				      &simple_driver_fops)) < 0) {
		printK(KERN_WARNING
		       "[%s] can't register character device with error code %i\n",
		       device_name, result);
		return result;
	}
	device_file_major_number = result;
	printk(KERN_NOTICE
	       "[%s] registered character device with major number %i \
                        and minor numbers 0...255\n",
	       device_name, device_file_major_number);
	return 0;
}

int unregister_devie(void)
{
	printk(KERN_NOTICE "[%s] unregister_device() is called.\n",
	       device_name);
	if (device_file_major_number != 0) {
		unregister_chrdev(device_file_major_number, device_name);
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("LGPL");
