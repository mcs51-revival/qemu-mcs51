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
#include "qemu/qemu-print.h"
#include "tcg/tcg.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "tcg/tcg-op.h"
#include "exec/cpu_ldst.h"
#include "exec/helper-proto.h"
#include "exec/helper-gen.h"
#include "exec/log.h"
#include "exec/translator.h"
#include "exec/gen-icount.h"

typedef struct DisasContext {
    DisasContextBase base;

} DisasContext;

static const TranslatorOps mcs51_tr_ops = {
    // .init_disas_context = mcs51_tr_init_disas_context,
    // .tb_start           = mcs51_tr_tb_start,
    // .insn_start         = mcs51_tr_insn_start,
    // .translate_insn     = mcs51_tr_translate_insn,
    // .tb_stop            = mcs51_tr_tb_stop,
    // .disas_log          = mcs51_tr_disas_log,
};

void gen_intermediate_code(CPUState *cs, TranslationBlock *tb, int max_insns)
{
    DisasContext dc = { };
    translator_loop(&mcs51_tr_ops, &dc.base, cs, tb, max_insns);
}

void restore_state_to_opc(CPUMCS51State *env, TranslationBlock *tb, target_ulong *data)
{
    env->pc = data[0];
}
