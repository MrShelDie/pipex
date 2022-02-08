/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:42:22 by nick              #+#    #+#             */
/*   Updated: 2022/02/09 01:41:15 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define FALSE 0
# define TRUE 1

# define READ_END 0
# define WRITE_END 1

/* The main data of the project */
typedef struct s_prime
{
	char	**argv;
	char	**envp;
	char	**envp_paths;
	char	***cmds;
	int		cmds_size;
	int		here_doc;
	int		argc;
}	t_prime;

/* Error handling codes */
typedef enum e_error
{
	FEW_ARGS,
	MALLOC,
	PIPE,
	FORK,
	NONE
}	t_error;

/*	Displays an error message, clears data and ends the process */
void	pipex_exit(t_prime *prime, t_error error, char *program, char *file);

/* Prepares pipe for the first process and forks it */
void	first_child(int pipefd[2], t_prime *prime);

/* Prepares pipes for the middle process and forks it */
void	middle_child(char **cmd, int pipefd[2], int readfd, t_prime *prime);

/* Prepares pipes for the last process and forks it. Returns the pid
*  of the process so that the calling function can call waitpid*/
pid_t	last_child(int readfd, t_prime *prime);

/* If there is here_doc, then this process is executed
*  first, binds stdin to the first command */
void	here_doc_exec(t_prime *prime, int writefd);

/* The first process connects the file for reading, the first
*  command and the second command. Not executed if there is a here_doc */
void	first_child_exec(t_prime *prime, int writefd);

/* The middle child processes are connected to each other using pipe */
void	middle_child_exec(t_prime *prime, char **cmd, int readfd, int writefd);

/* The last process connects using pipe
*  to the previous one and opens the file for writing */
void	last_child_exec(t_prime *prime, int readfd);

/* Prints the environment variable */
void	write_here_doc_line(const char *line, char **envp, int writefd);

#endif
