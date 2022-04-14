// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file spirits.c
	\brief Meta data structure to account for memory usage.

	^^
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <dlfcn.h> // dlsym

#include <spirits/all.h>

#ifdef _WIN32
#define KAJI_PATH_SIZE 256
#else
#define KAJI_PATH_SIZE 4096
#endif

#define MIN_SPIRIT_SIZE sysconf(_SC_PAGESIZE)

static uint8_t g_system_functions_initialized = 0;
static void* (*system_malloc)(size_t) = NULL;
static void* (*system_free)(void*) = NULL;

void*
__spirits_malloc(size_t size) {
	assert(NULL != system_malloc && "Missing memory functions!");
	return system_malloc(size);
}

void
__spirits_free(void* memory) {
	assert(NULL != system_free && "Missing memory functions!");
	system_free(memory);
}

uint8_t
spirits_summon(spirits_t* spirits, uint64_t size) {
	if (0 == g_system_functions_initialized) {
		system_malloc = dlsym(RTLD_NEXT, "malloc");
		system_free = dlsym(RTLD_NEXT, "free");
		g_system_functions_initialized = 1;
	}

	if (NULL == spirits) {
		return 1;
	}

	spirits->offset = 0;
	spirits->size = size;
	spirits->available = 1;
	spirits->next = NULL;
	spirits->prev = NULL;

	return 0;
}

spirits_t*
spirits_rift(spirits_t* spirits, uint64_t requested_size) {
	if (NULL == spirits) return NULL;

	spirits_t* splinter = __spirits_malloc(sizeof(spirits_t));
	splinter->size = requested_size;
	splinter->available = 1;

	splinter->offset = spirits->offset + (spirits->size - requested_size);
	splinter->next = spirits->next;
	if (NULL != splinter->next) {
		splinter->next->prev = splinter;
	}
	splinter->prev = spirits;
	spirits->next = splinter;

	spirits->size -= requested_size;

	return splinter;
}

uint8_t
spirits_unify_next(spirits_t* spirits) {
	if (NULL == spirits->next) {
		return 1;
	}

	spirits_t* next = spirits->next;
	if (NULL == next) {
		return 2;
	}

	spirits->next = next->next;
	if (NULL != spirits->next) {
		spirits->next->prev = spirits;
	}

	spirits->size += next->size;

	next->size = 0;
	next->offset = spirits->offset;
	next->next = NULL;
	next->prev = NULL;
	__spirits_free(next);

	return 0;
}

void
spirits_banish(spirits_t* spirits) {
	if (NULL == spirits) return;

	while (0 == spirits_unify_next(spirits)) {}

	spirits->offset = 0;
	spirits->size = 0;
	spirits->available = 1;
	spirits->next = NULL;
	spirits->prev = NULL;
}

spirits_t*
spirits_find_smallest_fit(spirits_t* spirits, uint64_t size) {
	if (NULL == spirits) return NULL;

	spirits_t* fit = NULL;
	spirits_t* next = spirits;
	uint8_t i = 0;
	while (NULL != next) {
		if (1 == next->available && size <= next->size) {
			if (NULL == fit || fit->size > next->size) {
				fit = next;
			}
		}

		if (++i == 3) {
			next = NULL;
		}
		else {
			next = next->next;
		}
	}

	return fit;
}

uint8_t
spirits_condense(spirits_t* spirits) {
	if (NULL == spirits) return 1;

	spirits_t* next = spirits;
	while (NULL != next) {
		if (1 == next->available) {
			while (NULL != next->next && 1 == next->next->available) {
				spirits_unify_next(next);
			}
		}

		next = next->next;
	}

	return 0;
}

uint8_t
spirits_allocate(spirits_t* spirits, uint64_t* address, uint64_t size) {
	if (NULL == spirits || NULL == address) return 1;

	spirits_t* fit = spirits_find_smallest_fit(spirits, size);
	if (NULL == fit) {
		spirits_condense(spirits);
		fit = spirits_find_smallest_fit(spirits, size);
		if (NULL == fit) {
			return 1;
		}
	}

	// if no smallest fit found, pass over memory and see if there are
	// neighboring cells that are free and would fit the size

	spirits_t* s;
	if (size == fit->size) {
		s = fit;
	}
	else {
		s = spirits_rift(fit, size);	
	}

	s->available = 0;
	*address = s->offset;
	return 0;
}

void
spirits_free(spirits_t* spirits, uint64_t address) {
	if (NULL == spirits) return;

	spirits_t* next = spirits;
	while (next) {
		if (address == next->offset) {
			next->available = 1;
			spirits_t* left = next->prev;
			if (NULL != left && 1 == left->available) {
				spirits_unify_next(left);
				if (NULL != left->next && 1 == left->next->available) {
					spirits_unify_next(left);
				}
			}
			else if (NULL != next->next && 1 == next->available) {
				spirits_unify_next(next);
			}

			break;
		}

		next = next->next;
	}
}

void
spirits_print(spirits_t* spirits, uint8_t newline) {
	if (NULL == spirits) {
		printf("No spirits summoned.\n");
		return;
	}

	printf("|-%s-%llu @ %llu-"
		, (spirits->available ? "free" : "used")
		, spirits->size, spirits->offset
	);
	if (1 == newline) {
		printf("\n");
	}
}

uint64_t
spirits_size(spirits_t* spirits, uint8_t only_this_node) {
	if (NULL == spirits) return 0;

	if (only_this_node) {
		return NULL != spirits ? spirits->size : 0;
	}

	uint64_t size = 0;
	spirits_t* next = spirits;	
	while (NULL != next) {
		size += next->size;
		next = next->next;
	}

	return size;
}

void
spirits_print_all(spirits_t* spirits) {
	if (NULL == spirits) {
		printf("No spirits summoned.");
		return;
	}

	spirits_t* next = spirits;
	while (NULL != next) {
		spirits_print(next, 0);
		next = next->next;
	}

	uint64_t size = spirits_size(spirits, 0);
	printf("| (total-size: %llu)", size);

	printf("\n");
}