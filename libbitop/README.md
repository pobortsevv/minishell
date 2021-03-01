# Bit operations library

## NAME
	libbitop - bit operations library

## SYNOPSIS
	#include "libbitop.h"

## DESCRIPTION
	The main area of application of this library is basic bit operations on the integer type.

## LIST OF FUNCTION
| Function | Description |
|----:|:----|
| checkbit | check the specified bit | 
| setbit | set the specified bit |
| unsetbit | unset the specified bit |
|switchbit | switch the specified bit |

## CONFORMING TO
	The libbitop library conforms to C99

## ENVIRONMENT
The library was compiled and tested:
gcc (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008

## MAKEFILE

	make 		- builds a static library
	make clean 	- deletes files :*.o and *.d
	make fclean	- deletes files	:libbitop.a, *.o and *.d
	make re		- clean all and builds a static library

## ABOUT FUNCTION
	size_t	checkbit(const int value, const int position)

	int	setbit(const int value, const int position)

	int	unsetbit(const int value, const int position)

	int	switchbit(const int value, const int position)

	
position  **must be greater than** 0 and **less than** sizeof(int)*CHAR_BIT. 
	If  the  value  of  **position**  is  negative  orisgreater than or equal to the width of the **value**, the behavior is undefined
