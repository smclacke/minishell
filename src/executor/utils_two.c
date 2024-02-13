/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_two.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:02:18 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/13 13:45:45 by dreijans      ########   odam.nl         */
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
 * @brief count's amount of words including cmd for 2d array
 * @return returns int representing word count.
 * @note do we need this??
 * @todo norm 
*/
static int	count_words(t_procs *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		// if (temp->cmd)
		// 	break ;
		if (temp->str[i])
			i++;
		// if (temp->meta)
		// 	temp = temp->next;
		// temp = temp->next;
	}
	return (i);
}

/**
 * @param temp parser linked list
 * @param new_str 2d array containing command + strings and flags
 * @param i int representing index of new_str
 * @brief fill's 2d array with content of temp->str
 * @return returns int representing word count.
 * @note do we need this??
 * @todo norm
*/
static char	**fill_array(t_parser *temp, char **new_str, int i)
{
	int j;

	j = 0;
	while (temp->proc->str[j])
	{
		// if (temp->proc->cmd)
		// 	break ;
		if (temp->proc->str[j])
		{
			new_str[i] = temp->proc->str[j];
			i++;
			j++;
		}
		// if (temp->meta)
		// 	temp = temp->next;
		// temp = temp->next;
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
	t_parser	*temp;
	char		**new_str;
	int			i;

	temp = lst->next;
	i = count_words(temp->proc);
	new_str = (char **)malloc(sizeof (char *) * (i + 2));
	if (new_str == NULL)
		mini_error(E_MALLOC, lst);
	new_str[0] = lst->proc->cmd;
	i = 1;
	new_str = fill_array(temp, new_str, i);
	return (new_str);
}
