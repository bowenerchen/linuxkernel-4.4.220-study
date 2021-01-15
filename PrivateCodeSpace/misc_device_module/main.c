#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/miscdevice.h>

/***
* 杂项设备也是在嵌入式系统中用得比较多的一种设备驱动，
* 在 Linux 内核的include/linux目录下有Miscdevice.h文件，自定义的misc device从设备定义在这里 
* 由于这些字符设备不符合预先确定的字符设备范畴，所有这些设备采用主编号10 ，一起归于misc device，
* 其实misc_register就是用主标号10调用register_chrdev()，也就是说，misc设备其实也就是特殊的字符设备。
* 
* 对于字符设备，使用register_chrdev(LED_MAJOR,DEVICE_NAME,&dev_fops)注册字符设备驱动程序时，
* 如果有多个设备使用该函数注册驱动程序，LED_MAJOR不能相同，否则几个设备都无法注册(我已验证)
* 如果模块使用该方式注册并且 LED_MAJOR为0(自动分配主设备号 )，使用insmod命令加载模块时会在终端显示分配的主设备号和次设备号，
* 在/dev目录下建立该节点，比如设备leds，
* 如果加载该模块时分配的主设备号和次设备号为253和0，则建立节点:mknod leds c 253 0
* 使用register_chrdev (LED_MAJOR,DEVICE_NAME,&dev_fops)注册字符设备驱动程序时都要手动建立节点 ，否则在应用程序无法打开该设备
***/

#define DEMO_NAME "my_demo_misc_dev"
// static struct device *my_misc_device;

static int demodrv_open(struct inode *inode, struct file *file)
{
    int major = MAJOR(inode->i_rdev);
    int minor = MINOR(inode->i_rdev);
    printk("%s: major=%d, minor=%d\n", __func__, major, minor);
    return 0;
}

static int demodrv_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t demodrv_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
    printk("%s enter\n", __func__);
    return 0;
}

static ssize_t demodrv_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos)
{
    printk("%s enter\n", __func__);
    return 0;
}

static const struct file_operations demodrv_fops = {
    .owner = THIS_MODULE,
    .open = demodrv_open,
    .release = demodrv_release,
    .read = demodrv_read,
    .write = demodrv_write};

static struct miscdevice demo_misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEMO_NAME,
    .fops = &demodrv_fops};

static int __init simple_char_init(void)
{
    int ret;
    // dev = 10;
    ret = misc_register(&demo_misc_dev);
    if (ret)
    {
        printk("failed to allocate misc device\n");
        return ret;
    }

    // my_misc_device = demo_misc_dev.this_device;
    printk("succeed register misc device:%s, minor:%d \n",
           demo_misc_dev.name, demo_misc_dev.minor);
    return 0;
}

static int __exit simple_char_exit(void)
{
    printk("removing device: %s\n", DEMO_NAME);
    misc_deregister(&demo_misc_dev);
    return 0;
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_AUTHOR("bowenerchen");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("simple misc device");