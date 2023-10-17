/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/17 20:00:33 by smclacke      ########   odam.nl         */
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
		printf("str = %s\t", list->str);
		printf("n_cmd = %i\n", list->n_cmd);
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

		tokens = parser(tokens);
		if (!tokens)
			continue ;

		print_the_full_thing(tokens);
		ft_execute(&env, tokens);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

		free_tokens(tokens);	
	}
	return (0);
}
