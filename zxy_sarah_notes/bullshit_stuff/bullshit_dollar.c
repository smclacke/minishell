
// do quote check and splitting before this ??
// figuring it out without quotes down here
//getting a bit of the logical without quotes, but not sure about orser plus need 
//to find expandable things, expand them, add them to assed str, 
//then empty expand_this to keep searching through unassed

	
	// str->
	// printf("before_dollar = %s\n", str->str_before_dol);
	// assed = full things returned after expansion 
	// concating and non expandable bits together

	// here all the expansion needs to happen
	


	// break it up, then check dollar parts for expansion
	// need to break up the string into
	// separate parts of the struct
	// check expansion if dollar part etc... (str->expand)

	// str->expand_this = check_if_expand(str->unassed);
	// if (!str->expand_this)
	// {
	// 	str->dont_expand_this = str->unassed;
	// }
// need to call separately and iterate, if expand_this has $USER, dont want to try 
// adding another $USER before its expanded and added to assed var		
	// while (str->unassed[i])
	// {
	// 	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
	// 		i++;
	// 	if (ft_dollar(str->unassed[i]))
	// 	{
	// 		str->unassed = expand_this(str, i);
	// 		if (!str->unassed)
	// 			return (str->assed);
	// 		printf("expand = %s\n", str->expand_this);
	// 		printf("unassed = %s\n", str->unassed);
	// 	}
	// 	i++;
	// }
	// str->unassed = expand_this(str, i);
	// if (!str->unassed)
	// 	return (str->assed);
	
	// printf("unassed[i] = %c\n", str->unassed[i]);
	// while (str->unassed[i] && !ft_dollar(str->unassed[i]))
	// 	i++;
	// 	// while (str->unassed[i] && !ft_dollar(str->unassed[i]))
	// 	// 	i++;
	// if (ft_dollar(str->unassed[i])) // or quote, get the stuff between the two dollars
	// {
	// 	str->unassed = expand_this(str, i);
	// 	if (!str->unassed)
	// 		return (str->assed);
	// 	i = 0;
	// }
	// str->unassed = expand_this(str, i); // or there are no quotes/dollars after first
	// // encounter and we can iust expand the stuff we have after last dollar is found
	// if (!str->unassed)
	// 	return (str->assed);



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
