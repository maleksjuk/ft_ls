/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:59:24 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 04:00:07 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	path_link(t_info *list, int i, char *file)
{
	char	*bufer;
	int		bufsize;

	list[i].mode[0] = 'l';
	bufsize = 1024;
	bufer = (char *)malloc(bufsize);
	ft_memset(bufer, '\0', bufsize);
	if (readlink(file, bufer, bufsize) > 0)
	{
		list[i].path_link = ft_strdup(bufer);
		list[i].flag_link = 1;
	}
	free(bufer);
}

int		get_list_mode(t_info *list, int i, mode_t mode)
{
	list[i].mode[0] = S_ISSOCK(mode) ? 's' :
		(S_ISLNK(mode) ? 'l' :
		(S_ISBLK(mode) ? 'b' :
		(S_ISDIR(mode) ? 'd' :
		(S_ISCHR(mode) ? 'c' :
		(S_ISFIFO(mode) ? 'p' :
		'-')))));
	list[i].mode[11] = '\0';
	list[i].mode[1] = mode & S_IRUSR ? 'r' : '-';
	list[i].mode[2] = mode & S_IWUSR ? 'w' : '-';
	list[i].mode[3] = (mode & S_ISUID) && (mode & S_IXUSR) ? 's' :
		(mode & S_ISUID ? 'S' : (mode & S_IXUSR ? 'x' : '-'));
	list[i].mode[4] = mode & S_IRGRP ? 'r' : '-';
	list[i].mode[5] = mode & S_IWGRP ? 'w' : '-';
	list[i].mode[6] = (mode & S_ISGID) && (mode & S_IXGRP) ? 's' :
		(mode & S_ISGID ? 'S' : (mode & S_IXGRP ? 'x' : '-'));
	list[i].mode[7] = mode & S_IROTH ? 'r' : '-';
	list[i].mode[8] = mode & S_IWOTH ? 'w' : '-';
	list[i].mode[9] = (mode & S_ISVTX) && (mode & S_IXOTH) ? 't' :
		(mode & S_ISVTX ? 'T' : (mode & S_IXOTH ? 'x' : '-'));
	list[i].mode[10] = ' ';
	return (0);
}

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
		{
			ft_printf("GLP ");	// DELETE
			return (error_message(file, (errno == EACCES) ? 0 : FULL_EXIT));
		}
		get_all_params(list, i, &about_file, NULL);
	}
	return (0);
}
