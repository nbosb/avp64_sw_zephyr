#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <app/drivers/vcml_simdev.h>

#define STACKSIZE 2048
#define PRIORITY  7

LOG_MODULE_REGISTER(main);

// devices
static const struct device* simdev = DEVICE_DT_GET(DT_NODELABEL(simdev));

int init() {
    if (!device_is_ready(simdev)) {
        LOG_ERR("simdev not ready");
        return 1;
    }

    return 0;
}

int main() {
    int init_ret = init();
    if (init_ret != 0)
        return init_ret;

    LOG_INF("Hello World");
    LOG_INF("Stopping in 1s...");
    log_flush();
    k_sleep(K_MSEC(1000));

    vcml_simdev_stop(simdev);
    return 0;
}
