# Linux Kernel Module - Real-Time System Health Monitor

##  Group Info
- **Group Name**: TriSecure
- **Members**: Firas Abdelgadir, Justin Duru, Sa'Niyah Council
- **Course**: SCIA 360 - Operating System Security
- **Project**: Real-Time System Health Monitoring Kernel Module

---

##  Project Overview

This project implements a Linux Kernel Module that collects system health metrics, including:
- **Memory usage** (completed )
- **CPU load** (to be implemented)
- **Disk I/O statistics** (to be implemented)

These metrics are:
- Monitored in real-time using a **kernel timer**
- Compared against **configurable thresholds**
- Exposed to user-space via the **`/proc/sys_health`** file
- Logged via **`printk()` alerts** when thresholds are exceeded

---

##  How to Build the Module

### 1. Install dependencies:
```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
