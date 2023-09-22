/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 14:49:36 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/21 17:14:12 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
#include <limits.h>

#define TOO_MANY_ARG "exit\nminishell: exit: too many arguments\n"

/**
 * @param node parsed list
 * @brief checks if content is a digit
*/
void	digit_check(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst->data_type->strs[i])
	{
		if (ft_isdigit(lst->data_type->strs[i]) == 0)
		{
			put_custom_error(lst, "exit");
			exit(255);
		}
		i++;
	}
}

/**
 * @param node parsed list
 * @brief checks if argument count is more than 1
*/
void	arg_check(t_parser *lst)
{
	if (lst->next)
	{
		write(STDOUT_FILENO, TOO_MANY_ARG, sizeof(TOO_MANY_ARG));
		exit(1);
	}
}

/**
 * @param node parsed list
 * @brief exits the program and displays corresponding error number
*/
void	ft_exit(t_parser *lst)
{
	long long	error;
	int			exit_status;
	int			status;

	exit_status = 0;
	status = 0;
	if (!lst->next && lst->data_type->cmd)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);//exit from prev child process
		exit(exit_status);
	}
	lst = lst->next;
	digit_check(lst);
	arg_check(lst);
	error = ft_atoi(lst->data_type->strs);
	if (error > 255)
	{
		put_custom_error(lst, "exit");
		exit(255);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit(error);
}
