NAME 		= libbitop.a

DIR 		= ./

HEADER 		= ./libbitop.h

HEADER_DIR	= ./

FUNCTIONS 	= checkbit.c\
		  setbit.c\
		  unsetbit.c\
		  switchbit.c

SOURCE		= $(addprefix $(DIR), $(FUNCTIONS))

OBJECTS		= $(SOURCE:.c=.o)

FLAGS		?= -Wall -Wextra -Werror

all: $(OBJECTS) $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@ -I $(HEADER_DIR) -MD

-include  *.d

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS) $?
	ranlib $(NAME)

clean:
	rm -f $(OBJECTS) *.d

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

