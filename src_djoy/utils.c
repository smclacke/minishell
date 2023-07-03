/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:13:16 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/03 15:53:40 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* 
	function that checks for the corresponding built-in
	maybe needs to be a bool?
	needs to be scalable, now only works with argv[1]
*/
void	check_for_builtin(char **argv)
{
	if (ft_strcmp(argv[1], "echo") == 0)// isnt [1] when I use the prompt
		ft_echo(*argv);
	if (ft_strcmp(argv[1], "cd") == 0)//same same
		ft_cd(argv[2]);//is going to be what's parsed
	else
		exit(EXIT_FAILURE);//not really necesary
}

/* error message with perror */
void	mini_error(char *string, int error)
{
	perror(string);
	exit(error);
}

// void	print_list(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->content);
// 		env = env->next;
// 	}
// }

//& gives * and &bla[1] gives **..... wellll