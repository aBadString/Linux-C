#ifndef PERM_IN_H
#define PERM_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STR_SIZE 64

int Change();
int Look();
static int getPermission(mode_t mode,char strPerm[]);

#endif
