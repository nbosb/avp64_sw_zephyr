/******************************************************************************
 *                                                                            *
 * Copyright (C) 2025 Nils Bosbach                                            *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is work is licensed under the terms described in the LICENSE file     *
 * found in the root directory of this source tree.                           *
 *                                                                            *
 ******************************************************************************/

#ifndef DRIVERS_VCML_SIMDEV_REGISTERS_H_
#define DRIVERS_VCML_SIMDEV_REGISTERS_H_

#include <zephyr/device.h>

struct vcml_simdev_regs {
    // simulation control
    uint32_t stop; // 0x00
    uint8_t reserved0[4];
    uint32_t exit; // 0x08
    uint8_t reserved1[4];
    uint32_t abrt; // 0x10
    uint8_t reserved2[4];

    // timing
    uint64_t sclk; // 0x18
    uint64_t hclk; // 0x20

    // output
    uint32_t sout; // 0x28
    uint8_t reserved3[4];
    uint32_t serr; // 0x30
    uint8_t reserved4[4];

    // random
    uint32_t prng; // 0x38
};

static inline volatile struct vcml_simdev_regs* get_vcml_simdev(
    const struct device* dev) {
    return (volatile struct vcml_simdev_regs*)DEVICE_MMIO_GET(dev);
}

#endif
