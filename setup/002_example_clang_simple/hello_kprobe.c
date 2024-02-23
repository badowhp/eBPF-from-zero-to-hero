#include <uapi/linux/bpf.h>
#include <uapi/linux/ptrace.h>

BPF_PERF_OUTPUT(events);

SEC("kprobe")
int kprobe__sys_clone(struct pt_regs *ctx) {
    char msg[] = "New process created\n";
    events.perf_submit(ctx, &msg, sizeof(msg));
    return 0;
} 
char LICENSE[] SEC("license") = "Dual BSD/GPL";