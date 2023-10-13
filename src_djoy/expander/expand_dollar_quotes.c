/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/13 21:33:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param len lenght of node->str
 * @brief checks if $ is at the end of the string
 * @return 1 if the $ is at the end of the string
 * 0 if not.
*/
int	check_at_len(char *str, t_expand *exp, int i, int len)
{
	if (str[i] == '$' && (i + 1) == len)
	{
		free_remain_struct(exp);
		return (1);
	}
	return (0);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @brief replaces the before_dollar string if it's NULL with 
 * node->str content of i lenght.
*/
void	get_before_dollar(char *str, t_expand *exp, int i)
{
	if (exp->before_dollar == NULL)
		exp->before_dollar = ft_substr(str, 0, i);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param j index at next $ sign
 * @brief gets the string to compare the environment key to
*/
void	get_compare_str(char *str, t_expand *exp, int i, int j)
{
	if (str[j] == '$')
		j++;
	while (str[j] != '$' && !ft_isquote(str[j]) && str[j] != '\0')
		j++;
	exp->comp_str = ft_substr(str, i, j - i);
}

static int	is_dollar(char c)
{
	return (c == '$');
}

/**
 * if "$USER", return $USER and expand
 * if '$SUER', return NULL and send og str back, don't expand
*/
char	*sarah_expand_dollar(char *str)
{
	int		i;
	int		quote;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote = quote_type(str[i]);
			i++;
			while (str[i] && !ft_isquote(str[i]))
			{
				if (is_dollar(str[i]) && quote == '\'')
					return (NULL);
				if (is_dollar(str[i]) && quote == '\"')
				{
					str = remove_quotes(str);
					return (str);
				}
				i++;
			}
		}
		i++;
	}
	return (str);
}
