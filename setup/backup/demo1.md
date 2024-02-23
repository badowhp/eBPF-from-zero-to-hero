### Prerequisites:
1. Linux machine with a recent kernel that supports eBPF.
2. Docker installed (optional but recommended for ease of setup).

### Steps:

#### 1. Install required tools:
If not already installed, install the following tools:

```bash
# On Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y git clang llvm libelf-dev

# On CentOS/RHEL
sudo yum install -y git clang llvm libelf-devel
```

#### 2. Clone eBPF samples repository:

```bash
git clone https://github.com/libbpf/libbpf
```

#### 3. Build and install libbpf:

```bash
cd libbpf/src
make
sudo make install
```

#### 4. Compile and run a simple eBPF program:

Create a simple eBPF program, for example, a program that prints "Hello, eBPF!" for each packet received:

```c
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
```

Compile the program:

```bash
clang -O2 -target bpf -c hello_ebpf.c -o hello_ebpf.o
```

Load the eBPF program:

```bash
sudo ip link set dev lo xdp obj hello_ebpf.o
```

#### 5. Test the eBPF program:

Open a new terminal and run a command that generates network traffic, such as:

```bash
ping localhost
```

You should see "Hello, eBPF!" printed in the terminal where you loaded the eBPF program.

#### 6. Cleanup:

Unload the eBPF program:

```bash
sudo ip link set dev lo xdp off
```



