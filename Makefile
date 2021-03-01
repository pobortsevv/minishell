# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabra <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 12:26:01 by sabra             #+#    #+#              #
#    Updated: 2021/03/01 12:46:25 by sabra            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ./minishell

SRCS	= srcs/main.c \


OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM 		= rm -rf
CFLAGS	= -Wall -Werror -Wextra -g
LIBFT_DIR = ./libft/libft/
LIBFT	= -L$(LIBFT_DIR) -lft
INCLUDES = -I./includes

.SILENT: $(NAME) clean fclean re

all:
	$(MAKE) $(NAME) -j4

%.o:	%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME):	$(OBJS)
	make bonus -j4 -C ./libft/libft
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)
	echo minishell compiled!

clean:
	$(RM) $(OBJS)
	make fclean -C ./libft/libft
	echo clean .o files
	
fclean: 	clean
	$(RM) $(NAME)
	make fclean -C ./libft/libft
	echo minishell deleted :\(

re:		fclean $(NAME)
