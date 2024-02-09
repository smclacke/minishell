/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 21:11:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/08 22:39:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	inside_while(char *str, char *new, int *i, int *j)
{
	int		q;

	q = quote_type(str[(*i)]);
	(*i)++;
	while (str[(*i)] && str[(*i)] != q)
	{
		new[(*j)] = str[(*i)];
		(*j)++;
		(*i)++;
	}
	if (str[(*i)] && ft_isquote(str[*i]) && str[(*i)] == q)
		(*i)++;
}

void	remove_quotes(char *str)
{
	int		i;
	int		j;
	int		q;
	char	*new;

	i = 0;
	j = 0;
	q = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new)
		return ;//malloc error
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
		{
			new[j] = str[i];
			j++;
			i++;
		}
		if (ft_isquote(str[i]))
			inside_while(str, new, &i, &j);
	}
	new[j] = '\0';
	str = ft_strcpy(str, new);
	free(new);
}
