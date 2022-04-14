// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file memory.h
	\brief Meta data structure to account for memory usage.

	^^
*/

#ifndef _H_SPIRITS_MEMORY_H_
#define _H_SPIRITS_MEMORY_H_

#include <stdint.h>

uint64_t
spirits_size(spirits_t* spirits, uint8_t only_this_node);

spirits_t*
spirits_rift(spirits_t* spirits, uint64_t requested_size);

uint8_t
spirits_unify_next(spirits_t* spirits);

spirits_t*
spirits_find_smallest_fit(spirits_t* spirits, uint64_t size);

uint8_t
spirits_condense(spirits_t* spirits);

#endif