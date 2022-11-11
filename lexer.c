#include "minishell.h"

static t_tokens	*lst_get_last_elem(t_tokens *list)
{
	if (!list)
		return (NULL);
	if (!list->next)
		return (list);
	else
	{
		while (list->next)
			list = list->next;
		return (list);
	}
}

static t_tokens	*lst_init_new_elem(char *value)
{
	t_tokens	*lst_new_elem;

	lst_new_elem = malloc(sizeof(t_tokens));
	if (lst_new_elem && value)
	{
		lst_new_elem->token = ft_strdup(value);
		lst_new_elem->type_of_tocken = NULL;
		lst_new_elem->next = NULL;
		return (lst_new_elem);
	}
	return (NULL);
}

static t_tokens	*lst_add_back(t_tokens *list_head, t_tokens *elem)
{
	t_tokens	*elem_to_add;

	if (!list_head)
		list_head = elem;
	else
	{
		elem_to_add = lst_get_last_elem(list_head);
		elem_to_add->next = elem;
	}
	return (list_head);
}

static size_t	find_parameters(char *readed_line, size_t *i)
{
	size_t	j;

	j = 0;
	while (readed_line[*i] && ft_isspace(readed_line[*i]))
		*i += 1;
	while (readed_line[*i + j] && !ft_isspace(readed_line[*i + j]))
	{
		if (readed_line[*i + j] == '\'')
		{
			j += 1;
			while (readed_line[*i + j] != '\'')
				j += 1;
			j += 1;
		}
		else if (readed_line[*i + j] == '"')
		{
			j += 1;
			while (readed_line[*i + j] != '"')
				j += 1;
			j += 1;
		}
		else
			j += 1;
	}
	return (j);
}

t_tokens	*lexer(char *readed_line, char **envp)
{
	char		*token;
	char		*uncovered_token;
	t_tokens	*list_head;
	size_t		i;
	size_t		j;

	i = 0;
	list_head = NULL;
	while (i < ft_strlen(readed_line))
	{
		j = find_parameters(readed_line, &i);
		token = ft_substr(readed_line, i, j);
		uncovered_token = uncover_token(token, envp);
		free(token);
		if (uncovered_token)
		{
			list_head = lst_add_back(list_head,
					lst_init_new_elem(uncovered_token));
			free(uncovered_token);
		}
		else
			return (free_and_return_null(list_head, uncovered_token, readed_line));
		i += j;
	}
	return (list_head);
}
