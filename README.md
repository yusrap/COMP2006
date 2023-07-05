## Details
**Name**: Yusra Patel

**Student Number**: 20823850

**Submission Date**: 08/05/2023

**Unit**: COMP2006 Operating Systems - Semester 1, 2023

**Purpose**: To simulate the operations of a hypothetical customer queue in a bank, using the POSIX threads library

---------------------

## Prerequisites

Linux build environment with make and gcc compiler

------------------------------
## Usage
Compile all the files via a Makefile.

`make`

Run the executable *cq.exe* file using the following format:

`./cq queue_size customer_arrival_interval withdrawal_time deposit_time information_time`

All parameters should be positive integers as shown in the example:

`./cq 20 2 3 4 7`

Using the command above, 20 customers will be placed into the queue at a time interval of 2 seconds - a withdrawal service requires 3 seconds, a deposit service requires 4 seconds whereas an information one requires 7 seconds.

The *r_log.txt* file can be viewed for all the logs of the program execution.

----------------
    
