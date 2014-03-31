#include "libsize.h"

int main(int argc, char **argv) {

	lsize_t lsz;
	lsize_element_t lsze;
	LSIZE_VALUE tres;
	int i, j;

	lsize_new(&lsz);

/*
	printf("format(32423)=%s\n", lsize_format(32423, LSIZE_OPT_ABBRV));
	printf("format(32423101)=%s\n", lsize_format(32423101, LSIZE_OPT_ABBRV));
	printf("format(324231019)=%s\n", lsize_format(324231019, LSIZE_OPT_ABBRV));
	printf("format(32423101924124)=%s\n", lsize_format(32423101924124, LSIZE_OPT_ABBRV));
*/



	for (i = LSIZE_SIZE_B; i < LSIZE_SIZE_MAX; i++) {
		tres = xpow(1024, i);
		tres = tres - 1;
		for(j=0; j < 3; j++) {
			if (j == 2) {
				tres = tres + (tres / 2);
			}

			lsize_set_precision(&lsz, j);
			lsize_set_value(&lsz, tres);

			lsize_set_opt(&lsz, LSIZE_OPT_ABBRV);
			printf("format(%f)=%s\n", tres, lsize_format(&lsz));
			lsize_unset_opt(&lsz, LSIZE_OPT_ABBRV);

			lsize_set_opt(&lsz, LSIZE_OPT_WHOLE | ~LSIZE_OPT_PLURAL);
			printf("format(%f)=%s\n", tres, lsize_format(&lsz));

			lsize_set_opt(&lsz, LSIZE_OPT_WHOLE | LSIZE_OPT_PLURAL);
			printf("format(%f)=%s\n", tres, lsize_format(&lsz));
			lsize_unset_opt(&lsz, LSIZE_OPT_WHOLE | LSIZE_OPT_PLURAL);

			lsize_set_opt(&lsz, LSIZE_OPT_WHOLE | LSIZE_OPT_PLURAL);
			lsize_use_bits(&lsz);
			printf("format(%f)=%s\n", tres, lsize_format(&lsz));
			lsize_unset_opt(&lsz, LSIZE_OPT_WHOLE | LSIZE_OPT_PLURAL);
			lsize_use_bytes(&lsz);

			tres += 1;
			puts("");
		}
	}


	for (i = LSIZE_SIZE_B; i < LSIZE_SIZE_MAX; i++) {
		tres = xpow(1024, i);
		tres = tres - 1;
		for(j=0; j < 3; j++) {
			if (j == 2) {
				tres = tres + (tres / 2);
			}
			/*
			printf("format(%f)=%s\n", tres, lsize_format(tres, LSIZE_OPT_ABBRV));
			printf("format(%f)=%s\n", tres, lsize_format(tres, LSIZE_OPT_WHOLE | LSIZE_OPT_PLURAL));
			printf("format(%f)=%s\n", tres, lsize_format(tres, LSIZE_OPT_ABBRV));
			printf("format(%f)=%s\n", tres, lsize_format(tres, LSIZE_OPT_WHOLE | LSIZE_OPT_PLURAL));
			*/
			lsize_set_precision(&lsz, j);
			lsize_set_value(&lsz, tres);
			lsze = lsize_guess(&lsz);
			lsize_dump_element(&lsze);

			tres += 1;
			puts("");
		}
	}


	for (i = LSIZE_SIZE_B; i < LSIZE_SIZE_MAX; i++) {
		tres = xpow(1024, i);
		tres = tres - 1;
		for(j=0; j < 3; j++) {
			if (j == 2) {
				tres = tres + (tres / 2);
			}
			lsize_set_precision(&lsz, j);
			lsize_set_value(&lsz, tres);
			lsize_get_all(&lsz);
			lsize_dump(&lsz);

			tres += 1;
			puts("");
		}
	}

	return 0;
}
