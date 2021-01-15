#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>

/***
 * 字符设备驱动管理的核心对象是以字符为单位进行IO数据流传输的设备，常见的如键盘，鼠标，触摸屏等都属于字符设备
 * struct cdev{} -- 对字符设备的抽象数据结构
 * cdev_alloc() -- cdev实例化
 * cdev_init() -- 初始化cdev，并建立设备与驱动操作方法集file_operations之间的关联关系
 * cdev_add() -- 把一个字符设备添加到系统中，通常在驱动程序probe函数里会调用该接口来注册一个字符设备
 * cdev_del() -- 从系统中删除一个字符设备，通常在驱动程序的卸载函数中会调用该接口
 * alloc_chrdev_region() -- 自动为设备分配主设备号，避免主设备号冲突
 * unregister_chrdev_region() -- 归还设备的主设备号给系统
 * 
 * 用户自定义实现：
 * static int demodrv_open()
 * static int demodrv_release()
 * static ssize_t demodrv_read()
 * static ssize_t demodrv_write()
 * 以上4个函数，为自定义实现的与用户态交互的逻辑
 * 
 * cat /proc/devices:
 * 252 my_demo_dev
 * ***/

#define DEMO_NAME "my_demo_char_dev"
static dev_t dev;              // 设备号
static struct cdev *demo_cdev; // 指向设备实例的指针
static signed count = 1;       // 同属一个主设备号的次设备号的个数，这里初始化为1

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

static int __init simple_char_init(void)
{
    int ret;
    // 分配主设备号
    ret = alloc_chrdev_region(&dev, 0, count, DEMO_NAME);
    if (ret)
    {
        printk("failed to allocate char device region\n");
        return ret;
    }

    // 实例化cdev
    demo_cdev = cdev_alloc();
    if (!demo_cdev)
    {
        printk("cdev_alloc failed\n");
        goto unregister_chrdev;
    }

    // 初始化demo_cdev，将demo_cdev与回调函数进行绑定
    cdev_init(demo_cdev, &demodrv_fops);

    // 注册该字符设备
    ret = cdev_add(demo_cdev, dev, count);
    if (ret)
    {
        printk("cdev_add failed\n");
        goto cdev_fail;
    }

    printk("succeed register char device: %s, module name: %s, version: %s\n", DEMO_NAME, THIS_MODULE->name, THIS_MODULE->version);
    printk("Major number = %d, minor number = %d\n", MAJOR(dev), MINOR(dev));
    return 0;

cdev_fail:
    // 从系统中卸载字符设备
    cdev_del(demo_cdev);

unregister_chrdev:
    // 归还主设备号给系统
    unregister_chrdev_region(dev, count);

    return ret;
}

static void __exit simple_char_exit(void)
{
    printk("removing device\n");
    if (demo_cdev)
    {
        // 从系统中卸载字符设备
        cdev_del(demo_cdev);
    }
    // 归还主设备号给系统
    unregister_chrdev_region(dev, count);
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_AUTHOR("bowenerchen");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("simple character device");