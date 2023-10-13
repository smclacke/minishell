/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/13 17:52:55 by dreijans      ########   odam.nl         */
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
	t_execute	data;

	init_execute_struct(&data, *env);
	ft_expand(lst, env);
	build(lst, env, &data);
}

void	build(t_parser *lst, t_env **env, t_execute *data)
{
	t_parser	*head;

	head = lst;
	while (head)
	{
		if (check_redirect(head) != 0)
			redirect_outfile(head, env, data);
		head = head->next;
	}
	head = lst;
	while (head)
	{
		if (check_for_child_builtin(head) != 0)
		{
			do_builtin(head, env);
			return ;
		}
		head = head->next;
	}
	close (STDIN_FILENO);
	// return ;
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
