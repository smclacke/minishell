**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT**

gutentag frau Shelly, wie geht's?
dein computer, kein computer

~~~ Lexer ~~~

-> quotes in lexer: 
	> pretty simple while loopidyloop
	> don't forget to check either side of the quotes for chars

~~~ Parser ~~~

-> when checking first token in parser if valid, <<LIMITER, <input, etc won't work cause extra shit after inside the token.... handle this!

-> quotes inside cmds, remove this before validating in the parser...


ERRORS :)


!!!!!!!!!!! TALK TO DJOYKE ABOUT THIS:
Gutentag Fräulein Shelly, wie geht's?echo abc$abc
lexer: 		~: echo
lexer: 		~: abc$abc
first->cmd: echo
second->str: abc$abc


Do you then take the "parsed token" and check for the dollar or do i need to do something
different cause right now it's seen as a string but that could actually
be more helpful for you

