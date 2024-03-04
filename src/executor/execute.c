/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:56:26 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/04 17:51:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks environment to find PATH put it in temp_path
 * split temp_path into 2d array and put it in the struct data->path
*/
static bool	parse_path(t_env *env, t_execute *data, t_parser *node)
{
	char	*temp_path;

	temp_path = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			if (env->value == NULL)
				return (false);
			temp_path = mini_substr(env->value, 0, ft_strlen(env->value));
			data->path = ft_split(temp_path, ':');
			if (data->path == NULL)
				node->exit_code = E_MALLOC;
			free (temp_path);
			if (data->path == NULL)
				node->exit_code = E_MALLOC;
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
*/
void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;
	char		**argv;
	int			cmd_type;

	init_pipes_child(data, lst);
	if (redirect(lst, data) == false)
		exit (lst->exit_code);
	if (data->error == false)
		exit (EXIT_FAILURE);
	if (shelly_strcmp(lst->proc->cmd, "") == 0)
		put_exit_error(lst);
	cmd_type = check_for_builtin(lst);
	if (cmd_type != 0)
	{
		do_builtin(lst, env, cmd_type);
		exit (lst->exit_code);
	}
	executable = check_access(*env, lst, data);
	executable_check(lst, data, executable);
	data->env_array = list_to_string(*env);
	argv = get_argv(lst);
	if (execve(executable, argv, data->env_array) == -1)
		no_valid_command(lst, executable);
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * @todo norm it
 */
static void	build(t_parser *lst, t_env **env, t_execute *data)
{
	int		status;

	status = 0;
	if (!lst)
		lst->exit_code = E_GENERAL;
	init_heredoc(lst, env);
	if (single_builtin_cmd(lst, env, data) == true)
		return ;
	pipeline(lst, env, data);
	close_all(data, lst);
	waitpid(data->fork_pid, &status, 0);
	exit_status(status, lst);
	while (wait(NULL) != -1)
		(void)NULL;
	close_hd_fd(lst);
	unlink_heredoc(lst);
}

/**
 * @param env environment linked list
 * @param lst linked list parsed
 * @brief calls functions needed to start executing process
*/
void	execute(t_env **env, t_parser *lst)
{
	t_execute	*data;

	data = mini_malloc(sizeof(t_execute));
	init_execute_struct(data);
	ft_expand(lst, env);
	lst->exit_code = 0;
	build(lst, env, data);
	free(data);
}
