from time import sleep, strftime
from bcc import BPF
from bcc.utils import printb
from bcc.syscall import syscall_name, syscalls
from ctypes import *

b = BPF(text="""

BPF_HASH(start, u32, u64);

TRACEPOINT_PROBE(raw_syscalls, sys_exit)
{
    u32 syscall_id = args->id;
    u32 key = 1;
    u64 *val;
    u32 uid = bpf_get_current_uid_gid();

    if (uid == 0)
    {
        val = start.lookup(&key); //find value associated with key 1
        if (val)
            bpf_trace_printk("Hello world, I have value %d!\\n", *val);

    }
    return 0;
}
""")

thisStart = b["start"]
thisStart[c_int(1)] = c_int(9)  # insert key-value part 1->9

while 1:
    try:
        (task, pid, cpu, flags, ts, msg) = b.trace_fields()
    except KeyboardInterrupt:
        print("Detaching")
        exit()
    print("%-18.9f %-16s %-6d %s" % (ts, task, pid, msg))
