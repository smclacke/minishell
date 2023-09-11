/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/11 18:21:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

t_parser	*print_the_full_thing(t_parser *tokens)
{
	t_parser	*list;
	int			i = 0;
	
	list = tokens;
	while (list)
	{
		printf("[%i] | ", i);
		printf("list->data_list->cmd: [%s] \n", list->data_list->cmd);
		i++;
		list = list->next;
	}
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	// t_env		*env;

	(void) argc;
	(void) argv;
	(void) envp;
	// env = NULL;
	// env = env_list(envp, env);
	tokens = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		tokens = lexer(input);
		if (!tokens)
			continue ;
		// shelly_print_list(tokens);
		tokens = parser(tokens);
		if (!tokens)
			continue ;
		// shelly_parser_print(tokens);
		print_the_full_thing(tokens);


		// ft_execute(&env, tokens);
		// free input (readline needs to be fred at end)	
	}
	return (0);
}

