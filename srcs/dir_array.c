/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:38:00 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/02 17:57:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	processing_dir(t_options *options, t_info *list)	// file = directories
{
//	t_info		*list;
//	struct stat	about;
	int			count;

	if ((count = reading(list, options->cur_dir, options)) == 0)
		return (-1);
	return (count);
}

/*
**	processing_general	--> processing		FOR all
**	processing_dir							FOR dir in args and empty args
**	processing_files						FOR files in args
**	processing	--> processing_recursion	FOR -R
*/
