#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/io.h>
#include "led.h"

#define LEDCON 0x56000050
#define LEDDAT 0x56000054

unsigned int *led_config; 
unsigned int *led_data; 

struct cdev cdev;
dev_t devno;

int led_open(struct inode *node, struct file *filp)
{
	int reg_val = 0;
	led_config = ioremap(LEDCON,4);
	
	reg_val = readl(led_config);
	reg_val &= ~((0x3<<(4*2)) | (0x3<<(5*2)) | (0x3<<(6*2)));
	reg_val |= ((0x1<<(4*2)) | (0x1<<(5*2)) | (0x1<<(6*2)));
		
	writel(reg_val,led_config);

	led_data = ioremap(LEDDAT,4);
	return 0;
}

long led_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int on, off;

	on = readl(led_data);
	on &= ~((1<<4) | (1<<5) | (1<<6)); 

	off = readl(led_data);
	off |= (1<<4) | (1<<5) | (1<<6);	

	switch (cmd)
	{
	    case LED_ON:
	        writel(on,led_data);
	        return 0;

	    case LED_OFF:
	        writel(off,led_data);
	        return 0;

	    default:
	    	return -EINVAL;
	}
}

static struct file_operations led_fops =
{
    .open = led_open,
    .unlocked_ioctl = led_ioctl,
};

static int led_init(void)
{
    cdev_init(&cdev,&led_fops);
    alloc_chrdev_region(&devno, 0 , 1 , "myled");
    cdev_add(&cdev, devno, 1);

    return 0;	
}

static void led_exit(void)
{
	cdev_del(&cdev);
	unregister_chrdev_region(devno,1);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
