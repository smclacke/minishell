------------------------------TO DO----------------------------

1) change dprintfs

2) handle exit codes
    //in wait for child proces get the exit codes there..

3) ERRORS TO STANDARD ERROR!

4) met t_execute struct pointer maar t_export en t_env maken zodat ik clean functie kan.


!!*we are not:*!!
- SHLVL
- export ls="ls -l"

REMEMBER! exit from parser when:
	- nothing after meta
	- unclosed quotes
	- pipe after pipe
	- malloc
	- if string doesnt come back exit
 