/*
 * MCS-51 Timer16
 *
 * Copyright (c) 2022 John Sanpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see
 * <http://www.gnu.org/licenses/lgpl-2.1.html>
 */

#ifndef HW_TIMER_MCS51_TIMER16_H
#define HW_TIMER_MCS51_TIMER16_H

#include "hw/sysbus.h"
#include "qemu/timer.h"
#include "qom/object.h"

#define TYPE_MCS51_TIMER16 "mcs51-timer16"
OBJECT_DECLARE_SIMPLE_TYPE(MCS51Timer16State, MCS51_TIMER16)

struct MCS51Timer16State {

};

#endif  /* HW_TIMER_MCS51_TIMER16_H */
