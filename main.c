#include "minishell.h"

static void	signals_handler(int signal, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signal == SIGINT)
	{
//		rl_on_new_line();
//		rl_replace_line("", 1);
//		write(1, "\n", 1);
//		rl_redisplay();
//		exit_status = 130;
	}
}

char	*read_line(char *readed_line)
{
	readed_line = readline(">> ");
	if (!readed_line)
	{
		printf("\n[Process completed]\n");
		exit(0);
	}
	add_history(readed_line);
	return (readed_line);
}

static void	print_list(t_tokens *list)
{
	printf("list: ");
	while (list)
	{
		printf("\"%s\", ", list->token);
		list = list->next;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	char				*readed_line;
	char				*trimmed_readed_line;
	t_minishell			*minishell;
	struct sigaction	sig_int;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	sig_int.sa_flags = SA_SIGINFO;
	sig_int.sa_sigaction = signals_handler;
	sigaction(SIGINT, &sig_int, NULL);
	readed_line = NULL;
	g_exit_status = 0;
	while (1)
	{
		readed_line = read_line(readed_line);
		trimmed_readed_line = ft_strtrim(readed_line, " ");
		if (!trimmed_readed_line)
			continue ;
//		minishell->envp = set_envp_to_list(envp);
		minishell->env = envp;
		minishell->tokens = lexer(trimmed_readed_line, envp);
		if (!minishell->tokens || parser(minishell, trimmed_readed_line))
//			print_list(minishell->tokens);
			continue ;
//		print_list(minishell->tokens);
		// executor();
		free_while_result(minishell->tokens, trimmed_readed_line);
	}
//	free(minishell);
}
