/******************************************************************************
 *                                                                            *
 * Copyright (C) 2025 Nils Bosbach                                            *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is work is licensed under the terms described in the LICENSE file     *
 * found in the root directory of this source tree.                           *
 *                                                                            *
 ******************************************************************************/

#ifndef APP_INCLUDE_APP_DRIVERS_VCML_SIMDEV_H_
#define APP_INCLUDE_APP_DRIVERS_VCML_SIMDEV_H_

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/** @cond INTERNAL_HIDDEN */

typedef void (*vcml_simdev_stop_t)(const struct device* dev);
typedef void (*vcml_simdev_exit_t)(const struct device* dev);
typedef void (*vcml_simdev_abort_t)(const struct device* dev);
typedef uint64_t (*vcml_simdev_sim_time_ps_t)(const struct device* dev);
typedef uint64_t (*vcml_simdev_host_time_us_t)(const struct device* dev);
typedef void (*vcml_simdev_write_stdout_t)(const struct device* dev,
                                           uint32_t val);
typedef void (*vcml_simdev_write_stderr_t)(const struct device* dev,
                                           uint32_t val);
typedef uint32_t (*vcml_simdev_prng_t)(const struct device* dev);

__subsystem struct vcml_simdev_driver_api {
    vcml_simdev_stop_t stop;
    vcml_simdev_exit_t exit;
    vcml_simdev_abort_t abort;
    vcml_simdev_sim_time_ps_t sim_time_ps;
    vcml_simdev_host_time_us_t host_time_us;
    vcml_simdev_write_stdout_t write_stdout;
    vcml_simdev_write_stderr_t write_stderr;
    vcml_simdev_prng_t prng;
};

/** @endcond */

__syscall void vcml_simdev_stop(const struct device* dev);

static inline void z_impl_vcml_simdev_stop(const struct device* dev) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    api->stop(dev);
}

__syscall void vcml_simdev_exit(const struct device* dev);

static inline void z_impl_vcml_simdev_exit(const struct device* dev) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    api->exit(dev);
}

__syscall void vcml_simdev_abort(const struct device* dev);

static inline void z_impl_vcml_simdev_abort(const struct device* dev) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    api->abort(dev);
}

__syscall uint64_t vcml_simdev_sim_time_ps(const struct device* dev);

static inline uint64_t z_impl_vcml_simdev_sim_time_ps(
    const struct device* dev) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    return api->sim_time_ps(dev);
}

__syscall uint64_t vcml_simdev_host_time_us(const struct device* dev);

static inline uint64_t z_impl_vcml_simdev_host_time_us(
    const struct device* dev) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    return api->host_time_us(dev);
}

__syscall void vcml_simdev_write_stdout(const struct device* dev,
                                        uint32_t val);

static inline void z_impl_vcml_simdev_write_stdout(const struct device* dev,
                                                   uint32_t val) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    api->write_stdout(dev, val);
}

__syscall void vcml_simdev_write_stderr(const struct device* dev,
                                        uint32_t val);

static inline void z_impl_vcml_simdev_write_stderr(const struct device* dev,
                                                   uint32_t val) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    api->write_stderr(dev, val);
}

__syscall uint32_t vcml_simdev_prng(const struct device* dev);

static inline uint32_t z_impl_vcml_simdev_prng(const struct device* dev) {
    const struct vcml_simdev_driver_api*
        api = (const struct vcml_simdev_driver_api*)dev->api;
    return api->prng(dev);
}

#include <syscalls/vcml_simdev.h>

#endif
