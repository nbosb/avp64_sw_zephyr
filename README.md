# Zephyr-based Application for AVP64

A Zephyr RTOS application for the [AVP64 ARM64 virtual platform](https://github.com/aut0/avp64) with custom [VCML](https://github.com/machineware-gmbh/vcml) simulation device (SIMDEV) driver support.

## Overview

This project provides a complete Zephyr RTOS application stack targeting the AVP64 ARM64 virtual platform. It includes:

- **Zephyr RTOS kernel** - Real-time operating system for embedded systems
- **AVP64 board support** - Device tree bindings and configurations for multiple CPU variants
- **VCML Simulation Device driver** - Custom driver for simulation control and monitoring
- **Hello World application** - Example application demonstrating system initialization and logging

## Features

### Board Variants

The AVP64 platform supports multiple CPU configurations:

- **avp64_x1** - 1 CPU variant
- **avp64_x2** - 2 CPU variant
- **avp64_x4** - 4 CPU variant
- **avp64_x8** - 8 CPU variant

### VCML Simulation Device (SIMDEV)

Custom driver for the [VCML SIMDEV](https://github.com/machineware-gmbh/vcml/blob/main/include/vcml/models/meta/simdev.h) peripheral providing:

- Simulation control (stop, exit, abort)
- Time monitoring (simulation time, host time)
- I/O operations (stdout, stderr)
- Heartbeat functionality
- Interrupt generation

## Building

### Prerequisites

- Docker (for containerized build)
- Linux-based development environment

### Quick Build

```bash
./build.sh
```

This script will:

1. Build a Docker image with the Zephyr SDK
1. Compile the application for all AVP64 variants
1. Generate kernel images in the `build/` and `images/` directories

### Manual Build (Inside Docker or with Zephyr SDK)

```bash
# Initialize west workspace
west init -m west.yml

# Update manifest
west update

# Build for specific configuration
west build -b avp64_avp64_x1 app/hello_world -d build/hello_worldx1
west build -b avp64_avp64_x2 app/hello_world -d build/hello_worldx2
west build -b avp64_avp64_x4 app/hello_world -d build/hello_worldx4
west build -b avp64_avp64_x8 app/hello_world -d build/hello_worldx8
```

## Configuration

### Project Configuration (prj.conf)

Key configuration options in [app/hello_world/prj.conf](app/hello_world/prj.conf):

- `CONFIG_VCML_SIMDEV=y` - Enable VCML simulation device driver
- `CONFIG_LOG=y` - Enable logging
- `CONFIG_LOG_DEFAULT_LEVEL=3` - Set default log level
- `CONFIG_KERNEL_VM_SIZE=0x80000000` - 2GB virtual memory
- `CONFIG_MINIMAL_LIBC=y` - Use minimal C library

### Device Tree Overlay

The device tree overlay in [app/hello_world/boards/avp64.overlay](app/hello_world/boards/avp64.overlay) configures the VCML simulation device binding.

## Application

The hello world application ([app/hello_world/src/main.c](app/hello_world/src/main.c)) demonstrates:

1. **Device Initialization** - Checking device readiness
1. **Logging** - Using Zephyr's logging subsystem
1. **Simulation Control** - Triggering simulation stop via VCML device
1. **Sleep Operations** - Using Zephyr kernel delays

## License

Copyright (C) 2025 Nils Bosbach. All Rights Reserved.

This work is licensed under the terms described in the [LICENSE](LICENSE) file found in the root directory of this source tree.
