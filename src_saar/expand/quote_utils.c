/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/28 16:44:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	len_wo_quotes(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*remove_quotes(char *str, int len)
{
	int		i = 0;
	int		j = 0;
	char	*tmp;

	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		// while (str[i] && !ft_isquote(str[i]))
		// {
			tmp[j] = str[i];
			j++;
			i++;
		// }
		// if (ft_isquote(str[i]))
		// 	i++;
	}
	// printf("tmp = %s\n", tmp);
	// str = tmp;
	// printf("str = %s\n", str);
	return (str);
}
