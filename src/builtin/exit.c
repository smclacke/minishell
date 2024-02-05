/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:05 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/05 20:12:00 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node parsed list
 * @brief checks if content is a digit
 * @todo is this still working?
*/
static void	digit_check(t_parser *lst)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (lst->proc->str[i])
	{
		while (ft_isdigit(lst->proc->str[i][j]) != 0)
		{
			j++;
			if (ft_isdigit(lst->proc->str[i][j]) == 0)
			{
				put_custom_error(lst, "exit");
				exit(255);
			}
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
	if (lst->proc->str_count > 1)
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
 * check it thouroughly
*/
void	ft_exit(t_parser *lst)
{
	long long	error;
	int			exit_status;
	int			status;

	exit_status = 0;
	status = 0;
	if (lst->proc->proc_count != 1)
		return ;
	if (lst->proc->str_count == 0)
		exit_with_stat(exit_status, status);
	digit_check(lst);
	arg_check(lst);
	error = ft_atoi(lst->proc->str[0]);
	if (error > 255)
	{
		put_custom_error(lst, "exit");
		exit(255);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit(error);
}
