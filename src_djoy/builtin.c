/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 15:41:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/01 17:44:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* compares 2 strings */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

/* function that checks for the corresponding built-in
maybe needs to be a bool? */
void	check_for_builtin(char *argv[1], int argc)
{
	if (argc <= 1)
		exit(EXIT_FAILURE); // should give prompt back
	if (ft_strcmp(argv[1], "echo") == 0)
		ft_echo(&argv[1]);
	else
		exit(EXIT_FAILURE);//not really necesairy?
}

void	*ft_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

/*

NAME
     echo -- write arguments to the standard output

SYNOPSIS
     echo [-n] [string ...]

DESCRIPTION
     The echo utility writes any specified operands, separated by single blank
     (` ') characters and followed by a newline (`\n') character, to the stan-
     dard output.

     The following option is available:

     -n    Do not print the trailing newline character.  This may also be
           achieved by appending `\c' to the end of the string, as is done by
           iBCS2 compatible systems.  Note that this option as well as the
           effect of `\c' are implementation-defined in IEEE Std 1003.1-2001
           (``POSIX.1'') as amended by Cor. 1-2002.  Applications aiming for
           maximum portability are strongly encouraged to use printf(1) to
           suppress the newline character.

     Some shells may provide a builtin echo command which is similar or iden-
     tical to this utility.  Most notably, the builtin echo in sh(1) does not
     accept the -n option.  Consult the builtin(1) manual page.

EXIT STATUS
     The echo utility exits 0 on success, and >0 if an error occurs.

*/

/* 	echo function, takes the argv and executes.
	in case of argc = 1: no input,
	argc 2 echo's content of argv[1]
	unless that is a flag then : no input, etc etc. 
*/

/*

• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

*/

//compare the string to said built in
//make function that does the same as said built-in
