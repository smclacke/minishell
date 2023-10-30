/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_two.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:02:18 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/29 16:10:27 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param exp expand struct
 * @brief frees parts of the struct and entire struct
*/
void	free_remain_struct(t_expand *data)
{
	if (data == NULL)
		return ;
	free (data->before_dollar);
	free (data->env_value);
	free (data->comp_str);
	free (data);
}

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
 * @param node linked list
 * @brief checks arguments to find output or input redirect
 * @todo add append with O_APPEND and << 
*/
bool	check_redirect(t_parser *node)
{
	if (!node)
		return (false);
	if (mini_strcmp(node->meta, ">") == 0)
		return (true);
	else if (mini_strcmp(node->meta, "<<") == 0)
		return (true);
	else if (mini_strcmp(node->meta, "<") == 0)
		return (true);
	// else if (mini_strcmp(node->meta, "<<") == 0)
	// 	return (true); or add append to redirect_output
	else
		return (false);
}

static int	count_words(t_parser *temp)
{
	int i;

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
 * @param lst parser linked list
 * @brief set's linked list from cmd to next cmd to 2d array
 * cmd at 0, plus args at 1 , 2 etc.
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
		mini_error("malloc", errno);
	temp = lst->next;
	new_str[0] = lst->cmd;
	i = 1;
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
