
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