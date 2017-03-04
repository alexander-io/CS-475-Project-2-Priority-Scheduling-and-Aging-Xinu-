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

	// If rescheduling is deferred, record attempt and return
	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	// Point to process table entry for the current (old) process
	ptold = &proctab[currpid];


	//  check ptold's state. If it's running, put it on the ready queue and change state to ready
	if (ptold->prstate == PR_CURR){
		ptold->prstate = PR_READY;
		enqueue(currpid, readyqueue);
	}
	
	pid32 id = dequeue(readyqueue);	

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
