CS 475 Project 2 : Priority Scheduling and Aging
David Olson & Alex Harris

In this project we have implemented a priority scheduling policy with aging.

To implement the scheduling policy we first made a modification inside of the procent struct definition, adding the field of "prprio" with the type pri16. This modification was done in include/kernel.h.

Next, we modified the create() function in the system directory so that it accepts a third parameter of type pri16. With this parameter we initialize the prprio field of the process entry.

Finally we modified our queue structure to consider the priority of each queue entry