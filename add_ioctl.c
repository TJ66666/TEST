#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

//static struct class *firstdrv_class;
//static struct class_device  *firstdrv_class_dev;

//#define set 

static int first_drv_open(struct inode *inode, struck file *file)
{
	printk("first_drv_open\n");
	/*配置GPF4,5,6为输出 */
	
	return 0;
}                                                  /*写出led_open函数*/
long first_drv_ioctl (struct file * file, unsigned int  cmd, unsigned long  arg)
{
	switch(cmd)
	{
		case RESTART:
			printk(KERN_WARING"restart device!\n");
			return 0;
		case SET:
			printk(KERN_WARING"arg is : %d\n",arg);
			return 0;
		default:
			return -EINVAL;
	}
	return 0;
}
static ssize_t first_drv_write(struct file *file, const char __user *buf,size_t count,loff_t * ppos )
{
	printk("first_drv_write\n");
	return 0;
}                                                //写出led_write函数

static ssize_t first_drv_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
	//printk("first_drv_read\n");
	return 0;
}

static struct file_operations first_drv_fops = {
	.owner =  THIS_MODULE, //这是一个宏，推向编译模块时自动创建
	.open   =   first_drv_open,
 	.write   =   first_drv_write,
 	.compat_ioct = first_drv_ioctl,
 };                                           /*定义file_operation结构体，告诉内核应用程序要用
					                        什么接口*/

int first_drv_init(void)
{
	register_chrdev(major, "first_drv",  &first_drv_fops);  //注册，调用register_chrdev函数把file_operarion这个结构体告诉内核
	return 0;
}                                                        //驱动入口函数
void first_drv_exit(void)
{
	unregister_chrdev(major,"first_drv"); //卸载
}

module_init(first_drv_init);//入口修饰，知道调用的函数是first_drv_init
module_exit(first_drv_exit);
/*
struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*aio_read) (struct kiocb *, const struct iovec *, unsigned long, loff_t);
	ssize_t (*aio_write) (struct kiocb *, const struct iovec *, unsigned long, loff_t);
	int (*readdir) (struct file *, void *, filldir_t);
	unsigned int (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*aio_fsync) (struct kiocb *, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long, struct file_lock **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
};*/
