#include "blackbox_fielddefs.h"
#include <stdlib.h>

const char * const FLIGHT_LOG_FLIGHT_MODE_NAME[] = {
    "ANGLE_MODE",
    "HORIZON_MODE",
    "MAG",
    "BARO",
    "GPS_HOME",
    "GPS_HOLD",
    "HEADFREE",
    "AUTOTUNE",
    "PASSTHRU",
    "SONAR",
    NULL
};

const char * const FLIGHT_LOG_FLIGHT_MODE_NAME_BETAFLIGHT[] = {
    "ARM",
    "ANGLE",
    "HORIZON",
    "MAG",
    "HEADFREE",
    "PASSTHRU",
    "FAILSAFE",
    "GPSRESCUE",
    "GPSRESCUE",
    "ANTIGRAVITY",
    "HEADADJ",
    "CAMSTAB",
    "BEEPERON",
    "LEDLOW",
    "CALIB",
    "OSD",
    "TELEMETRY",
    "SERVO1",
    "SERVO2",
    "SERVO3",
    "BLACKBOX",
    "AIRMODE",
    "3D",
    "FPVANGLEMIX",
    "BLACKBOXERASE",
    "CAMERA1",
    "CAMERA2",
    "CAMERA3",
    "FLIPOVERAFTERCRASH",
    "PREARM",
    "BEEPGPSCOUNT",
    "VTXPITMODE",
    "PARALYZE",
    "USER1",
    "USER2",
    "USER3",
    "USER4",
    "PIDAUDIO",
    "ACROTRAINER",
    "VTXCONTROLDISABLE",
    "LAUNCHCONTROL",
    NULL
};

const char * const FLIGHT_LOG_FLIGHT_MODE_NAME_INAV[] = {
    "ARM",	// 0
    "ANGLE",	// 1
    "HORIZON",	// 2
    "NAVALTHOLD",	// 3
    "HEADINGHOLD",	// 4
    "HEADFREE",	// 5
    "HEADADJ",	// 6
    "CAMSTAB",	// 7
    "NAVRTH",	// 8
    "NAVPOSHOLD",	// 9
    "MANUAL",	// 10
    "BEEPERON",	// 11
    "LEDLOW",	// 12
    "LIGHTS",	// 13
    "NAVLAUNCH",	// 14
    "OSD",	// 15
    "TELEMETRY",	// 16
    "BLACKBOX",	// 17
    "FAILSAFE",	// 18
    "NAVWP",	// 19
    "AIRMODE",	// 20
    "HOMERESET",	// 21
    "GCSNAV",	// 22
    "KILLSWITCH",	// 23
    "SURFACE",	// 24
    "FLAPERON",	// 25
    "TURNASSIST",	// 26
    "AUTOTRIM",	// 27
    "AUTOTUNE",	// 28
    "CAMERA1",	// 29
    "CAMERA2",	// 30
    "CAMERA3",	// 31
    "OSDALT1",	// 32
    "OSDALT2",	// 33
    "OSDALT3",	// 34
    "NAVCOURSEHOLD",	// 35
    "BRAKING",	// 36
    "USER1",	// 37
    "USER2",	// 38
    "FPVANGLEMIX",	// 39
    "LOITERDIRCHN",	// 40
    "MSPRCOVERRIDE",	// 41
    "PREARM",	// 42
    "TURTLE",	// 43
    "NAVCRUISE",	// 44
    "AUTOLEVEL",	// 45
    NULL
};

const char * const FLIGHT_LOG_FLIGHT_STATE_NAME[] = {
    "GPS_FIX_HOME",
    "GPS_FIX",
    "CALIBRATE_MAG",
    "SMALL_ANGLE",
    "FIXED_WING",
    NULL
};

const char * const FLIGHT_LOG_FLIGHT_STATE_NAME_INAV[] = {
    "GPS_FIX_HOME",
    "GPS_FIX",
    "CALIBRATE_MAG",
    "SMALL_ANGLE",
    "FIXED_WING",
    "ANTI_WINDUP",
    "FLAPERON_AVAILABLE",
    "NAV_MOTOR_STOP_OR_IDLE",
    "COMPASS_CALIBRATED",
    "ACCELEROMETER_CALIBRATED",
    "PWM_DRIVER_AVAILABLE",
    "NAV_CRUISE_BRAKING",
    "NAV_CRUISE_BRAKING_BOOST",
    "NAV_CRUISE_BRAKING_LOCKED",
    "NAV_EXTRA_ARMING_SAFETY_BYPASSED",
    "AIRMODE_ACTIVE",
    "ESC_SENSOR_ENABLED",
    "AIRPLANE",
    "MULTIROTOR",
    "ROVER",
    "BOAT",
    "ALTITUDE_CONTROL",
    "MOVE_FORWARD_ONLY",
    "SET_REVERSIBLE_MOTORS_FORWARD",
    "FW_HEADING_USE_YAW",
    "ANTI_WINDUP_DEACTIVATED",
    NULL
};

const char * const FLIGHT_LOG_FAILSAFE_PHASE_NAME[] = {
    "IDLE",
    "RX_LOSS_DETECTED",
    "RX_LOSS_IDLE",
    "RETURN_TO_HOME",
    "LANDING",
    "LANDED",
    "RX_LOSS_MONITORING",
    "RX_LOSS_RECOVERED"
};
