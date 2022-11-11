#include "minishell.h"

int	are_quotes_closed(char *token, size_t *i)
{
	size_t	j;

	j = *i;
	if (token[j] == '\'')
	{
		while (token[j])
		{
			j++;
			if (token[j] == '\'')
				return (1);
		}
	}
	else if (token[j] == '"')
	{
		while (token[j])
		{
			j++;
			if (token[j] == '"')
				return (1);
		}
	}
	return (0);
}

char	*find_envp_key(char **envp, char *envp_key, char *uncovered_token)
{
	char	**envp_copy;
	int		i;

	envp_copy = envp;
	i = 0;
	while (envp_copy[i])
	{
		if (!ft_strncmp(envp_key, envp_copy[i], ft_strlen(envp_key))
			&& envp_copy[i][ft_strlen(envp_key)] == '=')
		{
			uncovered_token = ft_strjoin_and_free(
					uncovered_token, &(envp_copy[i][ft_strlen(envp_key) + 1]));
			return (uncovered_token);
		}
		i += 1;
	}
	return (uncovered_token);
}

char	*process_env(char *token, size_t *i, char *uncovered_token, char **envp)
{
	char	*envp_key;
	char	*exit_status_str;

	*i += 1;
	envp_key = ft_strdup("");
	if (token[*i] == '?')
	{
		exit_status_str = ft_itoa(g_exit_status);
		uncovered_token = ft_strjoin(uncovered_token, exit_status_str);
		free_if_not_null(exit_status_str);
		*i += 1;
	}
	else if (ft_isalnum(token[*i]) || token[*i] == '_')
	{
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			envp_key = ft_append(envp_key, token[(*i)++]);
		uncovered_token = find_envp_key(envp, envp_key, uncovered_token);
	}
	else if (ft_isspace(token[*i]) || token[*i] == '\"' || token[*i] == '\0')
	{
		uncovered_token = ft_append(uncovered_token, '$');
		*i += 1;
	}
	return (uncovered_token);
}

char	*process_single_quotes(char *token, size_t *i, char *res)
{
	if (are_quotes_closed(token, i))
	{
		*i += 1;
		while (token[(*i)] && token[(*i)] != '\'')
			res = ft_append(res, token[(*i)]);
		*i += 1;
	}
	else
	{
		printf("minishell: expected closing \' in the line\n");
		*i = ft_strlen(token);
		free_if_not_null(res);
		return (NULL);
	}
	return (res);
}

char	*process_double_quotes(char *token, size_t *i, char *res, char **envp)
{
	if (are_quotes_closed(token, i))
	{
		*i += 1;
		while (token[(*i)] && token[(*i)] != '\"')
		{
			if (token[*i] != '$')
			{
				res = ft_append(res, token[(*i)]);
				*i += 1;
			}
			else
				res = process_env(token, i, res, envp);
		}
		*i += 1;
	}
	else
	{
		printf("minishell: expected closing \" in the line\n");
		*i = ft_strlen(token);
		free_if_not_null(res);
		return (NULL);
	}
	return (res);
}

char	*uncover_token(char *token, char **envp)
{
	char	*res;
	size_t	i;

	i = 0;
	res = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '$')
			res = process_env(token, &i, res, envp);
		else if (token[i] == '\'')
		{
			res = process_single_quotes(token, &i, res);
			if (!res)
				return (res);
		}
		else if (token[i] == '\"')
		{
			res = process_double_quotes(token, &i, res, envp);
			if (!res)
				return (res);
		}
		else
			res = ft_append(res, token[i++]);
	}
	return (res);
}
