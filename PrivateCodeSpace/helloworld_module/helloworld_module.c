#include <linux/init.h>
#include <linux/module.h>

static int __init helloworld_init(void)
{
    printk("this is a helloworld kernel module\n");
    return 0;
}

static void __exit helloworld_exit(void)
{
    printk("helloworld module exit...\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bowenerchen");
MODULE_DESCRIPTION("this is a test kernel module");
MODULE_ALIAS("helloworld_module");
