<br/><br/>

**WHAT THE SHELL?**

<br/><br/>


<br/><br/>

**TO DO**

KEEP IT SIMPLE, STUPID :)

- split the input accordingly, find way to not hard code it too much
- test
- parser

<br/><br/>

**HOW, WHAT, WHY, TOKENS**

--- new solution ---

~!~ give input to parse_input() which returns array, split via spaces except for when there
	are quotes, then everything inside the quotes (till the last found quote) is given as a string in
	the array, also, check for symbols and send as single strings 
	
	(will need to parser through quotation tokens properly but do it in the parser).
	e.g.
		some "input" | given in command line
	returned array:
		- some
		- "input"
		- | 
		- given
		- in
		- command
		- line

~!~	parse through argv[i] (argv = parse_input(input))
	tokens = lexer
	these strings are given to the lexer, and a token list is returned

~!~ token list is passed to parser. 

--------------------------------------------
Old confusion...
 ~!~ - start with a clear set up...

!!--- what about the order?? 
-- HOW DO I KEEP THE ORDER CORRECT???

 ---- the lexer now takes the double array argv and returns the tokens
 ---- NO MORE SPLITING IN MAIN
 ---- tokens are given to the parser
 ---- AST passed to expander
 ---- WORK IN PARSE_TOKEN, LEAVE THE REST AS IT IS

 ~!~ - do as little as possible in main, create main lexer func, start there with quotes, make those tokens, then
	ft_split, then find symbols etc.. then make those tokens, return the list 

 ~!~ - Separate quotes
	- if there is a space before first quote and after last quote, tokenize it
	!! - check when tokenizing quotes, if there's a built in
	!! - handling redirects and delimiters in quotes???
	!! - how to handle quotes in quotes: "something "some" things" ??? I dont want to tokenize "something "
		but if: echo "wc -l" | hello "something", I don't want to tokenize everything...

 ~!~ - split via spaces (outside of any quotations)
	- just like I had before with ft_split but now after parsing the quotations
	- in cases like "ec'h'o" and "abc$abc", just pass whole thing as token, can parse in parser and expand in expander

 ~!~ - tokenize: (<< delimiters), redirects, built-ins and words


<br/><br/>

**BELANGRIJK** 
	MUST KNOW WHERE + HOW MANY SPACES
	SO IF SPLIT TO MAKE TOKENS, EITHER REMEMBER OR TOKENIZE THE SPACES TOO === NOPE NOPE NOPE .. >>>


	e'ch'o a		-> STILL WORKS, so remove both types of quotes from built-ins
	ec'h'o a |		-> hangs in bash, JUST THROW ERROR

	FIRST CHECK FOR QUOTES AND TOKENIZE THOSE
	THEN
	SPLIT ON SPACES BUT NOT IN QUOTES
	THEN TOKENIZE EVERYTHING TOGETHER EXCEPT FOR DELIMITERS AND REDIRECTS, 
	PARSE THE SHIT IN THE PARSE: abc$abc - as one token, parsed in parsed...

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


**OTHER RANDOM NOTES**

!!!! remember Djoyke needs to handle absolute paths, and relatives
!!!! specify if double or single quotes by, maybe, token for single, token for double.. or is that 
part of the parsing tree?

### **lexer:** takes *cmd arugments, separates into tokens, puts into linked list

### **parser:** parse linked list and make a AST to pass to the expander...

**metas:** pipe, ampersand, semicolon, less-than, more-than, left parenthesis, right parenthesis, <br/>
dollar, backquote, backslash, single quote, double quote, newline, space and tab


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
