SRC =							\
	child_exec.c				\
	child.c						\
	pipex_error.c				\
	pipex.c

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
	ft_substr.c

FT_TOOLS		= $(addprefix ../ft_tools/, $(_FT_TOOLS_))

SRC				+= $(FT_TOOLS)
OBJ				= $(SRC:.c=.o)
DEP				= $(OBJ:.o=.d)

NAME			= pipex
INCDIR			= ../ft_tools

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
CPPFLAGS		= -MMD -I./$(INCDIR)

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
