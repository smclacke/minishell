/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/01 14:36:30 by smclacke      ########   odam.nl         */
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
	t_parser	*tokens;
	// t_env		*env;

	(void) argc;
	(void) argv;
	(void) envp;

	tokens = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		tokens = lexer(input);
		if (!tokens)
			continue ;
		shelly_print_list(tokens);

		tokens = parser(tokens);
		if (!tokens)
			continue ;





		//-- Djoyke --//
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		if (shelly_check_for_builtin(tokens))//will be a expand funct
			printf("there's a builtin whoop\n");
		// execution // make env_list, create child processes, execve
		micro_execute(envp, tokens);
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
