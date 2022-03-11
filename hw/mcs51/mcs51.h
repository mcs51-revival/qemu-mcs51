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

#ifndef HW_MCS51_MCS51_H
#define HW_MCS51_MCS51_H

#include "hw/char/mcs51_uart.h"
#include "hw/timer/mcs51_timer8.h"
#include "hw/timer/mcs51_timer16.h"
#include "hw/misc/mcs51_power.h"
#include "hw/intc/mcs51.h"
#include "target/mcs51/cpu.h"
#include "qom/object.h"

#define TYPE_MCS51_MCU "mcs51"
typedef struct MCS51McuState MCS51McuState;
DECLARE_INSTANCE_CHECKER(MCS51McuState, MCS51_MCU, TYPE_MCS51_MCU)

struct MCS51McuState {
    SysBusDevice parent_obj;

    MCS51CPU cpu;
    MemoryRegion flash;
    MemoryRegion sram;
    DeviceState *io;

    MCS51Timer8State timer8;
    MCS51Timer16State timer16;
    MCS51UartState uart;
    MCS51PowerState pwr;
};

#endif  /* HW_MCS51_MCS51_H */
