/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/05 13:36:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * string after closed quotes that needs to be added to expanded string
*/
int	save_extra_string(t_expand *str, char *input, int i)
{
	int	start;
	int	end;
	int	len;
	char	*tmp;

	start = i;
	tmp = str->expanded;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	end = i;
	len = end - start;
	str->string = ft_substr(input, start, len);
	if (!str->string)
	{
		free(tmp);
		return (0);
	}
	if (tmp && str->string)
		str->expanded = ft_strjoin(tmp, str->string); // leakyyyy
	free(tmp);
	free(str->string);
	return (i);
}

/**
 * before any dollar or quotes, just save the string
*/
int	first_bit(t_expand *str, char *input)
{
	int		i;

	i = 0;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	if (is_dollar_or_quote(input[i]))
	{
		if (i == 0)
			return (0);
		str->expanded = ft_substr(input, 0, i);
		if (!str->expanded)
			return (0);
	}
	return (i);
}

/**
 * get first part of string, then loop through separating dollars and quotes...
 * @todo fix this, leaks, norm, test test test...
 * write version (or have func for here_doc and only edit that bit)
*/
static void	dollar(t_expand *str, t_env **env)
{
	int		i;

	i = first_bit(str, str->input);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, str->input, env, (i + 1));
		if (ft_issquote(str->input[i]))
		{
			i = squote_bit(str, str->input, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
		if (ft_isdquote(str->input[i]))
		{
			i = dquote_bit(str, str->input, env, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
	}
}

/**
 * adding expanded str back into correct parser struct var
 * @todo comment
 * @todo	when expanding a non expandable... need an empty string but this was 
 * causing problems...
*/
void	expand_dollar(t_parser *lst, t_env **env, t_expand *str)
{
	t_parser	*tmp;

	tmp = lst;
	str->input = set_expand_string(lst, str);
	if (!str->input)
		return ;
	if (str->sign == 1 || str->sign == 2 || str->sign == 3)
	{
		dollar(str, env);
		if (str->sign == 1)
		{
			tmp->cmd = ft_strdup(str->expanded);
			free(str->expanded);
		}
		else if (str->sign == 2)
		{
			tmp->str = ft_strdup(str->expanded);
			free(str->expanded);
		}
		else if (str->sign == 3)
		{	
			tmp->file = ft_strdup(str->expanded);
			free(str->expanded);
		}
	}
	lst = tmp;
}
