/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:42:22 by nick              #+#    #+#             */
/*   Updated: 2022/02/07 00:34:59 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>

# include "libft_tools.h"

# define FALSE 0
# define TRUE 1

/* The main data of the project */
typedef struct s_prime
{
	char	**argv;
	char	**envp_paths;
	char	***cmds;
	int		cmds_size;
	int		here_doc;
}	t_prime;

/* Error handling codes */
typedef enum e_error
{
	FEW_ARGS,
	MALLOC,
	NONE
}	t_error;

/*	Displays an error message, closes files, clears data and ends the process */
void	pipex_exit(t_prime *prime, t_error error, char *program, char *file);

#endif
