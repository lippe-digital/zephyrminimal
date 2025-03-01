#include <zephyr.h>
#include <drivers/led_strip.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(main);

void main(void) {
    const struct device *led_strip = DEVICE_DT_GET(DT_ALIAS(led_strip));

    if (!device_is_ready(led_strip)) {
        LOG_ERR("LED strip device not ready");
        return;
    }

    LOG_INF("LED strip initialized");

    struct led_rgb pixels[10] = {0};

    while (1) {
        // Set all LEDs to red
        for (int i = 0; i < 10; i++) {
            pixels[i].r = 255;
            pixels[i].g = 0;
            pixels[i].b = 0;
        }
        led_strip_update_rgb(led_strip, pixels, 10);

        k_sleep(K_MSEC(1000));

        // Turn off all LEDs
        for (int i = 0; i < 10; i++) {
            pixels[i].r = 0;
            pixels[i].g = 0;
            pixels[i].b = 0;
        }
        led_strip_update_rgb(led_strip, pixels, 10);

        k_sleep(K_MSEC(1000));
    }
}
