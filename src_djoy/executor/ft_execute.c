/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/17 14:55:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param envp environment passed as 2d array
 * @param lst linked list parsed
 * @brief puts env in linked list and initializes struct
 * containing fd's and 2d arrays for later use
 * @todo 
 * 1) check if decisions need to be made in here
*/
void	ft_execute(char **envp, t_parser *lst)
{
	int			i;
	t_env		*env;
	t_execute	data;

	i = 0;
	env = env_list(envp);
	init_execute_struct(&data, env);
	build(lst, env, &data);
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * waits for last child processes to finish
 * @todo 
 * 1) make condition to pipe according parsed input.
 * 2) determine how many pipes need to be made
 * 3) how to keep up with the amount of pipes created
 * 4) how to wait for all child processes
 * 5) how to redirect output/input?
*/
void	build(t_parser *lst, t_env *env, t_execute *data)
{
	if (dup2(STDIN_FILENO, data->fd_in) == -1)
		mini_error("dup2", errno);
	if (!lst)
		mini_error("list", errno);
	//lst_len cmd check
	if (pipe(data->pipe_fd) == -1)
		mini_error("pipe", errno);
	while (lst)
	{
		if (lst)
		{
			data->fork_pid = fork();
			if (data->fork_pid == -1)
				mini_error("fork", errno);
			if (data->fork_pid == 0)
			{
				printf("build_process:		have to get a kindergarten\n");
				mini_forks(lst, env, data);
				// if (dup2(data->pipe_fd[READ], data->fd_in) == -1)
				// {
				// 	printf("build process:		you came back huh\n");
				// 	mini_error("1 dup2", errno);
				// }
				// close(data->pipe_fd[READ]);
				// close(data->pipe_fd[WRITE]);
			}
		}
		lst = lst->next;
		//need to wait for the individual children to return (maybe the loop)
	}
	// Parent process - Wait for the child process to finish
	waitpid(data->fork_pid, NULL, 0); // Properly wait for the last child process
	close(data->pipe_fd[READ]);
	//if redirect found for outfile dup read end to outfile 
	// close(data->pipe_fd[WRITE]);
}

//int dup2(int oldfd, int newfd);

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks parser input for executable and executes with execve
 * @return parser lst
 * @todo how to redirect output form pipe? or only need to do that in build?
 * 1) int dup2(int oldfd, int newfd);
*/
t_parser	*mini_forks(t_parser *lst, t_env *env, t_execute *data)
{
	char	*executable;

	if (data->fork_pid == 0)
	{
		printf("mini_forks:		children made\n");
		if (dup2(data->pipe_fd[READ], data->fd_in) == -1)
			mini_error(" 2.... dup2", errno);
		if (close(data->pipe_fd[READ]) == -1)
			mini_error("close", errno);
		// if (dup2(data->pipe_fd[WRITE], STDOUT_FILENO) == -1)
		// 	mini_error(" 3..... dup2", errno);
		// dprintf(2, "euagegauweg\n");
		// puts("huehue");
		close(data->pipe_fd[WRITE]);
		executable = check_access(env, lst, data);
		// printf("executble = [%s]\n", executable);
		if (access(executable, X_OK) == -1)
			mini_error(executable, errno);
		if (execve(executable, &lst->str, data->env_array) == -1)
			mini_error(lst->str, errno);
	}
	close(data->fd_in);
	close(data->pipe_fd[WRITE]);
	close(data->pipe_fd[READ]);
	return (lst);
}

/**
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks environment to find PATH put it in temp_path
 * split temp_path into 2d array and put it in the struct data->path
 * @todo 
 * 
*/
bool	parse_path(t_env *env, t_execute *data)
{
	int		i;
	char	*temp_path;

	i = 0;
	temp_path = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			temp_path = ft_substr(env->value, 0, ft_strlen(env->value));
			printf("temp_path = %s\n", temp_path);
			if (temp_path == NULL)
				mini_error ("malloc", errno);
			data->path = ft_split(temp_path, ':');
			if (data->path == NULL)
				mini_error ("malloc", errno);
			free (temp_path);
			if (data->path == NULL)
				mini_error ("malloc", errno);
			return (true);
		}
		env = env->next;
	}
	return (false);
}

/**
 * @param env linked list with environment
 * @param node noded from parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks is command has access
 * 
*/
char	*check_access(t_env *env, t_parser *node, t_execute *data)
{
	char	*ok_path;
	char	*command;
	int		i;

	i = 0;
	if (!absolute_check(node) && parse_path(env, data))
	{
		while (data->path && data->path[i] != NULL)
		{
			command = ft_strjoin("/", node->str);
			if (command == NULL)
				mini_error("malloc", errno);
			ok_path = ft_strjoin(data->path[i], command);
			// printf("ok_path = [%s]\n", ok_path);
			if (command == NULL)
				mini_error("malloc", errno);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		mini_error(node->cmd, errno);// command_error(node->cmd, errno);
	}
	return (node->cmd);//of node->str?
}
