// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file memory.h
	\brief Meta data structure to account for memory usage.

	^^
*/

#ifndef _H_SPIRITS_MEMORY_H_
#define _H_SPIRITS_MEMORY_H_

#include <stdint.h>

#ifndef SPIRITS_MINIMUM_SIZE
#define SPIRITS_MINIMUM_SIZE 1
#endif

struct spirits;

uint64_t
spirits_size (struct spirits* spirits, uint8_t only_this_node);

uint64_t
spirits_size_used (struct spirits* spirits, uint8_t only_this_node);

uint64_t
spirits_size_free (struct spirits* spirits, uint8_t only_this_node);

struct spirits*
spirits_rift (struct spirits* spirits, uint64_t requested_size);

uint8_t
spirits_unify_next (struct spirits* spirits);

struct spirits*
spirits_find_smallest_fit (struct spirits* spirits, uint64_t size);

uint8_t
spirits_condense (struct spirits* spirits);

#endif