/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD:src_djoy/executor/execute.c
/*   Created: 2023/10/19 21:13:53 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/19 22:18:52 by dreijans      ########   odam.nl         */
=======
/*   Created: 2023/10/17 19:43:54 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 20:19:39 by smclacke      ########   odam.nl         */
>>>>>>> bafe4027e8c0281e85e398570406ea12de154202:src_djoy/executor/ft_execute.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
<<<<<<< HEAD:src_djoy/executor/execute.c
=======
// #include <assert.h>

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
	// ft_expand(lst, env);
	build(lst, env, data);
	free (data);
	data = NULL;
	return ;
}

void	close_check(int num)
{
	// assert(close(num) != -1);
	if (close(num) < 0)
		perror("close");
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
	int			count;

	head = lst;
	count = lst->n_cmd;
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
		// if (dup2(data->fd_out, data->pipe_fd_1[WRITE]) == -1)
		// 	mini_error("pipe_fd_1", errno);
		// // only if need to fork again
		// if (dup2(data->pipe_fd_2[READ], data->fd_in) == -1)
		// 	mini_error("pipe_fd_2", errno);
		if (count == 1 && check_for_builtin(lst))
		{
			do_builtin(lst, env);
		}
		else if (count >= 1 && lst->next)
		{
			data->fork_pid = fork();
			if (data->fork_pid == -1)
				mini_error("fork", errno);
			if (data->fork_pid == 0)
				mini_forks(lst, env, data);
		}
		count--;
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
	// ft_expand(lst, env);
	build(lst, env, data);
	free (data);
	data = NULL;
	return ;
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

	printf("childddd\n");
	if (check_for_builtin(lst))
	{
		do_builtin(lst, env);
		close_check(data->pipe_fd_1[READ]);
		close_check(data->pipe_fd_1[WRITE]);
		close_check(data->pipe_fd_2[READ]);
		close_check(data->pipe_fd_2[WRITE]);
		return ;
	}
	close_check(data->pipe_fd_1[WRITE]);
	close_check(data->pipe_fd_2[READ]);
	if (dup2(data->fd_in, data->pipe_fd_2[WRITE]) == -1)
		mini_error("dup2", errno);
	if (dup2(data->fd_out, data->pipe_fd_1[READ]) == -1)
		mini_error("dup2", errno);
	executable = check_access(*env, lst, data);
	printf("executble = [%s]\n", executable);
	if (access(executable, X_OK) == -1)
		mini_error(executable, errno);
	data->env_array = list_to_string(*env);
	if (execve(executable, &lst->str, data->env_array) == -1)
		mini_error(lst->str, errno);
	return ;
}
>>>>>>> bafe4027e8c0281e85e398570406ea12de154202:src_djoy/executor/ft_execute.c

/**
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks environment to find PATH put it in temp_path
 * split temp_path into 2d array and put it in the struct data->path
*/
static bool	parse_path(t_env *env, t_execute *data)
{
	char	*temp_path;

	temp_path = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			temp_path = ft_substr(env->value, 0, ft_strlen(env->value));
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
 * @todo check is i need to give errno to mini_error
 * check if need to return node->cmd when it's absolute check etc
*/
static char	*check_access(t_env *env, t_parser *node, t_execute *data)
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
			if (command == NULL)
				mini_error("malloc", errno);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		mini_error(node->cmd, errno);
	}
	return (node->cmd);
}

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks parser input for executable and executes with execve
 * @todo replace exit int with the existatus global we pass on
*/
void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;

	init_pipes_child(data);
	redirect(lst, data);
	if (check_for_builtin(lst))
	{
		do_builtin(lst, env);
		exit (0);
	}
	executable = check_access(*env, lst, data);
	if (access(executable, X_OK) == -1)
		mini_error(executable, errno);
	data->env_array = list_to_string(*env);
	if (execve(executable, &lst->str, data->env_array) == -1)
		mini_error(lst->str, errno);
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
 * check the last while(wait(NULL) != -1) loop
*/
static void	build(t_parser *lst, t_env **env, t_execute *data)
{
	t_parser	*head;

	head = lst;
	if (!lst)
		mini_error("list", errno);
	if (single_builtin_cmd(lst, env, data) == 1)
		return ;
	child_builtin_cmd(lst, env, data);
	close_all(data);
	waitpid(data->fork_pid, NULL, 0);
	while (wait(NULL) != -1)
		(void)NULL;
}

/**
 * @param env environment linked list
 * @param lst linked list parsed
 * @brief calls functions needed to start executing process
 * @todo 
 * unset is double freeing
*/
void	execute(t_env **env, t_parser *lst)
{
	t_execute	*data;

	data = malloc(sizeof(t_execute));
	if (data == NULL)
		mini_error("malloc data", errno);
	init_execute_struct(data);
	// ft_expand(lst, env);
	build(lst, env, data);
	free (data);
	data = NULL;
	return ;
}
