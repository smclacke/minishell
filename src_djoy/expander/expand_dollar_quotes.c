/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar_quotes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/17 14:01:37 by smclacke      ########   odam.nl         */
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
 * put space between "$USER" and something
 * remove quotes from "$USER" and expand, then handle separate attached string
*/
// static char	*handle_double_q(char *str, int quote)
// {
// 	int	i = 0;
// 	int	j = 0;
// 	int	k = 0;
// 	int	g = 0;
// 	char	*tmp;
// 	char	*tmp1;

// 	tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
// 	tmp1 = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
// 	while (str[i])
// 	{
// 		if (str[i] == quote)
// 		{
// 			str[i] = next_quote(str, (char)quote);
// 			if (str[i + 1])
// 			{
// 				g = i;
// 				printf("i = %i | g = %i\n", i, g);
// 				i = 0;
// 				while (str[i] && i < g)
// 				{
// 					tmp1[k] = str[i];
// 					i++;
// 					k++;
// 				}
// 				g++;
// 				printf("str[g] = %c\n", str[g]);
// 				while (str[g])
// 				{
// 					tmp[j] = str[g];
// 					j++;
// 					g++;
// 				}
// 				tmp1[k] = ' ';
// 				k++;
// 				while (tmp[j])
// 				{
// 					tmp1[k] = str[g];
// 					k++;
// 					g++;get_before_dollar(str, exp, i);
// 				}
// 				printf("tmp1[k] = %c\n", tmp1[k]);
// 				return (tmp1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (str);
// }

// strtrim?
// then add space?

/**
 * if "$USER", return $USER and expand
 * if '$SUER', return NULL and send og str back, don't expand
*/
char	*check_if_expand(char *str)
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
					// str = handle_double_q(str, quote);
					return (str);
				}
				i++;
			}
		}
		i++;
	}
	return (str);
}
