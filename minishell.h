/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:10:49 by nnelson           #+#    #+#             */
/*   Updated: 2022/08/04 02:39:44 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

int	g_exit_status;

typedef struct s_tokens
{
	char				*token;
	char				*type_of_tocken;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_envp
{
	char				*key;
	char				*value;
	struct s_envp		*next;
}						t_envp;

typedef struct s_arguments
{
	char				*arg;
	struct s_arguments	*next;
}						t_arguments;

typedef struct s_processes
{
	int					idx;
	char				*cmd;
	struct s_arguments	*args_to_cmd;
	char				*infile;
	char				*stop_word;
	char				*outfile_with_replace;
	char				*outfile_without_replace;
	struct s_processes	*next;
}						t_processes;

typedef struct s_executor
{
	int			processes_num;
	char		*paths;
	char		**cmd_paths;
	int			*pipe;
	int			pipe_nmbs;
}						t_executor;

typedef struct s_minishell
{
	struct s_envp		*envp;
	struct s_tokens		*tokens;
	struct s_processes	*processes;
	int					n_pipes;
	int					n_redirects;
	char				**env;
}						t_minishell;

t_tokens	*lexer(char *readed_line, char **envp);
char		*uncover_token(char *token, char **envp);
char		*get_token_type(char *token);

int			parser(t_minishell *minishell, char *trimmed_readed_line);
t_envp		*set_envp_to_list(char **envp);
int			get_token_types(t_minishell *minishell);

void		*free_list(t_tokens *list);
void		free_if_not_null(void *pointer);
void		free_if_not_null_s(void *pointer1, void *pointer2);
void		*free_and_return_null(t_tokens *list_head, char *uncovered_token, char *readed_line);
int			free_and_return_1(t_tokens *list_head, char *readed_line);
void		free_while_result(t_tokens *list_head, char *readed_line);

void		parse(t_minishell *minishell);
void		parse_pipe(t_processes **p);
void		parse_arg(t_processes *p, t_tokens *t, t_arguments **args);

int			pipes_error(t_minishell *minishell);
int			redirects_error(t_minishell *minishell);
int			is_command_first(t_minishell *minishell);
int			return_error(char *error);

void		deal_with_redir(t_tokens *t, t_processes *p);

#endif
