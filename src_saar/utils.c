/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/24 20:00:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

void	free_tokens(t_parser *tokens)
{
	t_parser	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free (tokens->cmd);
		free (tokens->meta);
		free (tokens->file);
		free (tokens->str);
		free (tokens);
		tokens = tmp;
	}
}

// find out how many cmds there are total for pipe purposes
int	get_no_cmds(t_parser *tokens)
{
	t_parser	*tmp;
	int			i = 0;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->cmd)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
}

void	print_expand_vals(t_expand *str)
{
	printf("unassed\t\t\t\t\t= [%s]\n", str->input);
	printf("expand_this\t\t\t\t= [%s]\n", str->do_expand);
	printf("expand_this\t\t\t\t= [%s]\n", str->dont_expand);
	printf("assed\t\t\t\t\t= [%s]\n", str->expanded);
	printf("------------------------------------------------------\n");
}
