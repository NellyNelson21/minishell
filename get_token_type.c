#include "minishell.h"

static int	is_cmd(char *token)
{
	if (!ft_strcmp(token, "echo\0")
		|| !ft_strcmp(token, "cd\0")
		|| !ft_strcmp(token, "pwd\0")
		|| !ft_strcmp(token, "export\0")
		|| !ft_strcmp(token, "unset\0")
		|| !ft_strcmp(token, "env\0")
		|| !ft_strcmp(token, "exit\0"))
		return (1);
	return (0);
}

static char	*get_type_v1(char *token)
{
	if (is_cmd(token))
		return ("cmd\0");
	else if (!ft_strcmp(token, "|\0"))
		return ("pipe\0");
	else if (!ft_strcmp(token, ">\0")
		|| !ft_strcmp(token, "<\0")
		|| !ft_strcmp(token, ">>\0")
		|| !ft_strcmp(token, "<<\0"))
		return ("redir\0");
	return ("arg\0");
}

static void	malloc_list(t_minishell *minishell, t_tokens *list_head)
{
	while (list_head)
	{
		list_head->type_of_tocken = ft_strdup(get_type_v1(list_head->token));
		list_head = list_head->next;
	}
	list_head = minishell->tokens;
}

static void	change_type_of_tocken(t_tokens	*list_head)
{
	free(list_head->type_of_tocken);
	list_head->type_of_tocken = ft_strdup("file\0");
}

int	get_token_types(t_minishell *minishell)
{
	t_tokens	*list_head;

	list_head = minishell->tokens;
	malloc_list(minishell, list_head);
	if (minishell->n_redirects)
	{
		while (list_head)
		{
			if (!ft_strcmp(list_head->type_of_tocken, "redir\0"))
			{
				if (list_head->next)
				{
					list_head = list_head->next;
					if (!ft_strcmp(list_head->type_of_tocken, "arg\0"))
						change_type_of_tocken(list_head);
					else
						return_error("minishell: no file after redirect");
				}
				else
					return_error("minishell: redirect in the end of the line");
			}
			list_head = list_head->next;
		}
	}
	return (0);
}
