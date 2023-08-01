**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT, and during...**

gutentag frau Shelly, wie geht's?
dein computer, kein computer

~~~ Lexer ~~~

-> quotes in lexer: 
	> pretty simple while loopidyloop
	> don't forget to check either side of the quotes for chars

~~~ Parser ~~~

-> some<<something
-> <<something

-> for first token, it could be a cmd from bash (not builtin), how to handle this??


ERRORS :!!!

---------------------------------------------------------------------------------
**TALK TO DJOYKE ABOUT THIS**

Gutentag Fräulein Shelly, wie geht's?echo abc$abc
lexer: 		~: echo
lexer: 		~: abc$abc
first->cmd: echo
second->str: abc$abc 

// i could check the exact behaviour of this and parse it to remove the unnecessary bits

+++++++++++

Gutentag Fräulein Shelly, wie geht's?/usr/bin/cd some thing
lexer: 		~: /usr/bin/cd
lexer: 		~: some
lexer: 		~: thing
first->abso: /usr/bin/cd
second->str: some
second->str: thing
Gutentag Fräulein Shelly, wie geht's?/bin/echo some thing
lexer: 		~: /bin/echo
lexer: 		~: some
lexer: 		~: thing
first->abso: /bin/echo
second->str: some
second->str: thing

IM GOING TO GIVE YOU AN ABSO PATH IN THE STRUCT, STILL NEED TO CHECK IF ITS THE CORRECT 
ABSO PATH, ECHO WORKS, CD DOESN'T, ETC ETC., USE EXECVE FOR THESE BECAUSE USING
THE ENV PATH FOR THESE NOT OUR BUILDINS
// I COULD CHECK THESE PATHS AND ONLY GIVE YOU VALID ONES

+++++++++++++++++++++

djoyke... maybe use a static function once in a while.... please

+++++++++++++++++++++++++=


t_expand	*micro_expand(char **envp, t_parser *node)
{
	// t_env	    *env;
    t_expand    *expand;

    (void) envp;
	expand = NULL;
	// env = micro_env_list(envp);
	while (node)
	{
        shelly_expand_lstadd_back(&expand, init_expand_list(node));
		node = node->next;
	}
	return (expand);
}



--------------------------------------------------------------------------
SAVING OLD SHIT JUST INCASE


// UNNCESSARY CHECK ALL TOKENS WITH A SEPARATE FUNCTION IN PARSER() AND THEN JUST DEFINE WITH THE SPECIFIC TWO FUNCS IN PARSER()
// /**
//  * @brief	compare the first token to cmds and valid signs
//  * 			// will also need to find a way to allow first token to be non-built in command...
//  * @param	tokens first arg token passed from the lexer to the parser
//  * @param	parser_struct  structure to assign each token to the correct type
//  * @return	bool: true/false 1/0
// */
// static bool	parser_first_token(t_lexer *tokens, t_parser *parser_struct)
// {
// 	ft_lower_str(tokens->input);
// 	if (parser_check_quotes(tokens))
// 	{
// 		tokens->input = remove_quotes(tokens);
// 		if (!tokens->input)
// 			return (0);
// 		if (parser_cmp_builtins(tokens))
// 		{
// 			parser_struct->cmd = tokens->input;
// 			printf("first->cmd: %s\n", parser_struct->cmd);
// 			return (true);
// 		}
// 	}
// 	else
// 		if (parser_cmp(tokens, parser_struct))
// 			return (true);
// 	return (false);
// }
