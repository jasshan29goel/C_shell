# C_shell
cse_Assignment shell

## About
A shell like in linux which is completely implemented in c

## Steps to use

Step 1 Clone the repository
Step 2 Move in the bash directory
Step 3 $ make
Step 4 $ ./make

## Commands you can run
A new prompt will appear
Note -: Background processes Any command invoked with "&" is treated as background command. 
When the background process exits then the shell must display the appropriate message to the user.

### user defined commands
$ cd newdir
$ ls [al]
$ pwd 
$ echo
$ pinfo
$ pinfo <pid>
$ history <num>
  
### Piping and Redirection

$ diff file1.txt file2.txt > output.txt
$ sort < lines.txt > sortedlines.txt
$ grep "new" temp.txt | cat somefile.txt | wc

### Other specific commands
$ jobs 

$ kjob <jobNumber> <signalNumber> 
Note -: takes the job id of a running job and
sends a signal value to that process
  
$ fg <jobNumber> 
Note-: brings a running or a stopped background job with given job
number to foreground
  
$ bg <jobNumber> : 
Note : - changes a stopped background job to a running background
job.
  
$ overkill
Note: kills all background process at once.

$ quit
