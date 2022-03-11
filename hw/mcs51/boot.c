/*
 * MCS51 loader helpers
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
#include "qemu-common.h"
#include "qemu/datadir.h"
#include "hw/loader.h"
#include "elf.h"
#include "boot.h"
#include "qemu/error-report.h"

bool mcs51_load_firmware(MCS51CPU *cpu, MachineState *ms, MemoryRegion *program_mr, const char *firmware)
{
    g_autofree char *filename;
    int bytes_loaded;
    uint64_t entry;
    uint32_t e_flags;

    filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, firmware);
    if (filename == NULL) {
        error_report("Unable to find %s", firmware);
        return true;
    }

    bytes_loaded = load_elf_ram_sym(
        filename, NULL, NULL, NULL, &entry, NULL, NULL,
        &e_flags, 0, EM_MCS51, 0, 0, NULL, true, NULL
    );

    if (bytes_loaded < 0)
        bytes_loaded = load_image_mr(filename, program_mr);

    else {

    }

    if (bytes_loaded < 0) {
        error_report("Unable to load firmware image %s as ELF or raw binary", firmware);
        return true;
    }

    return false;
}
