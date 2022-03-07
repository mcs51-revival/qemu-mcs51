/*
 * QEMU MCS-51 CPU
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

#ifndef QEMU_MCS51_QOM_H
#define QEMU_MCS51_QOM_H

#include "hw/core/cpu.h"
#include "qom/object.h"

#define TYPE_MCS51_CPU "mcs51-cpu"

OBJECT_DECLARE_TYPE(MCS51CPU, MCS51CPUClass, MCS51_CPU)

struct MCS51CPUClass {
    CPUClass parent_class;
    DeviceRealize parent_realize;
    DeviceReset parent_reset;
};

#endif /* QEMU_MCS51_QOM_H */
