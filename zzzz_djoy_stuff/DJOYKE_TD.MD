
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
