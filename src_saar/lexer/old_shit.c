/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   old_shit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/16 16:23:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/22 12:01:44 by smclacke      ########   odam.nl         */
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

// **HOW, WHAT, WHY, TOKENS**

// --- new solution ---

// ~!~ give input to parse_input() which returns array, split via spaces except for when there
// 	are quotes, then everything inside the quotes (till the last found quote) is given as a string in
// 	the array, also, check for symbols and send as single strings 
	
// 	(will need to parser through quotation tokens properly but do it in the parser).
// 	e.g.
// 		some "input" | given in command line
// 	returned array:
// 		- some
// 		- "input"
// 		- | 
// 		- given
// 		- in
// 		- command
// 		- line

// ~!~	parse through argv[i] (argv = parse_input(input))
// 	tokens = lexer
// 	these strings are given to the lexer, and a token list is returned

// ~!~ token list is passed to parser. 

// --------------------------------------------
// Old confusion...
//  ~!~ - start with a clear set up...

// !!--- what about the order?? 
// -- HOW DO I KEEP THE ORDER CORRECT???

//  ---- the lexer now takes the double array argv and returns the tokens
//  ---- NO MORE SPLITING IN MAIN
//  ---- tokens are given to the parser
//  ---- AST passed to expander
//  ---- WORK IN PARSE_TOKEN, LEAVE THE REST AS IT IS

//  ~!~ - do as little as possible in main, create main lexer func, start there with quotes, make those tokens, then
// 	ft_split, then find symbols etc.. then make those tokens, return the list 

//  ~!~ - Separate quotes
// 	- if there is a space before first quote and after last quote, tokenize it
// 	!! - check when tokenizing quotes, if there's a built in
// 	!! - handling redirects and delimiters in quotes???
// 	!! - how to handle quotes in quotes: "something "some" things" ??? I dont want to tokenize "something "
// 		but if: echo "wc -l" | hello "something", I don't want to tokenize everything...

//  ~!~ - split via spaces (outside of any quotations)
// 	- just like I had before with ft_split but now after parsing the quotations
// 	- in cases like "ec'h'o" and "abc$abc", just pass whole thing as token, can parse in parser and expand in expander

//  ~!~ - tokenize: (<< delimiters), redirects, built-ins and words