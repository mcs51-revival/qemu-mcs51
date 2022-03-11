/*
 * QEMU MCS-51 MCU
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

#include "qemu/osdep.h"
#include "qemu/module.h"
#include "qemu/units.h"
#include "qapi/error.h"
#include "exec/memory.h"
#include "exec/address-spaces.h"
#include "sysemu/sysemu.h"
#include "hw/qdev-properties.h"
#include "hw/sysbus.h"
#include "qom/object.h"
#include "hw/misc/unimp.h"
#include "mcs51.h"

struct MCS51McuClass {

};

typedef struct MCS51McuClass MCS51McuClass;
DECLARE_CLASS_CHECKERS(MCS51McuClass, MCS51_MCU, TYPE_MCS51_MCU)

static void mcs51_class_init(ObjectClass *oc, void *data)
{


}

static const TypeInfo mcs51_mcu_types[] = {
    {
        .name           = TYPE_MCS51_MCU,
        .parent         = TYPE_SYS_BUS_DEVICE,
        .instance_size  = sizeof(MCS51McuState),
        .class_size     = sizeof(MCS51McuClass),
        .class_init     = mcs51_class_init,
        .abstract       = true,
    }
};

DEFINE_TYPES(mcs51_mcu_types)
