/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/22 12:04:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

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
		argv = split_input(input);
		if (!argv)
			return (0);
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
