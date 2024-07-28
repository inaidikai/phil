/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:26 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/28 22:41:24 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "phil.h"
// check the actual numbers < int max
// tiime sa,ps >60ms
static inline bool isdigit(char c)
{
	return(c>= '0' && c <= '9');
}
static inline bool isspace(char c)
{
	return((c >= 9 && c <= 13) || c == 32);
}
static const char *valid_input(const char *str)
{
	int len;
	const char *number;

	len = 0;
	while(isspace(*str))
	  str++;
	if(*str == '+')
		++str;
	if(*str == '-')
		error_Exit("pls be positive");
	if(!isdigit(*str))
		error_Exit("hey add numbers only");
	number =  str;
	while(isdigit(*str++))
		++len;
	if (len > 10)
		error_Exit("big , int max the limit");
		return(number);
	
}
static long ft_atol(const char *str)
{
	long num;
	num = 0;
	str = valid_input(str);
	while(isdigit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_Exit("num too big");
	return (num);
}
void parse(t_table *table , char **av)
{
	table->philo_number =  ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if(table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_Exit( " use time stamps moreeeeeeee");
	if(av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}