/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Management Component Transport Protocol (MCTP) - device
 * definitions.
 *
 * Copyright (c) 2021 Code Construct
 * Copyright (c) 2021 Google
 */

#ifndef __NET_MCTPDEVICE_H
#define __NET_MCTPDEVICE_H

#include <linux/list.h>
#include <linux/types.h>
#include <linux/refcount.h>

struct mctp_dev {
	struct net_device	*dev;

	refcount_t		refs;

	unsigned int		net;

	/* Only modified under RTNL. Reads have addrs_lock held */
	u8			*addrs;
	size_t			num_addrs;
	spinlock_t		addrs_lock;

	struct rcu_head		rcu;
};

#define MCTP_INITIAL_DEFAULT_NET	1

struct mctp_dev *mctp_dev_get_rtnl(const struct net_device *dev);
struct mctp_dev *__mctp_dev_get(const struct net_device *dev);

void mctp_dev_hold(struct mctp_dev *mdev);
void mctp_dev_put(struct mctp_dev *mdev);

#endif /* __NET_MCTPDEVICE_H */
