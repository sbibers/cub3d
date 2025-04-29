/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:20:16 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/08 22:57:17 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	ft_count_word(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static int	ft_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_fill_words(char **str, const char *s, char c)
{
	int	i;
	int	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			word_len = ft_word_len(s, c);
			str[i] = (char *)malloc((word_len + 1) * sizeof(char));
			if (!str[i])
			{
				while (i > 0)
					free(str[--i]);
				free(str);
				return ;
			}
			ft_strncpy(str[i], s, word_len);
			str[i][word_len] = '\0';
			i++;
			s += word_len;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_word(s, c);
	str = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!str)
	{
		return (NULL);
	}
	ft_fill_words(str, s, c);
	str[word_count] = NULL;
	return (str);
}
