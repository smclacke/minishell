/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:05 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/19 22:53:55 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
#include <limits.h>

#define TOO_MANY_ARG "exit\nminishell: exit: too many arguments\n"

/**
 * @param node parsed list
 * @brief checks if content is a digit
*/
static void	digit_check(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst->str[i])
	{
		if (ft_isdigit(lst->str[i]) == 0)
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
 * @todo does it need to be exit(1)?
*/
static void	arg_check(t_parser *lst)
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
 * @todo check for exitstatus line 68 if it's exit status from prev child process
*/
void	ft_exit(t_parser *lst)
{
	long long	error;
	int			exit_status;
	int			status;

	exit_status = 0;
	status = 0;
	if (!lst->next && lst->cmd)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);//exit from prev child process
		exit(exit_status);
	}
	lst = lst->next;
	digit_check(lst);
	arg_check(lst);
	error = ft_atoi(lst->str);
	if (error > 255)
	{
		put_custom_error(lst, "exit");
		exit(255);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit(error);
}
