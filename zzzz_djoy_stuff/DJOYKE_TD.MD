
----------Make the executor expandable based on pipes--------

1) basic structure works
2) how do I want to expand it?
3) do I want to use 2 pipes and pass it on?


--------------------RANDOM-------------------------

2) as soon as quotes are fixed 
    1) check exit and unset again for the quoted value etc
    2) check echo again
3) make bash script for easier testing


---------------BUILTIN------------------------------

review the checking of the builtins because its case sensitive

cd:

 * relative: cd src
 * absolute: cd src/bin/pannekoek/whatever TESTT!!!
 * 				cd alone gives prompt back
 * 				cd jfhjvhs gives: cd: no such file or directory: jfhjvhs
 * line 66: check if needs error message with exit
 * 			give prompt back, and endline?

export, cd , exit, unset before childprocess because you need the environment. and exit needs to exit the whole program.
rest in the child proces. 

---------------------METAA-------------------------------

1) infile <
2) outfile >

check stat function video youtube https://www.youtube.com/watch?v=5k0Eh1ZpT0o

//    if (stat(path, &fileStat) == 0) {
//         if (S_ISREG(fileStat.st_mode)) {
//             printf("%s is a regular file.\n", path);
//         } else if (S_ISDIR(fileStat.st_mode)) {
//             printf("%s is a directory.\n", path);
//         } else {
//             printf("%s is neither a regular file nor a directory.\n", path);
//         }
//     } else {
//         perror("stat");
//     }

- `R_OK`: Check if the file or directory is readable. XXXXX
- `W_OK`: Check if the file or directory is writable. XXXXX
- `X_OK`: Check if the file or directory is executable.
- `F_OK`: Check if the file or directory exists.

should we handle this in the parser?
assigning fd to the same node the file name is in.
do that tomorrow together

how will fd work in the parser struct?

test echo hi > haha.txt

-----------------------------------------------------------
3) pipe |

check how I should pipe accordingly yeah that
echo | wc test that no stress or yes

-----------------------------------------------------------
4) append >>
5) heredoc <<

---------------------SARAH NOTES-------------------------------

hello lovely, it will all be ok soon... hopefully.. hehe


-------------------------EXPANDER-------------------------
bash-3.2$ cat $djoyke
 * cat: haaa: No such file or directory
 * cat: ggg: No such file or directory (is moeilijk maybe not)
 * 		cat $USER
 * 
 * 		char ** =	[0] cat
 * 					[1] $USER
 * 					[2] NULL
 * 
 * 		expanding handles [1]$USER (could be djoyke etc or nothing)
 * 		if it's nothing char ** after expanding should look like
 * 
 * 		char ** = [0] cat
 * 		[1] NULL
 *		give that to execve
 *		
 *		or:
 * 		
 *		char ** = [0] cat
 *				  [1] djoyke
 *				  [2] NULL
 *
 * 		[1] $USER get's removed not overwritten! (memcpy)
 * 		[2] NULL get's moved up!
 * 		
 * 		➜  ~ echo $USER
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0	
 * 		➜  ~ echo ${USER}
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0
 * 		➜  ~ echo "$USER"
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0
 * 		➜  ~
 * 
 * 		bash-3.2$ echo hi > outfile
 * 		bash-3.2$ cat outfile
 * 		hi
 * 			
 * builtin needs to be redirected to outfile
 * does this mean that if a process ended correctly 
 * it needs to return 0? as in EXIT_SUCCESS?
 * if >>$USER no expanding user it's a delimiter now
 * 
 * dreijans@f0r2s3:~$ $USER echo abc$USER
 * dreijans: command not found
 * make it into proper error message

 -----------------------SARAH UPDATE------------------------------

 sarah can you when there's a redirect set the [0]cmd first in the linked list with [1]meta and [2]filename in the following

 cat < infile.txt infile1.txt infile2.txt infile3.txt

example:

 echo hallo > file.txt | < infile cat

 echo hallo > file.txt | cat < infile

 can you make the cmd the first token when a new command needs to be executed? :)

for now I'll do as if thats already the case in my exectuting.

• Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.
Be carefull. This global variable cannot provide any other
information or data access than the number of a received signal.
Therefore it is forbidden to use "norm" type structures in global.

we need to have a part in our linked list that keeps our exit codes. because we cant use the global for these.

/**
 * @brief	specifies the different variable types of tokens from the
 * 			lexer that are parsed and then given to the executor
 * @param	cmd: first string in each process without redirect char
 * @param	meta: pipe, more, less, moremore, lessless. 
 * 			**dollar is excluded and handled as a string
 * @param	file: in and out files; after more, less and moremore chars
 * @param	str:  limiter for here_doc (string after <<) and all other input
*/
typedef struct s_parser
{
	void				*input;
	char				*cmd;
	char				*meta;
	char				*file;
	char				*str;
	int					n_cmd;
	--->// int					exit_code 
	--->// this will be updated after each process will happen automatically
	struct s_parser		*next;
}				t_parser;

--------------------HERE_DOC---------------------------------


kan readline/gnl gebruiken, zoeken op deilmiter\n strncmp 


<< "DELIMAMEM"

DELIMAMEMTA werkt niet.






yoooooooooooooooooooooooooooooo

minishell 🍌cat <<
[0]      cmd = cat      file = (null)   meta = (null)  str = (null)     n_cmd = 1
[1]      cmd = (null)   file = (null)   meta = <<      str = (null)     n_cmd = 0
heredoc found
AddressSanitizer:DEADLYSIGNAL
=================================================================
==65582==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000020 (pc 0x0000004d370f bp 0x7ffdebe3f840 sp 0x7ffdebe3f770 T0)
==65582==The signal is caused by a READ memory access.
==65582==Hint: address points to the zero page.
    #0 0x4d370f in heredoc /home/dreijans/Documents/rank3/minishell/src_djoy/executor/redirect.c:119:18
    #1 0x4ce881 in build /home/dreijans/Documents/rank3/minishell/src_djoy/executor/execute.c:129:2
    #2 0x4ce7b5 in execute /home/dreijans/Documents/rank3/minishell/src_djoy/executor/execute.c:154:2
    #3 0x4d47d6 in main /home/dreijans/Documents/rank3/minishell/src_saar/main_saar.c:67:3
    #4 0x7f8953958d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #5 0x7f8953958e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #6 0x41f3a4 in _start (/home/dreijans/Documents/rank3/minishell/djoyke+0x41f3a4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/dreijans/Documents/rank3/minishell/src_djoy/executor/redirect.c:119:18 in heredoc
==65582==ABORTING

parser or lexer need to throw syntax errors! :) jippie

alsooooo

dreijans@f0r3s15:~/Documents/rank3/minishell$ cat Makefile > $bla
bash: $bla: ambiguous redirect

dreijans@f0r3s15:~/Documents/rank3/minishell$ cat | $bla | $bla
dreijans@f0r3s15:~/Documents/rank3/minishell$ echo $bla (echoed empty argument)
dreijans@f0r3s15:~/Documents/rank3/minishell$ echo $bla

dreijans@f0r3s15:~/Documents/rank3/minishell$

lastige zegt ruben 

nice huh?

------------------TO DO----------------------------

◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.

• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

 Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.

descriptions on my own structs.