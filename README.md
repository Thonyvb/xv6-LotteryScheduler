# xv6-LotteryScheduler

Simple version of Lottery Scheduler 

It assigns each running process a slice of the processor based in proportion to the number of tickets it has; the more tickets a process has, the more it runs. Each time slice, a randomized lottery determines the winner of the lottery; that winning process is the one that runs for that time slice.
