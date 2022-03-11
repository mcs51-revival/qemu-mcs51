/*
 * MCS-51 Interrupt Management
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

#ifndef HW_INTC_MCS51_H
#define HW_INTC_MCS51_H

#include "qemu/units.h"
#include "hw/sysbus.h"
#include "qom/object.h"

#define IE_EA       (1 << 7)
#define IE_ET2      (1 << 5)
#define IE_ES       (1 << 4)
#define IE_ET1      (1 << 3)
#define IE_EX1      (1 << 2)
#define IE_ET0      (1 << 1)
#define IE_EX0      (1 << 0)

#define IP_PT2      (1 << 5)
#define IP_PS       (1 << 4)
#define IP_PT1      (1 << 3)
#define IP_PX1      (1 << 2)
#define IP_PT0      (1 << 1)
#define IP_PX0      (1 << 0)

#define IPH_PX3H    (1 << 7)
#define IPH_PX2H    (1 << 6)
#define IPH_PT2H    (1 << 5)
#define IPH_PSH     (1 << 4)
#define IPH_PT1H    (1 << 3)
#define IPH_PX1H    (1 << 2)
#define IPH_PT0H    (1 << 1)
#define IPH_PX0H    (1 << 0)

#define XICON_PX3   (1 << 7)
#define XICON_EX3   (1 << 6)
#define XICON_IE3   (1 << 5)
#define XICON_IT3   (1 << 4)
#define XICON_PX2   (1 << 3)
#define XICON_EX2   (1 << 2)
#define XICON_IE2   (1 << 1)
#define XICON_IT2   (1 << 0)

#define TYPE_MCS51_INTC "mcs51-intc"
OBJECT_DECLARE_SIMPLE_TYPE(MCS51IntcState, MCS51_INTC)

#endif  /* HW_INTC_MCS51_H */
