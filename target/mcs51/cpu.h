/*
 * QEMU MCS-51 CPU
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

#ifndef QEMU_MCS51_CPU_H
#define QEMU_MCS51_CPU_H

#include "cpu-qom.h"
#include "exec/cpu-defs.h"

#define MCS51_CPU_TYPE_SUFFIX "-" TYPE_MCS51_CPU
#define MCS51_CPU_TYPE_NAME(name) (name MCS51_CPU_TYPE_SUFFIX)
#define CPU_RESOLVING_TYPE TYPE_MCS51_CPU

#define MMU_CODE_IDX 0
#define MMU_DATA_IDX 1

#define MCS51_SFR_SP    0x81
#define MCS51_SFR_DPL   0x82
#define MCS51_SFR_DPH   0x83
#define MCS51_SFR_PSW   0xd0
#define MCS51_SFR_ACC   0xe0
#define MCS51_SFR_B     0xf0

/* Number of CPU registers */
#define NUMBER_OF_CPU_REGISTERS 32

typedef struct CPUMCS51State {
    uint8_t reg[NUMBER_OF_CPU_REGISTERS];

    uint8_t dpl;        /*  */
    uint8_t dph;        /*  */
    uint8_t acc;        /*  */
    uint8_t b;          /*  */
    uint8_t sp;         /*  */
    uint8_t pc;         /*  */

    uint8_t pswCY;      /*  */
    uint8_t pswAC;      /*  */
    uint8_t pswF0;      /*  */
    uint8_t pswRS1;     /*  */
    uint8_t pswRS0;     /*  */
    uint8_t pswOV;      /*  */
    uint8_t pswP;       /*  */
} CPUMCS51State;

typedef struct MCS51CPU {
    CPUState parent_obj;
    CPUNegativeOffsetState neg;
    CPUMCS51State env;
} MCS51CPU;

extern const VMStateDescription vms_mcs51_cpu;

extern void mcs51_cpu_tcg_init(void);
extern void mcs51_cpu_synchronize_from_tb(CPUState *cs, const TranslationBlock *tb);
extern bool mcs51_cpu_exec_interrupt(CPUState *cpu, int int_req);
extern bool mcs51_cpu_tlb_fill(CPUState *cs, vaddr address, int size, MMUAccessType access_type, int mmu_idx, bool probe, uintptr_t retaddr);
extern void mcs51_cpu_do_interrupt(CPUState *cs);
extern hwaddr mcs51_cpu_get_phys_page_debug(CPUState *cs, vaddr addr);
extern int mcs51_cpu_memory_rw_debug(CPUState *cs, vaddr addr, uint8_t *buf, int len, bool is_write);

extern int mcs51_cpu_gdb_read_register(CPUState *cpu, GByteArray *buf, int reg);
extern int mcs51_cpu_gdb_write_register(CPUState *cpu, uint8_t *buf, int reg);
extern vaddr mcs51_cpu_gdb_adjust_breakpoint(CPUState *cpu, vaddr addr);

static inline uint8_t cpu_get_sreg(CPUMCS51State *env)
{
    uint8_t sreg;
    sreg = (env->pswCY)     << 7
         | (env->pswAC)     << 6
         | (env->pswF0)     << 5
         | (env->pswRS1)    << 4
         | (env->pswRS0)    << 3
         | (env->pswOV)     << 2
         | (env->pswP)      << 0;
    return sreg;
}

static inline void cpu_set_sreg(CPUMCS51State *env, uint8_t sreg)
{
    env->pswCY  = (sreg >> 7) & 0x01;
    env->pswAC  = (sreg >> 6) & 0x01;
    env->pswF0  = (sreg >> 5) & 0x01;
    env->pswRS1 = (sreg >> 4) & 0x01;
    env->pswRS0 = (sreg >> 3) & 0x01;
    env->pswOV  = (sreg >> 2) & 0x01;
    env->pswP   = (sreg >> 0) & 0x01;
}

#define cpu_mmu_index mcs51_cpu_mmu_index
static inline int mcs51_cpu_mmu_index(CPUMCS51State *env, bool ifetch)
{
    return ifetch ? MMU_CODE_IDX : MMU_DATA_IDX;
}

static inline void cpu_get_tb_cpu_state(CPUMCS51State *env, target_ulong *pc,
                                        target_ulong *cs_base, uint32_t *pflags)
{
    uint32_t flags = 0;

    *pc = env->pc;
    *cs_base = 0;
    *pflags = flags;
}

typedef CPUMCS51State CPUArchState;
typedef MCS51CPU ArchCPU;

#include "exec/cpu-all.h"

#endif  /* QEMU_MCS51_CPU_H */
