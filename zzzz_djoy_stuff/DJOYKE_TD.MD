
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
<<<<<<< HEAD:DJOYKE_TD.MD




 if no pipes and just 1 builtin single builtin executor

maybe use sleep in childprocess 




/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * line 81 : need to wait for the individual children to return (maybe the loop)
 * line 83 : Parent process properly wait for the last child process
 * @todo 
 * 1) line 55: 	
 * 				lst_len cmd check 
 * make condition to pipe according parsed input.
 * 2) determine how many pipes need to be made
 * 3) how to keep up with the amount of pipes created
 * 4) how do redirect output from one pipe to the pipe of another child process?
 * line 70: after mini_forks
 * 				if (dup2(data->pipe_fd[READ], data->fd_in) == -1)
				{
					printf("build process:		you came back huh\n");
					mini_error("1 dup2", errno);
				}
				close(data->pipe_fd[READ]);
				close(data->pipe_fd[WRITE]);
 * 4) how to wait for all child processes
 * 5) how to redirect output/input? 
 * 				if redirect found for outfile dup read end to outfile 
				close(data->pipe_fd[WRITE]);
 * pipe recursively!!! opens and closes step by step
*/
// void	build(t_parser *lst, t_env *env, t_execute *data)
// {
// 	int i;

// 	i = 0;
// 	if (dup2(STDIN_FILENO, data->fd_in) == -1)
// 		mini_error("dup2", errno);
// 	if (!lst)
// 		mini_error("list", errno);
// 	if (pipe(data->pipe_fd) == -1)
// 		mini_error("pipe", errno);
// 	while (lst)
// 	{
// 		//check for heredoc
// 		if (lst->cmd || (mini_strcmp(lst->meta, "|") == 0))
// 		{
// 			data->fork_pid = fork();
// 			if (data->fork_pid == -1)
// 				mini_error("fork", errno);
// 			if (data->fork_pid == 0)
// 			{
// 				printf("build_process:		have to get a kindergarten\n");
// 				mini_forks(lst, env, data);
// 			}
// 		}
// 		lst = lst->next;
// 	}
// 	//put usleep or wait thing here so I can properlu read output.
// 	waitpid(data->fork_pid, NULL, 0);
// 	wait(NULL);// wait for forked process to finish??
// 	close(data->pipe_fd[READ]);
// }

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks parser input for executable and executes with execve
 * @return parser lst
 * @todo how to redirect output form pipe? or only need to do that in build?
 * 1) when do I need to dup WRITE to STDOUT_FILENO?
 * 				if (dup2(data->pipe_fd[WRITE], STDOUT_FILENO) == -1)
		 			mini_error(" 3..... dup2", errno);
				dprintf(2, "euagegauweg\n"); (prints on standard error)
 * remember!!! int dup2(int oldfd, int newfd);
*/
// t_parser	*mini_forks(t_parser *lst, t_env *env, t_execute *data)
// {
// 	char	*executable;

// 	if (data->fork_pid == 0)
// 	{
// 		printf("mini_forks:		children made\n");
// 		//check is single builtin no next cmd in list, needs a different execution function??
// 		if (check_redirect(lst) == 0)
// 		{
// 			printf("redirect found\n");
// 			redirect(lst, &env, data);// check if it needs to be redirected or not
// 			//do i need to change 
// 		}
// 		if (check_redirect(lst) != 0)
// 		{
// 			if (dup2(data->pipe_fd[READ], data->fd_in) == -1)
// 				mini_error(" 2.... dup2", errno);
// 			if (close(data->pipe_fd[READ]) == -1)
// 				mini_error("close", errno);
// 			close(data->pipe_fd[WRITE]);
// 			if (check_for_child_builtin(lst) == 0)
// 				do_builtin(lst, &env);	
// 		}
// 		if (check_for_child_builtin(lst) != 0)
// 		{
// 			executable = check_access(env, lst, data);
// 			printf("executble = [%s]\n", executable);
// 			if (access(executable, X_OK) == -1)
// 				mini_error(executable, errno);
// 			if (execve(executable, &lst->str, data->env_array) == -1)
// 				mini_error(lst->str, errno);
// 		}
// 	}
// 	close(data->fd_in);
// 	close(data->pipe_fd[WRITE]);
// 	close(data->pipe_fd[READ]);
// 	return (lst);
// }

