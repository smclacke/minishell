**Quote Expansion**

--------------------------------------------------------------------------

**DOLLAR QUOTES YAY**

LA'OHGUUsdlfmsadflkamslfkmlfkmlmglmglaskm
11/10, the dollar quote bullshit day...

===========================================
 ---> leaks when ending with quote

 ---> need to handle "$USER" and '$USER' YYAYAYAYYAYAYAYAYAYAA OUI GENAU

 ---> then norm it

===========================================


echo "HELLO"$USER
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = "HELLO"$USER
HELLO 


echo 'hello'$USER
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = 'hello'$USER
hello 


echo hello$USER
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = hello$USER
hellosmclacke

 *********************************************

:)


echo $USER"HELLO"$USER$USER"something"$PWD'wtf'
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = $USER"HELLO"$USER$USER"something"$PWD'wtf'
smclackeHELLOsmclackesmclackesomething/home/smclacke/Desktop/minishellwtf 



 *********************************************


THE OLD ONE JUST INCASE

/**
 * @param node parser linked list
 * @param env environmet linked list
 * @brief checks for a $ sign in the node
 * expands the string to actual value
 * @todo when "" '' quotes are handled check and adjust again
*/
// char	*exp_dollar(char *str, t_env **env, t_expand *exp, int len)
// {
// 	int			i;
// 	int			j;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		// if (!sarah_expand_dollar(str))
// 		// {
// 		// 	printf("don't expand hehe\n");
// 		// 	// fix up the str for return 
// 		// 	// str = fix_up(str);
// 		// 	return (str);
// 		// }
// 		// else if expand but "$USER"
// 		if (check_at_len(str, exp, i, len) != 0)
// 			return (str);
// 		else if (((str[i] == '$') || (ft_isquote(str[i]))) && (i + 1) != len)
// 		{
// 			get_before_dollar(str, exp, i);
// 			if (ft_isquote(str[i]))
// 			{
// 				i = get_var_str(str, exp, i, j);
// 				exp->var = remove_quotes(exp->var);
// 				reassing_before_dollar_with_var(exp);
// 			}
// 			i++;
// 			j = i;
// 			if (i == len)
// 			{
// 				str = return_exp(str, exp);
// 				return (str);
// 			}
// 			printf("what?\n");
// 			printf("before-dollar = %s\n", exp->before_dollar);
// 			printf("str = %s\n", str);
// 			printf("str[i] = %c\n", str[i]);
// 			// one func, call these things...
// 			get_compare_str(str, exp, i, j);
// 			get_check_value(exp, env);
// 			save_expanded(exp);	
// 			printf("str[i] 2 = %c\n", str[i]);
// 		}
// 		i++;
// 	}
// 	str = return_exp(str, exp);
// 	return (str);
// }





 *********************************************
 *********************************************
 *********************************************
 *********************************************
 *********************************************

when dollar in double remove quotes 		-> expand
when dollar in single take string literally -> don't expand
	!! how do we know this.... ?

else, dollar + anything not quotes 			-> expand
anything quoted = string to add as cmd arg	-> don't expand

*********************************************



->>> $USER
expand = cmd = smclacke



dollar should also be seen as cmd after expansion
i.e. -> $USER
[0] cmd = smclacke

so that 
export hi=echo
-> $hi
[0] cmd = echo



**DOLLAR QUOTES YAY**

--------------------------------------------------------------------------


// $USER
// zsh: command not found: smclacke
// this was still expanded

/**
 * is dollar and thing after is quote then there is no dollar to expand
 * then just dollar on its own , then whatever in quotes...
 * 
 * 
 * "$USER" = remove quotes, expand dollar, becomes smclacke
 * '$USER' = literally what's in quotes
 * 
 * if inside quotes dollar, if double, remove double and expand
 * if single, take as literal string
 * 
 * if dollar, expand anything following OUTSIDE QUOTES
 * anything in quotes (without a dollar) is just a quoted string
 * 
 * 
*/

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

--------------------------------------------------------------------------

bash = 

echo "something << hello >in"
something << hello >in


e'c""h'o something
ec""ho: command not found


e""ch''o

 e'c""h"'o" UNCLOSED
> e'c""h"'o"^C
 e"ch''''''''o"
ech''''''''o: command not found
 e"ch""""""o"

 e""ch''o

 "e""ch''o"
ech''o: command not found




**THIS**

echo "some'thi'ng"
some'thi'ng

echo "somet""hing"
something

echo 'something'
something

echo 'some''thing'
something

echo 'some""thing'
some""thing

echo "some'th'in"g
some'th'ing

**THIS**
remove the OUTER MOST (but not necessarily actually outside chars) quotes
if more quotes inside and not matching the outer most, keep them

- **SINGLE QUOTES**

    - preserves literal value of each character
    - a single quote may not occur between single quotes, even when 	preceded by a backslash GOOD

- **DOUBLE QUOTES**

    - double quote can be quoted within double quotes by preceding it with a backslash DON'T HANDLE THIS
    - preserve the literal value of all characters within the quotes
    - EXCEPT FOR ‘$’

- **DOLLAR**

        - BUT subject = Handle " (double quote) which should prevent the shell from interpreting the meta characters in the quoted sequence except for $ (dollar sign).
=== // dollar in or out DOUBLE quotes should still be dollar
=== // dollar in SINGLE quotes should not be dollar:
echo '$USER'
$USER



meta characters have special meaning and need to be quoted if representing itself


	**COMMAND QUOTATIONS**
:):):)

"wc -l" < file somthing | << eof
[0]	 cmd = "wc -l"	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = <	str = (null)
[2]	 cmd = (null)	file = file	meta = (null)	str = (null)
[3]	 cmd = (null)	file = (null)	meta = (null)	str = somthing
[4]	 cmd = (null)	file = (null)	meta = |	str = (null)
[5]	 cmd = (null)	file = (null)	meta = <<	str = (null)
[6]	 cmd = (null)	file = (null)	meta = (null)	str = eof


wc -l < file something | << eof
[0]	 cmd = wc	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = -l
[2]	 cmd = (null)	file = (null)	meta = <	str = (null)
[3]	 cmd = (null)	file = file	meta = (null)	str = (null)
[4]	 cmd = (null)	file = (null)	meta = (null)	str = something
[5]	 cmd = (null)	file = (null)	meta = |	str = (null)
[6]	 cmd = (null)	file = (null)	meta = <<	str = (null)
[7]	 cmd = (null)	file = (null)	meta = (null)	str = eof


< Makefile wc -l
234
< Makefile "wc -l"
wc -l: command not found
< Makefile "wc"
 234  639 6115

================

 < Makefile "echo"

 < Makefile "echo -n"
echo -n: command not found


