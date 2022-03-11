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

#ifndef HW_CHAR_MCS51_UART_H
#define HW_CHAR_MCS51_UART_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"

#define UART_SCON_SM0   (1 << 7)
#define UART_SCON_SM1   (1 << 6)
#define UART_SCON_SM2   (1 << 5)
#define UART_SCON_REN   (1 << 4)
#define UART_SCON_TB8   (1 << 3)
#define UART_SCON_RB8   (1 << 2)
#define UART_SCON_TI    (1 << 1)
#define UART_SCON_RI    (1 << 0)

#define TYPE_MCS51_UART "mcs51-uart"
OBJECT_DECLARE_SIMPLE_TYPE(MCS51UartState, MCS51_UART)

struct MCS51UartState {

};

#endif  /* HW_CHAR_MCS51_UART_H */
