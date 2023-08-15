/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:47:04 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/15 13:08:35 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param string argument given to perror
 * @param error int errno given to exit
 * @brief provides correct error message and exits
*/
void	mini_error(char *string, int error)
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
int	mini_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);

	
	// printf("s1[%s]\n", s1);
	// printf("s2[%s]\n", s2);
	// while (s1[i] && s2[i])
	// {
	// 	if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
	// 		return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
	// 	i++;
	// }
	// return (0);
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
void	do_builtin(t_parser *lst, t_env *env)
{
	if (mini_strcmp(lst->cmd, "echo") == 0)
		ft_echo(lst);
	if (mini_strcmp(lst->cmd, "cd") == 0)
		ft_cd(lst, env);
	if (mini_strcmp(lst->cmd, "pwd") == 0)
		ft_pwd();
	if (mini_strcmp(lst->cmd, "export") == 0)
		ft_export(lst, env);
	if (mini_strcmp(lst->cmd, "unset") == 0)//gives pwd not the entire path after unsetting
		ft_unset(lst, env);
	if (mini_strcmp(lst->cmd, "env") == 0)
		ft_env(env);
}

int	mini_lstsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
