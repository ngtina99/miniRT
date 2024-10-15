/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:49:52 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/15 14:12:33 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to add any form (cylinder, plane, sphere) to the array
void add_form(void **array, int *count, int *capacity, void *new_form, size_t form_size) {
    // Check if we need to initialize or expand the array
    if (*count == 0) {
        *capacity = INITIAL_CAPACITY;
        *array = malloc(form_size * (*capacity));
        if (!*array) {
            printf("Error: Memory allocation failed for array.\n");
            exit(1);
        }
    } else if (*count == *capacity) {
        void *new_array = malloc(form_size * (*capacity) * 2);
        if (!new_array) {
            printf("Error: Memory allocation failed when expanding array.\n");
            exit(1);
        }
        
        int i = 0;
        while (i < *count) {
            ft_memcpy((char*)new_array + i * form_size, (char*)(*array) + i * form_size, form_size);
            i++;
        }
        
        free(*array);
        *array = new_array;
        *capacity *= 2;
    }

    // Copy the new form into the array
    ft_memcpy((char*)(*array) + (*count) * form_size, new_form, form_size);
    (*count)++;
}


//parse_rt function