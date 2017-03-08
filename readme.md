CS 475 Project 2 : Priority Scheduling and Aging
David Olson & Alex Harris

In this project we have implemented a priority scheduling policy with aging.

To implement the scheduling policy we first made a modification inside of the procent struct definition, adding the field of "prprio" with the type pri16. This modification was done in include/kernel.h.

Next, we modified the create() function in the system directory so that it accepts a third parameter of type pri16. With this parameter we initialize the prprio field of the process entry.

Finally we modified our queue structure to consider the priority of each queue entry. We do this specifically by iterating through the queue entries and comparing priorities in the queue for each invocation of enqueue(). If we find that the insertion queue entry has a relatively higher priority than other entries inside the queue, then we insert the new entry according to its relative priority.

To prevent process starvation in our priority queue, we have also implemented an aging policy.

According to the assignment, we have modified the priority of each entry in the queue & for each invocation of the resched() function. This occurs only when the kernel configuration variable "AGING" is set to TRUE.

The major modifications for our aging policy were made inside system/resched.c, especially in the 'if (AGING)' block that is nested in the resched() function. We are able to age each entry (except the null process, the most recently reempted process, and the process that is most recently selected for scheduling) by traversing the queue and incrementing each entry's priority, or 'key'.