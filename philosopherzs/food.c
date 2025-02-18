/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:01:48 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/26 14:01:48 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "phil.h"

void thinking(t_philo *philo)
{
      write_status(THINKING, philo, DEBUG_MODE);
}

void *lone_philo(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    wait_all_thread(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
    increase_long(&philo->table->table_mutex, &philo->table->threads_run_nbr);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE );
    while(!simul_finished(philo->table))
        usleep(200);
    return(NULL);
}
static void eat(t_philo *philo)
{
    safe_mutex(&philo->one_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex(&philo->one_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);

    set_long(&philo->philo_mutex,&philo->last_meal,gettime(MILLISECOND));
    philo->meals_c++;
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat, philo->table);
    if(philo->table->limit_meals > 0
    && philo->meals_c == philo->table->limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    safe_mutex(&philo->one_fork->fork, UNLOCK);
    safe_mutex(&philo->two_fork->fork, UNLOCK);  
}

void *dinner_sim(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;
    wait_all_thread(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
    increase_long(&philo->table->table_mutex,
        &philo->table->threads_run_nbr);
    while(!simul_finished(philo->table))
    {
        if(philo->full)
            break;
        eat(philo);

        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        thinking(philo);
    }
    return NULL;
}
void start(t_table *table)
{
    int i = 0;
    if(table->limit_meals == 0)
        return;
    else if (table->philo_number == 1)
        safe_thread(&table->philo[0].thread_id, lone_philo, &table->philo[0],CREATE);
    else
    {
        while(i < table->philo_number)
        {
            safe_thread(&table->philo[i].thread_id, dinner_sim, &table->philo[i],CREATE);

        }
    }
    safe_thread(&table->monitor, monitor_dine, table, CREATE);
    table->start_sim = gettime(MILLISECOND);

    set_bool(&table->table_mutex, &table->all_threads_ready_syn, true);
    i = -1;
    while(++i < table->philo_number)
        safe_thread(&table->philo[i].thread_id, NULL, NULL, JOIN);
    set_bool(&table->table_mutex, &table->end_sim, true);
    safe_thread(&table->monitor, NULL, NULL,JOIN);
}