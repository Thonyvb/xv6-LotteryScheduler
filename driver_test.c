/* DRIVER TICKETS */

/*
  P2 MODIFIED SCHEDULER: LOTTERY SCHEDULER
  TESTER: DRIVER_TEST
  BY: GEORGE ANTHONY VILLACRES BOTTA
  CLASS: CS1550

  RUN: on linux
  $ make qemu-nox
  $ driver_test

  Note: with high amount of tickets
  it gets slower
*/

#include "types.h"
#include "user.h"
#include "pstat.h"
#include "stat.h"
#include "param.h"

/*
    method that keeps process occupied
*/
int
dosomething(){
    int count = 0;
    int h = 1;
        while(count < 2500000000000){
            h = h * 2;
            count++;

        }
    return count;
}

int
main(int argc, char *argv[])
{
	struct pstat astat;
	int i;

    //allocate ratios 3:2:1
    printf(1,"Allocating tickets on ratio 3:2:1\n");
	int tickets[3] = {30,20,10};
    int pids[3];

    //fork 3 children from parent proc
    for (i = 0; i < 3; i++ ){
        pids[i] = fork();
        if ( pids[i] == 0 )
        {
            if(settickets(tickets[i]) < 0){
               exit();
            }
            //schedule
            while(1){
                dosomething();
                exit();
            }
        }
    }

    int begining = uptime();

    sleep(600);
    printf(1,"Time: %d\n", uptime() - begining);

    //get processes info
    if (getpinfo(&astat)<0){
    	exit();
    }

	for(i = 2; i < NPROC; i++) {
        //avoid printing whole table 
        if(astat.inuse[i]){
		  printf(1, "pid: %d ticks: %d in use: %d tickets: %d\n", astat.pid[i], astat.ticks[i], astat.inuse[i], astat.tickets[i]);
        }
	}

    //terminate processes
    for ( int i = 0; i < 3; i++ ){
        kill(pids[i]);
        wait();
    }
    exit();
}

	