-------------------------------------------

/*
	➜  minishell git:(djoyke) ✗ < hi.txt wc > outfile.txt 
	zsh: no such file or directory: hi.txt
	➜  minishell git:(djoyke) ✗ pwd
	/home/dreijans/Documents/rank3/minishell
	➜  minishell git:(djoyke) ✗ rm outfile.txt
	rm: cannot remove 'outfile.txt': No such file or directory
	➜  minishell git:(djoyke) ✗ cd src_djoy 
	➜  src_djoy git:(djoyke) ✗ < hi.txt wc |  > outfile.txt 
	zsh: no such file or directory: hi.txt
	➜  src_djoy git:(djoyke) ✗ rm outfile.txt   

		dreijans@f0r2s3:~$ < hi | echo hello
		hello
		dreijans@f0r2s3:~$ bash: hi: No such file or directory
		^C
		dreijans@f0r2s3:~$ < hi echo hello | echo hello
		hello
		bash: hi: No such file or directory
*/

---------------------------------------------------example---------------------------------------------------------------

Hi sorry for being late
Okay I'll try to do my best to explain it with simple words as there's a lot to explain.


1) iterate all your linked lists and check if they are built in or execute commands. If it's build in just do it as normal without forking for example if I have ls | echo hi → file it will be something like this


typedef struct s_cmd 
{
    char *cmd;
    char *file;
    struct s_cmd *next;
} 				t_cmd;

int main() 
{
		// Imagine you already created your linked list
    t_cmd cmds[] = 
	{
        {"ls", NULL, &cmds[1]},
        {"echo hi", "file", &cmds[2]},
    };

    int pipefd[2] = {-1, -1};
    int in_fd = STDIN_FILENO; 

		//this is just to help yourself later on to close FD
		// Iterate over the linked list and execute each command
    for (t_cmd *cmd = cmds; cmd != NULL; cmd = cmd->next) 
	{
        int out_fd = cmd->next ? pipefd[1] : STDOUT_FILENO;
        if (cmd->next && pipe(pipefd) == -1) 
		{
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        execute_cmd(cmd->cmd, cmd->file, in_fd, out_fd);
        if (in_fd != STDIN_FILENO) 
			close(in_fd);
        if (out_fd != STDOUT_FILENO) 
			close(out_fd);
        in_fd = pipefd[0];
	}
}


In the execute function you'll check whenever they are build in or execute cmd
A) if the command is built in, execute it directly in the current process.
B) if the command is not built in, you'll need to create a new process to execute it. This is where Fork() comes in.
2) when we use Fork() to create a new child process. The child process will execute the command, while the parent process will wait for the child to complete. (I recommend you to set up the pipe communication between the processs before you Fork() look example 1 how I set up the pipe.
The parent process should write to the write of the pipe and child process should read from the read. You can use dup2() to replace the standard input or output with the appropriate end of the pipe)
If you have (← or →) set up the redirection before you Fork() . Use Open() to get the file descriptor for the file and dup2 to replace the standard input or output with the file descriptor
(Sorry I'm writing with my phone and I'm kind lost with examples ahahah)
Example


void execute_cmd(char *cmd, char *file, int in_fd, int out_fd) 
{
    		// Check if the command is a built-in command

   			//Do this if it's not built in
    
	pid_t pid = fork();

    if (pid == -1) 
	{
        perror("fork");
        exit(EXIT_FAILURE);
    } 
	else if (pid == 0) 
	{
        	// Child process
        if (in_fd != STDIN_FILENO) 
		{
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) 
		{
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
			//This is only when you have a file
        if (file) 
		{
            int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) 
			{
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
    	}
      	
		}	// execute here your command
	Else
    		//Wait for the child process
}


Final note, remember that when using Fork, the child process will be the exact copy of the parent process at the point of the Fork that includes the current file descriptors which is why you need to set up pipes and redirection before the fork
=======
>>>>>>> sarah:zzzz_djoy_stuff/DJOYKE_TD.MD
