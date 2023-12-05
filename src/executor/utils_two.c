/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_two.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:02:18 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/04 18:08:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
*/
bool	check_for_builtin(t_parser *node)
{
	if (!node)
		return (false);
	else if (mini_strcmp(node->cmd, "exit") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "cd") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "export") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "unset") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "echo") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "pwd") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "env") == 0)
		return (true);
	else
		return (false);
}

/**
 * @param temp parser linked list
 * @brief count's amount of words including cmd for 2d array
 * @return returns int representing word count.
*/
static int	count_words(t_parser *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->cmd)
			break ;
		if (temp->str)
			i++;
		if (temp->meta)
			temp = temp->next;
		temp = temp->next;
	}
	return (i);
}

/**
 * @param temp parser linked list
 * @param new_str 2d array containing command + strings and flags
 * @param i int representing index of new_str
 * @brief fill's 2d array with content of temp->str
 * @return returns int representing word count.
*/
static char	**fill_array(t_parser *temp, char **new_str, int i)
{
	while (temp)
	{
		if (temp->cmd)
			break ;
		if (temp->str)
		{
			new_str[i] = temp->str;
			i++;
		}
		if (temp->meta)
			temp = temp->next;
		temp = temp->next;
	}
	new_str[i] = NULL;
	return (new_str);
}

/**
 * @param lst parser linked list
 * @brief set's linked list from cmd to next cmd to 2d array
 * cmd at 0, plus args at 1 , 2 etc.
 * @todo error code
*/
char	**get_argv(t_parser *lst)
{
	t_parser	*temp;
	char		**new_str;
	int			i;

	temp = lst->next;
	i = count_words(temp);
	new_str = (char **)malloc(sizeof (char *) * (i + 2));
	if (new_str == NULL)
		mini_error("malloc", "E_MALLOC", lst);
	temp = lst->next;
	new_str[0] = lst->cmd;
	i = 1;
	new_str = fill_array(temp, new_str, i);
	return (new_str);
}
