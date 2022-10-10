// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file allocation.c
	\brief Example usage of memory accounting.

	^^
*/

#include <stdio.h>

#include <spirits/all.h>

int main (int ac, char **av) {
	spirits_t spirits;
	if (0 != spirits_summon (&spirits, 4096)) {
		printf("Could not summon spiris.\n");
		return 13;
	}

	spirits_print_all (&spirits);

	spirits_t* a = spirits_rift (&spirits, 2*1024);
	spirits_print_all (&spirits);

	spirits_t* b = spirits_rift (a, 1024);
	spirits_print_all (&spirits);

	spirits_t* c = spirits_rift (a, 64);
	spirits_print_all (&spirits);

	uint64_t address = 0;
	if (0 == spirits_allocate (&spirits, &address, 920)) {
		printf ("Allocated %u bytes at offset: %llu\n", 920, address);
	}
	else {
		printf ("Allocation error :/\n");
		return -1;
	}

	spirits_print_all (&spirits);

	uint64_t address2 = 0;
	if (0 == spirits_allocate (&spirits, &address2, 64)) {
		printf ("Allocated %u bytes at offset: %llu\n", 64, address2);
	}
	else {
		printf ("Allocation error address2:/\n");
		return -1;
	}

	uint64_t address3 = 0;
	if (0 == spirits_allocate (&spirits, &address3, 40)) {
		printf ("Allocated %u bytes at offset: %llu\n", 40, address3);
	}
	else {
		printf ("Allocation error address3:/\n");
		return -1;
	}

	spirits_print_all (&spirits);

	printf ("Freeing memory at offset: %llu\n", address);
	spirits_free (&spirits, address);
	printf ("After free:\n");
	spirits_print_all (&spirits);
	printf ("Condensing ...\n");
	spirits_condense (&spirits);
	printf ("Condensed:\n");
	spirits_print_all (&spirits);
	printf ("Freeing memory at offset: %llu\n", address2);
	spirits_free (&spirits, address2);
	spirits_print_all (&spirits);

	printf ("Banishing spirits ...\n");
	spirits_banish (&spirits);

	spirits_print_all (&spirits);
	return 0;
}