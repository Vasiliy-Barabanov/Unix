#include <linux/init.h>             // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>           // Core header for loading module into the kernel
#include <linux/kernel.h>   
#include <linux/fs.h>
#include <linux/uaccess.h>  
#include <linux/slab.h>  
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <mydriverio.h>
 
MODULE_LICENSE("GPL");              ///< The license type -- this affects function visibility
MODULE_AUTHOR("Alex Maximov");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux module");  ///< The description -- see modinfo
MODULE_VERSION("1.0");              

 
/** @brief The module initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that  the function is only used at initialization and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
 
static char kbuf[1000] = "hello";
static dev_t first;
static unsigned int count=1;
static int my_major =300, my_minor=0;
static struct cdev *my_cdev;

#define MYDEV_NAME "mychrdev"
#define KBUF_SIZE (size_t) ((10)* PAGE_SIZE) 
 

static int mychrdev_open(struct inode *inode, struct file *file){
   return 0;
}
static int mychrdev_release(struct inode *inode, struct file *file){
   return 0;
}
static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos){ //доставка в юзерспейс
       if (lbuf>1000)
         lbuf = 1000;
       copy_to_user(buf, kbuf,lbuf);
       printk(KERN_INFO "Read dev");  
   return lbuf;
}
static ssize_t mychrdev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos){
   return 0;
}

static inline long foo_unlocked_ioctl(struct file *fp,unsigned long cmd, unsigned long arg){
	int ret=0;
	switch(cmd){
		case IOC_GET;
		printk("a \n");
		break;
		case F;
		printk("b \n");
		break;
	}
	return 0;
}


static const struct file_operations mycdev_fops={
   .owner=THIS_MODULE,
   .unlocked_ioctl=foo_unlocked_ioctl,
   .read=mychrdev_read,
   .write=mychrdev_write,
   .open=mychrdev_open,
   .release=mychrdev_release,
};



static int __init simple_init(void){
   //kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
   first = MKDEV (my_major,my_minor);
   register_chrdev_region(first,count,MYDEV_NAME);
   my_cdev = cdev_alloc();
   cdev_init(my_cdev, &mycdev_fops);
   cdev_add(my_cdev,first,count);
   return 0;
}

 
/** @brief The modul cleanup function
 */
static void __exit simple_exit(void){
   unregister_chrdev_region(first,count);
   printk(KERN_INFO "Goodbye from the mai 307 team!\n");
}
 
module_init(simple_init);
module_exit(simple_exit);
