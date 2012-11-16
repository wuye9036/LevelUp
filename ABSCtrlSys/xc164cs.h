#ifndef XC164CS_H
#define XC164CS_H

#include <malloc.h>
#include <memory.h>

#define FRONT_LEFT_WHEEL 0
#define FRONT_RIGHT_WHEEL 1
#define BACK_LEFT_WHEEL 2
#define BACK_RIGHT_WHEEL 3
struct ecpu;

static const int threshold_car_speed = 10000;//meter per hour
static const int ticks_per_cycle = 10000;
static const int threshold_positive_acceleration = 10000;
static const int threshold_negative_acceleration = 10000;
static const int threshold_slide_ratio = 10000;
static const int speed_slope = 10000;

struct ecpu{

	//properties

	int is_braked;

	int last_cycle_tick;
	int current_tick;

	int wheel_rotate_speed_old[4];
	int wheel_rotate_speed[4]; //
	int wheel_rotate_acceleration[4];

	int origin_car_speed;
	int brake_start_tick;

	int car_speed; //meter per hour
	int car_acceleration; //meter per hour
	int slide_ratio[4];

	int braking_stage[4];

	/////////////////////////////////
	//methods

	//main
	int (*main)(struct ecpu*);

	//cpu and abs controls
	int (*init_cpu)(struct ecpu*);
	int (*init_abs)(struct ecpu*);
	int (*write_eeprom)(struct ecpu* pcpu);

	int (*shutdown_abs)(struct ecpu*);

	//check abs state
	int (*is_enable_abs)(struct ecpu*);
	int (*check_valve)(struct ecpu*);
	int (*check_pump)(struct ecpu*);

	int (*alarm)(struct ecpu* pcpu, int is_alarm);

	int (*get_braked_signal)(struct ecpu*);

	//data measurement
	int (*get_cpu_tick)(struct ecpu*);
	int (*measure_wheel_rotate_speed)(struct ecpu*);
	int (*measure_slide_ratio)(struct ecpu*);

	int (*read_eeprom)(struct ecpu* pcpu);

	//compute and operations.
	int (*accommodate_brake_pressure)(struct ecpu* pcpu);
	int (*compute_parameters)(struct ecpu* pcpu);

	int (*inc_pressure)(struct ecpu* pcpu, int i_wheel);
	int (*dec_pressure)(struct ecpu* pcpu, int i_wheel);
	int (*keep_pressure)(struct ecpu* pcpu, int i_wheel);

	//on idle
	int (*on_idle)(struct ecpu* pcpu);
};

extern int cpu_main(struct ecpu* pcpu);

extern int init_cpu(struct ecpu*);
extern int init_abs(struct ecpu*);

extern int is_enable_abs(struct ecpu*);
extern int check_valve(struct ecpu*);
extern int check_pump(struct ecpu*);

extern int alarm(struct ecpu* pcpu, int is_alarm);
extern int write_eeprom(struct ecpu* pcpu);

extern int get_braked_signal(struct ecpu*);

extern int get_cpu_tick(struct ecpu*);
extern int measure_wheel_rotate_speed(struct ecpu*);
extern int measure_slide_ratio(struct ecpu*);

extern int read_eeprom(struct ecpu* pcpu);

extern int accommodate_brake_pressure(struct ecpu* pcpu);
extern int compute_parameters(struct ecpu* pcpu);

extern int inc_pressure(struct ecpu* pcpu, int i_wheel);
extern int dec_pressure(struct ecpu* pcpu, int i_wheel);
extern int keep_pressure(struct ecpu* pcpu, int i_wheel);

extern int on_idle(struct ecpu* pcpu);


extern struct ecpu* create_cpu();
extern void release_cpu(struct ecpu* pcpu);
#endif // XC164CS_H
