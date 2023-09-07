/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/07 15:59:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

		// printf("[%i] || input: [%s] | cmd_list->cmd: [%s] | cmd_list->strs: [%s] | redirect->meta: [%s]\n", 
		// 	i, list->input, (char *)list->cmd_list->cmd, (char *)list->cmd_list->strs, (char *)list->redirect_list->meta);

t_parser	*print_the_full_thing(t_parser *tokens)
{
	t_parser	*list;
	int			i = 0;
	
	list = tokens;
	while (list)
	{
		printf("[%i] | ", i);
		printf("input: [%s] ", list->input);
		printf("cmd_list->cmd: [%s] | ", list->cmd_list->cmd);
		printf("cmd_list->str: [%s] | ", list->cmd_list->strs);
		// printf("redirect->meta: [%s]\n", list->redirect_list->meta);
		// if (list->cmd_list)
		// {
		// 	printf("cmd_list->cmd: [%s] | ", list->cmd_list->cmd);
		// 	printf("cmd_list->str: [%s] | ", list->cmd_list->strs);
		// }
		// if (list->redirect_list)
		// 	printf("redirect->meta: [%s]\n", list->redirect_list->meta);
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
		if (!tokens)
			continue ;
		// shelly_print_list(tokens);
		tokens = parser(tokens);
		if (!tokens)
			continue ;
		shelly_parser_print(tokens);
		// print_the_full_thing(tokens);


		ft_execute(&env, tokens);
		// free input (readline needs to be fred at end)	
	}
	return (0);
}

