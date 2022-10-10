// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file memory.h
	\brief Meta data structure to account for memory usage.

	^^
*/

#ifndef _H_SPIRITS_ALLOCATION_H_
#define _H_SPIRITS_ALLOCATION_H_

#include <stdint.h>

struct spirits;

uint8_t
spirits_allocate (struct spirits* spirits, uint64_t* address, uint64_t size);

void
spirits_free (struct spirits* spirits, uint64_t address);

#endif