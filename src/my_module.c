#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int __init my_init(void)
{
	int num_major = register_device();
	return 0;
}

static void __exit my_exit(void)
{
	unregister_device();
	return;
}

static ssize_t device_file_read(struct file *, char *, size_t, loff_t *);
static unsigned int device_file_major_number;
static const char device_name[] = "Simple-driver";
static const char g_s_Hello_World_string[] = "Hello world from kernel mode !\n";
static const ssize_t g_s_Hello_World_size = sizeof g_s_Hello_World_string;

static struct file_operations simple_driver_fops = {
	.owner = THIS_MODULE,
	.read = device_file_read,
};

int register_device(void)
{
	int result = 0;
	printk(KERN_NOTICE "[%s] register_device() is called.\n", device_name);
	if ((result = register_chrdev(device_file_major_number, device_name,
				      &simple_driver_fops)) < 0) {
		printk(KERN_WARNING
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

void unregister_device(void)
{
	printk(KERN_NOTICE "[%s] unregister_device() is called.\n",
	       device_name);
	if (device_file_major_number != 0) {
		unregister_chrdev(device_file_major_number, device_name);
	}
}

static ssize_t device_file_read(struct file *file_ptr, char __user *user_buffer,
				size_t count, loff_t *position)
{
	printk(KERN_NOTICE
	       "[%s] Device file is read at offset %i, read bytes count = %u",
	       device_name, (int)*position, (unsigned int)count);
	/* if we try to read data out of our file => we have nothing to read */
	if (*position >= g_s_Hello_World_size) {
		return 0;
	}
	if (*position + count > g_s_Hello_World_size) {
		count = g_s_Hello_World_size - *position;
	}
	if (copy_to_user(user_buffer, g_s_Hello_World_string + *position,
			 count) != 0) {
		return -EFAULT;
	}
	*position += count;
	return count;
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("LGPL");
