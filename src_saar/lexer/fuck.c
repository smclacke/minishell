static int	start_token(char *input, int old_start)
{
	int 	j;
	char	*quote_type;

	j = 0;
	quote_type = NULL;
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	j = old_start;
	while (input[old_start] && !ft_isspace(input[old_start]))
	{
		if (ft_ismeta(input[old_start]))
			return (j);
		if (ft_isquote(input[old_start]))
		{
			quote_type = which_quote(&input[old_start]);
			old_start += next_quote(&input[old_start], *quote_type);
		}
		old_start++;
	}
	return (j);
}

static int	len_token(char *input, int len)
{
	int		j;
	char	*quote_type;

	j = 0;
	quote_type = NULL;
	while (input[len] && ft_isspace(input[len]))
		len++;
	j = len;
	if (ft_ismeta(input[len]))
	{
		len += which_meta(&input[len]);
		len = len - j;
		return (len);
	}
	while (input[len] && !ft_isspace(input[len]) && !ft_ismeta(input[len]))
	{	
		if (ft_isquote(input[len]))
		{
			quote_type = which_quote(&input[len]);
			len += next_quote(&input[len], *quote_type);
		}
		len++;
	}
	len = len - j;
	return (len);	
}

static int	amount_tokens(char *input)
{
	int		i = 0;
	int		count = 0;
	char	*quote_type = NULL;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (ft_ismeta(input[i]))
		{
			if (ft_ismeta(input[i + 1])) // like... different?
				i++;
			count++;
			i++;
		}
		if (input[i] && !ft_isspace(input[i]))
		{
			while (input[i] && !ft_isspace(input[i]) && !ft_ismeta(input[i]))
			{
				if (ft_isquote(input[i]))
				{
					quote_type = which_quote(&input[i]); //
					i += next_quote(&input[i], *quote_type); // these two in one func ?
				}
				i++;
			}
			count++;
		}
	}
	return (count);
}

static char	*split_tokens(char *input, int len)
{
	char	*token;

	token = ft_substr(input, 0, len);
	if (!token)
		return (NULL);
	input += len;
	return (token);
}

static int	annoying_split(char *input)
{
	int	i = 0;

	while (input[i])
	{
		if (ft_isquote(input[i]) || ft_ismeta(input[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief	takes the input string from the command line, iterates through it. While there
 * 			are no quotations, the string is split on spaces with metas (exc. dollar) also being 
 * 			split into separate str. If a quotation is encountered, the matching quote is found and
 * 			all of that input is put into token
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, ready to be tokenized
*/
char	**parse_input(char *input)
{
	char	**array = NULL;
	int		no_tokens = 0;
	int		start = 0;
	int		len = 0;
	int		i = 0;

	if (annoying_split(input))
	{
		no_tokens = amount_tokens(input);
		printf("no_tokens: %i\n", no_tokens);
		array = (char **)malloc(sizeof(char *) * (no_tokens + 1));
		if (!array)
			return (NULL);
		while (i < no_tokens)
		{
			start = start_token(input, (start + len));
			printf("start = %i\n", start);
			len = len_token(input, start);
			array[i] = (char *)malloc(sizeof(char) * (len + 1));
			// if (!array)
			// 	return (NULL);
			array[i] = split_tokens(&input[start], len);
			i++;
		}
		array[no_tokens] = NULL;
	}
	else
		array = ft_split(input, ' ');
	if (!array)
		return (NULL);   /// does this protect the while loop array?
					/// ++ maybe the if statment one...?
	return (array);
}




int		which_meta(char *input)
{
	if (ft_strnstr(input, MOREMORE, 2))
		return (2);
	else if (ft_strnstr(input, LESSLESS, 2))
		return (2);
	else if (ft_strnstr(input, MORE, 1))
		return (1);
	else if (ft_strnstr(input, LESS, 1))
		return (1);
	else if (ft_strnstr(input, PIPE, 1))
		return (1);
	return (0);
}

char	*which_quote(char *input)
{
	if (ft_strnstr(input, SINGLE_Q, 1))
		return (SINGLE_Q);
	else if (ft_strnstr(input, DOUBLE_Q, 1))
		return (DOUBLE_Q);
	return (0);
}

int	next_quote(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

bool	is_meta(char *input)
{
	if (ft_strnstr(input, MOREMORE, 2))
		return (true);
	else if (ft_strnstr(input, LESSLESS, 2))
		return (true);
	else if (ft_strnstr(input, MORE, 1))
		return (true);
	else if (ft_strnstr(input, LESS, 1))
		return (true);
	else if (ft_strnstr(input, PIPE, 1))
		return (true);
	return (false);
}

int	ft_ismeta(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_token(char *input) // am i even using this function?
{
	if (*input == '|')
		return (1);
	if (*input == '<')
	{
		if (!ft_strncmp(input, "<<", 2))
			return (1);
		return (2);
	}
	else if (*input == '>')
	{
		if (!ft_strncmp(input, ">>", 2))
			return (1);
		return (2);
	}
	return (0);
}