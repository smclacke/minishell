/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:02:18 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 14:18:05 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
*/
int	check_for_builtin(t_parser *node)
{
	if (!node)
		return (0);
	else if (mini_strcmp(node->proc->cmd, "exit") == 0)
		return (EXIT);
	else if (mini_strcmp(node->proc->cmd, "cd") == 0)
		return (CD);
	else if (mini_strcmp(node->proc->cmd, "export") == 0)
		return (EXPORT);
	else if (mini_strcmp(node->proc->cmd, "unset") == 0)
		return (UNSET);
	else if (mini_strcmp(node->proc->cmd, "echo") == 0)
		return (5);
	else if (mini_strcmp(node->proc->cmd, "pwd") == 0)
		return (PWD);
	else if (mini_strcmp(node->proc->cmd, "env") == 0)
		return (ENV);
	else
		return (0);
}

/**
 * @param temp parser linked list
 * @param new_str 2d array containing command + strings and flags
 * @param i int representing index of new_str
 * @brief fill's 2d array with content of temp->str
 * @return returns int representing word count.
 * @note commented out bzero in init parser and iterate
 * with j in fill array. super weird it kinda works now but don't really
 * understand why
*/
static char	**fill_array(t_procs *lst, char **new_str)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	new_str[0] = lst->cmd;
	if (lst->str_count == 0 && lst->hd_count == 0)
	{
		new_str[i] = NULL;
		return (new_str);
	}
	while (j < lst->str_count)
	{
		new_str[i] = lst->str[j];
		i++;
		j++;
	}
	new_str[i] = NULL;
	return (new_str);
}

/**
 * @param lst parser linked list
 * @brief set's linked list from cmd to next cmd to 2d array
 * cmd at 0, plus args at 1 , 2 etc.
 * @note this needs to put the commands and the strs in an array
*/
char	**get_argv(t_parser *lst)
{
	char		**new_str;
	int			i;

	new_str = NULL;
	i = lst->proc->str_count;
	new_str = (char **)mini_malloc(sizeof (char *) * (i + 2));
	new_str = fill_array(lst->proc, new_str);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

/**
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
*/
int	mini_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
}

/**
 * @param data struct to be updated with fd's and 2d arrays for later use
 * @param env 
 * @brief intitializes struct before further use
*/
void	init_execute_struct(t_execute *data)
{
	data->fork_pid = -1;
	data->pipe_left[READ] = -1;
	data->pipe_left[WRITE] = -1;
	data->pipe_right[READ] = -1;
	data->pipe_right[WRITE] = -1;
	data->path = NULL;
	data->env_array = NULL;
	data->in = -1;
	data->out = -1;
	data->count = 0;
	data->error = true;
}
