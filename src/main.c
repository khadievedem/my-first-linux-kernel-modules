#include "my_simple_module.h"

static int __init my_init(void)
{
	register_device();
	return 0;
}

static void __exit my_exit(void)
{
	unregister_device();
	return;
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("LGPL");