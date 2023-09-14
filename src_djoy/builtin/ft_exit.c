/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 14:49:36 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/14 21:46:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"
// #include "../../include/djoyke.h"
#include <limits.h>
#include <stdint.h>

#define LONG_MIN_STR "-9223372036854775808"
#define LONG_MAX_STR "9223372036854775807"
#define TOO_MANY_ARG "exit\nminishell: exit: too many arguments\n"


// MAX = GOOD
// exit 9223372036854775807
// MIN = GOOD
// exit -9223372036854775808

// MORE THAN MAX = BAD
// exit 9223372036854775808 // DOESNT WORK !!
// exit 9223372036854775819 // WORKS

// LESS THAN MAX = GOOD
// exit 9223372036854775708 // WORKS
// exit 9223372036854775803 // WORKS

// LESS THAN MIN = BAD
// exit -9223372036854775810 // WORKS
// exit -9223372036854775809 // DOESNT WORK !!

// MORE THAN MIN = GOOD
// exit -9223372036854775805 // WORKS
// exit -9223372036854775706 // WORKS


// printf("LLONG_MAX = [%lld]\n", LLONG_MAX);
// printf("LLONG_MIN CAL = [%lld]\n", (LLONG_MIN / 10) * -1);
// printf("LLONG_MIN = [%lld]\n", LLONG_MIN);
// printf("LLONG_MAX CAL = [%lld]\n", (LLONG_MAX / 10));
// LLONG_MAX = [9223372036854775807]
// LLONG_MIN = [-9223372036854775808]
// LLONG_MAX CAL = [922337203685477580]
// LLONG_MIN CAL = [922337203685477580]



/**
 * @param str string to convert
 * @brief converts array to long long int
 * @todo nothing but limits.h is very cool wow
 * 		write (1, LONG_MIN_STR, sizeof(LONG_MIN_STR));
 * 		zo cool he size changes when long_min_str changes
 * 		remember forever
*/
static long long int	mini_atoll(t_parser *node, char *str)
{
	int			i;
	int			sign;
	long long	number;

	number = 0;
	sign = 1;
	i = 0;
	if (mini_strcmp(str, LONG_MIN_STR) == 0)
		return (LLONG_MIN);
	if (mini_strcmp(str, LONG_MAX_STR) == 0)
		return (LLONG_MAX);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	printf("LLONG_MAX = [%lld]\n", LLONG_MAX);
	printf("LLONG_MIN = [%lld]\n", LLONG_MIN);
	printf("LLONG_MAX CAL = [%lld]\n", (LLONG_MAX / 10));
	printf("LLONG_MIN CAL = [%lld]\n", (LLONG_MIN / 10) * -1);
	while (ft_isdigit(str[i]))
	{
		printf("number = [%lld]\n", number);
		if ((number > (LLONG_MAX / 10) && ((number * 10 + str[i] - 48) > LLONG_MAX % 10)) || (number > (LLONG_MAX / 10)))
		{
			if (number == number + 8)
			{	
				printf("you?\n");
				put_custom_error(node, "exit");
				exit(255);
			}
		}
		else if (sign == -1)
		{
			if (number > (LLONG_MAX / 10) * -1)
			{
				printf("or you?\n");
				put_custom_error(node, "exit");
				exit(255);
			}
		}
		number = number * 10 + str[i] - 48;
		i++;
	}
	printf("last number = [%lld]\n", number * sign);
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