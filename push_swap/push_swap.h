/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:33:13 by tlima-de          #+#    #+#             */
/*   Updated: 2024/06/22 15:51:19 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_lst
{
	int				content;
	int				index;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_stack;

// SIMPLE_SORT_C
int					is_sorted(t_stack **stack);
void				conditional_sort_based_on_size(t_stack **a_stack,
						t_stack **b_stack);

// SIMPLE_SORT_UTILS_C
int					is_order(t_stack **stack, int size);
void				reset_index(t_stack **stack);
void				rotate_to_min(t_stack **stack, int size);

// INDEX_C
void				index_all_elements_by_content(t_stack **stack);

// RADIX_C
int					get_stack_size(t_stack *lst);
void				radix_sort(t_stack **a_stack, t_stack **b_stack);

// LST_UTILS_C
void				lst_addfront(t_stack **stack, t_stack *news);
void				lst_addback(t_stack **stack, t_stack *news);
t_stack				*lst_new(int content);
t_stack				*lst_last(t_stack *stack);

// SWAP_C
void				sa(t_stack **stack);
void				sb(t_stack **stack);
void				ss(t_stack **a_stack, t_stack **b_stack);

// PUSH_C
void				pa(t_stack **a_stack, t_stack **b_stack);
void				pb(t_stack **a_stack, t_stack **b_stack);

// ROTATE_C
void				rotate(t_stack **stack);
void				ra(t_stack **stack);
void				rb(t_stack **stack);
void				rr(t_stack **a_stack, t_stack **b_stack);

// REVERSE_C
void				reverse(t_stack **stack);
void				rra(t_stack **stack);
void				rrb(t_stack **stack);
void				rrr(t_stack **a_stack, t_stack **b_stack);

// UTILS
int					ft_atoi(const char *str);
long				ft_atol(const char *str);
int					ft_putstr_fd(char *s, int fd);
void				free_split(char **split);
size_t				ft_strlen(const char *str);
int					is_number(char *str);
void				ps_stackclear(t_stack **stack);
int					ps_check_dup(t_stack *stack);
int					ps_initstack(int ac, char **av, t_stack **a_stack);

void				print_error_and_exit(t_stack **a_stack);

// SPLIT
char				**ft_split(char const *s, char c);

#endif