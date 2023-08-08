**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT, and during...**

Gutentag Frälein Shelly, wie geht's?
dein computer, kein computer

---------------------------------------------------------------------------------
**CURRENT TO DO'S:**

~~QUOTES~~

----> handle quotes with spaces on either side (until when then? need to find the last quote)
----> then handle the letters on either side of the quotes

----> i give without variable too much space... leaky

!!!
-> take quoted tokens from lexer and break them up futher in parser, what am i checking for? (how is the parser handling quoted tokens?)


~~FLAGS~~

-> echo -n, only built in
-> + if 'space' and '-' after something, check for flag validity in comb with cmd


~~ERRORS~~

-> cmd not found
-> unclosed quotes
-> pipe stuff


---------------------------------------------------------------------------------
**FUTURE TO DOS::**

*Lexer*

-> send good tokens to parser


*Parser*

->	some<<something 
->	<<something
				bash-3.2$ some<<something
				> something
				bash: some: command not found
				bash-3.2$ some<<something
				> hello
				> some
				> something
				bash: some: command not found
				bash-3.2$ <<something
				> some
				> something
				bash-3.2$

*Other*


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


