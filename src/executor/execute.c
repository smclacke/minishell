/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:56:26 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/21 17:08:48 by dreijans      ########   odam.nl         */
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
			// if (temp_path == NULL)
			// 	mini_error (E_MALLOC, node);
			data->path = ft_split(temp_path, ':');
			if (data->path == NULL)
				node->exit_code = E_MALLOC;
				// mini_error (E_MALLOC, node);// or just exit?
			free (temp_path);
			if (data->path == NULL)
				node->exit_code = E_MALLOC;
				// mini_error (E_MALLOC, node);
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
		put_execute_error(node);// here mini_error aangezet
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
 * exitstatus global needed 
 * NORM IT
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

	printf("exit code search 12[%d]\n", lst->exit_code);
	init_pipes_child(data, lst);
	printf("exit code search 13[%d]\n", lst->exit_code);
	redirect(lst, data);
	printf("exit code search 14[%d]\n", lst->exit_code);
	if (data->error == false)
		exit (43);
	cmd_type = check_for_builtin(lst);
	if (cmd_type != 0)
	{
		do_builtin(lst, env, cmd_type);
		printf("exit code search 15[%d]\n", lst->exit_code);
		// lst->exit_code = EXIT_SUCCESS;//need this?
		// mini_error(EXIT_SUCCESS, lst);
		exit (EXIT_SUCCESS);//exit success??
	}
	printf("exit code search 16[%d]\n", lst->exit_code);
	if (!lst->proc->cmd) // we do need this?
		exit (44);
	printf("exit code search 17[%d]\n", lst->exit_code);
	executable = check_access(*env, lst, data);
	printf("exit code search 18[%d]\n", lst->exit_code);
	if (executable == NULL)
	{
		put_execute_error(lst);
		printf("exit code search 19[%d]\n", lst->exit_code);
		exit (45);
	}
	printf("exit code search 20[%d]\n", lst->exit_code);
	if (data->error == false)
	{
		printf("exit code search 23[%d]\n", lst->exit_code);
		exit (lst->exit_code);
	}
	printf("exit code search 21[%d]\n", lst->exit_code);
	if (access(executable, X_OK) == -1)
	{
		put_permission_error(lst);
		exit (EXIT_FAILURE);
	}
	printf("exit code search 22[%d]\n", lst->exit_code);
	data->env_array = list_to_string(*env);
	argv = get_argv(lst);
	if (argv == NULL)
		exit(47);
	if (execve(executable, argv, data->env_array) == -1)
	{
		// mini_error(99, lst);
		lst->exit_code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
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
		lst->exit_code = E_GENERAL;
		// mini_error (E_GENERAL, lst);
	printf("exit code search 3[%d]\n", lst->exit_code);
	init_heredoc(lst, env);
	printf("exit code search 4[%d]\n", lst->exit_code);
	if (single_builtin_cmd(lst, env, data) == true)
		return ;
	printf("exit code search 5[%d]\n", lst->exit_code);
	pipeline(lst, env, data);
	printf("exit code search 6[%d]\n", lst->exit_code);
	close_all(data, lst);
	printf("exit code search 7[%d]\n", lst->exit_code);
	waitpid(data->fork_pid, NULL, 0);//insert lst->exit_code?
	while (wait(NULL) != -1)
		(void)NULL;
	printf("exit code search 8[%d]\n", lst->exit_code);
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
	printf("exit code search 1[%d]\n", lst->exit_code);
	init_execute_struct(data);
	ft_expand(lst, env);
	printf("exit code search 2[%d]\n", lst->exit_code);
	build(lst, env, data);
	printf("exit code search 9[%d]\n", lst->exit_code);
	free (data);
}
