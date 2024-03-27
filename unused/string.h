/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:00:47 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/26 10:20:13 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_string
{
	char	*str;
	size_t	len;
}	t_string;

t_string	new_string(char *s, int l);

#endif