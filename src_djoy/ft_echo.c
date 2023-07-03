/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/03 15:54:42 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* 
	compares 2 strings 
	replace by the libft version without -n
*/
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
	writes argv after command on standart output followed by /n char
	-n TBA that eliminates the endline char in output 
	The echo utility exits 0 on success, and > 0 if an error occurs.
*/
void	*ft_echo(char **argv)//for now index 1
{
	int	i;
	int	is_flag;

	i = 1;
	is_flag = 0;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			i++;
			++is_flag;
		}
		else
		{
			printf("%s", argv[i]);
			i++;
		}
	}
	if (is_flag != 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
