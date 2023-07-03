/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:13:16 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/03 10:50:44 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* 
	function that checks for the corresponding built-in
	maybe needs to be a bool?
	needs to be scalable, now only works with argv[1]
*/
void	check_for_builtin(char *argv[1])
{
	if (ft_strcmp(argv[1], "echo") == 0)
		ft_echo(&argv[1]);
	// if (ft_strcmp(argv[1], "cd") == 0)
	// 	ft_cd(&argv[1]);
	else
		exit(EXIT_FAILURE);//not really necesary
}
