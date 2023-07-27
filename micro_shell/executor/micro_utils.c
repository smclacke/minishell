/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:28:45 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/27 15:24:36 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param string argument given to perror
 * @param error int errno given to exit
 * @brief provides correct error message and exits
*/
void	micro_error(char *string, int error)
{
	perror(string);
	exit(error);
}

/**
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
*/
int	micro_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

/**
 * @param node linked list
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
 * @return EXIT_FAILURE if no built-in was found
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) exit(EXIT_FAILURE) is it really neccesary?
 * 3) MAYBE MAKE IT A BOOL?
*/
void	micro_check_for_builtin(t_parser *node, t_env *env)
{
	if (ft_strcmp(node->cmd, "echo") == 0)
		micro_echo(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		micro_cd(node, env);
	if (ft_strcmp(node->cmd, "pwd") == 0)
		micro_pwd(NULL, env);
	if (ft_strcmp(node->cmd, "export") == 0)
		micro_export(node, env);
	if (ft_strcmp(node->cmd, "unset") == 0)//gives pwd not the entire path after unsetting
		micro_unset(node, env);
	if (ft_strcmp(node->cmd, "env") == 0)
		micro_env(env);
	else
		exit(EXIT_FAILURE);
}
