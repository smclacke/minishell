/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/10 19:58:50 by dreijans      ########   odam.nl         */
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
		printf("[%i]\t ", i);
		printf("cmd = %s\t", list->cmd);
		printf("file = %s\t", list->file);
		printf("meta = %s\t", list->meta);
		printf("str = %s\n", list->str);
		i++;
		list = list->next;
	}
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	t_env		*env;

	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);
	tokens = NULL;

	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		tokens = lexer(input);
		free (input);
		if (!tokens)
			continue ;
		shelly_print_list(tokens);

		tokens = parser(tokens);
		if (!tokens)
			continue ;

		print_the_full_thing(tokens);

		expand_quotes(tokens);
		
		print_the_full_thing(tokens);

		ft_execute(&env, tokens);
		
		free_tokens(tokens);	
	}
	return (0);
}
