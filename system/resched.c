/* resched.c - resched */

#include <xinu.h>

/**
 * Reschedule processor to next ready process
 *
 */
void	resched(void)		// assumes interrupts are disabled
{
	struct procent *ptold;	// ptr to table entry for old process
	struct procent *ptnew;	// ptr to table entry for new process

	// kprintf("\nabout to check Defer.ndfefers > 0\n");
	// If rescheduling is deferred, record attempt and return
	if (Defer.ndefers > 0) {
		// kprintf("\nDefer.ndefers > 0 evaluated to true\n");
		Defer.attempt = TRUE;
		return;
	}


	// Point to process table entry for the current (old) process
	ptold = &proctab[currpid];

	// kprintf("\nabout to compare ptold->prstate == PR_CURR\n");
	//  check ptold's state. If it's running, put it on the ready queue and change state to ready
	if (ptold->prstate == PR_CURR){
		// kprintf("\nptold->orstate == PR_CURR, evaluated to true\n");
		ptold->prstate = PR_READY;
		enqueue(currpid, readyqueue, ptold->prprio);
	}
	
	pid32 id = dequeue(readyqueue);	
	// kprintf("\njust called dequeue on the process in resched.c, pid : %d\n", id);
	//  dequeue next process off the ready queue and point ptnew to it
	ptnew = &proctab[id];
	
	//  change its state to "current" (i.e., running)
	ptnew->prstate = PR_CURR;
	//  set currpid to reflect new running process' PID
	currpid = id;

	// Context switch to next ready process
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	// Old process returns here when resumed
	return;
}
