// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file print.h
	\brief Meta data structure to account for memory usage.

	^^
*/

#ifndef _H_SPIRITS_PRINT_H_
#define _H_SPIRITS_PRINT_H_

#include <stdint.h>

struct spirits;

void
spirits_print_all(struct spirits* spirits);

void
spirits_print(struct spirits* spirits, uint8_t newline);

#endif