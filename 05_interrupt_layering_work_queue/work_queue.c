#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

struct workqueue_struct *my_wq;
struct work_struct *work1;
struct work_struct *work2;

void work1_func(struct work_struct *work)
{
	printk("This is work1 !!\n");
}

void work2_func(struct work_struct *work)
{
	printk("This is work2 !!\n");
}

int init_queue(void)
{
	work1 = kmalloc(sizeof(struct work_struct),GFP_KERNEL);
	INIT_WORK(work1,work1_func);
	schedule_work(work1);

	work2 = kmalloc(sizeof(struct work_struct),GFP_KERNEL);
	INIT_WORK(work2,work2_func);
	schedule_work(work2);

	return 0;
}

void clean_queue(void)
{

}
module_init(init_queue);
module_exit(clean_queue);
MODULE_LICENSE("GPL");
