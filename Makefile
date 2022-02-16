_SRC_ =							\
	child_exec.c				\
	child.c						\
	pipex_error.c				\
	pipex.c

_SRC_B_ =						\
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

MAND_FLAG		= .mand_flag
BONUS_FLAG		= .bonus_flag

SRC				= $(addprefix src/mandatory/, $(_SRC_))
SRC_B 			= $(addprefix src/bonus/, $(_SRC_B_))
FT_TOOLS		= $(addprefix src/ft_tools/, $(_FT_TOOLS_))

SRC				+= $(FT_TOOLS)
SRC_B			+= $(FT_TOOLS)

OBJ				= $(SRC:.c=.o)
OBJ_B			= $(SRC_B:.c=.o)

DEP				= $(OBJ:.o=.d)
DEP_B			= $(OBJ_B:.o=.d)

NAME			= pipex
INCDIR			= include

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
CPPFLAGS		= -MMD -I./$(INCDIR)

all:		$(NAME)

bonus:
	@make --no-print-directory OBJ="$(OBJ_B)" all

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ) $(OBJ_B) $(DEP) $(DEP_B)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)
-include $(DEP_B)
