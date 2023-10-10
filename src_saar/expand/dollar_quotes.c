/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/10 17:14:41 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// static int	is_dollar(int c)
// {
// 	return (c == '$');
// }

// char	*handle_dollar_qs(char *str)
// {
	
// }


// char	*handle_dollar_qs(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*q;
// 	char	*dollar_str;
// 	char	*no_dollar;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	q = 0;
// 	dollar_str = NULL;
// 	no_dollar = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] && !is_dollar(str[i]) && ft_isquote(str[i]))
// 		{
// 			// q = quote_type(str[i]);
// 			q = which_quote(&str[i]);
// 			k = i + next_quote(&str[i], *q);
// 			printf("k = %i\n", k);
// 			printf("i = %i\n", i);
// 			while (k > i)
// 			{
// 				if (is_dollar(str[i]))
// 				{	
// 					printf("handle_quoted_dollar\n");

// 				}
// 				k--;
// 			}
// 		}
// 		i++;
// 	}
// 	printf("str = %s\n", str);
// 	return (str);
// }

// static char	*handle_quoted_dollar(char *str, char *quote_type, int i, int j)
// {
// 	char	*dollar_str;

// 	dollar_str = (char *)malloc(sizeof(char) * (i - j) + 1);

// 	return (dollar_str);
// }

// while str and !dollar, if quotes (all before dollar), remove closed quotes. 
// if dollar inside quotes, handle...
// if quotes after dollar handle...

// char	*handle_dollar_qs(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		q;
// 	char	*dollar_str;
// 	char	*no_dollar;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	q = 0;
// 	dollar_str = NULL;
// 	no_dollar = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] && !is_dollar(str[i]) && ft_isquote(str[i]))
// 		{
// 			q = quote_type(str[i]);
// 			// i++;
// 			// printf("str = %c, [%i]\n", str[i], i);
// 			k = i + next_quote(&str[i], (char)q);
// 			printf("k = %i\n", k);
// 			printf("i = %i\n", i);
// 			while (k > i)
// 			{
// 				if (is_dollar(str[i]))
// 				{	
// 					printf("handle_quoted_dollar\n");
// 					// dollar_str = handle_quoted_dollar(str, quote_type, i, j);
// 					// return (dollar_str);
// 				}
// 				k--;
// 			}
// 				// no_dollar = ft_substr(str, i, k - i);
// 				// no_dollar = remove_quotes(no_dollar);
// 			// i++;
// 		}
// 		// if (str[i])
// 		// 	printf("yup\n");
// 		i++;
// 	}
// 	// if (no_dollar)
// 	// 	str = ft_strjoin(no_dollar, str);
// 	return (str);
// }

// char	*handle_dollar_qs(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		q;
// 	char	*dollar_str;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	q = 0;
// 	dollar_str = NULL;
// 	while (str[i])
// 	{
// 		if (ft_isquote(str[i]))
// 		{
// 			j = i;
// 			q = quote_type(str[i]);
// 			k = i + next_quote(str, (char)q);
// 			while (k > j)
// 			{
// 				if (is_dollar(str[i]))
// 				{
// 					printf("handle_quoted_dollar\n");
// 					// dollar_str = handle_quoted_dollar(str, quote_type, i, j);
// 					return (dollar_str);
// 				}
// 				k--;
// 			}
// 		}
// 		i++;
// 	}
// 	printf("here\n");
// 	str = remove_quotes(str);
// 	return (str);
// }
