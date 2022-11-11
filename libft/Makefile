NAME = libft.a

C_FILES = ft_append.c \
		  ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_isspace.c \
		  ft_itoa.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_striteri.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strcmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c

O_FILES = $(patsubst %.c,%.o,$(C_FILES))

D_FILES = $(patsubst %.c,%.d,$(C_FILES))

H_FILES = libft.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(O_FILES)
	ar rcs $(NAME) $?

%.o: %.c $(H_FILES)
	gcc $(FLAGS) -c $< -o $@ -MD

clean:
	rm -f $(O_FILES) $(D_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

include $(wildcard $(D_FILES))

.PHONY: all clean fclean re