/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * difftool.h
 *
 * Copyright (C) 2019 David Oberhollenzer <goliath@infraroot.at>
 */
#ifndef DIFFTOOL_H
#define DIFFTOOL_H

#include "config.h"

#include "highlevel.h"
#include "fstree.h"
#include "util.h"

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_WINDOW_SIZE (1024 * 1024 * 4)

extern const char *first_path;
extern const char *second_path;
extern int compare_flags;
extern sqfs_reader_t sqfs_a;
extern sqfs_reader_t sqfs_b;

enum {
	COMPARE_NO_PERM = 0x01,
	COMPARE_NO_OWNER = 0x02,
};

int compare_dir_entries(tree_node_t *a, tree_node_t *b);

char *node_path(tree_node_t *n);

int compare_files(file_info_t *a, file_info_t *b, const char *path);

int node_compare(tree_node_t *a, tree_node_t *b);

#endif /* DIFFTOOL_H */