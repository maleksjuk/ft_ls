/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:59:24 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 10:50:07 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*set_format_date(char *date, long time_digit)
{
	int		i;
	int		j;
	long	cur_time;
	char	*new_date;

	i = -1;
	while (i++ < 6)
		date[i] = date[4 + i];
	cur_time = time(NULL);
	j = 0;
	if (cur_time - time_digit < SEMI_YEAR)
		while (j < 5)
			date[i++] = date[11 + j++];
	else
	{
		date[i++] = ' ';
		while (j < 4)
			date[i++] = date[20 + j++];
	}
	date[i] = '\0';
	new_date = ft_strdup(date);
	return (new_date);
}

int		get_list_time(t_info *list, int i, struct stat about_file)
{
	char	*tmp;

	list[i].time_modif_digit = about_file.st_mtimespec.tv_sec;
	tmp = ft_strdup(ctime(&about_file.st_mtimespec.tv_sec));
	list[i].time_modif = set_format_date(tmp, list[i].time_modif_digit);
	free(tmp);
	list[i].time_active_digit = about_file.st_atimespec.tv_sec;
	tmp = ft_strdup(ctime(&about_file.st_atimespec.tv_sec));
	list[i].time_active = set_format_date(tmp, list[i].time_active_digit);
	free(tmp);
	list[i].time_create_digit = about_file.st_ctimespec.tv_sec;
	tmp = ft_strdup(ctime(&about_file.st_ctimespec.tv_sec));
	list[i].time_create = set_format_date(tmp, list[i].time_create_digit);
	free(tmp);
	return (0);
}

int		get_user_and_group(t_info *list, int i, struct stat *about)
{
	struct passwd	*uid;
	struct group	*gid;

	if (!(uid = getpwuid(about->st_uid)))
		return (error_message("UID", 0));
	list[i].user = ft_strdup(uid->pw_name);
	if (!(gid = getgrgid(about->st_gid)))
		return (error_message("GID", 0));
	list[i].group = ft_strdup(gid->gr_name);
	return (0);
}

int		get_all_params(t_info *list, int i, struct stat *about, char *file)
{
	get_list_time(list, i, *about);
	if (!(list[i].full_params))
		return (0);
	get_list_mode(list, i, about->st_mode);
	get_user_and_group(list, i, about);
	if (list[i].mode[0] == 'c' || list[i].mode[0] == 'b')
	{
		list[i].size = -1;
		list[i].major_num = major(about->st_rdev);
		list[i].minor_num = minor(about->st_rdev);
	}
	else
		list[i].size = (intmax_t)about->st_size;
	list[i].nlink = (int)about->st_nlink;
	list[i].flag_link = 0;
	if (file)
		path_link(list, i, file);
	list[i].total = (intmax_t)about->st_blocks;
	return (0);
}

int		get_list_params(char *file, t_info *list, int i)
{
	struct stat	about_file;
	struct stat	about_link;

	lstat(file, &about_link);
	if (S_ISLNK(about_link.st_mode))
		get_all_params(list, i, &about_link, file);
	else
	{
		if (stat(file, &about_file))
			return (error_message(file, (errno == EACCES) ? 0 : FULL_EXIT));
		get_all_params(list, i, &about_file, NULL);
	}
	return (0);
}
