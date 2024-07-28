/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:12 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/26 14:02:12 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "phil.h"
int main(int argc, char **argv)
{
    t_table table;
    if (5 == argc || 6 == argc)
    {
        parse(&table, argv);
        dataq_inti(&table);
        start(&table);
        clean(&table); // philo loop or died
    }
    else
    {
        error_Exit("wrong output:");
    }
    
}