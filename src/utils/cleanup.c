/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 17:27:40 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/23 22:56:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	free_strs(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

/**
 * @param s const string 
 * @param start int index indicating start of new string
 * @param len size_t indicating lenght of new string
 * @brief creates new string of size len
 * @return string.
*/
char	*mini_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (mini_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	str = mini_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

/**
 * @param s1 const string to join
 * @brief duplicates string with malloc
 * @return string.
*/
char	*mini_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	s2 = mini_malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

/**
 * @param s1 string to join
 * @param s2 string to join
 * @brief joins 2 strings
 * @return returns joined string.
*/
char	*mini_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = mini_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

/**
 * @param size int size 
 * @brief custom malloc, exits when malloc fails
 * @return malloced variable
*/
void	*mini_malloc(int size)
{
	void	*data;

	data = malloc(size);
	if (!data)
		exit(E_MALLOC);
	return (data);
}
