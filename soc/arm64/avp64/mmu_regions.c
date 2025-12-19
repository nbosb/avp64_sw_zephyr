/******************************************************************************
 *                                                                            *
 * Copyright (C) 2025 Nils Bosbach                                            *
 * All Rights Reserved                                                        *
 *                                                                            *
 * This is work is licensed under the terms described in the LICENSE file     *
 * found in the root directory of this source tree.                           *
 *                                                                            *
 ******************************************************************************/

#include <zephyr/arch/arm64/arm_mmu.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/util.h>

static const struct arm_mmu_region mmu_regions[] = {

    MMU_REGION_FLAT_ENTRY(
        "GIC", DT_REG_ADDR_BY_IDX(DT_INST(0, arm_gic), 0),
        DT_REG_SIZE_BY_IDX(DT_INST(0, arm_gic), 0),
        MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE),

    MMU_REGION_FLAT_ENTRY(
        "GIC", DT_REG_ADDR_BY_IDX(DT_INST(0, arm_gic), 1),
        DT_REG_SIZE_BY_IDX(DT_INST(0, arm_gic), 1),
        MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE),
};

const struct arm_mmu_config mmu_config = {
    .num_regions = ARRAY_SIZE(mmu_regions),
    .mmu_regions = mmu_regions,
};
