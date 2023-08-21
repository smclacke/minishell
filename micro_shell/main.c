/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/21 21:26:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// struct: buildins + cmds, make new nodes with everything in it up to pipes and redirects
// call vars in struct whatever they 'are' i.e., buildin = (echo hello) or
// cmd = (ls -la), or redirect = (infile>>) 

// don't just put all parts back into ONE node, create mini node arrays of the strings 
// that need to be together

// if str, put into str array, keep adding the separate strings up to pipes and redirect 

echo hello | unset USER

cmd, str, str -> cmd, **str = str, str


echo hello
ls -la

~ builtins
-> tokens
lst->builtin
lst->str
-> parser
lst->buildin = builtin + str 

~ cmds
-> tokens
lst->cmd
lst->str
-> parser look for pipes and redirects
lst->cmd = cmd + str in one node

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*parser_struct;
	t_expand	*expand_list;

	(void) argc;
	(void) argv;
	tokens = NULL;
	parser_struct = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		//-- Sarah --//
		tokens = lexer(input);
		if (!tokens)
			continue ;
		print_lexer(tokens);
		

		parser_struct = parser(tokens);
		if (!parser_struct)
			continue ;
		




		//-- Djoyke --//
		// micro_echo(parser_struct);
		// env = micro_env_list(envp);
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		// micro_execute(envp, par_tokens);
		expand_list = micro_expand(parser_struct);
		if (micro_execute(envp, parser_struct))
			continue ;
		// micro_echo(parser_struct);
		// execution // make env_list, create child processes, execve
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
