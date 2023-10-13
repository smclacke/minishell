/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/13 23:09:26 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

//take all the nodes until the pipe or redirect, built-in and put it in execve

/**
 * @param envp environment passed as 2d array
 * @param lst linked list parsed
 * @brief puts env in linked list and initializes struct
 * containing fd's and 2d arrays for later use
 * @todo 
 * 1) check if decisions need to be made in here
 * env als double pointer meegeven
*/
void	ft_execute(t_env **env, t_parser *lst)
{
	t_execute	*data;

	data = malloc(sizeof(t_execute));
	init_execute_struct(data, *env);
	ft_expand(lst, env);
	// single_build(lst, env, data); // only works for outfile now
	build(lst, env, data);
	free_data(data);
	free(data);
	return ;
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * @todo 
 * check for heredoc before forking
 * put usleep or wait thing here so I can properlu read output.
*/
void	build(t_parser *lst, t_env **env, t_execute *data)
{
	if (dup2(STDIN_FILENO, data->fd_in) == -1)
		mini_error("dup2", errno);
	if (!lst)
		mini_error("list", errno);
	if (pipe(data->pipe_fd) == -1)
		mini_error("pipe", errno);
	while (lst)
	{
		if (lst->cmd)
		{
			data->fork_pid = fork();
			if (data->fork_pid == -1)
				mini_error("fork", errno);
			if (data->fork_pid == 0)
			{
				printf("build_process:		have to get a kindergarten\n");
				mini_forks(lst, env, data);
			}
		}
		lst = lst->next;
	}
	waitpid(data->fork_pid, NULL, 0);
	wait(NULL);
	close(data->pipe_fd[READ]);
}

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
t_parser	*mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;
	t_parser	*head;

	head = lst;
	if (data->fork_pid == 0)
	{
		printf("mini_forks:		children made\n");
		while (head)
		{
			printf("hi?\n");
			if (check_redirect(head) != 0)
			{
				printf("yes\n");
				printf("redirect found\n");
				redirect_infile(head, data);
			}
			head = head->next;
		}
		head = lst;
		// if (check_redirect(lst) == 0)
		// {
		// 	if (dup2(data->pipe_fd[READ], data->fd_in) == -1)
		// 		mini_error(" 2.... dup2", errno);
		// 	if (close(data->pipe_fd[READ]) == -1)
		// 		mini_error("close", errno);
		// 	close(data->pipe_fd[WRITE]);
		// 	if (check_for_child_builtin(lst) == 0)
		// 		do_builtin(lst, &env);
		// }
		executable = check_access(*env, lst, data);
		printf("executble = [%s]\n", executable);
		if (access(executable, X_OK) == -1)
			mini_error(executable, errno);
		if (execve(executable, &lst->str, data->env_array) == -1)
			mini_error(lst->str, errno);
		ft_free_arr(data->env_array);
	}
	close(data->fd_in);
	close(data->pipe_fd[WRITE]);
	close(data->pipe_fd[READ]);
	return (lst);
}

/**
 * @param lst parser linked list
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function
 * @todo
 * needs infile redirect function in here too?
 * check if we need to close outfile_fd, or STDOUT in here?
 * 
*/
void	single_build(t_parser *lst, t_env **env, t_execute *data)
{
	t_parser	*head;

	head = lst;
	while (head)
	{
		if (check_redirect(head) != 0)
			redirect_outfile(head, data);
		head = head->next;
	}
	head = lst;
	while (head)
	{
		if (check_for_child_builtin(head) != 0)
			do_builtin(head, env);
		head = head->next;
	}
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
	char	*temp_path;

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
 * @todo 
 * 1) line 196: command_error(node->cmd, errno); instead of current func
 * 2) line 199; node->str? instead of node->cmd?
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
			command = ft_strjoin("/", node->cmd);
			if (command == NULL)
				mini_error("malloc", errno);
			ok_path = ft_strjoin(data->path[i], command);
			printf("ok_path = [%s]\n", ok_path);
			if (command == NULL)
				mini_error("malloc", errno);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		mini_error(node->cmd, errno);//check this out please
	}
	return (node->cmd);//check this out please
}
