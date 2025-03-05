/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:15:50 by raph              #+#    #+#             */
/*   Updated: 2025/03/05 21:52:33 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_pile
{
    struct s_pile	*next;
    int				data;
	int				size;
} t_pile;

typedef struct s_info
{
	int	substract;
	int	substract_i;
	int	position;
	int	data;
	int	diff;
	int	flag;
} t_info;

int	abs(int	a)
{
	if (a < 0)
		a = -a;
	return (a);
}

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

    /*if (!(*b))
        return ;*/
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

int	is_full(t_pile	**a)
{
	t_pile	*current;
	int size = 0;

	current = *a;
    while (current)
    {
        size++;
        current = current->next;
    }
    //printf("size = %d, *a->size = %d\n", size, (*a)->size);
    if (size == (*a)->size)
    	return (1);
    return (0);
}

void print_pile(t_pile *pile, const char *pile_name)
{
    t_pile *current = pile;

    printf("Pile %s : ", pile_name);
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
//
//
//
//
//
//
//
//
//
//HELP
int	fft_sort(t_pile **pile_a, t_pile **pile_b)
{
	t_pile	*buffer = NULL;
	t_info	*info = malloc(sizeof(t_info));
	int		i;
	int		j;
	int		result;

	result = 0;
	while (1)
	{
		if(is_full(pile_a) == 1)
			break;
		info->diff = 100000;
		i = 1;
		buffer = *pile_a;
		while (buffer)
		{
			if (abs(buffer->data - (*pile_b)->data) <= abs(info->diff))
			{
				info->flag = 1;
				if (abs(buffer->data - (*pile_b)->data) == abs(info->diff))
				{
					if (info->position > (*pile_a)->size/2)
						info->substract  = (*pile_a)->size;
					else
						info->substract = (*pile_a)->size/2;
					if (i > (*pile_a)->size/2)
						info->substract_i = (*pile_a)->size;
					else
						info->substract = (*pile_a)->size/2;
					if (info->substract - info->position < info->substract_i - i)
						info->flag = 0;
				}
				if (info->flag == 1)
				{
					info->diff = buffer->data - (*pile_b)->data;
					info->data = buffer->data;
					info->position = i;
				}
			}
			i++;
			buffer = buffer->next;
		}
		j = 0;
		/*if (info->position == 1)
		{
			swap(pile_a);
			write(1, "sa\n", 3);
		}*/
		if (info->position <= i/2)
		{
			if(info->data < (*pile_b)->data)
			{
				while (j != info->position)
				{
					rotate(pile_a);
					write(1, "ra\n", 3);
					j++;
				}
			}
			else
			{
				while (j != info->position - 1)
				{
					rotate(pile_a);
					write(1, "ra\n", 3);
					j++;
				}
			}

		}
		else if (info->position > i/2)
		{
			if (info->data < (*pile_b)->data)
			{
				while (j != (i - 1) - info->position)
				{
					rrotate(pile_a);
					write(1, "rra\n", 4);
					j++;
				}
			}
			else if (info->data > (*pile_b)->data)
			{
				while (j != i - info->position)
				{
					rrotate(pile_a);
					write(1, "rra\n", 4);
					j++;
				}
			}
		}
		push(pile_a, pile_b);
		write(1, "pa\n", 3);
		result += j;
	}
	return (result);
}

int ft_list_size(t_pile *pile)
{
    int size = 0;
    t_pile *current = pile;

    while (current)
    {
        size++;
        current = current->next;
    }
    return size;
}

//////////////////
//
//
//
//
//
/////////////////// Refaire la fcontion lst_sort mais regarder pile_b et envoyer dans a que pile_a->data -1
int	ft_sort(t_pile	**a, t_pile **b)
{
	t_pile	*tmp;
    int     position;
    int     result;	

    result = 0;
    while (1)
    {

        printf("data de a : %d\n", (*a)->data);
        print_pile(*a, "pile a");
        print_pile(*b, "pile b");

        tmp = *b;
        position = 0;
        if (is_full(a) == 1)
            break ;
        while (tmp->data != (*a)->data - 1)
        {
            position++;
            tmp = tmp->next;
        }
        printf("position : %d\n", position);
        if (position == 1)
        {
            result++;
            swap(b);
            write(1, "sa\n", 3);
        }
        else if (position < ft_list_size(*b) / 2)
        {
            while ((*b)->data != (*a)->data - 1)
            {
                result++;
                rotate(b);
                write(1, "rb\n", 3);
            }
        }
        else
        {
            while((*b)->data != (*a)->data - 1)
            {
                result++;
                rrotate(b);
                write(1, "rrb\n", 4);
            }
        }

        result++;
        push(a, b);
        write(1, "pa\n", 3);
    }
    return (result);
}



t_pile	*ft_init(char **str, int size)
{
	t_pile	*pile = NULL;
	t_pile	*buffer = NULL;
	t_pile	*newElem = NULL;
	int		i;

	i = 0;
	while (i < size)
	{
		newElem = malloc(sizeof(t_pile));
		if (!newElem)
		{
			while (pile)
			{
				buffer = pile;
				pile = pile->next;
				free(buffer);
			}
			return (NULL);
		}
		newElem->data = atoi(str[i+1]);
		newElem->size = size;
		newElem->next = NULL;
		if (!pile)
		{
			pile = newElem;
			buffer = pile;
		}
		else
		{
			buffer->next = newElem;
			buffer = buffer->next;
		}
		i++;
	}
	return (pile);
}

int	is_sorted(t_pile **a)
{
	t_pile	*current;
	int		minimum;
	
	minimum = 100000;
	current = *a;
	while(current)
	{
		if (current->data < minimum)
			minimum = current->data;
		current = current->next;
	}
	current = *a;
	while (current)
	{
		if (current->data != minimum)
			return (0);
		minimum++;
		current = current->next;
	}
	return (1);
}

void	lst_sort(t_pile	**a)
{
	t_pile	*current;
	int		minimum;
	int		minimum_id;
	int		i;
	
	i = 0;
	minimum = 100000;
	current = *a;
	while(current)
	{
		if (current->data < minimum)
		{
			minimum_id = i;
			minimum = current->data;
		}
		i++;
		current = current->next;
	}
	if (minimum_id > (*a)->size/2)
	{
		while(minimum_id < (*a)->size)
		{
			rrotate(a);
			write(1, "rra\n", 4);
			minimum_id++;
		}
	}
	else
	{
		while(minimum_id > 0)
		{
			rotate(a);
			write(1, "ra\n", 3);
			minimum_id--;
		}
	}
}

int	lst_push_mini(t_pile **a, t_pile **b)
{
	t_pile	*current;
	int		minimum;
	int		minimum_id;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	minimum = 100000;
	current = *a;
	while(current)
	{
		if (current->data < minimum)
		{
			minimum_id = i;
			minimum = current->data;
		}
		i++;
		current = current->next;
	}
	current = *a;
	while (j < minimum_id)
	{
		rotate(a);
		write(1, "ra\n", 3);
		j++;
	}
	push(b, a);
	write(1, "pb\n", 3);
	j++;
	return (j);
}

int	lst_compare_top_bottom(t_pile *a, t_pile *b)
{
		t_pile	*temp;
		static int	max;

		if (!max)
			max = b->data;
		temp = b;
		while(temp->next)
			temp = temp->next;
		//printf("temp : %d\n", temp->data);
		if (max < temp->data)
			max = temp->data;
		if (abs(a->data - b->data) <= abs(a->data - temp->data))
			return (1);
		else
			return (0);

}
////
////
///
///
///
///
///
///
///
///A MODIF JSP PK CA SEGFAULT
///FAUT LLDB CETTE MERDE
int    closest_nb(t_pile *pile_a, t_pile *pile_b, int threshold)
{
    t_pile  *tmp = NULL;
    int     tmp1;
    int     tmp2;

    tmp1 = 0;
    tmp2 = 0;
    tmp = pile_a;
    while ((abs(tmp->data - threshold) > 9 || tmp->data > pile_b->data) && tmp->data != 100)
    {
        rotate(&tmp);
        tmp1++;    
    }
    tmp = pile_a;
    while ((abs(tmp->data - threshold) > 9 || tmp->data > pile_b->data) && tmp->data != 100)
    {
        rrotate(&tmp);
        tmp2++;
    }
    if (tmp1 <= tmp2)
        return (free(tmp), 1);
    else
        return (free(tmp), 0);
}

int	main(int argc, char **argv)
{
	t_pile	*pile_a;
	t_pile	*pile_b;
	int		i;
	int		threshold;
	int		j;

	threshold = 1;
	i = 0;
	pile_a = ft_init(argv, argc - 1);
	pile_b = NULL;
	if (!is_sorted(&pile_a))
	{
		i += lst_push_mini(&pile_a, &pile_b);
		while (ft_list_size(pile_a) != 1)
		{

		//printf("%d\n", threshold);	
			//printf("pile_a %d - %d pile_b\n", pile_a->data ,pile_b->data);
			if ((abs(pile_a->data - threshold) < 9 || pile_a->data < pile_b->data) && pile_a->data != 100)
			{
				//print_pile(pile_a, "pile a");
				j = 0;
				if(pile_a->data > pile_b->data)
				{
				//manque des conditions a rasjouter
					threshold++;
					push(&pile_b, &pile_a);
					write(1, "pb\n", 3);
					i++;
					//
				}
				else
				{
					//print_pile(pile_a, "pile a");
					threshold++;
					push(&pile_b, &pile_a);
					write(1, "pb\n", 3);
					rotate(&pile_b);
					write(1, "rb\n", 3);
					i += 2;
					//print_pile(pile_b, "pile b");	
				}
			}
			else if (closest_nb(pile_a, pile_b, threshold) == 1)
			{
				j++;
				rotate(&pile_a);
				write(1, "ra\n", 3);
				i++;
			}
            else
            {
                j++;
                rrotate(&pile_a);
                write(1, "rra\n", 4);
                i++;
            }
			if(j == 100)
				break;
		}
		i += ft_sort(&pile_a, &pile_b);
		//lst_sort(&pile_a);
	}
    printf("NB ACTIONS = %d\n", i);
	//print_pile(pile_a, "pile a");	
	/*printf("Tableau trie en %d etapes\n", i);
	while (pile_a)
	{
		printf("%d\n", pile_a->data);
		pile_a = pile_a->next;
	}*/

	return (0);
}


