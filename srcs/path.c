/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 08:39:21 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 09:18:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		add_path(char *directory, char *path)
{
	int	len1;
	int	len2;
	int	i;

	len1 = ft_strlen(directory);
	len2 = ft_strlen(path);
	if (len1 + len2 > MAX_PATH)
		return (len1);
	if (len1 > 0 && directory[len1 - 1] != '/')
	{
		directory[len1] = '/';
		len1++;
	}
	i = 0;
	while (i < len2)
	{
		directory[len1 + i] = path[i];
		i++;
	}
	return (len1 + i);
}

int		delete_last_path(char *directory)
{
	int	len;
	int	flag;

	len = ft_strlen(directory);
	flag = 0;
	while (len > 0)
	{
		len--;
		if (directory[len] == '/' && flag)
			break ;
		directory[len] = '\0';
		flag = 1;
	}
	return (len);
}

void	set_path(char *cur_dir, char *file)
{
	int	len;
	int	i;

	len = ft_strlen(cur_dir);
	if (len > 0 && cur_dir[len - 1] != '/')
	{
		cur_dir[len] = '/';
		len++;
	}
	i = 0;
	while (file[i])
	{
		cur_dir[len] = file[i];
		i++;
		len++;
	}
	cur_dir[len] = '\0';
}

int		update_path(char *cur_dir, char *path)
{
	ft_memset(cur_dir, '\0', MAX_PATH);
	if (!path)
		return (0);
	if (ft_strlen(path) > MAX_PATH)
		return (1);
	ft_strcpy(cur_dir, path);
	return (0);
}

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
