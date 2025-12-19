 ##############################################################################
 #                                                                            #
 # Copyright (C) 2025 Nils Bosbach                                            #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

cmake_minimum_required(VERSION 3.20)

set(DTC_OVERLAY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/boards/avp64.overlay")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

target_sources(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

target_include_directories(app PRIVATE include)
