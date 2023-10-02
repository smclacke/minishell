/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/02 14:40:33 by smclacke      ########   odam.nl         */
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
		printf("cmd = %s\t", list->data->cmd);
		printf("file = %s\t", list->data->file);
		printf("meta = %s\t", list->data->meta);
		printf("str = %s\n", list->data->str);
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
	t_parser	*tmp;

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
		if (!tokens)
			continue ;

		// shelly_print_list(tokens);
		tokens = parser(tokens);
		if (!tokens)
			continue ;
		// shelly_parser_print(tokens);
		// print_the_full_thing(tokens);

		// cmd_quotes(tokens); // part of the expander
		// print_the_full_thing(tokens);


		ft_execute(&env, tokens);
		// free input (readline needs to be fred at end)	
	}
	tmp = tokens;
	while (tokens)
	{
		tmp = tokens->next;
		ft_bzero(tmp, sizeof(t_parser));
		tmp = tokens;
	}
	return (0);
}
