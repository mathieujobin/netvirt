/*
 * NetVirt - Network Virtualization Platform
 * Copyright (C) 2009-2017 Mind4Networks inc.
 * Nicolas J. Bouliane <nib@m4nt.com>
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

#ifndef REQUEST_H
#define REQUEST_H

#include <jansson.h>
#include "ctrler.h"

int client_create(char *);
int client_activate(char *);
int client_get_newapikey(char *, char **);
int client_get_newresetkey(char *, char **); 
int client_reset_password(char *);
int client_delete(const char *, const char *);

int network_create(char *, const char *);
int network_delete(const char *, const char *);
int network_list(const char *, char **);

int node_create(const char *, const char *);
int node_delete(const char *, const char *);
int node_list(const char *, const char *, char **);

int provisioning(const char *, char **);



void update_node_status(struct session_info **, json_t *);
void listall_network(struct session_info **, json_t *);
void listall_node(struct session_info **, json_t *);

void reset_account_password(struct session_info *, json_t *);

#endif
