/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:56:26 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/24 21:48:20 by dreijans      ########   odam.nl         */
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
 * @todo exit codes
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
 * @todo
 * NORM IT
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
		exit (43);
	cmd_type = check_for_builtin(lst);
	if (cmd_type != 0)
	{
		do_builtin(lst, env, cmd_type);
		exit (lst->exit_code);
	}
	if (lst->proc->cmd == NULL)
		exit (127);
	executable = check_access(*env, lst, data);
	executable_check(lst, data, executable);
	data->env_array = list_to_string(*env);
	argv = get_argv(lst);
	if (argv == NULL)
		exit(47);
	if (execve(executable, argv, data->env_array) == -1)
		exit(EXIT_FAILURE);
}

/**
 * @param lst linked list from parser
 * @param env linked list with environment
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief determines how many times needs to fork
 * pipes and makes child process
 * @todo norm it!
 */
static void	build(t_parser *lst, t_env **env, t_execute *data)
{
	int	status;

	status = 0;
	if (!lst)
		lst->exit_code = E_GENERAL;
	// printf("exit code search 3[%d]\n", lst->exit_code);
	init_heredoc(lst, env);
	// printf("exit code search 4[%d]\n", lst->exit_code);
	if (single_builtin_cmd(lst, env, data) == true)
		return ;
	// printf("exit code search 5[%d]\n", lst->exit_code);
	pipeline(lst, env, data);
	// printf("exit code search 6[%d]\n", lst->exit_code);
	close_all(data, lst);
	// printf("exit code search 7[%d]\n", lst->exit_code);
	waitpid(data->fork_pid, &status, 0);
	// printf("status 1[%d]\n", status);
	// printf("exit code search 8[%d]\n", lst->exit_code);
	exit_status(status, lst);
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

	data = mini_malloc(sizeof(t_execute));
	// printf("exit code search 1[%d]\n", lst->exit_code);
	init_execute_struct(data);
	ft_expand(lst, env);
	// printf("exit code search 2[%d]\n", lst->exit_code);
	build(lst, env, data);
	// printf("exit code search 9[%d]\n", lst->exit_code);
	free (data);
}
