/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/22 18:25:02 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/22 18:56:20 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/**
 * @param input linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief sets pipe to be reused in every child process
*/
void	set_pipes(t_command *input, t_env *env)
{
	int	pipe_fd[2];
	int	fd_in;

	if (dup2(STDIN_FILENO, fd_in) == -1)//dupes standard input to fd_in (WHY NEED TO DO THIS?)
		mini_error("dup2", errno);
	while (input->command)//loops through command part of t_command struct
	{
		if (pipe(pipe_fd) == -1)//throws error when pipe fails
			mini_error("pipe", errno);
		set_forks(input, env, fd_in, pipe_fd);//sets fork for each command, need to pass fd's 
		if (dup2(pipe_fd[READ], fd_in) == -1)//dupes read to fd_in
			mini_error("dup2", errno);
		close(pipe_fd[READ]);//closes what I dont use
		input->command = input->command->next;
	}
}

/**
 * @param input linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
void	set_forks(t_command *input, t_env *env, int fd_in, int pipe_fd)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error("fork", errno);
	if (fork_pid == 0)
		printf("children made\n");
	if (dup2(pipe_fd[READ], fd_in) == -1)
		mini_error("dup2", errno);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		mini_error("dup2", errno);
	close(fd_in);
	close(pipe_fd[WRITE]);
}

//[cat(1 part in node)] -> [ls + la (2 parts in node)] -> outfile
//watch pipe videos again

// void	child_1(int *pipe_fd, t_pipex *args, char **envp, char **argv)
// {
// 	char	*executable;
// 	int		fd1;

// 	close_check(pipe_fd[READ]);
// 	fd1 = open(args->input_file, O_RDONLY);
// 	if (fd1 == -1)
// 		ft_error(args->input_file, errno);
// 	if (dup2(fd1, STDIN_FILENO) == -1)
// 		ft_error("dup2", errno);
// 	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
// 		ft_error("dup2", errno);
// 	close_check(fd1);
// 	close_check(pipe_fd[WRITE]);
// 	check_space_and_null(argv[2]);
// 	executable = check_access(envp, args, args->first_command[0]);
// 	if (access(executable, X_OK) == -1)
// 		ft_error(executable, errno);
// 	if (execve(executable, args->first_command, envp) == -1)
// 		ft_error(*args->first_command, errno);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	*args;
// 	int		pid[2];
// 	int		pipe_fd[2];

// 	if (argc != 5)
// 		ft_error("./pipex: incorrect arguments", errno);
// 	args = parse_args(argv);
// 	if (pipe(pipe_fd) == -1)
// 		ft_error("pipe", errno);
// 	pid[0] = fork();
// 	if (pid[0] < 0)
// 		ft_error("fork", errno);
// 	if (pid[0] == 0)
// 		child_1(pipe_fd, args, envp, argv);
// 	pid[1] = fork();
// 	if (pid[1] < 0)
// 		ft_error("fork", errno);
// 	if (pid[1] == 0)
// 		child_2(pipe_fd, args, envp, argv);
// 	close_pipes(pipe_fd);
// 	status_check(pid[1]);
// }