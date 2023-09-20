/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 14:49:36 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/20 14:56:41 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
#include <limits.h>
#include <stdint.h>

#define LONG_MAX_STR "9223372036854775807"
#define TOO_MANY_ARG "exit\nminishell: exit: too many arguments\n"

/**
 * @param str string to convert
 * @brief converts array to long long int
 * @todo nothing but limits.h is very cool wow
 * 		write (1, LONG_MIN_STR, sizeof(LONG_MIN_STR));
 * 		zo cool he size changes when long_min_str changes
 * 		remember forever
*/
static unsigned long long	mini_atoll(t_parser *node, char *str)
{
	size_t					i;
	int						sign;
	long long				num_check;
	unsigned long long		number;

	number = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putstr_fd(": positive digit argument required\n", STDOUT_FILENO);
		}
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + str[i] -48;
		i++;
	}
	num_check = number * sign;
	printf("number = [%lld]\n", num_check);
	if (num_check < 0)
		put_custom_error(node, str);
	return (number * sign);
}

/**
 * @param node parsed list
 * @brief exits the program and displays corresponding error number
 * @todo 
 * 1) more than 2? place error  (don't exit)
 * 2) equal to 2? (exit)
 * 		- 1) is it numeric?
 * 		- 2) ato long long weeeh
 * 		- 3) do freeking exit codes
 * 		- up until 255 it displays 255
 * 		- else should %256 to get the correct exit code if its numeric
 * 		- above long long is considered as characters
 * 		so same exit code as characters
 * 		- 4) not numeric display error message  (still exit)
 * 3) only exit? exit 0 (EXIT_SUCCES) (exit)
 * exit | something doesnt print exit (also exit in pipe?? so sad)
 * check alpha numeric first and then the arguments if more than 1 (done)
 * 
 * make: *** [djoyke] Error 20
 * bash-3.2$ echo $?
 * 2
*/
void	ft_exit(t_parser *node)
{
	long long	error;
	int			i;

	i = 0;
	if (!node->next && node->data_type->cmd)
		exit(0);
	node = node->next;
	while (node->data_type->strs[i])
	{
		if (node->data_type->strs[0] == '-')
			i++;
		if (ft_isdigit(node->data_type->strs[i]) == 0)
		{
			put_custom_error(node, "exit");
			exit(255); //needs to be return, int error needs to be 
		}
		i++;
	}
	if (node->next)
	{
		write(STDOUT_FILENO, TOO_MANY_ARG, sizeof(TOO_MANY_ARG));
		exit(1);
	}
	error = mini_atoll(node, node->data_type->strs);
	if (error > 255)
		error = error % 256;
	write(STDOUT_FILENO, "exit\n", 5);
	exit(error); //needs to be a return
}

// ➜  ~ bash
// bash-3.2$ exit 
// exit
// ➜  ~ echo $
// $
// ➜  ~ echo $?
// 0
// DONE!!!!!
//--------------------
// ➜  ~ bash
// bash-3.2$ exit
// exit
// ➜  ~ echo $?
// 0
// DONE!!!!!!
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 1
// exit
// ➜  ~ $?
// zsh: command not found: 1
// DONE!!!!!!!
//--------------------
// ➜  ~ bash
// bash-3.2$ exit poop
// exit
// bash: exit: poop: numeric argument required
// ➜  ~ $?
// zsh: command not found: 255
// DONE!!!!!
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 1 2
// exit
// bash: exit: too many arguments
// bash-3.2$ $?
// bash: 1: command not found
// DONE!!!!!
//--------------------
// ➜  ~ bash
// bash-3.2$ exit -5
// exit
// ➜  ~ echo $?
// 251
// DONE!!!!!!!!!
//--------------------
// bash-3.2$ exit 9223372036854775808
// exit
// bash: exit: 9223372036854775808: numeric argument required
// ➜  ~ echo $?
// 255
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 9223372036854775807
// exit
// ➜  ~ $?
// zsh: command not found: 255
//--------------------
// ➜  ~ bash exit 20
// bash: exit: No such file or directory
// ➜  ~ $?
// zsh: command not found: 127
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 20
// exit
// ➜  ~ $?
// zsh: command not found: 20
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 9223372036854775806
// exit
// ➜  ~ $?
// zsh: command not found: 254
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 9223372036854775805
// exit
// ➜  ~ $?
// zsh: command not found: 253
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 9223372036854775804
// exit
// ➜  ~ $?
// zsh: command not found: 252
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 256
// exit
// ➜  ~ $?
// zsh: command not found: 0
// ➜  ~