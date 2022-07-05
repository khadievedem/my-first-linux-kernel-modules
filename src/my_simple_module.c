#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "my_simple_module.h"

#define DEVICE_NAME "Simple-driver"
/*
 * Prototypes
 */
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
/*
 * Device data
 */
static int is_device_open;
static unsigned int device_file_major_number;
static const char g_s_Hello_World_string[] = "Hello world from kernel mode !\n";
static const ssize_t g_s_Hello_World_size = sizeof g_s_Hello_World_string;

static struct file_operations simple_driver_fops = {
	owner: THIS_MODULE,
	read: device_read,
	write: device_write,
	open: device_open,
	release: device_release
};
/*
 *
 * device registration
 * 
 */
int register_device(void)
{
	int result = 0;
	printk(KERN_NOTICE "[%s] register_device() is called.\n", DEVICE_NAME);
	if ((result = register_chrdev(device_file_major_number, DEVICE_NAME,
				      &simple_driver_fops)) < 0) {
		printk(KERN_WARNING
		       "[%s] can't register character device with error code %i\n",
		       DEVICE_NAME, result);
		return result;
	}
	device_file_major_number = result;
	printk(KERN_NOTICE
	       "[%s] registered character device with major number %i \
                        and minor numbers 0...255\n",
	       DEVICE_NAME, device_file_major_number);
	return 0;
}

void unregister_device(void)
{
	printk(KERN_NOTICE "[%s] unregister_device() is called.\n",
	       DEVICE_NAME);
	if (device_file_major_number != 0) {
		unregister_chrdev(device_file_major_number, DEVICE_NAME);
	}
}
/*
 *
 * Methods 
 *
 */
static ssize_t device_read(struct file *file_ptr, char __user *user_buffer,
			   size_t count, loff_t *position)
{
	printk(KERN_NOTICE
	       "[%s] Device file is read at offset %i, read bytes count = %u",
	       DEVICE_NAME, (int)*position, (unsigned int)count);
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

static ssize_t device_write(struct file *file_ptr, const char *user_buffer,
			    size_t count, loff_t *position)
{
	printk(KERN_WARNING "This operation isn't supported");
	return -EINVAL;
}

static int device_open(struct inode *inode, struct file *file)
{
	/* called when a process tries to open the device file */
	static int counter;

	if (is_device_open) {
		return -EBUSY;
	}
	is_device_open++;
	try_module_get(THIS_MODULE); /*
                                  * increments the use count of device
                                  */
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	/* called when a process closes the device file */
	is_device_open--;
	module_put(THIS_MODULE); /* decrements the use count of the module
                              * to be able to get rid of them in future
                              */
	return 0;
}