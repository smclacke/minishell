/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:05 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/20 17:08:53 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node parsed list
 * @brief checks if content is a digit
 * @todo exit codes for the exit at line 30
*/
static void	digit_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]) != 0)
		i++;
	if (str[i] != '\0')
	{
		dprintf(STDERR_FILENO, NON_NUM_ARG, str);
		exit(2);
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
		write(STDERR_FILENO, TOO_MANY_ARG, sizeof(TOO_MANY_ARG));
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
	write(STDERR_FILENO, "exit\n", 5);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	exit(exit_status);
}

/**
 * @param lst parsed list
 * @brief exits the program and displays corresponding error number
 * @todo check for exitstatus line 68 if it's exit status from prev child process
 * is it bad that exit always displays? even with exit > test.txt
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
	arg_check(lst);
	digit_check(lst->proc->str[0]);
	error = ft_atoi(lst->proc->str[0]);
	if (error > 255)
	{
		put_custom_error(lst, "exit");
		exit(255);
	}
	write(STDERR_FILENO, "exit", 5);
	exit(error);
}
