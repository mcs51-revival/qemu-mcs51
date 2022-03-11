/*
 * MCS-51 Power Reduction Management
 *
 * Copyright (c) 2022 John Sanpe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef HW_MISC_MCS51_POWER_H
#define HW_MISC_MCS51_POWER_H

#include "hw/sysbus.h"
#include "qom/object.h"

#define PCON_SMOD   (1 << 7)
#define PCON_SMOD0  (1 << 6)
#define PCON_POF    (1 << 4)
#define PCON_GP1    (1 << 3)
#define PCON_GP0    (1 << 2)
#define PCON_PD     (1 << 1)
#define PCON_IDL    (1 << 0)

#define TYPE_MCS51_POWER "mcs51-power"
OBJECT_DECLARE_SIMPLE_TYPE(MCS51PowerState, MCS51_POWER)

struct MCS51PowerState {

};

#endif  /* HW_MISC_MCS51_POWER_H */
