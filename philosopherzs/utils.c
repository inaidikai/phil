/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:52 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/26 14:02:52 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "phil.h"

long gettime(t_time_code time_code)
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL))
        error_Exit("gettime failed");
    if(SECOND == time_code)
        return(tv.tv_sec + (tv.tv_usec/1e6));
    else if(MILLISECOND == time_code)
        return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if(MICROSECOND == time_code)
        return((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_Exit("wrong input to gettime");
    return(1337);
}
void precise_usleep(long usec, t_table *table)
{
    long start;
    long elas;
    long rem;

    start = gettime(MICROSECOND);
    while(gettime(MICROSECOND) - start < usec)
    {
        if(simul_finished(table))
            break;
        elas = gettime(MICROSECOND) - start;
        rem = usec - elas;
        if(rem>1e3)
            usleep(rem/2);
        else
            {
                while(gettime(MICROSECOND) - start < usec)
                    ;
            }

    }
}
void clean(t_table *table)
{
    t_philo *philo;
    int i;
     i = -1;
     while(++i < table->philo_number)
     {
        philo = table->philo+i;
        safe_mutex(&philo->philo_mutex, DESTROY);
     }
     safe_mutex(&table->write_mutex, DESTROY);
     safe_mutex(&table->table_mutex, DESTROY);
     free(table->forks);
     free(table->philo);
}

void error_Exit(const char *error)
{
 printf(R"%s\n"RE, error);
 exit(EXIT_FAILURE);  
}