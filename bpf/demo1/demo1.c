int hello_world(void* ctx) {
    bpf_trace_printk("hello world");
    return 0;
}
