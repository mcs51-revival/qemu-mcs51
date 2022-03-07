/*
 * QEMU MCS-51 gdbstub
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
#include "exec/gdbstub.h"

int mcs51_cpu_gdb_read_register(CPUState *cs, GByteArray *mem_buf, int n)
{
    MCS51CPU *cpu = MCS51_CPU(cs);
    CPUMCS51State *env = &cpu->env;

    if (n <= 31)
        return gdb_get_reg8(mem_buf, env->reg[n]);

    if (n == 32)
        return gdb_get_reg8(mem_buf, env->dpl);

    if (n == 33)
        return gdb_get_reg8(mem_buf, env->dph);

    if (n == 34)
        return gdb_get_reg8(mem_buf, env->acc);

    if (n == 35)
        return gdb_get_reg8(mem_buf, env->b);

    if (n == 36)
        return gdb_get_reg8(mem_buf, env->sp);

    if (n == 37)
        return gdb_get_reg16(mem_buf, env->pc);

    if (n == 38) {
        uint8_t psw = cpu_get_sreg(env);
        return gdb_get_reg8(mem_buf, psw);
    }

    return 0;
}

int mcs51_cpu_gdb_write_register(CPUState *cs, uint8_t *mem_buf, int n)
{
    MCS51CPU *cpu = MCS51_CPU(cs);
    CPUMCS51State *env = &cpu->env;

    if (n <= 31) {
        env->reg[n] = mem_buf[0];
        return 1;
    }

    if (n == 32) {
        env->dpl = mem_buf[0];
        return 1;
    }

    if (n == 33) {
        env->dph = mem_buf[0];
        return 1;
    }

    if (n == 34) {
        env->acc = mem_buf[0];
        return 1;
    }

    if (n == 35) {
        env->b = mem_buf[0];
        return 1;
    }

    if (n == 36) {
        env->sp = mem_buf[0];
        return 1;
    }

    if (n == 37) {
        env->pc = mem_buf[0] | mem_buf[1] << 8;
        return 2;
    }

    if (n == 38) {
        cpu_set_sreg(env, mem_buf[0]);
        return 1;
    }

    return 0;
}

vaddr mcs51_cpu_gdb_adjust_breakpoint(CPUState *cpu, vaddr addr)
{
    return addr;
}
