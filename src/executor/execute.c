/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:56:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/10 22:32:36 by dreijans      ########   odam.nl         */
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
*/
static char	*check_access(t_env *env, t_parser *node, t_execute *data)
{
	char	*ok_path;
	char	*command;
	int		i;

	i = 0;
	if (!absolute_check(node) && parse_path(env, data, node))
	{
		while (data->path && data->path[i] != NULL)
		{
			command = ft_strjoin("/", node->cmd);
			if (command == NULL)
				mini_error (E_MALLOC, node);
			ok_path = ft_strjoin(data->path[i], command);
			if (command == NULL)
				mini_error (E_MALLOC, node);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		put_execute_error(node);
		data->error = false;
	}
	return (node->cmd);
}

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks parser input for executable and executes with execve
 *  replace exit int with the existatus global we pass on
*/
void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;
	char		**array;

	array = get_argv(lst);
	data->env_array = list_to_string(*env, lst);
	init_pipes_child(data, lst);
	redirect(lst, data);
	if (data->error == false)
		exit (0);
	if (check_for_builtin(lst))
	{
		do_builtin(lst, env);
		exit (0);
	}
	if (!lst->cmd)
		exit (0);
	executable = check_access(*env, lst, data);
	if (execve(executable, array, data->env_array) == -1)
		mini_error (E_GENERAL, lst);
	exit (0);
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * @todo exit codes
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
