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

void mcs51_cpu_tcg_init(void)
{

}

void mcs51_cpu_synchronize_from_tb(CPUState *cs, const TranslationBlock *tb)
{

}

bool mcs51_cpu_exec_interrupt(CPUState *cpu, int int_req)
{

    return true;
}

bool mcs51_cpu_tlb_fill(CPUState *cs, vaddr address, int size, MMUAccessType access_type, int mmu_idx, bool probe, uintptr_t retaddr)
{

    return true;
}

void mcs51_cpu_do_interrupt(CPUState *cs)
{

}

hwaddr mcs51_cpu_get_phys_page_debug(CPUState *cs, vaddr addr)
{
    return addr;
}

int mcs51_cpu_memory_rw_debug(CPUState *cs, vaddr addr, uint8_t *buf, int len, bool is_write)
{
    return cpu_memory_rw_debug(cs, addr, buf, len, is_write);
}

void helper_sleep(CPUMCS51State *env)
{
    CPUState *cs = env_cpu(env);

    cs->exception_index = EXCP_HLT;
    cpu_loop_exit(cs);
}

void helper_unsupported(CPUMCS51State *env)
{
    CPUState *cs = env_cpu(env);

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

target_ulong helper_fullrd(CPUMCS51State *env, uint32_t addr)
{
    uint8_t data;

    if (addr < NUMBER_OF_CPU_REGISTERS)
        return env->reg[addr];

    switch (addr) {
        case MCS51_SFR_SP:
            data = env->sp;
            break;

        case MCS51_SFR_DPL:
            data = env->dpl;
            break;

        case MCS51_SFR_DPH:
            data = env->dph;
            break;

        case MCS51_SFR_PSW:
            data = cpu_get_sreg(env);
            break;

        case MCS51_SFR_ACC:
            data = env->acc;
            break;

        case MCS51_SFR_B:
            data = env->b;
            break;

        default:
            data = address_space_ldub(&address_space_memory, addr, MEMTXATTRS_UNSPECIFIED, NULL);
    }

    return data;
}

void helper_fullwr(CPUMCS51State *env, uint32_t data, uint32_t addr)
{
    data &= 0x000000ff;

    if (addr < NUMBER_OF_CPU_REGISTERS) {
        env->reg[addr] = data;
        return;
    }

    switch (addr) {
        case MCS51_SFR_SP:
            env->sp = data;
            break;

        case MCS51_SFR_DPL:
            env->dpl = data;
            break;

        case MCS51_SFR_DPH:
            env->dph = data;
            break;

        case MCS51_SFR_PSW:
            cpu_set_sreg(env, data);
            break;

        case MCS51_SFR_ACC:
            env->acc = data;
            break;

        case MCS51_SFR_B:
            env->b = data;
            break;

        default:
            address_space_stb(&address_space_memory, addr, data, MEMTXATTRS_UNSPECIFIED, NULL);
    }
}
