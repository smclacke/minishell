/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 15:41:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/01 17:54:16 by dreijans      ########   odam.nl         */
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

/* 
	function that checks for the corresponding built-in
	maybe needs to be a bool?
*/
void	check_for_builtin(char *argv[1], int argc)
{
	if (ft_strcmp(argv[1], "echo") == 0)
		ft_echo(&argv[1]);
	else
		exit(EXIT_FAILURE);//not really necesairy
}

/* 	
	writes argv after command on standart output followed by /n char
	-n TBA that eliminates the endline char in output 
	The echo utility exits 0 on success, and >0 if an error occurs.
*/
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

• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

*/