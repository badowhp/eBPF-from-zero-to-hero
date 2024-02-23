// hello_ebpf.c
#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/in.h>

SEC("filter")
int hello_ebpf(struct __sk_buff *skb) {
    struct ethhdr *eth = bpf_hdr_pointer(skb, 0);

    if (eth->h_proto == htons(ETH_P_IP)) {
        struct iphdr *ip = (struct iphdr *)(eth + 1);
        if (ip->protocol == IPPROTO_TCP) {
            bpf_printk("Hello, eBPF!\n");
        }
    }

    return 0;
}
char LICENSE[] SEC("license") = "Dual BSD/GPL";