/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:50 by raph              #+#    #+#             */
/*   Updated: 2025/02/18 19:34:27 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  <stdlib.h>

typedef struct s_pile
{
    struct s_pile *next;
    int           data;
} t_pile;


void swap(t_pile **a)
{
    t_pile  *tmp;

    if (!(*a) || !((*a)->next))
        return ;
    tmp = (*a)->next;
    (*a)->next = tmp->next;
    tmp->next = *a;
    *a = tmp;
}

void  push(t_pile **a, t_pile **b)
{
    t_pile  *tmp;

    if (!(*b))
        return ;
    tmp = *b;
    *b = (*b)->next;
    tmp->next = *a;
    *a = tmp;
}

void  rotate(t_pile **a)
{
    t_pile  *tmp;
    t_pile  *current;

    if (!(*a))
        return ;
    tmp = *a;
    *a = (*a)->next;
    current = *a;
    while (current->next)
        current = current->next;
    current->next = tmp;
    tmp->next = NULL;
}

void  rrotate(t_pile **a)
{
    t_pile  *tmp;
    t_pile  *current;

    if (!(*a))
        return ;
    current = *a;
    while (current->next->next)
        current = current->next;
    tmp = current->next;
    current->next = NULL;
    tmp->next = *a;
    *a = tmp;
}
