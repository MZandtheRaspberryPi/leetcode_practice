/*
Whats the difference between a thread and a process?

A process has resources allocated to it in terms of memory and has a main execution loop for the main function. One process cant access mem of other process unless sharing.
A thread shares those resources but many can execute at once and access each others memory.

processes threads related, but different fundamentally.

process, instance of program in execution. gets resources from system allocated (cpu time, memory). each process seperate address space,
one process cant access anothers variables and datastructures. if want to access, need to use inter-process communications. pipes, files, sockets, ect.

thread: same stack space of process, and multiple threads share parts of their states. usually, multiple threads read/write same memory, diff from process.

each thread has registers and own stack, but toher threads can read/write stack memory.

thread is particular execution path of process. when thread modifies process resource, immediately visible to other threads.


*/

