/*
 * MCS-51 UART
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
#include "hw/char/mcs51_uart.h"
#include "qemu/log.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"

static void mcs51_uart_init(Object *obj)
{

}

static void mcs51_uart_class_init(ObjectClass *klass, void *data)
{

}

static const TypeInfo mcs51_uart_info = {
    .name          = TYPE_MCS51_UART,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(MCS51UartState),
    .instance_init = mcs51_uart_init,
    .class_init    = mcs51_uart_class_init,
};

static void mcs51_uart_register_types(void)
{
    type_register_static(&mcs51_uart_info);
}

type_init(mcs51_uart_register_types)
