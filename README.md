# TriSecure: Linux Kernel Module for Real-Time Health Monitoring

##  Team Members
- Firas Abdelgadir
- Justin Duru
- Sa’Niyah Council  
- **Course**: SCIA 360 - Operating System Security  
- **Project**: Linux Kernel Module for System Health Monitoring  

---

## Project Overview

This project implements a Linux Kernel Module that monitors **real-time system health metrics**, including:

-  Memory usage
-  CPU load
- (Partial) Disk I/O activity

The goal is to track system resource usage, compare it against thresholds, and generate kernel alerts when those thresholds are exceeded — providing early warnings before performance or security issues arise.

---

##  Features & Design

###  Modular Monitoring
- Uses kernel timers to sample system metrics every **5 seconds**
- Compares metrics against **dynamic thresholds** passed via `insmod`

###  `/proc` Interface
- Exposes health info at:  


/proc/sys_health
YAML
Output example:
Free memory: 580 MB CPU load (1 min avg): 0.92
### Alerting
- Logs alerts using `printk()` if:
- Free memory drops below `mem_threshold`
- CPU load exceeds `cpu_threshold`

### Configurable Parameters
- Set thresholds during module insertion:
```bash
sudo insmod sys_health_monitor.ko mem_threshold=150 cpu_threshold=1

How to Build & Run
1. Clone the Repository
git clone https://github.com/Firasa7/TriSecure.git
cd TriSecure
Build the Kernel Module
bash

make

This generates:
sys_health_monitor.ko

Insert the Module
sudo insmod sys_health_monitor.ko mem_threshold=150 cpu_threshold=1

 Check /proc Output
cat /proc/sys_health

View Kernel Logs
sudo dmesg | grep TriSecure


Unload the Module
sudo rmmod sys_health_monitor


 Challenges Faced
One major challenge was testing on Azure Ubuntu VMs. Due to Secure Boot enforcement, our unsigned kernel module was rejected on insertion:
ERROR: could not insert module sys_health_monitor.ko: Key was rejected by service

Azure’s Secure Boot could not be disabled, so we pivoted to a local VMware Ubuntu VM, where we had full control, disabled Secure Boot, and tested the module successfully.

Evaluation & Lessons Learned
We learned that kernel-space development requires tight alignment between:

Kernel version & headers

Compiler toolchain

Permissions and system policies (e.g., Secure Boot)
