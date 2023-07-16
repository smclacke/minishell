/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   old_shit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/16 16:23:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/16 16:25:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * old stuff to refer to if necessary until my new solution works...
 * 
*/


/**
 * after:
 * quotes are found
 * spaces are parsed
 * redirects are found
 * delimiters are found
 * 
 * FIND dollar and word or dollar + ?
 * FIND buildins + flags are found
 * FIND ALL OTHER INPUT input
 */
// char *find_rest(char *input)
// {
// 	int		i;
// 	char	*dollar;

// 	i = 0;
// 	dollar = NULL;
// 	// while (input[i])
// 	// {	
// 	// 	while !quote, !pipes, !dollars, !arrows, !flags...
// 	// 	then find, else ill loose the string before these finds and cut the find away from the rest of the string
// 	// 	if (ft_isdollar(input[i]))
// 	// 	{
// 	// 		dollar = find_dollar(&input[i]);
// 	// 		printf("dollar: %s\n", dollar);
// 	// 		if (!dollar)
// 	// 			return (0);
// 	// 		return (dollar);
// 	// 	}
// 	// 	find build ins
// 	// 	find strings
// 	// 	i++;
// 	// }
// 	return (0);
// }

/**
 * parse spaces, find quoted tokens, redirects, and delimiters
 * then parse rest to find dollars, built in, string input...
 * 
*/
// char	*parse_token(char *input)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	// are there quotes? check_quote()
// 	//	if yes, return that part of input to lexer()
// 	// are there redirects?
// 	//	if yes, return that part of input to lexer()
// 	parse_space(input);
// 	// while (input[i])
// 	// {	
// 	// 	// if (find_quotes(input))
// 	// 	// 	return (input);
// 	// // 	// else if (find_redirects(input))
// 	// // 	// 	return (input);
// 	// // 	// else if (find_delimiter(input))
// 	// // 	// 	return (input);
// 	// // 	if (find_rest(&input[i]))
// 	// // 	{
// 	// // 		printf("parse_token input: %s\n", &input[i]);
// 	// // 		return (&input[i]);
// 	// // 	}
// 	// 	i++;
// 	// }
// 	// return (0);
// 	return (input);
// }



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

