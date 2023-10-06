/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/06 22:00:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// $USER
// zsh: command not found: smclacke
// this was still expanded

/**
 * echo "$USER"				// remove quotes, expand
 * smclacke
 * 
 * '$USER'				// echo what is literally in the quotes
 * $USER
 * 
 * $"USER"				// echo what is literally in the quotes, ignore the dollar
 * USER
 * 
 * abd$"USER"			// echo what is literally in the quotes, ignore the dollar
 * abdUSER
 * 
 * echo asdf'$USER'		// echo what is literally in the quotes
 * asdf$USER
 * 
 * $U"SER"				 // echo what is literally in the quotes, ignore the dollar
 * SER
 * 
 * $U'SER'				// echo what is literally in the quotes
 * SER
 * 
 * echo asdf$U"SER"		// echo what is literally in the quotes, ignore the dollar
 * asdfSER
*/

/**
 * all in doubles check env for var
 * 
 * if single, take literally 
 * 
 * save everything from start without quotes up to quote, then separate after/inside quotes
 * 
 * find dollar, if quote before, find matching, create separate strings
 * if dollar and quote after, ignore dollar
 * 
 * 
*/

/**
 * double quotes = 
 * 		remove and expand when whole is quoted
 * 		echo what is literally in the quotes
 * 		ignore the dollar and anything after dollar outside quotes
 * 		if something before dollar, that is also echoed with the rest
 * 
 * single qoutes = 
 * 		take what is inside the quotes literally
 * 		ignore dollar and anything after dollar outside quotes
*/

static int	is_dollar(int c)
{
	return (c == '$');
}

// static char	*handle_quoted_dollar(char *str, char *quote_type, int i, int j)
// {
// 	char	*dollar_str;

// 	dollar_str = (char *)malloc(sizeof(char) * (i - j) + 1);

// 	return (dollar_str);
// }

// while str and !dollar, if quotes (all before dollar), remove closed quotes. 
// if dollar inside quotes, handle...
// if quotes after dollar handle...

char	*handle_dollar_qs(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*q;
	char	*dollar_str;
	char	*no_dollar;

	i = 0;
	j = 0;
	k = 0;
	q = 0;
	dollar_str = NULL;
	no_dollar = NULL;
	while (str[i])
	{
		if (str[i] && !is_dollar(str[i]) && ft_isquote(str[i]))
		{
			// q = quote_type(str[i]);
			q = which_quote(&str[i]);
			k = i + next_quote(&str[i], *q);
			printf("k = %i\n", k);
			printf("i = %i\n", i);
			while (k > i)
			{
				if (is_dollar(str[i]))
				{	
					printf("handle_quoted_dollar\n");

				}
				k--;
			}
		}
		i++;
	}
	printf("str = %s\n", str);
	return (str);
}

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
