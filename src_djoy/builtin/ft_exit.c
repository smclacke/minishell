/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 14:49:36 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/01 13:02:21 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param str string to convert
 * @brief converts array to long long int
 * @todo actually make it into long long
*/
// long long	atoll(char *str)
// {
// 	long long	i;
// 	long long	sign;
// 	long long	number;

// 	number = 0;
// 	sign = 1;
// 	i = 0;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			sign = sign * -1;
// 		i++;
// 	}
// 	while (ft_isdigit(str[i]))
// 	{
// 		number = number * 10 + str[i] -48;
// 		i++;
// 	}
// 	return (number * sign);
// }

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
*/
void	ft_exit(t_parser *node)
{
	// long long	error;

	// error = atoi(node->str);
	// if (node->next->next)
	// {
	// 	put_custom_error(node, "exit");
	// 	return ;
	// }
	// node = node->next;
	// while (node->next)//loop through nodes else loop through string when parsing correct
	// {
	// 	if (ft_isalnum(node->str) != 0)
	// 	{
	// 		exit(error); //does this display the right error number?
	// 		bash-3.2$ exit 1
	// 		exit
	// 		➜  ~ echo $?
	// 		1
	// 	}
	// 	if ()
	// }
	while (node->next)//loop through nodes else loop through string when parsing correct
	{
		if (node->next != NULL)
		{
			put_custom_error(node, "exit");
			return ;
		}
		node = node->next;
	}
}

// ➜  ~ bash
// bash-3.2$ exit
// exit
// ➜  ~ echo $
// $
// ➜  ~ echo $?
// 0
//--------------------
// ➜  ~ bash
// bash-3.2$ exit
// exit
// ➜  ~ echo $?
// 0
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 1
// exit
// ➜  ~ $?
// zsh: command not found: 1
//--------------------
// ➜  ~ bash
// bash-3.2$ exit poop
// exit
// bash: exit: poop: numeric argument required
// ➜  ~ $?
// zsh: command not found: 255
//--------------------
// ➜  ~ bash
// bash-3.2$ exit 1 2
// exit
// bash: exit: too many arguments
// bash-3.2$ $?
// bash: 1: command not found
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