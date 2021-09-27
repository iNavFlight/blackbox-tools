#ifndef BATTERY_H_
#define BATTERY_H_

typedef struct currentMeterState_t {
    uint64_t lastTime;

    double energyMilliampHours;
    int32_t currentMilliamps;
} currentMeterState_t;

extern void currentMeterInit(currentMeterState_t *state);
extern void currentMeterUpdateVirtual(currentMeterState_t *state, int16_t currentMeterOffset, int16_t currentMeterScale, uint32_t throttle, uint64_t time);
extern void currentMeterUpdateMeasured(currentMeterState_t *state, int amperageMilliamps, uint64_t time);

#endif
