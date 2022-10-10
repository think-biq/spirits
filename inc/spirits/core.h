// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file spirits.h
	\brief Meta data structure to account for memory usage.

	^^
*/

#ifndef _H_SPIRITS_CORE_H_
#define _H_SPIRITS_CORE_H_

#include <stdint.h>

struct spirits {
	uint64_t offset;
	uint64_t size;
	uint8_t available;
	struct spirits* next;
	struct spirits* prev;
};
typedef
	struct spirits
	spirits_t
	;


uint8_t
spirits_summon (struct spirits* spirits, uint64_t size);

void
spirits_banish (struct spirits* spirits);

#endif