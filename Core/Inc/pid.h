#ifndef __PID_H
#define __PID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct
{
    float A0;
    float A1;
    float A2;

    float state[3];

    float Kp;
    float Ki;
    float Kd;

    float SP;

} arm_pid_instance_f32;

void pid_init(arm_pid_instance_f32 *S, float Kp, float Ki, float Kd);
void pid_setPoint(arm_pid_instance_f32 *S, float sp);
void pid_reset(arm_pid_instance_f32 *S);
float pid_cal(arm_pid_instance_f32 *S, float input);

#ifdef __cplusplus
}
#endif

#endif
