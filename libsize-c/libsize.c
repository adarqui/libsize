#include "libsize.h"

int isPlural(double m) {
	unsigned long long n;
	double o;
	n = (unsigned long long) m;
	o = m - (double)n;
	if (n == 1 && o == 0) {
		return 0;
	}
	return 1;
}



double xpow(double m, int n) {
	double r;
	int i;

	if(n == 0) return (double) 1;
	if(n == 1) return (double) m;

	r = m;
	for(i = 1; i < n; i++) {
		r = r * m;
	}

	return r;
}



void lsize_new(lsize_t *lsz) {
	memset(lsz, 0, sizeof(lsize_t));
	lsize_use_bytes(lsz);
	lsz->precision = 2;
	lsize_set_opt(lsz, LSIZE_OPT_ABBRV);
	return;
}



void lsize_use_bits(lsize_t *lsz) {
	lsz->type = LSIZE_TYPE_BITS;
	return;
}



void lsize_use_bytes(lsize_t *lsz) {
	lsz->type = LSIZE_TYPE_BYTES;
	return;
}



void lsize_set_type(lsize_t *lsz, LSIZE_TYPE type) {
	lsz->type = type;
	return;
}



void lsize_set_value(lsize_t *lsz, LSIZE_VALUE value) {
	lsz->val = value;
	return;
}


void lsize_set_precision(lsize_t *lsz, LSIZE_PRECISION precision) {
	lsz->precision = precision;
	return;
}



void lsize_set_opt(lsize_t *lsz, LSIZE_OPT opt) {
	lsz->opts |= opt;
	return;
}



void lsize_unset_opt(lsize_t *lsz, LSIZE_OPT opt) {
	lsz->opts &= ~opt;
	return;
}



LSIZE_SIZE lsize_guess_size(lsize_t *lsz) {
	double tres;
	LSIZE_TYPE j;
	
	for(j=(LSIZE_SIZE_MAX-1); j > LSIZE_SIZE_B; j--) {
		tres = xpow(lsize_get_conv(lsz), j);
		if(lsz->val >= tres) {
			return j;
		}
	}

	return LSIZE_SIZE_B;
}



void lsize_dump(lsize_t *lsz) {
	lsize_element_t *lsze;
	int i;

	for(i = 0; i < LSIZE_SIZE_MAX; i++) {
		lsze = &lsz->elements[i];
		if(lsze->tog == LSIZE_TOGGLE_ON) {
			lsize_dump_element(lsze);
		}
	}

	return;
}



void lsize_dump_element(lsize_element_t *lsze) {
	printf("size=%i, str=%s, val=%f, div=%f, result=%f\n",
		lsze->size, lsze->str, lsze->val, lsze->div, lsze->result);
}


int lsize_get_conv(lsize_t *lsz) {
	return (lsz->type == LSIZE_TYPE_BITS ? 1000 : 1024);
}



void lsize_get_all(lsize_t *lsz) {
	int j;

	for(j=0; j < LSIZE_SIZE_MAX; j++) {
		lsize_get_one(lsz, j);
	}

	return;
}



void lsize_get_one(lsize_t *lsz, LSIZE_SIZE size) {
	lsize_element_t *lsze;
	

	lsze = &lsz->elements[size];
	lsze->tog = LSIZE_TOGGLE_ON;
	lsze->size = size;
	lsze->val = lsz->val;
	lsze->div = xpow(lsize_get_conv(lsz), size);
	lsze->result = lsze->val / lsze->div;

	if(lsz->opts & LSIZE_OPT_WHOLE) {
		lsze->str = LSIZE_TABLE[size].whole[lsz->type];
		if(lsz->opts & LSIZE_OPT_PLURAL && isPlural(lsze->result)) {
			lsze->str = LSIZE_TABLE[size].wholep[lsz->type];
		}
	} else {
		lsze->str = LSIZE_TABLE[size].abbrv[lsz->type];
	}

	return;
}



lsize_element_t lsize_guess(lsize_t *lsz) {
	LSIZE_SIZE size;

	size = lsize_guess_size(lsz);
	lsize_get_one(lsz, size);

	return lsz->elements[size];
}



char * lsize_format(lsize_t *lsz) {
	static char buf[132];
	return lsize_format_bytes(lsz, buf, sizeof(buf)-1);
}



char * lsize_format_ptr(lsize_t *lsz, char * buf, int n) {
	return lsize_format_bytes(lsz, buf, n);
}



char * lsize_format_bytes(lsize_t *lsz, char * buf, int n) {
	lsize_element_t lsze;
	char fmtstr[132];

	lsze = lsize_guess(lsz);
	snprintf(fmtstr, sizeof(fmtstr)-1, "%%.%.2df %%s", lsz->precision);
	snprintf(buf, n, fmtstr, lsze.result, lsze.str);
	return buf;
}
