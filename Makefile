# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabra <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 12:26:01 by sabra             #+#    #+#              #
#    Updated: 2021/03/01 15:08:00 by sabra            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ./minishell

SRCS	= srcs/main.c \


OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM 		= rm -rf
CFLAGS	= -Wall -Werror -Wextra -g
LIBFT_DIR = ./libft/libft/
LIBBIT_DIR = ./libbitop/
LIBS	= -L$(LIBFT_DIR) -lft -L$(LIBBIT_DIR) -lbitop
INCLUDES = -I./includes

.SILENT: $(NAME) clean fclean re

all:
	@$(MAKE) $(NAME) -j4

%.o:	%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME):	$(OBJS)
	@make bonus  -C ./libft/libft
	@make -C ./libbitop
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	echo minishell compiled!

clean:
	@$(RM) $(OBJS)
	@make clean -C ./libft/libft
	@make clean -C ./libbitop
	echo clean .o files
	
fclean: 	clean
	@$(RM) $(NAME)
	@make fclean -C ./libft/libft
	@make fclean -C ./libbitop
	echo minishell deleted :\(

re:		fclean $(NAME)
