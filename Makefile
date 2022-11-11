NAME		= 	minishell

SRCS		= 	main.c\
				lexer.c\
				parser.c\
				uncover_token.c\
				set_envp_to_list.c\
				get_token_type.c\
				free.c\
				parse.c\
				parser_errors.c

OBJS		= 	$(SRCS:.c=.o)

LIBDIR		= 	libft

LIBFT_LIB	= 	$(LIBDIR)/libft.a

LIB			= 	-L$(LIBDIR) -lft

CFLAGS		= 	-Wall -Werror -Wextra

RDLN		= 	-lreadline -L/opt/homebrew/Cellar/readline/8.1.2/lib \
                -I/opt/homebrew/Cellar/readline/8.1.2/include \
                -lreadline -L~/.brew/Cellar/readline/8.1.2/lib \
                -I~/.brew/Cellar/readline/8.1.2/include

RM			= 	rm -f

%.o: %.c	minishell.h
			$(CC) -g $(CFLAGS) -I$(LIBDIR) -c $< -o $@

$(NAME):	$(LIBFT_LIB) $(OBJS)
			$(CC) $(CFLAGS) -I$(LIBDIR) $(OBJS) -o $(NAME) $(LIB) $(RDLN)
			make clean

.PHONY:		all clean fclean re make_lib

all:		$(NAME)

$(LIBFT_LIB):	make_lib

make_lib:
			make -C $(LIBDIR)

clean:
			make clean -C $(LIBDIR)
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C $(LIBDIR)
			$(RM) $(NAME)

re:			fclean all
