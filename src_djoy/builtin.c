/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 15:41:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/01 16:00:59 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

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
char	*ft_echo(char **argv)
{
	
}

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
