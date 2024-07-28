/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:38 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/26 14:02:38 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "phil.h"
void wait_all_thread(t_table *table)
{
    while(!get_bool(&table->table_mutex, &table->all_threads_ready_syn))
    ;
}
bool all_threads_runnig(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool ret;
    ret = false;
    safe_mutex(mutex, LOCK);
    if(*threads ==  philo_nbr)
        ret = true;
    safe_mutex(mutex, UNLOCK);
    return(ret);
}
void increase_long(t_mtx *mutex, long *value)
{
    safe_mutex(mutex, LOCK);
    (*value)++;
    safe_mutex(mutex, UNLOCK);
}