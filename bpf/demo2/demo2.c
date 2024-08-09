#include <uapi/linux/openat2.h>
#include <linux/sched.h> // 读进程名需要

// 定义数据结构
struct data_t {
	u32 pid;
	u64 ts;
	char comm[TASK_COMM_LEN];
	char fname[NAME_MAX];
};
// 定义性能事件映射
BPF_PERF_OUTPUT(events);

// 定义性能事件映射
// refer https://elixir.bootlin.com/linux/latest/source/fs/open.c#L1196 for the param definitions.
int hello_world(struct pt_regs *ctx, int dfd, const char __user * filename,
		struct open_how *how) {
	struct data_t data = { };
    // bpf 开头的函数都是 eBPF 提供的辅助函数
    // bpf_get_current_pid_tgid 用于获取进程的 TGID 和 PID。
    // 因为这儿定义的 data.pid 数据类型为 u32，所以高 32 位舍弃掉后就是进程的 PID
	data.pid = bpf_get_current_pid_tgid();
    // 用于获取系统自启动以来的时间，单位是纳秒；
	data.ts = bpf_ktime_get_ns();
    // 用于获取进程名，并把进程名复制到预定义的缓冲区中
	if (bpf_get_current_comm(&data.comm, sizeof(data.comm)) == 0) {
        // 用于从指定指针处读取固定大小的数据，这里则用于读取进程打开的文件名
		bpf_probe_read(&data.fname, sizeof(data.fname),
			       (void *)filename);
	}
    // 有了 BPF 映射之后，前面我们调用的 bpf_trace_printk() 其实就不再需要了
    // 因为用户态进程可以直接从 BPF 映射中读取内核 eBPF 程序的运行状态
    // 提交性能事件
	events.perf_submit(ctx, &data, sizeof(data));
	return 0;
}