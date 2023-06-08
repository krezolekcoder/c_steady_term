#ifndef PLATFORM_PORT_H
#define PLATFORM_PORT_H
#include <stdint.h>

void platform_port_init(void);
void platform_port_send_frame_buffer(const char *char_buffer, int width, int height);

#endif /* PLATFORM_PORT_H */
