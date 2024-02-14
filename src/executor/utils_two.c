/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_two.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:02:18 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/14 18:52:49 by dreijans      ########   odam.nl         */
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
 * @note do we need this?? commented out bzero in init parser and iterate
 * with j in fill array. super weird it kinda works now but don't really
 * understand why
 * @todo norm
*/
// static char	**fill_array(t_procs *lst, char **new_str, int i)
static char	**fill_array(t_procs *lst, char **new_str)
{

	int j;
	int i;

	j = 0;
	i = 0;
	new_str[0] = lst->cmd;
	i++;
	// fprintf(stderr, "lst->str[%s]\n", lst->str[0]);
	//whats wrong with the strings from the parser? is the string NULL terminated
	if (lst->str_count == 0)
		return (new_str = NULL);
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
 * @todo error code
 * @note this needs to put the commands and the strs in an array
*/
char	**get_argv(t_parser *lst)
{
	char		**new_str;
	int			i;

	new_str = NULL;
	i = lst->proc->str_count;
	new_str = (char **)malloc(sizeof (char *) * (i + 2));
	if (new_str == NULL)
		mini_error(E_MALLOC, lst);
	// new_str[0] = lst->proc->cmd;
	// i = 1;
	new_str = fill_array(lst->proc, new_str);
	// new_str = fill_array(lst->proc, new_str, i);
	return (new_str);
}
