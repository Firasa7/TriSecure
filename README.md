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
