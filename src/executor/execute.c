/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:56:26 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/19 22:17:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks environment to find PATH put it in temp_path
 * split temp_path into 2d array and put it in the struct data->path
 * @todo exit codes
*/
static bool	parse_path(t_env *env, t_execute *data, t_parser *node)
{
	char	*temp_path;

	temp_path = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			temp_path = ft_substr(env->value, 0, ft_strlen(env->value));
			if (temp_path == NULL)
				mini_error (E_MALLOC, node);
			data->path = ft_split(temp_path, ':');
			if (data->path == NULL)
				mini_error (E_MALLOC, node);
			free (temp_path);
			if (data->path == NULL)
				mini_error (E_MALLOC, node);
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
 * @todo exit codes
			// if (command == NULL)
			// 	mini_error (E_MALLOC, node);//
			// if (command == NULL)
			// 	mini_error (E_MALLOC, node);//
*/
static char	*check_access(t_env *env, t_parser *node, t_execute *data)
{
	char	*ok_path;
	char	*command;
	int		i;

	i = 0;
	if (!node->proc->cmd)
		return (node->proc->cmd);
	if (!absolute_check(node) && parse_path(env, data, node))
	{
		while (data->path && data->path[i] != NULL)
		{
			command = mini_strjoin("/", node->proc->cmd);
			ok_path = mini_strjoin(data->path[i], command);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		put_execute_error(node);
		data->error = false;
	}
	return (node->proc->cmd);
}

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks parser input for executable and executes with execve
 *  replace exit int with the existatus global we pass on
 * @todo added id !lst->cmd to stop segfault NORM IT
	// dprintf(STDERR_FILENO, "executable = [%s]\n", executable);
	// argv = NULL;//need?
	// executable = NULL;//need?
	// if (access(executable, F_OK) == -1)
	// {	
	// 	put_execute_error(lst);//specified executable error message?
	// 	exit (EXIT_FAILURE);
		// ft_free_arr(argv);//need this?
		// free(executable);//same
		// ft_free_arr(data->env_array);//same
	// cmd_type = 0;
	// }
*/
void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;
	char		**argv;
	int			cmd_type;

	init_pipes_child(data, lst);
	redirect(lst, data);
	if (data->error == false)
		exit (0);
	cmd_type = check_for_builtin(lst);
	if (cmd_type != 0)
	{
		do_builtin(lst, env, cmd_type);
		exit (EXIT_SUCCESS);//exit success??
	}
	if (!lst->proc->cmd) // we do need this?
		exit (0);
	executable = check_access(*env, lst, data);
	if (executable == NULL)
	{
		put_execute_error(lst);
		exit (0);
	}
	if (data->error == false)
		exit (0);
	if (access(executable, X_OK) == -1)
	{
		put_permission_error(lst);
		exit (EXIT_FAILURE);
	}
	data->env_array = list_to_string(*env);
	argv = get_argv(lst);
	if (argv == NULL)
		exit(0);
	if (execve(executable, argv, data->env_array) == -1)
		exit(EXIT_FAILURE);
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * @todo exit codes WAIT IS NOT WORKING BECAUSE ITS NONSENSE
 */
static void	build(t_parser *lst, t_env **env, t_execute *data)
{
	if (!lst)
		mini_error (E_GENERAL, lst);
	init_heredoc(lst, env);
	if (single_builtin_cmd(lst, env, data) == true)
		return ;
	pipeline(lst, env, data);
	close_all(data, lst);
	waitpid(data->fork_pid, NULL, 0);
	while (wait(NULL) != -1)
		(void)NULL;
}

/**
 * @param env environment linked list
 * @param lst linked list parsed
 * @brief calls functions needed to start executing process
 * @todo exit codes
*/
void	execute(t_env **env, t_parser *lst)
{
	t_execute	*data;
	data = malloc(sizeof(t_execute));
	if (data == NULL)
		mini_error (E_GENERAL, lst);
	init_execute_struct(data);
	ft_expand(lst, env);
	build(lst, env, data);
	free (data);
}
