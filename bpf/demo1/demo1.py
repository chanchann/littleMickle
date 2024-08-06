#!/usr/bin/env python3
from bcc import BPF

# load bpf program 
b = BPF(src_file="demo1.c")

# attach kprobe
b.attach_kprobe(event="do_sys_openat2", fn_name="hello_world")

# read and print /sys/debug/tracing/trace_pipe
b.trace_print()
