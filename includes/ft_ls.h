/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:40 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/17 17:57:02 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/includes/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>

typedef struct	s_options
{
	int		list;
	int		recursive;
	int		all;
	int		reverse;
	int		time_order;
	/*
	**	служебные переменные
	*/	
	char	illegal;
	char	**dir_array;
	int		flag;
}				t_options;

typedef struct	s_recursive
{
	char	*address;
	t_list	*next;
}				t_recursive;

/*
**	options.c
*/
void	init_options(t_options *options, int ac);
int		input_options(t_options *options, char *params);

/*
**	ft_ls.c
*/
int		ft_ls(t_options *options, int num);

#endif