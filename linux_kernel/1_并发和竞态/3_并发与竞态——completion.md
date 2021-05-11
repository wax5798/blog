<head><meta charset="UTF-8"></head>
<style>
h1 {
    text-align: center;
    border-left: 5px solid #e86422;
    border-right: 5px solid #e86422;
}
h2 {
    border-left: 5px solid #ff7f00;
    padding-left: 10px;
}
h3 {
    border-left: 5px solid #e86422;
    padding-left: 8px;
}
h4 {
    border-left: 3px solid #f0a000;
    padding-left: 5px;
}
</style>

Release log:
> 2021-05-10 一: 完成初版

[原文地址](https://github.com/wax5798/blog/blob/master/linux_kernel/1_%E5%B9%B6%E5%8F%91%E5%92%8C%E7%AB%9E%E6%80%81/3_%E5%B9%B6%E5%8F%91%E4%B8%8E%E7%AB%9E%E6%80%81%E2%80%94%E2%80%94completion.md)

# 并发与竞态——completion
内核编程中常见的一种模式是，在当前线程之外初始化某个活动，然后等待该活动的结束。这个活动可能是，创建一个新的内核线程或者新的用户空间进程、对一个已有进程的某个请求，或者某种类型的硬件动作，等等。在这种情况下，我们可以使用信号量来同步这两个任务。然而，内核中提供了另外一种机制—— completion 接口。completion 是一种轻量级的机制，他允许一个线程告诉另一个线程某个工作已经完成。

## completion 的初始化
为了使用 completion，必须包含头文件 `<linux/completion.h>`

completion 的初始化如下:
```
DECLARE_COMPLETION(var_name)
或者
struct completion my_completion;
init_completion(&my_completion);
```

## completion 的使用
要等待 completion,可进行如下调用:
```
void wait_for_completion(struct completion *x);
```
该函数执行一个非中断的等待。如果代码调用了 wait_for_completion 且没有人会完成该任务，则将产生一个不可杀的进程

实际的 completion 事件可以通过调用下面的函数之一来触发
```
void complete(struct completion *x);
void complete_all(struct completion *x);
```

complete 只会唤醒一个等待线程，而 complete_all 允许唤醒所有等待线程

## completion 的源码
completion 的结构
```
struct completion {
	unsigned int done;
	wait_queue_head_t wait;
};
```

do_wait_for_common 的实现涉及到多层调用
```
static inline long __sched
do_wait_for_common(struct completion *x,
		   long (*action)(long), long timeout, int state)
{
	if (!x->done) {
		DECLARE_WAITQUEUE(wait, current);

		__add_wait_queue_tail_exclusive(&x->wait, &wait);
		do {
			if (signal_pending_state(state, current)) {
				timeout = -ERESTARTSYS;
				break;
			}
			__set_current_state(state);
			spin_unlock_irq(&x->wait.lock);
			timeout = action(timeout);
			spin_lock_irq(&x->wait.lock);
		} while (!x->done && timeout);
		__remove_wait_queue(&x->wait, &wait);
		if (!x->done)
			return timeout;
	}
	x->done--;
	return timeout ?: 1;
}

static inline long __sched
__wait_for_common(struct completion *x,
		  long (*action)(long), long timeout, int state)
{
	might_sleep();

	spin_lock_irq(&x->wait.lock);
	timeout = do_wait_for_common(x, action, timeout, state);
	spin_unlock_irq(&x->wait.lock);
	return timeout;
}

static long __sched
wait_for_common(struct completion *x, long timeout, int state)
{
	return __wait_for_common(x, schedule_timeout, timeout, state);
}

void __sched wait_for_completion(struct completion *x)
{
	wait_for_common(x, MAX_SCHEDULE_TIMEOUT, TASK_UNINTERRUPTIBLE);
}
```

complete 的实现
```
void complete(struct completion *x)
{
	unsigned long flags;

	spin_lock_irqsave(&x->wait.lock, flags);
	x->done++;
	__wake_up_locked(&x->wait, TASK_NORMAL, 1);
	spin_unlock_irqrestore(&x->wait.lock, flags);
}
```

complete_all 的实现
```
void complete_all(struct completion *x)
{
	unsigned long flags;

	spin_lock_irqsave(&x->wait.lock, flags);
	x->done += UINT_MAX/2;
	__wake_up_locked(&x->wait, TASK_NORMAL, 0);
	spin_unlock_irqrestore(&x->wait.lock, flags);
}
```
