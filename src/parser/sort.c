/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 20:02:42 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/02 18:37:33 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/
/**
 * commmentntntntntnt
*/
static t_parser	*find_first_cmd(t_parser *tmp, t_parser *new_list)
{
	int			sign;

	sign = 0;
	if (!tmp)
		mini_error("some thing is maybe wrong", errno);
	while (tmp && !sign)
	{
		if (tmp->cmd)
		{
			new_list = add_new_cmd(tmp, new_list, tmp->cmd);
			if (!new_list)
				mini_error("what a jokkkeeee", errno);
			sign = 42;
		}
		tmp = tmp->next;
	}
	if (!new_list)
		mini_error("some thing is terribly wrong", errno);
	return (new_list);
}

/**
 * comment?
*/
static t_parser	*cmd_after_pipe(t_parser *tmp, t_parser *new_list, char *meta)
{
	t_parser	*tmp2;

	new_list = add_new_meta(tmp, new_list, meta);
	if (!tmp)
		return (NULL);
	tmp2 = tmp;
	if (!tmp2->next)
		return (NULL);
	tmp2 = tmp2->next;
	while (tmp2 && !tmp2->flag && shelly_strcmp(tmp2->meta, "|") != 0)
	{
		if (tmp2->cmd)
		{
			new_list = add_new_cmd(tmp2, new_list, tmp2->cmd);
			if (!new_list)
				mini_error("nein man", errno);
		}
		tmp2 = tmp2->next;
	}
	if (!new_list)
		mini_error("some thing is terribly wrong again", errno);
	return (new_list);
}

/**
 * commennttttttt
*/
static void	free_only_tokens(t_parser *tokens)
{
	t_parser	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free (tokens);
		tokens = tmp;
	}
}

/**
 * @brief	after identifying the cmd in each process, set it as the first 
 * 			node in the token list, of each process
 * 			i.e. <file cmd str | << EOF cmd str str 
 * 					= cmd <file str | cmd << EOF str str
 * @param	tokens once the tokens are split up and the type of 
 * 			input is identified, list is sorted and returned to the executor
 * @return	new_list, same parsed list of tokens, just sorted
*/
t_parser	*sort_list(t_parser *tokens)
{
	t_parser	*tmp;
	t_parser	*new_list;

	if (!tokens)
		return (NULL);
	tmp = tokens;
	new_list = NULL;
	new_list = find_first_cmd(tmp, new_list);
	while (tmp)
	{
		if (!tmp->flag && shelly_strcmp(tmp->meta, "|") == 0)
			new_list = cmd_after_pipe(tmp, new_list, tmp->meta);
		else if (!tmp->flag && tmp->file)
			new_list = add_new_file(tmp, new_list, tmp->file);
		else if (!tmp->flag && tmp->str)
			new_list = add_new_str(tmp, new_list, tmp->str);
		else if (!tmp->flag && tmp->meta)
			new_list = add_new_meta(tmp, new_list, tmp->meta);
		tmp = tmp->next;
	}
	if (!new_list)
		mini_error("ohhhhh noooooooo", errno);
	free_only_tokens(tokens);
	return (new_list);
}
