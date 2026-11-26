#include "pid.h"

void pid_init(arm_pid_instance_f32 *S, float Kp, float Ki, float Kd)
{
    S->Kp = Kp;
    S->Ki = Ki;
    S->Kd = Kd;

    S->A0 = Kp + Ki + Kd;
    S->A1 = -Kp - 2 * Kd;
    S->A2 = Kd;

    S->state[0] = 0;
    S->state[1] = 0;
    S->state[2] = 0;

    S->SP = 0;
}

void pid_setPoint(arm_pid_instance_f32 *S, float sp)
{
    S->SP = sp;
}

void pid_reset(arm_pid_instance_f32 *S)
{
    S->state[0] = 0;
    S->state[1] = 0;
    S->state[2] = 0;
}

float pid_cal(arm_pid_instance_f32 *S, float input)
{
    float err;
    float out;

    err = S->SP - input;

    out = S->A0 * err
        + S->A1 * S->state[0]
        + S->A2 * S->state[1]
        + S->state[2];

    S->state[1] = S->state[0];
    S->state[0] = err;
    S->state[2] = out;

    return out;
}
