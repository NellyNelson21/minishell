#include "minishell.h"

int	redirects_error(t_minishell *minishell)
{
	int			i;
	t_tokens	*t;

	t = minishell->tokens;
	while (t)
	{
		if (ft_strcmp(t->token, "<\0") && ft_strcmp(t->token, ">\0")
			&& ft_strcmp(t->token, "<<\0") && ft_strcmp(t->token, ">>\0"))
		{
			i = 0;
			while (t->token[i])
			{
				if (t->token[i] == '>' || t->token[i] == '<')
				{
					printf("minishell: redirect in argument not allowed\n");
					return (1);
				}
				i += 1;
			}
		}
		t = t->next;
	}
	return (0);
}

int	pipes_error(t_minishell *minishell)
{
	int			i;
	t_tokens	*t;

	t = minishell->tokens;
	while (t)
	{
		if (ft_strcmp(t->token, "|\0"))
		{
			i = 0;
			while (t->token[i])
			{
				if (t->token[i] == '|')
				{
					printf("minishell: pipe in argument not allowed\n");
					return (1);
				}
				i += 1;
			}
		}
		t = t->next;
	}
	return (0);
}

int	return_error(char *error)
{
	printf("%s\n", error);
	return (1);
}

int	is_command_first(t_minishell *minishell)
{
	t_tokens	*t;

	t = minishell->tokens;
	if (ft_strcmp(t->type_of_tocken, "cmd\0")
		&& ft_strcmp(t->type_of_tocken, "redir\0"))
		return (return_error("minishell: command not found"));
	while (minishell->n_pipes && t)
	{
		if (!ft_strcmp(t->type_of_tocken, "pipe\0"))
		{
			t = t->next;
			if (t)
			{
				if (ft_strcmp(t->type_of_tocken, "cmd\0")
					&& ft_strcmp(t->type_of_tocken, "redir\0"))
					return (return_error("minishell: command not found"));
			}
			else
				return (return_error(
						"minishell: pipe error: pipe in the end of the line"));
		}
		t = t->next;
	}
	return (0);
}
