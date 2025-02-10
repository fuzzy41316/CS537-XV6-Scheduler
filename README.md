# CS537 Fall 2024 - Project 4

## 🔍 Problem Statement  
In this project, I implemented a **dynamic stride scheduler** with **dynamic ticket modification** in **xv6**. The stride scheduler ensures **proportional-share CPU scheduling**, where processes receive CPU time based on their ticket allocation. I incorporated the following features:

- **Stride Scheduling**: Each process has an assigned number of tickets, and the scheduler selects the process with the lowest `pass` value, incremented by the process's `stride` value.  
- **Dynamic Ticket Modification**: A system call (`settickets`) allows processes to modify their ticket allocation, recalculating their `stride` and adjusting their `pass` accordingly.  
- **Global Scheduling Variables**: Introduced global variables like `global_tickets`, `global_stride`, and `global_pass` to manage the overall scheduling behavior for all processes.  
- **Remain Value**: When processes are interrupted or sleep, their remaining stride (`remain`) is calculated to maintain fairness when they rejoin the scheduler.  
- **Process Info Retrieval**: Implemented the `getpinfo` system call to provide detailed scheduling statistics for each process.  

The project involved working with **kernel-level scheduling**, **system calls**, and modifying **xv6's process scheduler** to support dynamic participation and ticket allocation adjustments.

---

## 🎯 What I Learned  
This assignment provided a deep dive into **CPU scheduling algorithms** and **operating system internals**. Key takeaways include:

✅ **Stride Scheduling** – How to implement proportional-share scheduling to allocate CPU time fairly based on a process’s tickets.  
✅ **Dynamic Ticket Allocation** – Modifying process ticket allocation and recalculating stride values, while keeping track of the global scheduling parameters.  
✅ **Process Scheduling Management** – Handling the entry and exit of processes, and how global parameters are affected by these changes.  
✅ **Remain Value** – Understanding the importance of maintaining fairness for processes that may sleep and rejoin the scheduler.  
✅ **System Call Development** – Creating new system calls to retrieve scheduling information and modify process states.  

---

## 🏆 Results  
I successfully implemented the **dynamic stride scheduler**, passing **all test cases** and verifying the correctness of both **RR** and **stride scheduling** through the use of **CSV logs**. My solution provided **accurate, fair scheduling** behavior in both cases, and I was able to generate the expected output for **process statistics**. This project improved my understanding of **scheduling algorithms** and **system call integration** in an operating system kernel.
