/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/04 16:51:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* 	
	writes argv after command on standart output followed by /n char
	-n TBA that eliminates the endline char in output 
	The echo utility exits 0 on success, and > 0 if an error occurs.
	wat als meerder -n :( -nnnnnnnnnnnnnnnnn etc -nnnnnnnnna whyyyyyyyy
	➜  Minishell git:(main) ✗ ./djoyke echo -n-n-n-n-n-n-n-n- haha
	echo-n-n-n-n-n-n-n-n-haha%
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
