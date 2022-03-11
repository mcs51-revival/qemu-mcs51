/*
 * MCS-51 16bit timer
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
#include "hw/timer/mcs51_timer16.h"
#include "migration/vmstate.h"
#include "hw/irq.h"
#include "hw/sysbus.h"
#include "hw/qdev-clock.h"
#include "qemu/timer.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qapi/error.h"
#include "trace.h"

static void mcs51_timer16_init(Object *obj)
{

}

static void mcs51_timer16_class_init(ObjectClass *klass, void *data)
{

}

static const TypeInfo mcs51_timer16_info = {
    .name           = TYPE_MCS51_TIMER16,
    .parent         = TYPE_SYS_BUS_DEVICE,
    .instance_size  = sizeof(MCS51Timer16State),
    .instance_init  = mcs51_timer16_init,
    .class_init     = mcs51_timer16_class_init,
};

static void mcs51_timer16_register_types(void)
{
    type_register_static(&mcs51_timer16_info);
}

type_init(mcs51_timer16_register_types)

