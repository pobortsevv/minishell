# Minishell
Group project with @LanaLebedeva
## Summary
The objective of this project is for us to create a simple shell. Yes, our little bash or zsh. We will learn a lot about processes and file descriptors.
## Task
-  Not interpret unclosed quotes or unspecified special characters like \ or;
-  Not use more than one global variable, think about it and be ready to explain why you do it.
-  Show a prompt when waiting for a new command.
-  Have a working History.
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
-   It must implement the builtins:
	-  echo with option -n
	-  cd with only a relative or absolute path
	- pwd with no options
	- export with no options
	- unset with no options
	- env with no options or arguments
	- exit with no options
-   ’ inhibit all interpretation of a sequence of characters.
-  " inhibit all interpretation of a sequence of characters except for $.
-  Redirections:
	-  < should redirect input.
	- \> should redirect output.
	-  “<<” read input from the current source until a line containing only the de- limiter is seen. it doesn’t need to update history!
	-  “>>” should redirect output with append mode.
- Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
- Environment variables ($ followed by characters) should expand to their values.
-  $? should expands to the exit status of the most recently executed foreground pipeline.
-  ctrl-C ctrl-D ctrl-\ should work like in bash.

## How to compile
	cd minishell
	make
	./minishell
![enter image description here](https://sun1-21.userapi.com/impg/CqgLKpkCiW-YVyf8B8iRLHS8vKFoFnmt470aJA/o6Ub19LvLYQ.jpg?size=1194x428&quality=96&sign=6f36a93ed3c913eca4c38b8b307fa976&type=album)

*42 école project.*
