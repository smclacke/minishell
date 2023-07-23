/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/24 00:24:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

// // I think I should call split_input, from there if token, lexer it. dont send back to main
// // and don't make 2d array, theyll be in the list and i think that is ok

void	lexing(char **args, t_lexer *data)
{
	char	*input;
	int		i;

	i = 0;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		split_input(input);
		if (!args)
			exit(EXIT_FAILURE);
		ft_print_tokens(data->token);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) 		argc;
	(void) 		envp;
	t_lexer		data;

	lexing(argv, &data);
	// parser
	// return AST to expander
}


//	OLD VERSION	
// void	lexing(char **args)
// {
// 	t_lexer	*tokens;
// 	char	*input;
// 	int		i;

// 	i = 0;
// 	while (1)
// 	{
// 		input = readline(PROMPT);
// 		add_history(input);
// 		args = split_input(input);
// 		if(!args)
// 			exit(EXIT_FAILURE);
// 		while (args[i])
// 		{
// 			tokens = lexer(args[i]);
// 			ft_print_tokens(tokens);
// 			i++;
// 		}
// 	}
// }


// int	main(int argc, char **argv, char **envp)
// {
// 	(void)	argc;
// 	// (void)	argv;
// 	(void)	envp;

// 	lexing(argv);
// 		// parser the tokens... 
// 		// return the AST to the expander
// 	// }
// }
