/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 08:34:47 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 08:35:06 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_list_mode_type(t_info *list, int i, mode_t mode)
{
	list[i].mode[0] = S_ISSOCK(mode) ? 's' : list[i].mode[0];
	list[i].mode[0] = S_ISLNK(mode) ? 'l' : list[i].mode[0];
	list[i].mode[0] = S_ISBLK(mode) ? 'b' : list[i].mode[0];
	list[i].mode[0] = S_ISDIR(mode) ? 'd' : list[i].mode[0];
	list[i].mode[0] = S_ISCHR(mode) ? 'c' : list[i].mode[0];
	list[i].mode[0] = S_ISFIFO(mode) ? 'p' : list[i].mode[0];
	if (list[i].mode[0] == '\0')
		list[i].mode[0] = '-';
}

void	get_list_mode_user(t_info *list, int i, mode_t mode)
{
	list[i].mode[1] = mode & S_IRUSR ? 'r' : '-';
	list[i].mode[2] = mode & S_IWUSR ? 'w' : '-';
	if ((mode & S_ISUID) && (mode & S_IXUSR))
		list[i].mode[3] = 's';
	else if (mode & S_ISUID)
		list[i].mode[3] = 'S';
	else
		list[i].mode[3] = mode & S_IXUSR ? 'x' : '-';
}

void	get_list_mode_group(t_info *list, int i, mode_t mode)
{
	list[i].mode[4] = mode & S_IRGRP ? 'r' : '-';
	list[i].mode[5] = mode & S_IWGRP ? 'w' : '-';
	if ((mode & S_ISGID) && (mode & S_IXGRP))
		list[i].mode[6] = 's';
	else if (mode & S_ISGID)
		list[i].mode[6] = 'S';
	else
		list[i].mode[6] = mode & S_IXGRP ? 'x' : '-';
}

void	get_list_mode_other(t_info *list, int i, mode_t mode)
{
	list[i].mode[7] = mode & S_IROTH ? 'r' : '-';
	list[i].mode[8] = mode & S_IWOTH ? 'w' : '-';
	if ((mode & S_ISVTX) && (mode & S_IXOTH))
		list[i].mode[9] = 't';
	else if (mode & S_ISVTX)
		list[i].mode[9] = 'T';
	else
		list[i].mode[9] = mode & S_IXOTH ? 'x' : '-';
}

void	get_list_mode(t_info *list, int i, mode_t mode)
{
	get_list_mode_type(list, i, mode);
	get_list_mode_user(list, i, mode);
	get_list_mode_group(list, i, mode);
	get_list_mode_other(list, i, mode);
	list[i].mode[10] = ' ';
}
