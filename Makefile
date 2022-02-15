NAME		= pipex
MANDDIR 	= mand/
BONDIR		= bon/

all:
	@make --no-print-directory -C $(MANDDIR) all
	@cp $(MANDDIR)/$(NAME) $(NAME)

bonus:
	@make --no-print-directory -C $(BONDIR) bonus
	@cp $(BONDIR)/$(NAME) $(NAME)

clean:
	@make --no-print-directory -C $(MANDDIR) fclean
	@make --no-print-directory -C $(BONDIR) fclean

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re