#pragma once

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "Simple-driver"
#define BUFFER_SIZE 256

int register_device(void);
void unregister_device(void);