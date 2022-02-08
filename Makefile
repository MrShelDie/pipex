_SRC_BONUS_ =				\
	pipex_bonus_utils.c		\
	pipex_bonus.c

_LIBFT_TOOLS_ =				\
	ft_free_split.c			\
	ft_putstr_fd.c			\
	ft_split.c				\
	ft_strdup.c				\
	ft_strjoin.c			\
	ft_strlcat.c			\
	ft_strlcpy.c			\
	ft_strlen.c				\
	ft_strncmp.c

SRC_BONUS 	= $(addprefix bonus/, $(_SRC_BONUS_))
LIBFT_TOOLS		= $(addprefix ft_tools/, $(_LIBFT_TOOLS_))

SRC_BONUS		+= $(LIBFT_TOOLS)
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

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP_BONUS)
