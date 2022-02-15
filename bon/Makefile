SRC =							\
	child_bonus.c				\
	child_exec_bonus.c			\
	child_exec_utils_bonus.c	\
	here_doc_exec_bonus.c		\
	pipex_bonus.c				\
	pipex_error_bonus.c

_FT_TOOLS_ =					\
	ft_free_split.c				\
	ft_putchar_fd.c				\
	ft_putstr_fd.c				\
	ft_split.c					\
	ft_strdup.c					\
	ft_strjoin.c				\
	ft_strlcat.c				\
	ft_strlcpy.c				\
	ft_strlen.c					\
	ft_strncmp.c				\
	ft_substr.c					\
	get_next_line_utils.c		\
	get_next_line.c

FT_TOOLS		= $(addprefix ../ft_tools/, $(_FT_TOOLS_))

SRC				+= $(FT_TOOLS)
OBJ				= $(SRC:.c=.o)
DEP				= $(OBJ:.o=.d)

NAME			= pipex
INCDIR			= ../ft_tools

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
CPPFLAGS		= -MMD -I./$(INCDIR)

bonus:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
