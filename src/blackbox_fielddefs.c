#include "blackbox_fielddefs.h"
#include <stdlib.h>

/*
 * Please leave the INAV HEADER: comments intact
 * Please add new INAV HEADER: commeants for any new INAV items
 * The contents of section may then be regenerated from the
 * "tools/rcmodes.rb" (sic) script
 */

// Legacy, Cleanflight
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

const char * const FLIGHT_LOG_FLIGHT_MODE_NAME_INAV_LEGACY[] = {
    "ARM",              // 0
    "ANGLE",            // 1
    "HORIZON",          // 2
    "NAVALTHOLD",       // 3
    "HEADINGHOLD",      // 4
    "HEADFREE",         // 5
    "HEADADJ",          // 6
    "CAMSTAB",          // 7
    "NAVRTH",           // 8
    "NAVPOSHOLD",       // 9
    "MANUAL",           // 10
    "BEEPERON",         // 11
    "LEDLOW",           // 12
    "LIGHTS",           // 13
    "NAVLAUNCH",        // 14
    "OSD",              // 15
    "TELEMETRY",        // 16
    "BLACKBOX",         // 17
    "FAILSAFE",         // 18
    "NAVWP",            // 19
    "AIRMODE",          // 20
    "HOMERESET",        // 21
    "GCSNAV",           // 22
    "KILLSWITCH",       // 23
    "SURFACE",          // 24
    "FLAPERON",         // 25
    "TURNASSIST",       // 26
    "AUTOTRIM",         // 27
    "AUTOTUNE",         // 28
    "CAMERA1",          // 29
    "CAMERA2",          // 30
    "CAMERA3",          // 31
    "OSDALT1",          // 32
    "OSDALT2",          // 33
    "OSDALT3",          // 34
    "NAVCOURSEHOLD",    // 35
    "BRAKING",          // 36
    "USER1",            // 37
    "USER2",            // 38
    "FPVANGLEMIX",      // 39
    "LOITERDIRCHN",     // 40
    "MSPRCOVERRIDE",    // 41
    "PREARM",           // 42
    "TURTLE",           // 43
    "NAVCRUISE",        // 44
    "AUTOLEVEL",        // 45
    "PLANWPMISSION",    // 46
    "SOARING",          // 47
    "USER3",            // 48
    "USER4",            // 49,
    "CHANGEMISSION",    // 50
    "BEEPERMUTE",       // 51
    "MULTIFUNCTION",    // 52,
    "MIXERPROFILE",     // 53,
    "MIXERTRANSITION",  // 54
    "ANGLEHOLD", 	// 55
    NULL
};

