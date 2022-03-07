/*
 * MCS-51 8bit timer
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
#include "hw/timer/mcs51-timer8.h"
#include "migration/vmstate.h"
#include "hw/irq.h"
#include "hw/sysbus.h"
#include "hw/qdev-clock.h"
#include "qemu/timer.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qapi/error.h"
#include "trace.h"


static void systick_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->vmsd = &vmstate_systick;
    dc->reset = systick_reset;
    dc->realize = systick_realize;
}

static const TypeInfo armv7m_systick_info = {
    .name = "mcs51-timer8",
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_init = systick_instance_init,
    .instance_size = sizeof(SysTickState),
    .class_init = systick_class_init,
};

static void armv7m_systick_register_types(void)
{
    type_register_static(&armv7m_systick_info);
}

type_init(armv7m_systick_register_types)
