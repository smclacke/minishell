/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:05 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 17:24:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node parsed list
 * @brief checks if content is a digit
*/
static void	digit_check(char *str, t_parser *lst)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] != '\0')
		i++;
	while (str[i] && ft_isdigit(str[i]) != 0)
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		lst->exit_code = 255;
		exit (lst->exit_code);
	}
}

/**
 * @param node parsed list
 * @brief checks if argument count is more than 1
*/
static void	arg_check(t_parser *lst)
{
	if (lst->proc->str_count > 1)
	{
		write(STDERR_FILENO, TOO_MANY_ARG, sizeof(TOO_MANY_ARG));
		lst->exit_code = E_GENERAL;
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
	digit_check(lst->proc->str[0], lst);
	arg_check(lst);
	if (lst->exit_code != 0)
		return ;
	error = ft_atoi(lst->proc->str[0]);
	if (error > 255)
	{
		put_custom_error(lst, lst->proc->str[0], "exit");
		exit(255);
	}
	write(STDERR_FILENO, "exit\n", 6);
	exit(error);
}
