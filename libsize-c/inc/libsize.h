#ifndef LIBSIZE_H
#define LIBSIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types.h"

enum LSIZE_TOGGLE {
	LSIZE_TOGGLE_OFF,
	LSIZE_TOGGLE_ON
};



enum LSIZE_TYPE {
	LSIZE_TYPE_BYTES,
	LSIZE_TYPE_BITS
};



enum LSIZE_OPTS {
	LSIZE_OPT_NO = 0x00,
	LSIZE_OPT_BYTES = 0x01,
	LSIZE_OPT_ABBRV = 0x02,
	LSIZE_OPT_WHOLE = 0x04,
	LSIZE_OPT_PLURAL = 0x08
};



enum LSIZE_SIZE {
	LSIZE_SIZE_B = 0,
	LSIZE_SIZE_KB = 1,
	LSIZE_SIZE_MB = 2,
	LSIZE_SIZE_GB = 3,
	LSIZE_SIZE_TB = 4,
	LSIZE_SIZE_PB = 5,
	LSIZE_SIZE_EB = 6,
	LSIZE_SIZE_ZB = 7,
	LSIZE_SIZE_YB = 8,
	LSIZE_SIZE_MAX = 9
};



typedef unsigned char LSIZE_TOGGLE;
typedef unsigned char LSIZE_TYPE;
typedef unsigned char LSIZE_SIZE;
typedef unsigned char LSIZE_PRECISION;
typedef unsigned int LSIZE_OPT;
typedef char * LSIZE_STR;
typedef double LSIZE_VALUE;




typedef struct lsize_table {
	LSIZE_SIZE size;
	LSIZE_STR abbrv[2];
	LSIZE_STR whole[2];
	LSIZE_STR wholep[2];
} lsize_table_t;



static lsize_table_t LSIZE_TABLE[LSIZE_SIZE_MAX+1] = {
	{ LSIZE_SIZE_B , { "B"  , "b" }, { "Byte", "Bytes" }, { "bit", "bits" } },
	{ LSIZE_SIZE_KB, { "KB" , "Kb"}, { "Kilobyte", "Kilobit" }, { "Kilobytes", "Kilobits" } },
	{ LSIZE_SIZE_MB, { "MB", "Mb" }, { "Megabyte", "Megabit" }, { "Megabytes", "Megabits" } },
	{ LSIZE_SIZE_GB, { "GB", "Gb" }, { "Gigabyte", "Gigabit" }, { "Gigabytes", "Gigabits" } },
	{ LSIZE_SIZE_TB, { "TB", "Tb" }, { "Terabyte", "Terabit" }, { "Terabytes", "Terabits" } },
	{ LSIZE_SIZE_PB, { "PB", "Pb" }, { "Petabyte", "Petabit" }, { "Petabytes", "Petabits" } },
	{ LSIZE_SIZE_EB, { "EB", "Eb" }, { "Exabyte", "Exabit" }, { "Exabytes", "Exabits" } },
	{ LSIZE_SIZE_ZB, { "ZB", "Zb" }, { "Zettabyte", "Zettabit" }, { "Zettabytes", "Zettabits" } },
	{ LSIZE_SIZE_YB, { "YB", "Yb" }, { "Yottabyte", "Yottabit" }, { "Yottabytes", "Yottabits" } },
	{ LSIZE_SIZE_MAX, { NULL, NULL }, { NULL, NULL }, { NULL, NULL } }
};



typedef struct lib_size_element {
	LSIZE_TOGGLE tog;
	LSIZE_SIZE size;
	LSIZE_STR str;
	LSIZE_VALUE val;
	LSIZE_VALUE div;
	LSIZE_VALUE result;
} lsize_element_t;



typedef struct lib_size {
	LSIZE_TYPE type;
	LSIZE_OPT opts;
	LSIZE_PRECISION precision;
	LSIZE_VALUE val;
	lsize_element_t elements[LSIZE_SIZE_MAX+1];
} lsize_t;


double xpow(double, int);


char * lsize_format(lsize_t *);
char * lsize_format_ptr(lsize_t *, char *, int);
char * lsize_format_bytes(lsize_t *, char *, int);



void lsize_new(lsize_t *);
void lsize_use_bits(lsize_t *);
void lsize_use_bytes(lsize_t *);
void lsize_set_type(lsize_t *, LSIZE_TYPE);
void lsize_set_value(lsize_t *, LSIZE_VALUE);
void lsize_set_precision(lsize_t *, LSIZE_PRECISION);
void lsize_set_opt(lsize_t *, LSIZE_OPT);
void lsize_unset_opt(lsize_t *, LSIZE_OPT);
void lsize_dump(lsize_t *);
void lsize_dump_element(lsize_element_t *);
LSIZE_SIZE lsize_guess_size(lsize_t *);
int lsize_get_conv(lsize_t *);



void lsize_get(lsize_t *);
void lsize_get_all(lsize_t *);
void lsize_get_one(lsize_t *, LSIZE_SIZE);
lsize_element_t lsize_guess(lsize_t *);

#endif
