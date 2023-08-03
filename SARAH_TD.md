**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT, and during...**

Gutentag Frälein Shelly, wie geht's?
dein computer, kein computer

---------------------------------------------------------------------------------
**FUTURE TO DOS::**

*Lexer*


*Parser*

-> some<<something 
	<<something

*Other*

-> FLAGS: WHERE WHAT HOW WHY

-> ERRORS :!!!


---------------------------------------------------------------------------------
**CURRENT TO DO'S:**

~~QUOTES~~
-> split on quotes and spaces correctly so initial list of tokens is good
	> pretty simple while loopidyloop
	> don't forget to check either side of the quotes for chars
	> dont do anything with the first token, it doesnt matter!!

-> take quoted tokens in lexer and break them up futher, what am i checking for?
	> lexer_quotes.c, whole file needs a lot of work, but keep what I have
		because it could be useful either in lexer or parser

-> send good tokens to parser

-> how will the parser handle quotes, need to add this


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


