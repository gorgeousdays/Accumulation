# fork.c

*Authors: gorgeousdays@outlook.com*

*Create time:2021.9.28*

*kernel-version：5.15*

## 概述

![linuxfork](https://gitee.com/undefineded/images/raw/master/linuxfork.png)

对于linux的各个创建进程命令

- fork()是将父进程的全部资源拷贝给子进程；
- vfork()是将父进程除mm_struct的所有资源拷贝给子进程；
- clone()是通过CLONE_XXX指定将哪些资源从父进程拷贝到子进程

fork,vfork,clone本质上都是对kernel_clone函数的调用，区别在于传入的参数不同

## fork

查看commit记录`cad6967ac10843a70842cd39c7b53412901dd21f`发现在v5.10-rc1将原来的_do_fork替换成了kernel_clone

```c
#ifdef __ARCH_WANT_SYS_FORK
SYSCALL_DEFINE0(fork)//定义系统调用 参见kernel/sys.c 0表示fork系统调用需要0个参数
{
#ifdef CONFIG_MMU
	struct kernel_clone_args args = {
		.exit_signal = SIGCHLD,
	};

	return kernel_clone(&args);
#else
	/* can not support in nommu mode */
	return -EINVAL;
#endif
}
#endif
```

fork函数会返回两次，一次在父进程，另一次在子进程，如果返回值为0，说明是子进程；如果返回值为正数，说明是父进程

## vfork

```c
#ifdef __ARCH_WANT_SYS_VFORK
SYSCALL_DEFINE0(vfork)
{
	struct kernel_clone_args args = {
		.flags		= CLONE_VFORK | CLONE_VM,
		.exit_signal	= SIGCHLD,
	};

	return kernel_clone(&args);
}
#endif
```

## kernel_clone

```c
pid_t kernel_clone(struct kernel_clone_args *args)//pid_t为进程号类型 函数返回进程号
{
	u64 clone_flags = args->flags;
	struct completion vfork;
	struct pid *pid;
	struct task_struct *p; //创建进程描述符结构体指针
	int trace = 0;
	pid_t nr; 

	/*
	 * For legacy clone() calls, CLONE_PIDFD uses the parent_tid argument
	 * to return the pidfd. Hence, CLONE_PIDFD and CLONE_PARENT_SETTID are
	 * mutually exclusive. With clone3() CLONE_PIDFD has grown a separate
	 * field in struct clone_args and it still doesn't make sense to have
	 * them both point at the same memory location. Performing this check
	 * here has the advantage that we don't need to have a separate helper
	 * to check for legacy clone().
	 */
	if ((args->flags & CLONE_PIDFD) &&
	    (args->flags & CLONE_PARENT_SETTID) &&
	    (args->pidfd == args->parent_tid))
		return -EINVAL;

	/*
	 * Determine whether and which event to report to ptracer.  When
	 * called from kernel_thread or CLONE_UNTRACED is explicitly
	 * requested, no event is reported; otherwise, report if the event
	 * for the type of forking is enabled.
	 */
	if (!(clone_flags & CLONE_UNTRACED)) {
		if (clone_flags & CLONE_VFORK)
			trace = PTRACE_EVENT_VFORK;
		else if (args->exit_signal != SIGCHLD)
			trace = PTRACE_EVENT_CLONE;
		else
			trace = PTRACE_EVENT_FORK;

		if (likely(!ptrace_event_enabled(current, trace)))
			trace = 0;
	}
    
    
    // 复制进程描述符，返回创建的task_struct的指针
	p = copy_process(NULL, trace, NUMA_NO_NODE, args);
	
   /*add_latent_entropy()参见linux/random.h 相当于  add_device_randomness() 用于随机数的生成
    *Linux 内核采用熵来描述数据的随机性
    *Linux内核维护了一个熵池用来收集来自设备驱动程序和其它来源的环境噪音。
    *可以实现产生真随机数序列。
    */
    add_latent_entropy();
    
    //IS_ERR()其实是在判断指针
	if (IS_ERR(p))
		return PTR_ERR(p);   //再将指针转换成long类型数据

	/*
	 * Do this prior waking up the new thread - the thread pointer
	 * might get invalid after that point, if the thread exits quickly.
	 */
	trace_sched_process_fork(current, p);
    
    // 得到新创建的进程描述符中的pid
	pid = get_task_pid(p, PIDTYPE_PID);//用于根据task和pid type找到对应的struct pid
	nr = pid_vnr(pid);//返回值为pid_t类型的变量，在此代表获取的进程的全局进程号  参数pid是struct pid类型的指针变量

	if (clone_flags & CLONE_PARENT_SETTID)
		put_user(nr, args->parent_tid);
    
    //如果使用的是vfork，则初始化vfork完成处理信息，确保父进程后运行
	if (clone_flags & CLONE_VFORK) {
		p->vfork_done = &vfork;
		init_completion(&vfork);
		get_task_struct(p);
	}
    
    // 将子进程添加到调度器的队列，使得子进程有机会获得CPU
	wake_up_new_task(p);

	//fork 完成，子进程即将开始运行
	if (unlikely(trace))
		ptrace_event_pid(trace, pid);
    // 如果为vfork 则将父进程插入等待队列，并挂起父进程直到子进程释放自己的内存空间
	// 保证子进程优先与父进程运行
    if (clone_flags & CLONE_VFORK) {
		if (!wait_for_vfork_done(p, &vfork))
			ptrace_event_pid(PTRACE_EVENT_VFORK_DONE, pid);
	}

	put_pid(pid);//用于释放进程所占用的Cache空间
	return nr;
}
```

## copy_process

1. 执行dup_task_struct()，拷贝当前进程task_struct
2. 检查进程数是否超过系统所允许的上限(默认32678)
3. 执行sched_fork()，设置调度器相关信息，设置task进程状态为TASK_RUNNING，并分配CPU资源
4. 执行copy_xxx()，拷贝进程的files, fs, mm, io, sighand, signal等信息
5. 执行copy_thread_tls(), 拷贝子进程的内核栈信息
6. 执行alloc_pid()，为新进程分配新pid

## 参考链接

https://www.cnblogs.com/sky-heaven/p/5715066.html

https://blog.csdn.net/notbaron/article/details/80033417

https://www.coolcou.com/linux-kernel/linux-process-management-kernel-api

