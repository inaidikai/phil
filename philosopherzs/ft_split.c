/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:01:54 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/26 14:01:54 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char    **ft_split(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **s =  malloc(1024);
    while(str[i] == ' ' || str[i] == '\t')
            i++;
    while(str[i])
    {
        if(str[i] > 32)
        {
            k = 0;
            s[j] = malloc(1024);
            while (str[i] > 32)
            {
                s[j][k++] = str[i++];
            }
            s[j][k] = '\0';
            j++;
        }
        else
            i++;
    }
    s[j] = 0;
    return (s);
}
