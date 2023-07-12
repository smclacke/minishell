/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 17:45:04 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/12 13:21:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

/**
 * NEW FILE SPECIAL FOR QUOTES maybe create new file for quotes cause this gunna be messyyyy
 * find quotes
 * check for dollar in double quotes!!
 * if unclosed, throw error
*/
// char	*find_quote(char *input)
// {
// 	// if ive found a quote, 
// 	if (!second_quote(input, ft_isquote(intput[i]))) // isquote returns either single or double which can be passed into second_quote()
// 		return (0);
// 	else 
// 		// split quoted part from rest
// 		// return specific part of input with quotes attached
// }


/**
 * find redirects
 * redirect = << >>, < >, and pipe
*/
// char	*find_redirect(char *input)
// {

// }

/**
 * find delimiters
 * whatever is after <<, for HERE_DOC
*/
// char	*find_delimiter(char *input)
// {
	
// }


/***
 * find dollars ( + $?)
 * 
 * bash-3.2$ echo $"USER"
 * USER
 * bash-3.2$ echo $USER
 * smclacke
 * ////////////
 * WHAT THE SHELL?!echo $ hello
 * token: echo
 * $
 * token: $
 * token: hello
 * WHAT THE SHELL?!echo $hello
 * token: echo
 * token: $hello
 * WHAT THE SHELL?!echo sdf$hello
 * token: echo
 * token: sdf$hello
 * WHAT THE SHELL?!echo sdf $hello
 * token: echo
 * token: sdf
 * token: $hello
*/
char	*find_dollar(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	printf("find_dollar: %s\n", input);
	while (input[i])
	{
		printf("HERE: %s\n", input);
		if (ft_strcmp(input, "$") == 0)
		{
			printf("HERE22: %s\n", input);
			if (ft_isspace(input[i + 1]))
				return (input);
			while (input)
			{	
				i++;
				return (input);
			}
			return (input);
		}
		i++;
	}
	return (0);
	
}

/**
 * built ins
 * cd + next argument (relative + abso paths)
 * echo + -n (can also be nnnnnnn and nnnndnnnnn) - they behave differently
 * pwd
 * export
 * unset
 * env
 * exit
*/
// char	*find_built_ins(char *input)
// {
	
// }

/**
 * find strings... need a func for that?
*/

