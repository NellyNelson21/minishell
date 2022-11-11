#include "minishell.h"

static int	ft_get_word_amount(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_get_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	*ft_delete_array(char **array, int word_amount)
{
	int	i;

	i = 0;
	while (i < word_amount)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**ft_fill_array(char const *s, char c, char **array, int
word_amount)
{
	int	i;
	int	k;
	int	word_len;

	i = -1;
	while (++i < word_amount)
	{
		while (*s == c)
			s++;
		word_len = ft_get_word_len(s, c);
		array[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!array[i])
			return (ft_delete_array(array, i));
		k = 0;
		while (k < word_len)
		{
			array[i][k] = *s;
			k++;
			s++;
		}
		array[i][k] = '\0';
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_amount;

	if (!s)
		return (NULL);
	word_amount = ft_get_word_amount(s, c);
	array = (char **)malloc((word_amount + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_fill_array(s, c, array, word_amount);
	return (array);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n) //0 - equals; 1 - not equals
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i]
			|| s1[i] == '\0' || s2[i] == '\0')
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

static char	*get_cmd(char **paths, char *cmd) // возвращает абсолютный путь к команде (.../bin/echo)
{
	char	*tmp_dir;
	char	*command;

	while (*paths)
	{
		tmp_dir = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp_dir, cmd);
		free(tmp_dir);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char	*find_path(char **envp) //возвращает указатель на папку с путями к командам
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int main(int argc, char **argv, char **envp)
{
    char *paths = find_path(envp);
	char **cmd_paths = ft_split(paths, ':');

    char **cmd_args = ft_split("export TEST=key", ' '); //аргументы к командам
                                                        //в данном случае команда - echo, аргументы - hello world
	char *cmd = get_cmd(cmd_paths, cmd_args[0]);

    execve(cmd, cmd_args, envp);
    return (0);
}
