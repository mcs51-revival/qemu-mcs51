/*
 * MCS-51 uart
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
#include "hw/char/avr_usart.h"
#include "qemu/log.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"

static const TypeInfo avr_usart_info = {
    .name          = TYPE_AVR_USART,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(AVRUsartState),
    .instance_init = avr_usart_init,
    .class_init    = avr_usart_class_init,
};

static void avr_usart_register_types(void)
{
    type_register_static(&avr_usart_info);
}

type_init(avr_usart_register_types)
