three threads:
High-Priority Thread (H): Needs to perform critical operations and is waiting for a mutex.
Medium-Priority Thread (M): Holds the mutex that H needs and is running.
Low-Priority Thread (L): Is running and does not need the mutex.


H starts and tries to acquire the mutex but finds it locked by M.
M is running and holding the mutex.
L starts running and consumes CPU time.
M finishes its work but H still cannot run because L is using the CPU.

So here, L's execution indirectly prevents H from making progress, creating a priority inversion.

Techniques to Handle Priority Inversion

Priority Inheritance:
When a low-priority thread holds a mutex that a higher-priority thread needs, the low-priority thread temporarily inherits the priority of the higher-priority thread.
Once the mutex is released, the thread’s priority is reverted to its original level.
This helps prevent the medium-priority thread from preempting the lower-priority thread while it is holding the mutex.

Priority Ceiling:
Each mutex is assigned a priority ceiling, which is the highest priority of any thread that can lock the mutex.
When a thread locks the mutex, its priority is raised to the priority ceiling of the mutex.
This prevents other threads from preempting the thread holding the mutex.
Avoiding Long Critical Sections:

Design the critical sections to be as short as possible to minimize the time the mutex is held.
This reduces the chance of priority inversion by limiting the duration during which higher-priority threads are blocked.


Non-Blocking Synchronization:
Use synchronization mechanisms that do not involve blocking, such as lock-free data structures or algorithms.
This avoids the issue of priority inversion by eliminating the need for mutexes in certain scenarios.
