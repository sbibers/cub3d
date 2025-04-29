SRCS_DIR = src
OBJS_DIR = obj

SRCS		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
      			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
      			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
      			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
				ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
				ft_putnbr_hex_fd.c ft_printf.c ft_printf_utils.c ft_printf_special.c \
				get_next_line.c get_next_line_utils.c find_path.c pipex_helper_functions.c \
				pipex_here_doc.c pipex_main.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC			= @cc
RM			= @rm -f
CFLAGS			= -Wall -Wextra -Werror -g -I.

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
			@ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
			@mkdir -p $(OBJS_DIR)

bonus:		all

clean:
	@rm -rf $(OBJS_DIR)

fclean:			clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:			all bonus clean fclean re

