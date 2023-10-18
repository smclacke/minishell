/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/18 15:06:19 by smclacke      ########   odam.nl         */
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

void	print_exp_dol_vals(t_exp_dol *str)
{
	printf("str->unassed\t\t\t\t\t= [%s]\n", str->unassed);
	printf("str->expand_this\t\t\t\t= [%s]\n", str->expand_this);
	printf("str->dont_expand_this\t\t\t\t= [%s]\n", str->dont_expand_this);
	printf("str->str_before_dol\t\t\t\t= [%s]\n", str->str_before_dol);
	printf("str->str_after_dol\t\t\t\t= [%s]\n", str->str_after_dol);
	printf("str->assed\t\t\t\t\t= [%s]\n", str->assed);
}
