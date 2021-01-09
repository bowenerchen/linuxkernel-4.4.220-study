#ifndef _LINUX_CDEV_H
#define _LINUX_CDEV_H

#include <linux/kobject.h>
#include <linux/kdev_t.h>
#include <linux/list.h>

struct file_operations;
struct inode;
struct module;

struct cdev
{
	struct kobject kobj;			   // linux设备驱动模型
	struct module *owner;			   // 字符设备驱动程序所在的内核模块对象指针
	const struct file_operations *ops; // 操作方法集，一般包含open，release，read，write等方法，和用户态程序交互时需要使用ops对上述方法进行注册
	struct list_head list;			   // 将字符设备串成一个链表
	dev_t dev;						   // 字符设备的设备号，由主设备号和次设备号组成，高12比特是主设备号，低20比特是次设备号
	unsigned int count;				   // 同属一个主设备号的次设备号的个数
};

void cdev_init(struct cdev *, const struct file_operations *);

struct cdev *cdev_alloc(void);

void cdev_put(struct cdev *p);

int cdev_add(struct cdev *, dev_t, unsigned);

void cdev_del(struct cdev *);

void cd_forget(struct inode *);

#endif
