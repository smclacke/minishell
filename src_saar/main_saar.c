/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/16 15:37:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

char	**parse_input(char *input)
{
	char	**array;
	// split spaces unless we encounter a quote, keep parsing from quote till last found quote
	// quotes not closed, ret error
	// send these strings to lexer
	// if quotes, tokenize whole thing
	// if redirect, tokenize that
	// make tokens, send back to main
	array = ft_split(input, ' ');
	return (array);
}

int	main(int argc, char **argv, char **envp)
{
	(void)	argc;
	// (void)	argv;
	(void)	envp;
	char	*input;
	t_lexer	*tokens;
	int		i;

	while(1)
	{
		i = 0;
		input = readline(PROMPT);
		add_history(input);
		argv = parse_input(input);
		while (argv[i])
		{
			tokens = lexer(argv[i]);
			ft_print_tokens(tokens);
			i++;
		}
		// parser the tokens... 
		// return the AST to the expander
	}
}
