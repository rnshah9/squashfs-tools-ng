/* SPDX-License-Identifier: GPL-3.0-or-later */
#ifndef MKFS_H
#define MKFS_H

#include "meta_writer.h"
#include "highlevel.h"
#include "squashfs.h"
#include "compress.h"
#include "id_table.h"
#include "fstree.h"
#include "config.h"

#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

typedef struct {
	unsigned int def_uid;
	unsigned int def_gid;
	unsigned int def_mode;
	unsigned int def_mtime;
	int outmode;
	int compressor;
	int blksz;
	int devblksz;
	bool quiet;
	const char *infile;
	const char *packdir;
	const char *outfile;
	const char *selinux;
	char *comp_extra;
} options_t;

typedef struct data_writer_t data_writer_t;

typedef struct {
	int outfd;
	options_t opt;
	sqfs_super_t super;
	fstree_t fs;

	id_table_t idtbl;

	compressor_t *cmp;
} sqfs_info_t;

void process_command_line(options_t *opt, int argc, char **argv);

int write_xattr(sqfs_info_t *info);

data_writer_t *data_writer_create(sqfs_super_t *super, compressor_t *cmp,
				  int outfd);

void data_writer_destroy(data_writer_t *data);

int data_writer_write_fragment_table(data_writer_t *data);

int write_data_from_fd(data_writer_t *data, file_info_t *fi, int infd);

int data_writer_flush_fragments(data_writer_t *data);

int write_data_to_image(data_writer_t *data, sqfs_info_t *info);

#endif /* MKFS_H */
