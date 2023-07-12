/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:13:16 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/12 15:48:29 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/**
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
*/
int	ft_strcmp(const char *s1, const char *s2)
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
 * @param argv string to compare
 * @param env string or char to compare with
 * @brief checks arguments to find built-ins: 
 * echo, cd, pwd, export, unset, env and exit
 * @return EXIT_FAILURE if no built-in was found
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) all [i] indexes need to be replaced by actual parsed data
 * 3) exit(EXIT_FAILURE) is it really neccesary?
*/
void	check_for_builtin(char **argv, t_env *env)
{
	(void) env;
	if (ft_strcmp(argv[1], "echo") == 0)
		ft_echo(argv);
	if (ft_strcmp(argv[1], "cd") == 0)
		ft_cd(argv[2]);
	if (ft_strcmp(argv[1], "pwd") == 0)
		ft_pwd(NULL);
	if (ft_strcmp(argv[1], "export") == 0)
		ft_export(argv, env);
	else
		exit(EXIT_FAILURE);
}

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
 * @param env argument given to perror
 * @brief prints linked list containing env key or value
*/
void	print_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
