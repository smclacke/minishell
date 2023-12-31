/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:28:45 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 18:44:01 by dreijans      ########   odam.nl         */
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
int	micro_strcmp(char *s1, char *s2)
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
*/
void	micro_check_for_builtin(t_parser *lst, t_env *env)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		micro_ft_echo(lst);
	if (ft_strcmp(lst->cmd, "cd") == 0)
		micro_ft_cd(lst, env);
	if (ft_strcmp(lst->cmd, "pwd") == 0)
		micro_ft_pwd();
	if (ft_strcmp(lst->cmd, "export") == 0)
		micro_ft_export(lst, env);
	if (ft_strcmp(lst->cmd, "unset") == 0)//gives pwd not the entire path after unsetting
		micro_ft_unset(lst, env);
	if (ft_strcmp(lst->cmd, "env") == 0)
		micro_env(env);
}
