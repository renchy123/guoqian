#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>

struct score
{
	int num;
	int english;
	int math;
	struct list_head list;
};

struct list_head score_head;
struct score stu1, stu2, stu3;
struct list_head *pos;
struct score *tmp;

int mylist_init(void)
{
	INIT_LIST_HEAD(&score_head);
	
	stu1.num = 1;
	stu1.english = 90;
	stu1.math = 98;
	list_add_tail(&(stu1.list),&score_head);

	stu2.num = 2;
	stu2.english = 92;
	stu2.math = 91;
	list_add_tail(&(stu2.list),&score_head);

	stu3.num = 3;
	stu3.english = 94;
	stu3.math = 95;
	list_add_tail(&(stu3.list),&score_head);

	list_for_each(pos,&score_head)
	{
		tmp = list_entry(pos,struct score,list);
		printk("No %d english is %d,\n math is %d\n",tmp->num,tmp->english,tmp->math);
	}
	
	return 0;
}

void mylist_exit(void)
{
	list_del(&(stu1.list));
	list_del(&(stu2.list));
}

module_init(mylist_init);
module_exit(mylist_exit);
MODULE_LICENSE("GPL");