// INAV HEADER: src/main/fc/rc_modes.h : boxId_e
const char * const FLIGHT_LOG_FLIGHT_MODE_NAME_INAV[] = {
    "ARM",		// 0
    "ANGLE",		// 1
    "HORIZON",		// 2
    "NAVALTHOLD",		// 3
    "HEADINGHOLD",		// 4
    "HEADFREE",		// 5
    "HEADADJ",		// 6
    "CAMSTAB",		// 7
    "NAVRTH",		// 8
    "NAVPOSHOLD",		// 9
    "MANUAL",		// 10
    "BEEPERON",		// 11
    "LEDLOW",		// 12
    "LIGHTS",		// 13
    "NAVLAUNCH",		// 14
    "OSD",		// 15
    "TELEMETRY",		// 16
    "BLACKBOX",		// 17
    "FAILSAFE",		// 18
    "NAVWP",		// 19
    "AIRMODE",		// 20
    "HOMERESET",		// 21
    "GCSNAV",		// 22
    "**REMOVED**",		// 23
    "SURFACE",		// 24
    "FLAPERON",		// 25
    "TURNASSIST",		// 26
    "AUTOTRIM",		// 27
    "AUTOTUNE",		// 28
    "CAMERA1",		// 29
    "CAMERA2",		// 30
    "CAMERA3",		// 31
    "OSDALT1",		// 32
    "OSDALT2",		// 33
    "OSDALT3",		// 34
    "NAVCOURSEHOLD",		// 35
    "BRAKING",		// 36
    "USER1",		// 37
    "USER2",		// 38
    "FPVANGLEMIX",		// 39
    "LOITERDIRCHN",		// 40
    "MSPRCOVERRIDE",		// 41
    "PREARM",		// 42
    "TURTLE",		// 43
    "NAVCRUISE",		// 44
    "AUTOLEVEL",		// 45
    "PLANWPMISSION",		// 46
    "SOARING",		// 47
    "USER3",		// 48
    "USER4",		// 49
    "CHANGEMISSION",		// 50
    "BEEPERMUTE",		// 51
    "MULTIFUNCTION",		// 52
    "MIXERPROFILE",		// 53
    "MIXERTRANSITION",		// 54
    "ANGLEHOLD",		// 55
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

// INAV HEADER: src/main/fc/runtime_config.h : stateFlags_t
const char * const FLIGHT_LOG_FLIGHT_STATE_NAME_INAV[] = {
    "GPS_FIX_HOME",             // 0
    "GPS_FIX",          // 1
    "CALIBRATE_MAG",            // 2
    "SMALL_ANGLE",              // 3
    "FIXED_WING_LEGACY",                // 4
    "ANTI_WINDUP",              // 5
    "FLAPERON_AVAILABLE",               // 6
    "NAV_MOTOR_STOP_OR_IDLE",           // 7
    "COMPASS_CALIBRATED",               // 8
    "ACCELEROMETER_CALIBRATED",         // 9
    "PWM_DRIVER_AVAILABLE",             // 10 (Obsoleted)
    "NAV_CRUISE_BRAKING",               // 11
    "NAV_CRUISE_BRAKING_BOOST",         // 12
    "NAV_CRUISE_BRAKING_LOCKED",                // 13
    "NAV_EXTRA_ARMING_SAFETY_BYPASSED",         // 14
    "AIRMODE_ACTIVE",           // 15
    "ESC_SENSOR_ENABLED",               // 16
    "AIRPLANE",         // 17
    "MULTIROTOR",               // 18
    "ROVER",            // 19
    "BOAT",             // 20
    "ALTITUDE_CONTROL",         // 21
    "MOVE_FORWARD_ONLY",                // 22
    "SET_REVERSIBLE_MOTORS_FORWARD",            // 23
    "FW_HEADING_USE_YAW",               // 24
    "ANTI_WINDUP_DEACTIVATED",          // 25
    "LANDING_DETECTED",                 // 26
    "IN_FLIGHT_EMERG_REARM",            // 27
    "TAILSITTER",			// 28
    NULL
};

// INAV HEADER: src/main/flight/failsafe.h : failsafePhase_e
const char * const FLIGHT_LOG_FAILSAFE_PHASE_NAME[] = {
    "IDLE",             // 0
    "RX_LOSS_DETECTED",         // 1
    "RX_LOSS_IDLE",             // 2
    "RETURN_TO_HOME",           // 3
    "LANDING",          // 4
    "LANDED",           // 5
    "RX_LOSS_MONITORING",               // 6
    "RX_LOSS_RECOVERED",                // 7
};

// INAV HEADER: src/main/fc/rc_adjustments.h : adjustmentFunction_e
const char * const INFLIGHT_ADJUSTMENT_FUNCTIONS[] = {
    "NONE",             // 0
    "RC_RATE",          // 1
    "RC_EXPO",          // 2
    "THROTTLE_EXPO",            // 3
    "PITCH_ROLL_RATE",          // 4
    "YAW_RATE",         // 5
    "PITCH_ROLL_P",             // 6
    "PITCH_ROLL_I",             // 7
    "PITCH_ROLL_D",             // 8
    "PITCH_ROLL_FF",            // 9
    "PITCH_P",          // 10
    "PITCH_I",          // 11
    "PITCH_D",          // 12
    "PITCH_FF",         // 13
    "ROLL_P",           // 14
    "ROLL_I",           // 15
    "ROLL_D",           // 16
    "ROLL_FF",          // 17
    "YAW_P",            // 18
    "YAW_I",            // 19
    "YAW_D",            // 20
    "YAW_FF",           // 21
    "RATE_PROFILE",             // 22
    "PITCH_RATE",               // 23
    "ROLL_RATE",                // 24
    "RC_YAW_EXPO",              // 25
    "MANUAL_RC_EXPO",           // 26
    "MANUAL_RC_YAW_EXPO",               // 27
    "MANUAL_PITCH_ROLL_RATE",           // 28
    "MANUAL_ROLL_RATE",         // 29
    "MANUAL_PITCH_RATE",                // 30
    "MANUAL_YAW_RATE",          // 31
    "NAV_FW_CRUISE_THR",                // 32
    "NAV_FW_PITCH2THR",         // 33
    "ROLL_BOARD_ALIGNMENT",             // 34
    "PITCH_BOARD_ALIGNMENT",            // 35
    "LEVEL_P",          // 36
    "LEVEL_I",          // 37
    "LEVEL_D",          // 38
    "POS_XY_P",         // 39
    "POS_XY_I",         // 40
    "POS_XY_D",         // 41
    "POS_Z_P",          // 42
    "POS_Z_I",          // 43
    "POS_Z_D",          // 44
    "HEADING_P",                // 45
    "VEL_XY_P",         // 46
    "VEL_XY_I",         // 47
    "VEL_XY_D",         // 48
    "VEL_Z_P",          // 49
    "VEL_Z_I",          // 50
    "VEL_Z_D",          // 51
    "FW_MIN_THROTTLE_DOWN_PITCH_ANGLE",         // 52
    "VTX_POWER_LEVEL",          // 53
    "TPA",              // 54
    "TPA_BREAKPOINT",           // 55
    "NAV_FW_CONTROL_SMOOTHNESS",                // 56
    "FW_TPA_TIME_CONSTANT",             // 57
    "FW_LEVEL_TRIM",            // 58
    "NAV_WP_MULTI_MISSION_INDEX",               // 59
/* 60 elements */
};
