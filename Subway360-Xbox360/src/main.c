/*
 * Subway360 - Xbox 360 native port bootstrap
 *
 * This is a boot/display test using the public xsdk API.
 * It is NOT yet the Subway Surfers gameplay port. The Unity C# gameplay,
 * models, animations, materials and shaders still need native replacements.
 */
#include <stdint.h>
#include "xsdk/gpu.h"
#include "xsdk/kernel.h"
#include "xsdk/log.h"
#include "xsdk/present.h"
#include "xsdk/splash.h"

enum {
    BUFFER_COUNT = 2,
    SWAP_INTERVAL = 1,
    FRAME_CLEAR_ARGB = 0xFF101820,
    BEGIN_TIMEOUT_MS = 5000
};

int main(void)
{
    xsdk_log_write("Subway360: Xbox 360 native bootstrap starting");
    xsdk_log_write("Subway360: this build verifies XEX startup and display only");

    NTSTATUS status = xsdk_splash_show(1500);
    if (!NT_SUCCESS(status))
        xsdk_log_write("Subway360: splash unavailable: 0x%08X", (unsigned)status);

    status = xsdk_gpu_open();
    if (!NT_SUCCESS(status)) {
        xsdk_log_write("Subway360: xsdk_gpu_open failed: 0x%08X", (unsigned)status);
        return 1;
    }

    uint32_t width = 0;
    uint32_t height = 0;
    status = xsdk_present_open(XSDK_DISPLAY_720P, BUFFER_COUNT, SWAP_INTERVAL,
                               &width, &height);
    if (!NT_SUCCESS(status)) {
        xsdk_log_write("Subway360: xsdk_present_open failed: 0x%08X", (unsigned)status);
        (void)xsdk_gpu_close();
        return 1;
    }

    xsdk_log_write("Subway360: display %ux%u; press Back to exit",
                   (unsigned)width, (unsigned)height);

    for (;;) {
        INPUT_STATE input = {0};
        if (XamInputGetState(0, 0, &input) == ERROR_SUCCESS &&
            (input.gamepad.buttons & INPUT_GAMEPAD_BACK))
            break;

        uint32_t framebuffer = 0;
        status = xsdk_present_begin(&framebuffer, BEGIN_TIMEOUT_MS);
        if (!NT_SUCCESS(status)) {
            xsdk_log_write("Subway360: present begin failed: 0x%08X",
                           (unsigned)status);
            break;
        }

        /* Temporary clear screen. Subway Surfers rendering is not implemented yet. */
        xsdk_gpu_resolve(framebuffer, width, height, FRAME_CLEAR_ARGB);
        xsdk_present_end();
    }

    xsdk_present_close();
    status = xsdk_gpu_close();
    if (!NT_SUCCESS(status))
        xsdk_log_write("Subway360: gpu close failed: 0x%08X", (unsigned)status);

    xsdk_log_write("Subway360: bootstrap ended");
    return 0;
}
