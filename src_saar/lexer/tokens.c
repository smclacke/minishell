/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 17:45:04 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/12 17:11:07 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"


// REDRIECTS
//////////////////////////////////////////

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


// DOLLARS
//////////////////////////////////////////

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
// char	*find_dollar(char *input)
// {
// 	int		i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 			return (&input[i]);
// 		// 	printf("input: %s\n", &input[i]);
// 		// 	// i++;
// 		// 	// if (ft_isspace(input[i + 1]))
// 		// 	// 	return (&input[i]);
// 		// 	// while (input[i] && !ft_isspace(input[i]))
// 		// 	// 	i++;
// 		// 	return (&input[i]);
// 		// }
// 		// else
// 		// 	return (78);
// 		i++;
// 	}
// 	return (input);
// }


// BUILT-INS
//////////////////////////////////////////

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

