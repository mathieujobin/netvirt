/*
 * NetVirt - Network Virtualization Platform
 * Copyright (C) 2009-2016
 * Nicolas J. Bouliane <admin@netvirt.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ippool.h"

static int
get_bit(const uint8_t bitmap[], size_t bit)
{
	return (bitmap[bit/8] >> (bit % 8)) & 1;
}

static void
set_bit(uint8_t bitmap[], size_t bit)
{
	bitmap[bit/8] |= (1 << (bit % 8));
}

static void
reset_bit(uint8_t bitmap[], size_t bit)
{
	bitmap[bit/8] &= ~(1 << (bit % 8));
}

static int
alloc_bitmap(size_t bits, uint8_t **bitmap)
{
	int byte_size = (bits+7)/8;

	*bitmap = calloc(byte_size, sizeof(uint8_t));
	return *bitmap != 0;
}

static int
allocate_bit(uint8_t bitmap[], size_t bits, uint32_t *bit)
{
	int i, j, byte_size;

	byte_size = (bits+7)/8;

	/* byte */
	for (i = 0; (i < byte_size) && (bitmap[i] == 0xff); i++);
	if (i == byte_size) {
		return 0;
	}

	/* bit */
	for (j = 0; get_bit( bitmap+i, j); j++);

	*bit = i * 8 + j;

	if (*bit > bits) {
		return 0;
	}

	set_bit(bitmap, *bit);

	return 1;
}

static int
free_bit(uint8_t bitmap[], size_t bits, size_t bit)
{
	if (bit <= bits) {
		reset_bit(bitmap, bit);
		return 1;
	}
	return 0;
}

static int
ipcalc(struct ippool *ippool, char *address, char *netmask)
{
	struct in_addr mask;

	if (inet_pton(AF_INET, "255.255.255.255", &mask) != 1) {
		return -1;
	}
	if (inet_pton(AF_INET, address, &ippool->address) != 1) {
		return -1;
	}
	if (inet_pton(AF_INET, netmask, &ippool->netmask) != 1) {
		return -1;
	}

	ippool->hosts = ntohl(mask.s_addr - ippool->netmask.s_addr);
	/* Remove network and broadcast address. */
	ippool->hosts -= 2;
	ippool->hostmax.s_addr = (ippool->address.s_addr | ~ippool->netmask.s_addr) - htonl(1);
	ippool->hostmin.s_addr = ippool->hostmax.s_addr - htonl(ippool->hosts);

	return 0;
}

char *
ippool_get_ip(struct ippool *ippool)
{
	struct in_addr new_addr;
	uint32_t bit = 0;
	int ret = 0;

	ret = allocate_bit(ippool->pool, ippool->hosts, &bit);
	if (ret == 0) { /* IP pool is depleeted. */
		return NULL;
	}

	new_addr = ippool->hostmin;
	new_addr.s_addr = htonl((ntohl(new_addr.s_addr) + bit));

	return inet_ntoa(new_addr);
}

void
ippool_release_ip(struct ippool *ippool, char *ip)
{
	int bit = 0;
	struct in_addr addr;

	if (inet_aton(ip, &addr) == 0) {
		/* The address is not valid. */
		return;
	}
	bit = ntohl(addr.s_addr) - ntohl(ippool->hostmin.s_addr);
	free_bit(ippool->pool, ippool->hosts, bit);
}

struct ippool *
ippool_new(char *address, char *netmask)
{
	struct ippool *ippool;

	ippool = malloc(sizeof(struct ippool));
	if (ipcalc(ippool, address, netmask) != 0) {
		return NULL;
	}
	alloc_bitmap(ippool->hosts, &(ippool->pool));

	return ippool;
}

void
ippool_free(struct ippool *ippool)
{
	if (ippool == NULL)
		return;

	free(ippool->pool);
	free(ippool);
}
