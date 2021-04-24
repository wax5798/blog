/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月20日 星期二 20时28分03秒
 ************************************************************************/

#include <linux/module.h>	// 包含了对模块的结构定义以及模块的版本控制
#include <linux/kernel.h>	// 包含常用的内核函数
#include <linux/fs.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init skb2pcap_init(void)
{
	struct file *fp = filp_open("/tmp/kernel_rw", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	const char *wstr = "write from kernel";
	int len = 0;
	mm_segment_t old_fs;

	if (IS_ERR(fp)) 
	{
		printk("[%s] open file failed\n", __func__);
		return -1;
	}

	old_fs = get_fs();
	/* 改变 kernel 对内存地址检查的处理方式, 如果此处被抢占是否会有风险 */
	set_fs(KERNEL_DS);
	len = vfs_write(fp, wstr, strlen(wstr), &fp->f_pos);
	set_fs(old_fs);
	filp_close(fp, NULL);

	printk("[%s] write len: %d\n", __func__, len);
    return 0;
}

static void __exit skb2pcap_exit(void)
{
	struct file *fp = filp_open("/tmp/kernel_rw", O_RDONLY, 0);
	int len = 0;
	char buf[128] = {0};
	mm_segment_t old_fs;

	if (IS_ERR(fp))
	{
		printk("[%s] open file failed\n", __func__);
		return;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	len = vfs_read(fp, buf, sizeof(buf) - 1, &fp->f_pos);
	set_fs(old_fs);
	filp_close(fp, NULL);

	printk("[%s] get str[%d]: %s\n", __func__, len, buf);
}

module_init(skb2pcap_init);
module_exit(skb2pcap_exit);
