/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nonesense.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 14:49:26 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 22:58:44 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/shelly.h"

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_list(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s=%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_list_key(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->key);
// 		env = env->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_list_value(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->value);
// 		env = env->next;
// 	}
// }

// /**
//  * @param data execute struct
//  * @brief frees content of execute struct plus struct
// */
// void	free_data(t_execute *data)
// {
// 	ft_free_arr(data->env_array);
// 	free(data->path);
// 	free (data);
// }

// /**
//  * @param lst parser linked list
//  * @brief returns list size
// */
// int	list_iter(t_parser *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		i++;
// 		lst = lst->next;
// 	}
// 	return (i);
// }

// EVEN OLDER MINIFORKS
// void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
// {
// 	char		*executable;
// 	char		**argv;
// 	int			cmd_type;

// 	init_pipes_child(data, lst);
// 	if (redirect(lst, data) == false)
// 		exit (lst->exit_code);
// 	if (data->error == false)
// 		exit (43);
// 	cmd_type = check_for_builtin(lst);
// 	if (cmd_type != 0)
// 	{
// 		do_builtin(lst, env, cmd_type);
// 		exit (lst->exit_code);
// 	}
// 	if (lst->proc->cmd == NULL)
// 		exit (127);
// 	executable = check_access(*env, lst, data);
// 	executable_check(lst, data, executable);
// 	// if (executable == NULL)
// 	// {
// 	// 	put_execute_error(lst);
// 	// 	exit (45);
// 	// }
// 	// if (data->error == false)
// 	// 	exit (lst->exit_code);
// 	// if (access(executable, X_OK) == -1)
// 	// {
// 	// 	put_permission_error(lst);
// 	// 	exit (EXIT_FAILURE);
// 	// }
// 	data->env_array = list_to_string(*env);
// 	argv = get_argv(lst);
// 	if (argv == NULL)
// 		exit(47);
// 	if (execve(executable, argv, data->env_array) == -1)
// 	{
// 		lst->exit_code = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// }

//OLD MINIFORKS
// void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
// {
// 	char		*executable;
// 	char		**argv;
// 	int			cmd_type;

// 	init_pipes_child(data, lst);
// 	if (redirect(lst, data) == false)
// 		exit (lst->exit_code);
// 	if (data->error == false)
// 		exit (EXIT_FAILURE);
// 	cmd_type = check_for_builtin(lst);
// 	if (cmd_type != 0)
// 	{
// 		do_builtin(lst, env, cmd_type);
// 		exit (lst->exit_code);
// 	}
// 	executable = check_access(*env, lst, data);
// 	executable_check(lst, data, executable);
// 	data->env_array = list_to_string(*env);
// 	argv = get_argv(lst);
// 	// if (argv == NULL)
// 	// 	exit();
// 	if (execve(executable, argv, data->env_array) == -1)
// 		exit(EXIT_FAILURE);
// }