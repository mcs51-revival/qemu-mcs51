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

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/qemu-print.h"
#include "exec/exec-all.h"
#include "cpu.h"
#include "disas/dis-asm.h"

static void mcs51_cpu_realizefn(DeviceState *dev, Error **errp)
{
    CPUState *cs = CPU(dev);
    MCS51CPUClass *mcc = MCS51_CPU_GET_CLASS(dev);
    Error *local_err = NULL;

    cpu_exec_realizefn(cs, &local_err);
    if (local_err != NULL) {
        error_propagate(errp, local_err);
        return;
    }
    qemu_init_vcpu(cs);
    cpu_reset(cs);

    mcc->parent_realize(dev, errp);
}

static ObjectClass *mcs51_cpu_class_by_name(const char *cpu_model)
{
    ObjectClass *oc;

    oc = object_class_by_name(cpu_model);
    if (object_class_dynamic_cast(oc, TYPE_MCS51_CPU) == NULL ||
        object_class_is_abstract(oc)) {
        oc = NULL;
    }

    return oc;
}

static bool mcs51_cpu_has_work(CPUState *cs)
{
    return (cs->interrupt_request & (CPU_INTERRUPT_HARD | CPU_INTERRUPT_RESET));
}

static void mcs51_cpu_reset(DeviceState *ds)
{
    CPUState *cs = CPU(ds);
    MCS51CPU *cpu = MCS51_CPU(cs);
    MCS51CPUClass *mcc = MCS51_CPU_GET_CLASS(cpu);
    CPUMCS51State *env = &cpu->env;

    mcc->parent_reset(ds);

    env->dpl        = 0x00;
    env->dph        = 0x00;
    env->acc        = 0x00;
    env->b          = 0x00;
    env->pc         = 0x00;
    env->sp         = 0x07;
    env->pswCY      = 0x00;
    env->pswAC      = 0x00;
    env->pswF0      = 0x00;
    env->pswRS1     = 0x00;
    env->pswRS0     = 0x00;
    env->pswOV      = 0x00;
    env->pswP       = 0x00;

    memset(env->reg, 0, sizeof(env->reg));
}

static void mcs51_cpu_dump_state(CPUState *cs, FILE *f, int flags)
{
    MCS51CPU *cpu = MCS51_CPU(cs);
    CPUMCS51State *env = &cpu->env;
    unsigned int index;

    qemu_fprintf(f, "\n");

    for (index = 0; index < ARRAY_SIZE(env->reg); ++index)
    qemu_fprintf(f, "REG%02d:   %02x\n", index, env->reg[index]);

    qemu_fprintf(f, "DPL:       %02x\n", env->dpl);
    qemu_fprintf(f, "DPH:       %02x\n", env->dph);
    qemu_fprintf(f, "ACC:       %02x\n", env->acc);
    qemu_fprintf(f, "B:         %02x\n", env->b);
    qemu_fprintf(f, "SP:        %02x\n", env->sp);
    qemu_fprintf(f, "PC:        %04x\n", env->pc);
    qemu_fprintf(f, "SREG:      [ %s %s %s %s %s %s %s ]\n",
                 env->pswCY     ? "CY"  : "cy",
                 env->pswAC     ? "AC"  : "ac",
                 env->pswF0     ? "F0"  : "f0",
                 env->pswRS1    ? "RS1" : "rs1",
                 env->pswRS0    ? "RS0" : "rs0",
                 env->pswOV     ? "OV"  : "ov",
                 env->pswP      ? "P"   : "p");
}

static void mcs51_cpu_set_pc(CPUState *cs, vaddr value)
{
    MCS51CPU *cpu = MCS51_CPU(cs);
    cpu->env.pc = value;
}

static void mcs51_cpu_disas_set_info(CPUState *cpu, disassemble_info *info)
{
    info->mach = bfd_arch_avr;
    // info->print_insn = mcs51_print_insn;
}

static void mcs51_cpu_initfn(Object *obj)
{
    MCS51CPU *cpu = MCS51_CPU(obj);
    cpu_set_cpustate_pointers(cpu);
}

#include "hw/core/sysemu-cpu-ops.h"

static const struct SysemuCPUOps mcs51_sysemu_ops = {
    // .get_phys_page_debug = avr_cpu_get_phys_page_debug,
};

#include "hw/core/tcg-cpu-ops.h"

static const struct TCGCPUOps mcs51_tcg_ops = {
    // .initialize = avr_cpu_tcg_init,
    // .synchronize_from_tb = avr_cpu_synchronize_from_tb,
    // .cpu_exec_interrupt = avr_cpu_exec_interrupt,
    // .tlb_fill = avr_cpu_tlb_fill,
    // .do_interrupt = avr_cpu_do_interrupt,
};

static void mcs51_cpu_class_init(ObjectClass *oc, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(oc);
    CPUClass *cc = CPU_CLASS(oc);
    MCS51CPUClass *mcc = MCS51_CPU_CLASS(oc);

    device_class_set_parent_realize(dc, mcs51_cpu_realizefn, &mcc->parent_realize);
    device_class_set_parent_reset(dc, mcs51_cpu_reset, &mcc->parent_reset);

    cc->class_by_name           = mcs51_cpu_class_by_name;
    cc->has_work                = mcs51_cpu_has_work;
    cc->dump_state              = mcs51_cpu_dump_state;
    cc->set_pc                  = mcs51_cpu_set_pc;
    // cc->memory_rw_debug         = mcs51_cpu_memory_rw_debug;
    // dc->vmsd                    = &vms_mcs51_cpu;
    cc->sysemu_ops              = &mcs51_sysemu_ops;
    cc->disas_set_info          = mcs51_cpu_disas_set_info;
    cc->gdb_read_register       = mcs51_cpu_gdb_read_register;
    cc->gdb_write_register      = mcs51_cpu_gdb_write_register;
    cc->gdb_adjust_breakpoint   = mcs51_cpu_gdb_adjust_breakpoint;
    cc->gdb_num_core_regs       = 38;
    cc->gdb_core_xml_file       = "mcs51-cpu.xml";
    cc->tcg_ops                 = &mcs51_tcg_ops;
}

static const TypeInfo mcs51_cpu_type_info[] = {
    {
        .name = TYPE_MCS51_CPU,
        .parent = TYPE_CPU,
        .instance_size = sizeof(MCS51CPU),
        .instance_init = mcs51_cpu_initfn,
        .class_size = sizeof(MCS51CPUClass),
        .class_init = mcs51_cpu_class_init,
        .abstract = true,
    },
};

DEFINE_TYPES(mcs51_cpu_type_info)
