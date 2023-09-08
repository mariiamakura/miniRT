/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:44:29 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/08 17:01:23 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) + 1;
	dst = (char *) malloc(j);
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* int main()
{
    char *str = "Hello, world!";
    char *copy = strdup(str);
	char *mycopy = ft_strdup(str);

    printf("Original string: %s\n", str);
    printf("Copy of string: %s\n", copy);int main()
{
    char *str = "Hello, world!";
    char *copy = strdup(str);
	char *mycopy = ft_strdup(str);

    printf("Original string: %s\n", str);
    printf("Copy of string: %s\n", copy);
	printf("Mycopy of string: %s\n", mycopy);

    free(copy);
	free(mycopy);

    return 0;
}

	printf("Mycopy of string: %s\n", mycopy);

    free(copy);
	free(mycopy);

    return 0;
}
 */