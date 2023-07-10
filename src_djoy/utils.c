/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:13:16 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/10 20:28:45 by dreijans      ########   odam.nl         */
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

/* 
	function that checks for the corresponding built-in
	maybe needs to be a bool?
	needs to be scalable, now only works with argv[1]
*/
void	check_for_builtin(char **argv, t_env *env)
{
	(void) env;
	if (ft_strcmp(argv[1], "echo") == 0)// isnt [1] when I use the prompt
		ft_echo(argv);
	if (ft_strcmp(argv[1], "cd") == 0)//same same
		ft_cd(argv[2]);//is going to be what's parsed
	if (ft_strcmp(argv[1], "pwd") == 0)
		ft_pwd(NULL);
	// if (ft_strcmp(argv[1], "export") == 0)
	// 	ft_export(argv, env);
	else
		exit(EXIT_FAILURE);//not really necesary
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


void	print_list(t_env *env)
{
	// while (env != NULL)
	// {
	// 	printf("%s\n", env->key);
	// 	env = env->next;
	// }
	while (env != NULL)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}

//& gives * and &bla[1] gives **..... wellll