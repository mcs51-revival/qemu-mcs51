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

    CPUMCS51State *env;
    CPUState *cs;

    target_long npc;
    uint8_t opcode;
} DisasContext;

struct mcs51_ops {
    uint8_t opcode;
    uint8_t mask;
    uint8_t reg;
    unsigned int min;
    unsigned int max;
    unsigned int size;
    const char *name;
    void (*operate)(CPUMCS51State *env, DisasContext *dc);
};

static void nop_non(CPUMCS51State *env, DisasContext *dc)
{
    /* Nothing */
}

static void ajmp_a11(CPUMCS51State *env, DisasContext *dc)
{

}

static void ljmp_a16(CPUMCS51State *env, DisasContext *dc)
{

}

static void rr_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void inc_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void inc_dir(CPUMCS51State *env, DisasContext *dc)
{

}

static void inc_tre(CPUMCS51State *env, DisasContext *dc)
{

}

static void inc_reg(CPUMCS51State *env, DisasContext *dc)
{

}

static void jbc_bio(CPUMCS51State *env, DisasContext *dc)
{

}

static void acall_a11(CPUMCS51State *env, DisasContext *dc)
{

}

static void lcall_a16(CPUMCS51State *env, DisasContext *dc)
{

}

static void rrc_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void dec_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void dec_dir(CPUMCS51State *env, DisasContext *dc)
{

}

static void dec_tre(CPUMCS51State *env, DisasContext *dc)
{

}

static void dec_reg(CPUMCS51State *env, DisasContext *dc)
{

}

static void jb_bio(CPUMCS51State *env, DisasContext *dc)
{

}

static void ret_non(CPUMCS51State *env, DisasContext *dc)
{

}

static void rl_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void add_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void add_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void add_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void add_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void jnb_bio(CPUMCS51State *env, DisasContext *dc)
{

}

static void reti_non(CPUMCS51State *env, DisasContext *dc)
{

}

