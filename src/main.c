/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 21:30:10 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

t_parser	*lexing(char *input)
{
	t_parser	*tokens;

	if (!input)
		exit(0);
	if (!is_space(input))
		add_history(input);
	tokens = lexer(input);
	free(input);
	return (tokens);
}

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_parser_list(t_parser *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		printf("||\n");
// 		printf("index = [%d], cmd = [%s]\n", i, lst->cmd);
// 		printf("index = [%d], str = [%s]\n", i, lst->str);
// 		printf("index = [%d], meta = [%s]\n", i, lst->meta);
// 		printf("index = [%d], file = [%s]\n", i, lst->file);
// 		printf("index = [%d], n_cmd = [%d]\n", i, lst->n_cmd);
// 		printf("next node\n");
// 		if (lst->next == NULL)
// 			printf("NULL\n");
// 		lst = lst->next;
// 		i++;
// 	}
// }

void	print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (arr[i] == NULL)
		{
			printf("NULL\n");
			break ;
		}
		printf("arr = [%s]\n", arr[i]);
		i++;
	}
	printf("end of array\n");
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	t_env		*env;
	int			og_stdout;
	int			og_stdin;

	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		tokens = lexing(input);
		if (!tokens)
			continue ;
		tokens = parser(tokens);
		if (!tokens)
			continue ;
		// print_the_full_thing(tokens);
		execute(&env, tokens);
		free_tokens(tokens);
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
