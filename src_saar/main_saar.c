/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/24 21:24:00 by smclacke      ########   odam.nl         */
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
		// printf("n_cmd = %i\n", list->n_cmd);
		i++;
		list = list->next;
	}
	return (tokens);
}

t_parser	*sort_list(t_parser *tokens)
{
	t_parser	*head;
	t_parser	*tmp;
	t_parser	*new;
	int			sign = 0;

	head = tokens;
	tmp = tokens;
	new = NULL;
	while (tmp && !sign)
	{
		printf("here\n");
		if (tmp->cmd)
		{
			printf("here1\n");
			lexer_listadd_back(&new, tmp);
			tmp->flag = 1;
			sign = 42;
		}
		tmp = tmp->next;
	}
	tmp = tokens;
	sign = 0;
	while (tmp)
	{
		printf("tmp->meta = %s\n", tmp->meta);
		printf("tmp->flag = %i\n", tmp->flag);
		printf("sign = %i\n", sign);
		if (!tmp->flag)
		{
			lexer_listadd_back(&new, tmp);
			tmp->flag = 1;
		}
		tmp = tmp->next;
		sign++;
	}
	// shelly_print_list(new);
	return (new);
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

	int	og_stdout = dup(STDOUT_FILENO);
	int	og_stdin = dup(STDIN_FILENO);

	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		tokens = lexer(input);
		free (input);
		if (!tokens)
			continue ;
		// shelly_print_list(tokens);

		tokens = parser(tokens);
		if (!tokens)
			continue ;

		tokens = sort_list(tokens);
		if (!tokens)
			printf("wtf?\n");
		print_the_full_thing(tokens);
		// ft_execute(&env, tokens);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

		free_tokens(tokens);	
	}
	return (0);
}
