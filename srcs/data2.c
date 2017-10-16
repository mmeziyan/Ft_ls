/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:53:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/09/24 19:53:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void acl(t_flst *new)
{
    acl_t acl;
    acl_entry_t entry;
	long int x;

    new->right[10] = '\0';
    x = 0;
    acl = NULL;
    new->right[9] = ' ';
    acl = acl_get_link_np(new->path, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
        return ;
    x = listxattr(new->path, NULL, 0, XATTR_NOFOLLOW);
    if (x > 0)
        new->right[9] = '@';
    else if (acl)
        new->right[9] = '+';
}