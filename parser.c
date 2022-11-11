#include "minishell.h"

static void	get_pipes(t_minishell *minishell)
{
	int			i;
	int			n_pipes;
	t_tokens	*t;

	t = minishell->tokens;
	i = 0;
	n_pipes = 0;
	while (t)
	{
		if (!ft_strcmp(t->token, "|\0"))
			n_pipes++;
		i++;
		t = t->next;
	}
	minishell->n_pipes = n_pipes;
}

static void	get_redirects(t_minishell *minishell)
{
	int			i;
	int			n_redirects;
	t_tokens	*t;

	t = minishell->tokens;
	i = 0;
	n_redirects = 0;
	while (t)
	{
		if (!ft_strcmp(t->token, "<\0")
			|| !ft_strcmp(t->token, ">\0")
			|| !ft_strcmp(t->token, "<<\0")
			|| !ft_strcmp(t->token, ">>\0"))
			n_redirects++;
		i++;
		t = t->next;
	}
	minishell->n_redirects = n_redirects;
}

static void	print_list(t_tokens *list)
{
	printf("types: ");
	while (list)
	{
		printf("\"%s\", ", list->type_of_tocken);
		list = list->next;
	}
	printf("\n");
}

static void	print_list_2(t_processes *head)
{
	t_processes	*list;
	t_arguments	*args;

	list = head;
	while (list)
	{
		printf("process %s: ", list->cmd);
		args = list->args_to_cmd;
		while (args)
		{
			printf("%s ", args->arg);
			args = args->next;
		}
		list = list->next;
		printf("\n");
	}
}

int	parser(t_minishell *minishell, char *trimmed_readed_line)
{
	if (redirects_error(minishell) || pipes_error(minishell))
		return (free_and_return_1(minishell->tokens, trimmed_readed_line));
	get_pipes(minishell);
	get_redirects(minishell);
	if (get_token_types(minishell))
		return (free_and_return_1(minishell->tokens, trimmed_readed_line));
	print_list(minishell->tokens);
	if (is_command_first(minishell))
		return (free_and_return_1(minishell->tokens, trimmed_readed_line));
	parse(minishell);
	print_list_2(minishell->processes);
	return (0);
}
