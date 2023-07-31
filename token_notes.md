<br/><br/>

**WHAT THE SHELL?**

<br/><br/>


<br/><br/>

**CURRENT PROBLEMS :)**

well... many :)


<br/><br/>

**TO DO**

KEEP IT SIMPLE, STUPID :)

- fix >> tokens
- write quote function
- write rest tokens function
- figure out index/order shizz
- test test test
- parser

--------------------------------------------------------------------------------------------
**NOTES**

<br/><br/>

**BELANGRIJK** 
	MUST KNOW WHERE + HOW MANY SPACES IN QUOTATIONS

	e'ch'o a		-> STILL WORKS, so remove both types of quotes from built-ins
	ec'h'o a |		-> hangs in bash, JUST THROW ERROR

	FIRST CHECK FOR QUOTES AND TOKENIZE THOSE
	THEN
	SPLIT ON SPACES BUT NOT IN QUOTES
	TOKENIZE REDIRECTS, TOKENIZE DELIMITERS + ALL SURROUNDING CHARACTERS (ABC$ABC)
	THEN TOKENIZE EVERYTHING LEFT OVER


!!!!!!!!!! absolute paths are valid first inputs :))))):))
	doesn't do anything though of course....
	bash-3.2$ which cd
	/usr/bin/cd
	bash-3.2$ /usr/bin/cd
	bash-3.2$ /usr/bin/cd desktop
	/usr/bin/cd: line 4: cd: desktop: No such file or directory
	bash-3.2$ /usr/bin/cd //
	bash-3.2$ /usr/bin/cd ..
	bash-3.2$ pwd
	/Users/smclacke/Desktop/minishell
	bash-3.2$ /usr/bin/cd ..
	bash-3.2$ pwd
	/Users/smclacke/Desktop/minishell
	bash-3.2$ /usr/bin/cd ..
	bash-3.2$ pwd
	/Users/smclacke/Desktop/minishell
	bash-3.2$ /usr/bin/cd src_saar
	bash-3.2$ pwd
	/Users/smclacke/Des

<br/>

**EXAMPLES TO KEEP IN MIND...**
	acs$acs									- >acs
	"something$something some things" 		- MESSY UNDEFINED BEHAVIOUR
	echo "abc$abc"							- >abc
	echo "abc$USER"							- >abcsmclacke
	echo 'abc$USER'							- >abc$USER
	echo 'abc$USER$'						- >abc$USER$
	echo "abc$USER$"						- >abcsmclacke$
	ec'h'o									- works just like echo
	echo a |								- hangs waiting for next cmd, just error.

token: >>>>>>>>>>>>
token: >>>>>>>>>>>
token: >>>>>>>>>>
token: >>>>>>>>>
token: >>>>>>>>
token: >>>>>>>
token: >>>>>>
token: >>>>>
token: >>>>
token: >>>
token: >>
token: >

WHAT THE SHELL?!|||||
token: |||||
token: ||||
token: |||
token: ||
token: |

WHAT THE SHELL?!>>
token: >>
token: >

<br/><br/>

**OTHER RANDOM NOTES**

!!!! remember Djoyke needs to handle absolute paths, and relatives

### **lexer:** takes *cmd arugments, separates into tokens, puts into linked list

### **parser:** parse linked list and make a AST to pass to the expander...

dollar, backquote, backslash, single quote, double quote, newline, space and tab
**metas:** pipe, ampersand, semicolon, less-than, more-than, left parenthesis, right parenthesis, 

<br/><br/>

**INFORMATION**

**delimiter:**  whatever is after <<
try delimiter with and without quotes!!! (ole note)
<< + DELIMITER

**redirects:** 
 - < > more-than/less-than 
 - << >> double more-than/less-than
 - pipe | 

**handle:** 
 - dollars (environment variables) 
 - $?
 - ctrl-C 
 - ctrl-D 
 - ctrl-\

**tokenize the builtins** 
 - echo ( + -n) 
 - cd (relative/abso path)
 - pwd 
 - export
 - unset
 - env
 - exit

**quotes:**
• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence

• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)

**FROM SUBJECT PDF**

• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
5
Minishell As beautiful as a shell
• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
