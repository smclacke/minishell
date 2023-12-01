/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:05 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/01 19:44:26 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"
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
 * @param exit_status int containing exit status from previous child process
 * @param status int containing exit status
 * @brief exits the program and displays corresponding error number
*/
void	exit_with_stat(int exit_status, int status)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	exit(exit_status);
}

/**
 * @param lst parsed list
 * @brief exits the program and displays corresponding error number
 * @todo check for exitstatus line 68 if it's exit status from prev child process
 * minishell: exit: 7767: positive numeric argument 255 or below required
 * make: *** [Makefile:91: run] Error 255
*/
void	ft_exit(t_parser *lst)
{
	long long	error;
	int			exit_status;
	int			status;

	exit_status = 0;
	status = 0;
	if (lst->n_cmd != 1)
		return ;
	if (!lst->next && lst->cmd)
		exit_with_stat(exit_status, status);
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
