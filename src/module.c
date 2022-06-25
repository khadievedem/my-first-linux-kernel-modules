#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


static int my_init(void)
{
    return  0;
}
    
static void my_exit(void)
{
    return;
}
    
module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("LGPL");