static void rlc_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void addc_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void addc_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void addc_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void addc_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void jc_off(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_dia(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_dii(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void jnc_off(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_dia(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_dii(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void jz_off(CPUMCS51State *env, DisasContext *dc)
{

}

static void xrl_dia(CPUMCS51State *env, DisasContext *dc)
{

}

static void xrl_dii(CPUMCS51State *env, DisasContext *dc)
{

}

static void xrl_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void xrl_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void xrl_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void xrl_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void jnz_off(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_cob(CPUMCS51State *env, DisasContext *dc)
{

}

static void jmp_tad(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_dii(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_tri(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_rei(CPUMCS51State *env, DisasContext *dc)
{

}

static void sjmp_off(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_cob(CPUMCS51State *env, DisasContext *dc)
{

}

static void movc_atc(CPUMCS51State *env, DisasContext *dc)
{

}

static void div_acb(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_did(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_dtr(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_dre(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_pti(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_bic(CPUMCS51State *env, DisasContext *dc)
{

}

static void movc_ata(CPUMCS51State *env, DisasContext *dc)
{

}

static void subb_aci(CPUMCS51State *env, DisasContext *dc)
{

}

static void subb_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void subb_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void subb_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void orl_cox(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_cob(CPUMCS51State *env, DisasContext *dc)
{

}

static void inc_ptr(CPUMCS51State *env, DisasContext *dc)
{

}

static void mul_acb(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_trd(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_red(CPUMCS51State *env, DisasContext *dc)
{

}

static void anl_cox(CPUMCS51State *env, DisasContext *dc)
{

}

static void cpl_bit(CPUMCS51State *env, DisasContext *dc)
{

}

static void cpl_con(CPUMCS51State *env, DisasContext *dc)
{

}

static void cjne_aio(CPUMCS51State *env, DisasContext *dc)
{

}

static void cjne_ado(CPUMCS51State *env, DisasContext *dc)
{

}

static void cjne_tio(CPUMCS51State *env, DisasContext *dc)
{

}

static void cjne_rio(CPUMCS51State *env, DisasContext *dc)
{

}

static void push_dir(CPUMCS51State *env, DisasContext *dc)
{

}

static void clr_bit(CPUMCS51State *env, DisasContext *dc)
{

}

static void clr_con(CPUMCS51State *env, DisasContext *dc)
{

}

static void swap_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void xch_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void xch_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void xch_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void pop_dir(CPUMCS51State *env, DisasContext *dc)
{

}

static void setb_bit(CPUMCS51State *env, DisasContext *dc)
{

}

static void setb_con(CPUMCS51State *env, DisasContext *dc)
{

}

static void da_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void djnz_dio(CPUMCS51State *env, DisasContext *dc)
{

}

static void xchd_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void djnz_reo(CPUMCS51State *env, DisasContext *dc)
{

}

static void movx_atp(CPUMCS51State *env, DisasContext *dc)
{

}

static void movx_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void clr_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_acd(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_atr(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_acr(CPUMCS51State *env, DisasContext *dc)
{

}

static void movx_tpa(CPUMCS51State *env, DisasContext *dc)
{

}

static void movx_tra(CPUMCS51State *env, DisasContext *dc)
{

}

static void cpl_acc(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_dia(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_tra(CPUMCS51State *env, DisasContext *dc)
{

}

static void mov_rea(CPUMCS51State *env, DisasContext *dc)
{

}

static const struct mcs51_ops mcs51_table[] = {
    { 0x00, 0xff, 0x00, 0x0, 0x0, 1, "nop",    nop_non    },    /* nop                              */
    { 0x01, 0x1f, 0x00, 0x0, 0x0, 2, "ajmp",   ajmp_a11   },    /* ajmp     addr11                  */
    { 0x02, 0xff, 0x00, 0x0, 0x0, 3, "ljmp",   ljmp_a16   },    /* ljmp     addr16                  */
    { 0x03, 0xff, 0x00, 0x0, 0x0, 1, "rr",     rr_acc     },    /* rr       a                       */
    { 0x04, 0xff, 0x00, 0x0, 0x0, 1, "inc",    inc_acc    },    /* inc      a                       */
    { 0x05, 0xff, 0x00, 0x0, 0x0, 2, "inc",    inc_dir    },    /* inc      direct                  */
    { 0x06, 0xf0, 0x0f, 0x6, 0x7, 1, "inc",    inc_tre    },    /* inc      @reg                    */
    { 0x08, 0xf0, 0x0f, 0x8, 0xf, 1, "inc",    inc_reg    },    /* inc      reg                     */

    { 0x10, 0xff, 0x00, 0x0, 0x0, 3, "jbc",    jbc_bio    },    /* jbc      bit, offset             */
    { 0x11, 0x1f, 0x00, 0x0, 0x0, 2, "acall",  acall_a11  },    /* acall    addr11                  */
    { 0x12, 0xff, 0x00, 0x0, 0x0, 3, "lcall",  lcall_a16  },    /* lcall    addr16                  */
    { 0x13, 0xff, 0x00, 0x0, 0x0, 1, "rrc",    rrc_acc    },    /* rrc      a                       */
    { 0x14, 0xff, 0x00, 0x0, 0x0, 1, "dec",    dec_acc    },    /* dec      a                       */
    { 0x15, 0xff, 0x00, 0x0, 0x0, 2, "dec",    dec_dir    },    /* dec      direct                  */
    { 0x16, 0xf0, 0x0f, 0x6, 0x7, 1, "dec",    dec_tre    },    /* dec      @reg                    */
    { 0x18, 0xf0, 0x0f, 0x8, 0xf, 1, "dec",    dec_reg    },    /* dec      reg                     */

    { 0x20, 0xff, 0x00, 0x0, 0x0, 3, "jb",     jb_bio     },    /* jb       bit, offset             */
    { 0x22, 0xff, 0x00, 0x0, 0x0, 1, "ret",    ret_non    },    /* ret                              */
    { 0x23, 0xff, 0x00, 0x0, 0x0, 1, "rl",     rl_acc     },    /* rl       a                       */
    { 0x24, 0xff, 0x00, 0x0, 0x0, 2, "add",    add_aci    },    /* add      a, #immed               */
    { 0x25, 0xff, 0x00, 0x0, 0x0, 2, "add",    add_acd    },    /* add      a, direct               */
    { 0x26, 0xf0, 0x0f, 0x6, 0x7, 1, "add",    add_atr    },    /* add      a, @reg                 */
    { 0x28, 0xf0, 0x0f, 0x8, 0xf, 1, "add",    add_acr    },    /* add      a, reg                  */

    { 0x30, 0xff, 0x00, 0x0, 0x0, 3, "jnb",    jnb_bio    },    /* jnb      bit, offset             */
    { 0x32, 0xff, 0x00, 0x0, 0x0, 1, "reti",   reti_non   },    /* reti                             */
    { 0x33, 0xff, 0x00, 0x0, 0x0, 1, "rlc",    rlc_acc    },    /* rlc      a                       */
    { 0x34, 0xff, 0x00, 0x0, 0x0, 2, "addc",   addc_aci   },    /* addc     a, #immed               */
    { 0x35, 0xff, 0x00, 0x0, 0x0, 2, "addc",   addc_acd   },    /* addc     a, direct               */
    { 0x36, 0xf0, 0x0f, 0x6, 0x7, 1, "addc",   addc_atr   },    /* addc     a, @reg                 */
    { 0x38, 0xf0, 0x0f, 0x8, 0xf, 1, "addc",   addc_acr   },    /* addc     a, reg                  */

    { 0x40, 0xff, 0x00, 0x0, 0x0, 2, "jc",     jc_off     },    /* jc       offset                  */
    { 0x42, 0xff, 0x00, 0x0, 0x0, 2, "orl",    orl_dia    },    /* orl      direct, a               */
    { 0x43, 0xff, 0x00, 0x0, 0x0, 3, "orl",    orl_dii    },    /* orl      direct, #immed          */
    { 0x44, 0xff, 0x00, 0x0, 0x0, 2, "orl",    orl_aci    },    /* orl      a, #immed               */
    { 0x45, 0xff, 0x00, 0x0, 0x0, 2, "orl",    orl_acd    },    /* orl      a, direct               */
    { 0x46, 0xf0, 0x0f, 0x6, 0x7, 1, "orl",    orl_atr    },    /* orl      a, @reg                 */
    { 0x48, 0xf0, 0x0f, 0x8, 0xf, 1, "orl",    orl_acr    },    /* orl      a, reg                  */

    { 0x50, 0xff, 0x00, 0x0, 0x0, 2, "jnc",    jnc_off    },    /* jnc      offset                  */
    { 0x52, 0xff, 0x00, 0x0, 0x0, 2, "anl",    anl_dia    },    /* anl      direct, a               */
    { 0x53, 0xff, 0x00, 0x0, 0x0, 3, "anl",    anl_dii    },    /* anl      direct, #immed          */
    { 0x54, 0xff, 0x00, 0x0, 0x0, 2, "anl",    anl_aci    },    /* anl      a, #immed               */
    { 0x55, 0xff, 0x00, 0x0, 0x0, 2, "anl",    anl_acd    },    /* anl      a, direct               */
    { 0x56, 0xf0, 0x0f, 0x6, 0x7, 1, "anl",    anl_atr    },    /* anl      a, @reg                 */
    { 0x58, 0xf0, 0x0f, 0x8, 0xf, 1, "anl",    anl_acr    },    /* anl      a, reg                  */

    { 0x60, 0xff, 0x00, 0x0, 0x0, 2, "jz",     jz_off     },    /* jz       offset                  */
    { 0x62, 0xff, 0x00, 0x0, 0x0, 2, "xrl",    xrl_dia    },    /* xrl      direct, a               */
    { 0x63, 0xff, 0x00, 0x0, 0x0, 3, "xrl",    xrl_dii    },    /* xrl      direct, #immed          */
    { 0x64, 0xff, 0x00, 0x0, 0x0, 2, "xrl",    xrl_aci    },    /* xrl      a, #immed               */
    { 0x65, 0xff, 0x00, 0x0, 0x0, 2, "xrl",    xrl_acd    },    /* xrl      a, direct               */
    { 0x66, 0xf0, 0x0f, 0x6, 0x7, 1, "xrl",    xrl_atr    },    /* xrl      a, @reg                 */
    { 0x68, 0xf0, 0x0f, 0x8, 0xf, 1, "xrl",    xrl_acr    },    /* xrl      a, reg                  */

    { 0x70, 0xff, 0x00, 0x0, 0x0, 2, "jnz",    jnz_off    },    /* jnz      offset                  */
    { 0x72, 0xff, 0x00, 0x0, 0x0, 2, "orl",    orl_cob    },    /* orl      c, bit                  */
    { 0x73, 0xff, 0x00, 0x0, 0x0, 1, "jmp",    jmp_tad    },    /* jmp      @a+dptr                 */
    { 0x74, 0xff, 0x00, 0x0, 0x0, 2, "mov",    mov_aci    },    /* mov      a, #immed               */
    { 0x75, 0xff, 0x00, 0x0, 0x0, 3, "mov",    mov_dii    },    /* mov      direct, #immed          */
    { 0x76, 0xf0, 0x0f, 0x6, 0x7, 2, "mov",    mov_tri    },    /* mov      @reg, #immed            */
    { 0x78, 0xf0, 0x0f, 0x8, 0xf, 2, "mov",    mov_rei    },    /* mov      reg, #immed             */

    { 0x80, 0xff, 0x00, 0x0, 0x0, 2, "sjmp",   sjmp_off   },    /* sjmp     offset                  */
    { 0x82, 0xff, 0x00, 0x0, 0x0, 2, "anl",    anl_cob    },    /* anl      c, bit                  */
    { 0x83, 0xff, 0x00, 0x0, 0x0, 1, "movc",   movc_atc   },    /* movc     a, @a+pc                */
    { 0x84, 0xff, 0x00, 0x0, 0x0, 1, "div",    div_acb    },    /* div      ab                      */
    { 0x85, 0xff, 0x00, 0x0, 0x0, 3, "mov",    mov_did    },    /* mov      direct, direct          */
    { 0x86, 0xf0, 0x0f, 0x6, 0x7, 2, "mov",    mov_dtr    },    /* mov      direct, @reg            */
    { 0x88, 0xf0, 0x0f, 0x8, 0xf, 2, "mov",    mov_dre    },    /* mov      direct, reg             */

    { 0x90, 0xff, 0x00, 0x0, 0x0, 3, "mov",    mov_pti    },    /* mov      dptr, #immed            */
    { 0x92, 0xff, 0x00, 0x0, 0x0, 2, "mov",    mov_bic    },    /* mov      bit, c                  */
    { 0x93, 0xff, 0x00, 0x0, 0x0, 1, "movc",   movc_ata   },    /* movc     a, @a+dptr              */
    { 0x94, 0xff, 0x00, 0x0, 0x0, 2, "subb",   subb_aci   },    /* subb     a, #immed               */
    { 0x95, 0xff, 0x00, 0x0, 0x0, 2, "subb",   subb_acd   },    /* subb     a, direct               */
    { 0x96, 0xf0, 0x0f, 0x6, 0x7, 1, "subb",   subb_atr   },    /* subb     a, @reg                 */
    { 0x98, 0xf0, 0x0f, 0x8, 0xf, 1, "subb",   subb_acr   },    /* subb     a, reg                  */

    { 0xa0, 0xff, 0x00, 0x0, 0x0, 2, "orl",    orl_cox    },    /* orl      c, /bit                 */
    { 0xa2, 0xff, 0x00, 0x0, 0x0, 2, "mov",    mov_cob    },    /* mov      c, bit                  */
    { 0xa3, 0xff, 0x00, 0x0, 0x0, 1, "inc",    inc_ptr    },    /* inc      dptr                    */
    { 0xa4, 0xff, 0x00, 0x0, 0x0, 1, "mul",    mul_acb    },    /* mul      ab                      */
    { 0xa6, 0xf0, 0x0f, 0x0, 0x0, 2, "mov",    mov_trd    },    /* mov      @reg, direct            */
    { 0xa8, 0xf0, 0x0f, 0x0, 0x0, 2, "mov",    mov_red    },    /* mov      reg, direct             */

    { 0xb0, 0xff, 0x00, 0x0, 0x0, 2, "anl",    anl_cox    },    /* anl      c, /bit                 */
    { 0xb2, 0xff, 0x00, 0x0, 0x0, 2, "cpl",    cpl_bit    },    /* cpl      bit                     */
    { 0xb3, 0xff, 0x00, 0x0, 0x0, 1, "cpl",    cpl_con    },    /* cpl      c                       */
    { 0xb4, 0xff, 0x00, 0x0, 0x0, 3, "cjne",   cjne_aio   },    /* cjne     a, #immed, offset       */
    { 0xb5, 0xff, 0x00, 0x0, 0x0, 3, "cjne",   cjne_ado   },    /* cjne     a, direct, offset       */
    { 0xb6, 0xf0, 0x0f, 0x6, 0x7, 3, "cjne",   cjne_tio   },    /* cjne     @reg, #immed, offset    */
    { 0xb8, 0xf0, 0x0f, 0x8, 0xf, 3, "cjne",   cjne_rio   },    /* cjne     reg, #immed, offset     */

    { 0xc0, 0xff, 0x00, 0x0, 0x0, 2, "push",   push_dir   },    /* push     direct                  */
    { 0xc2, 0xff, 0x00, 0x0, 0x0, 2, "clr",    clr_bit    },    /* clr      bit                     */
    { 0xc3, 0xff, 0x00, 0x0, 0x0, 1, "clr",    clr_con    },    /* clr      c                       */
    { 0xc4, 0xff, 0x00, 0x0, 0x0, 1, "swap",   swap_acc   },    /* swap     a                       */
    { 0xc5, 0xff, 0x00, 0x0, 0x0, 2, "xch",    xch_acd    },    /* xch      a, direct               */
    { 0xc6, 0xf0, 0x0f, 0x6, 0x7, 1, "xch",    xch_atr    },    /* xch      a, @reg                 */
    { 0xc8, 0xf0, 0x0f, 0x8, 0xf, 1, "xch",    xch_acr    },    /* xch      a, reg                  */

    { 0xd0, 0xff, 0x00, 0x0, 0x0, 2, "pop",    pop_dir    },    /* pop      direct                  */
    { 0xd2, 0xff, 0x00, 0x0, 0x0, 2, "setb",   setb_bit   },    /* setb     bit                     */
    { 0xd3, 0xff, 0x00, 0x0, 0x0, 1, "setb",   setb_con   },    /* setb     c                       */
    { 0xd4, 0xff, 0x00, 0x0, 0x0, 1, "da",     da_acc     },    /* da       a                       */
    { 0xd5, 0xff, 0x00, 0x0, 0x0, 3, "djnz",   djnz_dio   },    /* djnz     direct, offset          */
    { 0xd6, 0xf0, 0x0f, 0x6, 0x7, 1, "xchd",   xchd_atr   },    /* xchd     a, @reg                 */
    { 0xd8, 0xf0, 0x0f, 0x8, 0xf, 2, "djnz",   djnz_reo   },    /* djnz     reg, offset             */

    { 0xe0, 0xff, 0x00, 0x0, 0x0, 1, "movx",   movx_atp   },    /* movx     a, @dptr                */
    { 0xe2, 0xfc, 0x03, 0x2, 0x3, 1, "movx",   movx_acr   },    /* movx     a, @reg                 */
    { 0xe4, 0xff, 0x00, 0x0, 0x0, 1, "clr",    clr_acc    },    /* clr      a                       */
    { 0xe5, 0xff, 0x00, 0x0, 0x0, 2, "mov",    mov_acd    },    /* mov      a, direct               */
    { 0xe6, 0xf0, 0x0f, 0x6, 0x7, 1, "mov",    mov_atr    },    /* mov      a, @reg                 */
    { 0xe8, 0xf0, 0x0f, 0x8, 0xf, 1, "mov",    mov_acr    },    /* mov      a, reg                  */

    { 0xf0, 0xff, 0x00, 0x0, 0x0, 1, "movx",   movx_tpa   },    /* movx     @dptr, a                */
    { 0xf2, 0xfc, 0x03, 0x2, 0x3, 1, "movx",   movx_tra   },    /* movx     @reg, a                 */
    { 0xf4, 0xff, 0x00, 0x0, 0x0, 1, "cpl",    cpl_acc    },    /* cpl      a                       */
    { 0xf5, 0xff, 0x00, 0x0, 0x0, 2, "mov",    mov_dia    },    /* mov      direct, a               */
    { 0xf6, 0xf0, 0x0f, 0x6, 0x7, 1, "mov",    mov_tra    },    /* mov      @reg, a                 */
    { 0xf8, 0xf0, 0x0f, 0x8, 0xf, 1, "mov",    mov_rea    },    /* mov      reg, a                  */
};


static void mcs51_tr_init_disas_context(DisasContextBase *dcbase, CPUState *cs)
{

}

static void mcs51_tr_tb_start(DisasContextBase *db, CPUState *cpu)
{
    /* Nothing */
}

static void mcs51_tr_insn_start(DisasContextBase *dcbase, CPUState *cpu)
{
    tcg_gen_insn_start(dcbase->pc_next);
}

static void mcs51_tr_translate_insn(DisasContextBase *dcbase, CPUState *cs)
{
    DisasContext *ctx = container_of(dcbase, DisasContext, base);
    CPUMCS51State *env = cs->env_ptr;
    const struct mcs51_ops *walk, *ops;
    unsigned int count, tmp;
    uint8_t opcode;

    opcode = cpu_ldub_code(env, ctx->npc++);

    for (count = 0, ops = NULL; count < ARRAY_SIZE(mcs51_table); ++count) {
        walk = &mcs51_table[count];
        if ((walk->opcode ^ opcode) & walk->mask)
            continue;

        tmp = opcode & walk->reg;
        if (tmp < walk->min || walk->max < tmp)
            continue;

        ops = walk;
    }

    ops->operate(env, ctx);
}

static void mcs51_tr_tb_stop(DisasContextBase *dcbase, CPUState *cs)
{

}

static void mcs51_tr_disas_log(const DisasContextBase *dcbase, CPUState *cpu)
{
    qemu_log("IN: %s\n", lookup_symbol(dcbase->pc_first));
    log_target_disas(cpu, dcbase->pc_first, dcbase->tb->size);
}

static const TranslatorOps mcs51_tr_ops = {
    .init_disas_context = mcs51_tr_init_disas_context,
    .tb_start           = mcs51_tr_tb_start,
    .insn_start         = mcs51_tr_insn_start,
    .translate_insn     = mcs51_tr_translate_insn,
    .tb_stop            = mcs51_tr_tb_stop,
    .disas_log          = mcs51_tr_disas_log,
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
