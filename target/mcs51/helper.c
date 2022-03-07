/*
 * QEMU MCS51 CPU helpers
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
#include "qemu/log.h"
#include "cpu.h"
#include "hw/core/tcg-cpu-ops.h"
#include "exec/exec-all.h"
#include "exec/address-spaces.h"
#include "exec/helper-proto.h"

void helper_sleep(CPUMCS51State *env)
{
    CPUState *cs = env_cpu(env);

    cs->exception_index = EXCP_HLT;
    cpu_loop_exit(cs);
}

void helper_unsupported(CPUMCS51State *env)
{
    CPUState *cs = env_cpu(env);

    /*
     *  I count not find what happens on the real platform, so
     *  it's EXCP_DEBUG for meanwhile
     */
    cs->exception_index = EXCP_DEBUG;
    if (qemu_loglevel_mask(LOG_UNIMP)) {
        qemu_log("UNSUPPORTED\n");
        cpu_dump_state(cs, stderr, 0);
    }
    cpu_loop_exit(cs);
}

void helper_debug(CPUMCS51State *env)
{
    CPUState *cs = env_cpu(env);

    cs->exception_index = EXCP_DEBUG;
    cpu_loop_exit(cs);
}

void helper_break(CPUMCS51State *env)
{
    CPUState *cs = env_cpu(env);

    cs->exception_index = EXCP_DEBUG;
    cpu_loop_exit(cs);
}

void helper_wdr(CPUMCS51State *env)
{
    qemu_log_mask(LOG_UNIMP, "WDG reset (not implemented)\n");
}

target_ulong helper_inb(CPUMCS51State *env, uint32_t port)
{
    target_ulong data = 0;

    return data;
}

void helper_outb(CPUMCS51State *env, uint32_t port, uint32_t data)
{

}

target_ulong helper_fullrd(CPUMCS51State *env, uint32_t addr)
{
    uint8_t data = 0;

    return data;
}

void helper_fullwr(CPUMCS51State *env, uint32_t data, uint32_t addr)
{

}
