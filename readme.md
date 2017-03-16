CS 475 Project 2 : Priority Scheduling and Aging
David Olson & Alex Harris

In this project we have implemented a priority scheduling policy with aging.

To implement the scheduling policy we first made a modification inside of the procent struct definition, adding the field of "prprio" with the type pri16. This modification was done in include/kernel.h.

Next, we modified the create() function in the system directory so that it accepts a third parameter of type pri16. With this parameter we initialize the prprio field of the process entry.

Finally we modified our queue structure to consider the priority of each queue entry. We do this specifically by iterating through the queue entries and comparing priorities in the queue for each invocation of enqueue(). If we find that the insertion queue entry has a relatively higher priority than other entries inside the queue, then we insert the new entry according to its relative priority.

To prevent process starvation in our priority queue, we have also implemented an aging policy.

According to the assignment, we have modified the priority of each entry in the queue & for each invocation of the resched() function. This occurs only when the kernel configuration variable "AGING" is set to TRUE.

The major modifications for our aging policy were made inside system/resched.c, especially in the 'if (AGING)' block that is nested in the resched() function. We are able to age each entry (except the null process, the most recently reempted process, and the process that is most recently selected for scheduling) by traversing the queue and incrementing each entry's priority, or 'key'.

We have included our test suite of processes on lines 44-46 in our system/main.c file. This suite includes three separate processes to co-exist with the processes that were provided in the starter system/main.c file. These processes are identified by the strings TestSuite-1, TestSuite-2, and TestSuite-3; they have the priorities of 1, 5, and 10 respectively.

After compiling our project, issuing $ ./upload.sh, issuing $ sudo minicom, and firing up our back-end, it's clear to see the efficacy of our priority queue and aging policy. Given that the TestSuite-3 process has the highest priority, it is given the first service via our priority queue, as seen in this output : 

	Hello XINU WORLD!
	This is process 4 (PRINTER-C)
	This is process 9 (TestSuite-3) 

Despite the priority differential between TestSuite-3 and TestSuite-1 (high & low priority respectively), TestSuite-1 Does not starve as it is serviced soon after the TestSuite-3 and TestSuite-3 processes. 