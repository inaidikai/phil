/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:33 by inkahar           #+#    #+#             */
/*   Updated: 2024/07/26 14:02:33 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "phil.h"
void *safe(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
        if(NULL == ret)
            error_Exit("error with malloc");
        return(ret);
}
static void handle_mutex_error(int status, t_opcode opcode)
{
    if(0 == status)
        return ;
    if(EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
        error_Exit("the value specified by mutex is invalid ");
    else if(EINVAL == status  && INIT == opcode)
        error_Exit("the value specified is ninvalid");
    else if(EDEADLK == status)
        error_Exit("deadlock would occur if thread blocked waiting for mutex");
    else if (EPERM == status)
        error_Exit("THE current thread does not hold a lock on mutex");
    else if(ENOMEM == status)
        error_Exit("the process cannot allocate enough memory");
    else if (EBUSY == status)
        error_Exit("mutex is locked");
}
void safe_mutex(t_mtx *mutex, t_opcode opceode)
{
    if(LOCK == opceode)
        handle_mutex_error(pthread_mutex_lock(mutex), opceode);
    else if(UNLOCK == opceode)
        handle_mutex_error(pthread_mutex_unlock(mutex), opceode);
    else if(INIT == opceode)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), opceode);
    else if(DESTROY == opceode)
        handle_mutex_error(pthread_mutex_destroy(mutex), opceode);
    else
        error_Exit("wrong opcode for mutex");
}
static void handle_thread_error(int status , t_opcode code)
{
    if (0 == status)
        return ;
    if(EAGAIN == status)
        error_Exit("NO resources to create another tthread");
    else if(EPERM == status && CREATE == code)
        error_Exit("the caller does not have appropriate permission");
    else if (EINVAL == status && (JOIN == code || DETACH == code))
        error_Exit("value by attr invallid");
    else if(EINVAL == status)
        error_Exit("value by thread injoinable");
    else if (ESRCH == status)
        error_Exit("no thread to be found");
    else if(EDEADLK == status)
        error_Exit("deadlock detected");
}
void safe_thread(pthread_t *thread, void*(*foo)(void *), void *data , t_opcode code)
{
    if(CREATE == code)
        handle_thread_error(pthread_create(thread, NULL, foo, data), code);
    else if(JOIN == code)
        handle_thread_error(pthread_join(*thread, NULL), code);
    else if(DETACH == code)
        handle_thread_error(pthread_detach(*thread), code);
    else
        error_Exit("wrong code for thread handle: use <create><join><detach>");
}