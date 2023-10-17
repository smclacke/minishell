/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:18:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 16:36:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
	if (mini_strcmp(node->cmd, "exit") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "echo") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "cd") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "pwd") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "export") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "unset") == 0)
		return (true);
	else if (mini_strcmp(node->cmd, "env") == 0)
		return (true);
	else
		return (false);
}

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find meta_chars: 
 * $, >>, <<, >, <, |
*/
bool	check_for_meta(t_parser *node)
{
	if (!node)
		return (false);
	else if (mini_strcmp(node->meta, ">>") == 0)
	{
		printf("expander:		Output Append\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, "<<") == 0)
	{
		printf("expander:		here doc\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, ">") == 0)
	{
		printf("expander:		output Redirect\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, "<") == 0)
	{
		printf("expander:		Input Redirect\n");
		return (true);
	}
	else if (mini_strcmp(node->meta, "|") == 0)
	{
		printf("expander:		pipe\n");
		return (true);
	}
	else
		return (false);
}