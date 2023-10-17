/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 18:14:28 by dreijans      ########   odam.nl         */
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
 * unset is double freeing
*/
void	ft_execute(t_env **env, t_parser *lst)
{
	t_execute	*data;

	data = malloc(sizeof(t_execute));
	if (data == NULL)
		mini_error("malloc data", errno);
	init_execute_struct(data);
	ft_expand(lst, env);
	build(lst, env, data);
	free (data);
	data = NULL;
	return ;
}

void	close_check(int num)
{
	assert(close(num) != -1);
	// if (close(num) < 0)
	// 	perror("close");
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * @todo 
 * check for heredoc before forking
*/
void	build(t_parser *lst, t_env **env, t_execute *data)
{
	t_parser	*head;

	head = lst;
	if (dup2(STDIN_FILENO, data->fd_in) == -1)
		mini_error("dup2 std_in", errno);
	if (dup2(STDOUT_FILENO, data->fd_out) == -1)
		mini_error("dup2 std_out", errno);
	if (pipe(data->pipe_fd_1) == -1)
		mini_error("pipe_fd_1", errno);
	if (pipe(data->pipe_fd_2) == -1)
		mini_error("pipe_fd_2", errno);
	close_check(data->pipe_fd_1[READ]);
	close_check(data->pipe_fd_2[WRITE]);
	if (!lst)
		mini_error("list", errno);
	while (head)
	{
		if (check_redirect(head) != 0)
		{
			redirect_infile(head, data);
			redirect_outfile(head, data);
		}
		head = head->next;
	}
	while (lst)
	{
		if (lst->cmd && !lst->next && check_for_builtin(lst))
			do_builtin(lst, env);
		if (lst->cmd && lst->next && check_for_builtin(lst))
			do_builtin(lst, env);
		if (lst->cmd && lst->next && !check_for_builtin(lst))
		{
			if (dup2(STDOUT_FILENO, data->pipe_fd_1[WRITE]) == -1)
				mini_error("pipe_fd_1", errno);
			// only if need to fork again
			if (dup2(data->pipe_fd_2[READ], STDIN_FILENO) == -1);
				mini_error("pipe_fd_2", errno);
			data->fork_pid = fork();
			if (data->fork_pid == -1)
				mini_error("fork", errno);
			if (data->fork_pid == 0)
				mini_forks(lst, env, data);
		}
		// if ((lst->cmd || mini_strcmp(lst->meta, "|") == 0) && lst->next && !check_for_builtin(lst))
		// {
		// 	dup2(data->fd_out, data->pipe_fd[READ]);
		// 	data->fork_pid = fork();
		// 	if (data->fork_pid == -1)
		// 		mini_error("fork", errno);
		// 	if (data->fork_pid == 0)
		// 		mini_forks(lst, env, data);
		// }
		lst = lst->next;
	}
	close_check(data->fd_in);
	close_check(data->fd_out);
	close_check(data->pipe_fd_1[READ]);
	close_check(data->pipe_fd_1[WRITE]);
	close_check(data->pipe_fd_2[READ]);
	close_check(data->pipe_fd_2[WRITE]);
	waitpid(data->fork_pid, NULL, 0);
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
void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;

	if (data->fork_pid == 0)
	{
		close_check(data->pipe_fd_1[WRITE]);
		close_check(data->pipe_fd_2[READ]);
		if (dup2(STDIN_FILENO, data->pipe_fd_2[WRITE]) == -1)
			mini_error("dup2", errno);
		if (dup2(STDOUT_FILENO, data->pipe_fd_1[READ]) == -1)
			mini_error("dup2", errno);
		printf("mini_forks:		children made\n");
		executable = check_access(*env, lst, data);
		printf("executble = [%s]\n", executable);
		if (access(executable, X_OK) == -1)
			mini_error(executable, errno);
		data->env_array = list_to_string(*env);
		if (execve(executable, &lst->str, data->env_array) == -1)
			mini_error(lst->str, errno);
	}
	return ;
}

/**
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks environment to find PATH put it in temp_path
 * split temp_path into 2d array and put it in the struct data->path
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
