# Multithreaded-System-Simulator

## Description

A program required to be developed in C/C++, called a4tasks, that utilizes pthreads to simulate the concurrent execution of a set of tasks. The system has a number of resource types, and each resource type has a number of available units. All resource units in the system are non-sharable non-preemptable resources.

## Usage
To compile a4tasks with make:
```bash
make
```

After compiling the `a4tasks` binary it can be invoked using the command line:
```bash
./a4tasks inputFile monitorTime NITER
```

Where the arguments are defined as:

`inputFile`: file describing the tasks to be executed. 

`monitorTime`: integer (in milliseconds) that specifies how often a monitor
    thread runs.

`NITER`: integer noting the amount of iterations each task executes 
    before the simulator finishes.

### Input File
The simulator reads the system parameters from an input file. The file has a number of lines
formatted as follows:  
A line can be empty  
A line that starts with a ’#’ is a comment line  
A line of the form:  

```text
resources name1:value1 name2:value2 ...
```
specifies the resource types available in the system. The line starts with the keyword resources, followed by one, or more, name:value pairs of a resource type name, and the number of available units of this resource type, respectively.

A line of the form
```text
task taskName busyTime idleTime name1:value1 name2:value2 ...
```
specifies a task in the system. The line has the following fields:  
* `task`: a keyword that specifies a task line  
* `taskName`: the task’s name  

## Notes
- This is only part 1
- A simulation made by a4tasks may have up to `NRES TYPES = 10` resource types and `TASKS = 25` tasks
- Each string (a task or a resource type name) has at most 32 characters
- Each white space between fields is composed of one, or more, space character(s)
- There is no white space around the `:` field separator
