/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/14 12:48:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) envp;
	char	*input;
	t_list	*tokens;
	int		i;

	while(1)
	{
		i = 0;
		input = readline(PROMPT);
		add_history(input);
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

// old main:
// int	main(int argc, char **argv, char **envp)
// {
// 	(void) argc;
// 	// (void) argv;
// 	(void) envp;
// 	char	*input;
// 	t_lexer	*token = NULL;
// 	int	i = 0;

// 	while(1)
// 	{
// 		input = readline(PROMPT);
// 		argv = ft_split(input, ' ');
// 		while (argv[i])
// 		{
// 			token = lexer(argv[i]);
// 			ft_print_tokens(token);
// 			i++;
// 		}
// 	}
// }
