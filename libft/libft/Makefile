NAME			= libft.a
SRCS	=	ft_memset.c \
		 	ft_bzero.c \
		 	ft_memcpy.c \
		 	ft_memccpy.c \
		 	ft_memmove.c \
		 	ft_strrchr.c \
		 	ft_strnstr.c \
		 	ft_atoi.c \
			ft_atof.c \
		 	ft_isdigit.c \
		 	ft_memchr.c \
		 	ft_strdup.c \
		 	ft_strlcat.c \
		 	ft_calloc.c \
		 	ft_isalnum.c \
			ft_inset.c \
		 	ft_isalpha.c \
		 	ft_isascii.c \
		 	ft_isprint.c \
		 	ft_memcmp.c \
		 	ft_strchr.c \
		 	ft_strncmp.c \
		 	ft_tolower.c \
		 	ft_toupper.c \
		 	ft_strlcpy.c \
		 	ft_substr.c \
		 	ft_strjoin.c \
		 	ft_strtrim.c \
			ft_charcnt.c \
			ft_free_mat.c \
			ft_queq.c \
		 	ft_split.c \
		 	ft_itoa.c \
		 	ft_strmapi.c \
		 	ft_putchar_fd.c \
		 	ft_putstr_fd.c \
		 	ft_putendl_fd.c \
		 	ft_putnbr_fd.c \
		 	ft_strlen.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_putnbr16_fd.c \
			../printf/ft_printf.c \
 			../printf/parser/ft_flags.c \
			../printf/parser/ft_parser.c \
			../printf/process/ft_type_init.c \
			../printf/process/ft_cs_type.c \
			../printf/process/ft_di_type.c \
			../printf/process/ft_dwx_type.c \
			../printf/process/ft_u_type.c \
			../printf/process/ft_p_type.c \
			../printf/process/ft_upx_type.c \

OBJS			= $(SRCS:.c=.o)

.SILENT: all $(NAME) compile clean fclean re

BONUS			=	ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \

BONUS_OBJS		= 	$(BONUS:.c=.o)

CC				= @gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g 


all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)
				echo libft compiled succesfully!

compile:		$(OBJS)
				$(CC) $(CFLAGS) $(SRCS)
				./a.out

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)
				echo libft .o file removed

fclean:			clean
				$(RM) $(NAME)
				echo libft deleted :\(

re:				fclean $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
