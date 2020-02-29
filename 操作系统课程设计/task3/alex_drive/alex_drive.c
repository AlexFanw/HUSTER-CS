

#include <linux/module.h> 
#include <linux/version.h> 
#include <linux/types.h> 
#include <linux/fs.h> 
#include <linux/mm.h> 
#include <linux/errno.h> 
#include <asm/segment.h> 


long int ALEX_MAJOR = 0;
static ssize_t read_alex(struct file *flip,char *buf,size_t count, loff_t*f_pos)
{ 
	int left;   
	for(left = count ; left > 0 ; left--)   
{   
	put_user(9,buf);   
	buf++;   
}   
	return count; 
} 
static ssize_t write_alex(struct file *flip,const char *file,size_t count, loff_t*f_pos) 
{ 
	return count; 
} 
 
static int open_alex(struct inode *inode,struct file *file ) 
{
	
	return 0; 
} 
 
static int release_alex(struct inode *inode,struct file *file )
{

}

struct file_operations alex_fops={
	.read = read_alex,
	.write=write_alex,
	.open=open_alex,
	.release=release_alex
};




static int init_mymodule(void) 
{ 
	int result;
	result = register_chrdev(0, "alex", &alex_fops); 
	if (result < 0) { 
		printk(KERN_INFO "alex: can't get major number\n"); 
		return result;
	} 
	if (ALEX_MAJOR == 0) ALEX_MAJOR = result; /* dynamic */ 
	return 0; 
}


static void cleanup_mymodule(void) 
{ 
	unregister_chrdev(ALEX_MAJOR,"alex"); 
} 

MODULE_LICENSE("GPL");
module_init(init_mymodule);
module_exit(cleanup_mymodule);










