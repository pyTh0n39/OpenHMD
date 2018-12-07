// Copyright 2018, Philipp Zabel.
// SPDX-License-Identifier: BSL-1.0
/*
 * OpenHMD - Free and Open Source API and drivers for immersive technology.
 */

/* Windows Mixed Reality Driver */


#ifndef WMR_H
#define WMR_H

#include <stdint.h>
#include <stdbool.h>

#include "../openhmdi.h"

#define MICROSOFT_VID         0x045e
#define HOLOLENS_SENSORS_PID  0x0659
#define MOTION_CONTROLLER_PID 0x065b

typedef enum
{
	HOLOLENS_IRQ_SENSORS = 1,
	HOLOLENS_IRQ_CONTROL = 2,
	HOLOLENS_IRQ_DEBUG = 3,
} hololens_sensors_irq_cmd;

typedef enum
{
	CONTROLLER_IRQ_SENSORS = 1,
} motion_controller_irq_cmd;

typedef struct
{
        uint8_t id;
        uint16_t temperature[4];
        uint64_t gyro_timestamp[4];
        int16_t gyro[3][32];
        uint64_t accel_timestamp[4];
        int32_t accel[3][4];
        uint64_t video_timestamp[4];
} hololens_sensors_packet;

#define MOTION_CONTROLLER_BUTTON_STICK     0x01
#define MOTION_CONTROLLER_BUTTON_WINDOWS   0x02
#define MOTION_CONTROLLER_BUTTON_MENU      0x04
#define MOTION_CONTROLLER_BUTTON_GRIP      0x08
#define MOTION_CONTROLLER_BUTTON_PAD_PRESS 0x10
#define MOTION_CONTROLLER_BUTTON_PAD_TOUCH 0x40

typedef struct
{
	uint8_t id;
	uint8_t buttons;
	uint16_t stick[2];
	uint8_t trigger;
	uint8_t touchpad[2];
	uint8_t battery;
	int32_t accel[3];
	int32_t gyro[3];
	uint32_t timestamp;
} motion_controller_packet;

static const unsigned char hololens_sensors_imu_on[64] = {
	0x02, 0x07
};

static const unsigned char motion_controller_imu_on[64] = {
	0x06, 0x03, 0x01, 0x00, 0x02
};

bool hololens_sensors_decode_packet(hololens_sensors_packet* pkt, const unsigned char* buffer, int size);
bool motion_controller_decode_packet(motion_controller_packet* pkt, const unsigned char* buffer, int size);

ohmd_device* open_motion_controller_device(ohmd_driver* driver, ohmd_device_desc* desc);

#endif
