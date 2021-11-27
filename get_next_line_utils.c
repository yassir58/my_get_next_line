
#include "get_next_line.h"



size_t ft_strlen(char const *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char *ft_strdup(const char *str)
{
	int len;
	char *new_str;
	int i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}
char *ft_strjoin(char *s1, char *s2)
{
	int len1;
	int len2;
	char *str;
	int i;
	int j ;

	str = NULL;
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	//else if (!s1 && s2)
	//	s1 = ft_strdup("");

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	free(s2);
	return (str);
}

char *ft_strchr(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return(str + i);
	return (NULL);
}