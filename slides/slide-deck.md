---
theme: dracula
_class: lead
paginate: true
#backgroundColor: #fff
#backgroundImage: url('https://marp.app/assets/hero-background.svg')
---

![bg left:40% 80%](https://ebpf.foundation/wp-content/uploads/sites/9/2023/03/ebpf-icon-292x300.png)

### eBPF from zero to hero

Hipolit Badowski  
Karriere.at  
27.02.24


---

# Introduction

- **Who Am I?**
  - DevOps Engineer 
  - Started as System Administrator
  - Enjoys unconventional solutions

![bg right:45% 90%](ich.png)

---

![bg](https://path_to_your_section_divider_image_or_use_a_simple_line.png)

# My eBPF Journey

- My personal journey into eBPF:
  - Cilium
  - Observability and Network Policies including the tools (e.g., Hubble) sparked my interest


---

# Prerequisites & Resources

### **Prerequisites:**
- Basic Linux knowledge.
- Understanding of programming fundamentals, e.g., C.

### **Tools and Resources:**
- **Online Documentation:** Explore detailed eBPF resources at [Prototype Kernel Documentation](https://prototype-kernel.readthedocs.io/en/latest/bpf/index.html).
- **Interactive Learning:** For a more engaging learning experience, check out resources recommended by Liz.

---

# How to Start Your eBPF Journey

- Liz's book is freely shared by Isovalent: [Learning eBPF](https://cilium.isovalent.com/hubfs/Learning-eBPF%20-%20Full%20book.pdf)
- Install necessary tools: `` `pacman -S bcc bcc-tools python-bcc` ``
- Explore `bcc` and `clang`
- Dive into `XDP`
- Try out the `cursor.sh` example (with Liz's load balancer)

---
# Getting Started with eBPF and Python

### **1. Python and BCC Example**

To begin exploring eBPF, let's start with a simple Python script using the BCC library. This script attaches an eBPF program to the `execve` system call, printing "Hello World!" whenever a new program is executed.

---

```python
#!/usr/bin/python
from bcc import BPF

program = r"""
int hello(void *ctx) {
    bpf_trace_printk("Hello World!");
    return 0;
}
"""

b = BPF(text=program)
syscall = b.get_syscall_fnname("execve")
b.attach_kprobe(event=syscall, fn_name="hello")
b.trace_print()
```

---

## Demo

![width:900px](diagram.png "eBPF in Action")

---

# Writing and Compiling an eBPF Program


Using `clang` and `llvm` to compile the eBPF program into an ELF object file.
```bash
	clang \
	    -target bpf \
		-I/usr/include/$(shell uname -m)-linux-gnu \
		-g \
	    -O2 -o $@ -c $<
```

---

The output `counter.o` is an ELF object file containing the compiled eBPF program. This file can be loaded into the Linux kernel using eBPF tools like `bpf` command-line tool or libraries like `BCC` or `libbpf`.

```bash
sudo bpf load hello_kprobe.o /sys/kernel/debug/tracing/events/syscalls/sys_enter_clone/id
```

This command loads the `hello_kprobe.o` program and attaches it to the `sys_clone` system call.


---

# Attaching eBPF XDP program to networkf interface

- bpftools prog load
- bpftools prog show
- bpftools attach
- bpftools show trace

---

# eBPF reading a eBPF map with Python

```python
```


- 

---

# Recap

- eBPF is no magic, and solid craft
- Now has the time come to support and implement it

---

# Q&A


- Dimi support
- There are no stupid questions

---

# Thank You

Let's Connect and Explore eBPF Together!

- Feel free to contact me:

[LinkedIn](https://at.linkedin.com/in/hipolitb)  
Email: [badowhp@gmail.com](mailto:badowhp@gmail.com)

---


