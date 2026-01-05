/******************************************************************************
 *                                                                            *
 * Copyright (C) 2025 Nils Bosbach                                            *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is work is licensed under the terms described in the LICENSE file     *
 * found in the root directory of this source tree.                           *
 *                                                                            *
 ******************************************************************************/

#define DT_DRV_COMPAT vcml_simdev

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <app/drivers/vcml_simdev.h>

#include "vcml_simdev_registers.h"

LOG_MODULE_REGISTER(vcml_simdev, CONFIG_VCML_SIMDEV_LOG_LEVEL);

struct vcml_simdev_config {
    DEVICE_MMIO_ROM;
};

struct vcml_simdev_data {
    DEVICE_MMIO_RAM;
};

void simdev_stop(const struct device* dev) {
    get_vcml_simdev(dev)->stop = 1;
}

void simdev_exit(const struct device* dev) {
    get_vcml_simdev(dev)->exit = 1;
}

void simdev_abort(const struct device* dev) {
    get_vcml_simdev(dev)->abrt = 1;
}

uint64_t simdev_sim_time_ps(const struct device* dev) {
    return get_vcml_simdev(dev)->sclk;
}

uint64_t simdev_host_time_us(const struct device* dev) {
    return get_vcml_simdev(dev)->hclk;
}

void simdev_write_stdout(const struct device* dev, uint32_t val) {
    get_vcml_simdev(dev)->sout = val;
}

void simdev_write_stderr(const struct device* dev, uint32_t val) {
    get_vcml_simdev(dev)->serr = val;
}

uint32_t simdev_prng(const struct device* dev) {
    return get_vcml_simdev(dev)->prng;
}

static const struct vcml_simdev_driver_api vcml_simdev_api = {
    .stop = simdev_stop,
    .exit = simdev_exit,
    .abort = simdev_abort,
    .sim_time_ps = simdev_sim_time_ps,
    .host_time_us = simdev_host_time_us,
    .write_stdout = simdev_write_stdout,
    .write_stderr = simdev_write_stderr,
    .prng = simdev_prng,
};

static int simdev_init(const struct device* dev) {
    DEVICE_MMIO_MAP(dev, K_MEM_CACHE_NONE);
    return 0;
}

#define VCML_SIMDEV_CONFIG(i)                                         \
    static const struct vcml_simdev_config vcml_simdev_config_##i = { \
        DEVICE_MMIO_ROM_INIT(DT_DRV_INST(i))                          \
    };

#define VCML_SIMDEV_DATA(i) \
    static struct vcml_simdev_data vcml_simdev_data_##i = {};

#define VCML_SIMDEV_DEFINE(i)                                                 \
    VCML_SIMDEV_DATA(i)                                                       \
    VCML_SIMDEV_CONFIG(i)                                                     \
                                                                              \
    DEVICE_DT_INST_DEFINE(                                                    \
        i, simdev_init, NULL, &vcml_simdev_data_##i, &vcml_simdev_config_##i, \
        POST_KERNEL, CONFIG_VCML_SIMDEV_INIT_PRIORITY, &vcml_simdev_api);

DT_INST_FOREACH_STATUS_OKAY(VCML_SIMDEV_DEFINE)
