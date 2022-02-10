_SRC_BONUS_ =					\
	child_bonus.c				\
	child_exec_bonus.c			\
	child_exec_utils_bonus.c	\
	here_doc_exec_bonus.c		\
	pipex_bonus.c				\
	pipex_error_bonus.c

_FT_TOOLS_ =					\
	ft_free_split.c				\
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


SRC_BONUS 		= $(addprefix bonus/, $(_SRC_BONUS_))
FT_TOOLS		= $(addprefix ft_tools/, $(_FT_TOOLS_))

SRC_BONUS		+= $(FT_TOOLS)
OBJ_BONUS		= $(SRC_BONUS:.c=.o)
DEP_BONUS		= $(OBJ_BONUS:.o=.d)

NAME			= pipex
INCDIR			= include

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g		# TODO delte -g
CPPFLAGS		= -MMD -I./$(INCDIR)

all:		$(NAME)

$(NAME):	$(OBJ_BONUS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ_BONUS) $(DEP_BONUS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP_BONUS)
