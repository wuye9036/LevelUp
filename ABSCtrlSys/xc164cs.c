#include "xc164cs.h"


struct ecpu* create_cpu()
{
	struct ecpu* pcpu = (struct ecpu*)malloc(sizeof(struct ecpu));

	pcpu->main = cpu_main;

	pcpu->init_cpu = init_cpu;
	pcpu->init_abs = init_abs;

	pcpu->is_enable_abs = is_enable_abs;
	pcpu->check_valve = check_valve;
	pcpu->check_pump = check_pump;

	pcpu->alarm = alarm;

	pcpu->write_eeprom = write_eeprom;

	pcpu->get_braked_signal = get_braked_signal;

	pcpu->get_cpu_tick = get_cpu_tick;
	pcpu->measure_wheel_rotate_speed = measure_wheel_rotate_speed;
	pcpu->measure_slide_ratio = measure_slide_ratio;

	pcpu->read_eeprom = read_eeprom;

	pcpu->accommodate_brake_pressure = accommodate_brake_pressure;
	pcpu->compute_parameters = compute_parameters;

	pcpu->inc_pressure = inc_pressure;
	pcpu->keep_pressure = keep_pressure;
	pcpu->dec_pressure = dec_pressure;

	pcpu->on_idle = on_idle;

	//初始化变量
	memset(pcpu, 0, sizeof(struct ecpu));

	return pcpu;
}

void release_cpu(struct ecpu* pcpu)
{
	free(pcpu);
}

int cpu_main(struct ecpu* pcpu)
{
	pcpu->init_cpu(pcpu);

	while(1)
	{
		pcpu->init_abs(pcpu);
		pcpu->write_eeprom(pcpu);

		if (!pcpu->is_enable_abs(pcpu)
			|| !pcpu->get_braked_signal(pcpu)
			|| pcpu->car_speed < threshold_car_speed
			)
		{
			pcpu->shutdown_abs(pcpu);
			pcpu->is_braked = 0;
		} else {
			pcpu->is_braked = 1;

			pcpu->get_cpu_tick(pcpu);
			pcpu->brake_start_tick = pcpu->current_tick;

			pcpu->measure_wheel_rotate_speed(pcpu);
			pcpu->accommodate_brake_pressure(pcpu);
		}

		pcpu->compute_parameters(pcpu);
		pcpu->on_idle(pcpu);
	}

	return 1;
}

int init_cpu(struct ecpu* pcpu)
{
	return 1;
}

int init_abs(struct ecpu* pcpu)
{
	return 1;
}

int is_enable_abs(struct ecpu* pcpu)
{
	return pcpu->check_valve(pcpu) && pcpu->check_pump(pcpu);
}

int check_valve(struct ecpu* pcpu)
{
	return 1;
}

int check_pump(struct ecpu* pcpu)
{
	return 1;
}

int alarm(struct ecpu* pcpu, int is_alarm)
{
	return 1;
}

int write_eeprom(struct ecpu* pcpu){
	return 1;
}

int get_braked_signal(struct ecpu* pcpu){
	//need implementation for fecthing braking signal.
	return 1;
}

int get_cpu_tick(struct ecpu* pcpu)
{
	//need implementation for getting clock ticks,
	//and store the result into variable pcpu->current_tick.
	return 0;
}

int measure_wheel_rotate_speed(struct ecpu* pcpu){
	//set to slide_ratio
	return 1;
}

int measure_slide_ratio(struct ecpu* pcpu)
{
	//calculating car speed and then transfer to variable pcpu->slide_ratio.
	//note that the unit of speed must be right.

	return 1;
}

int read_eeprom(struct ecpu* pcpu){
	return 1;
}

int accommodate_brake_pressure(struct ecpu* pcpu){
	//状态机，表示ABS在不同过程下的不同动作。需要仔细调试。
	int i_wheel = FRONT_LEFT_WHEEL;
	for (i_wheel = FRONT_LEFT_WHEEL; i_wheel <= BACK_RIGHT_WHEEL; ++i_wheel)
	{
		switch (pcpu->braking_stage[i_wheel])
		{
			case 0:
				if (pcpu->wheel_rotate_acceleration[i_wheel] < threshold_negative_acceleration)
				{
					pcpu->keep_pressure(pcpu, i_wheel);
					pcpu->braking_stage[i_wheel] = 1;
				}
				break;
			case 1:
				if (pcpu->slide_ratio[i_wheel] > threshold_slide_ratio)
				{
					pcpu->dec_pressure(pcpu, i_wheel);
				} else {
					pcpu->braking_stage[i_wheel] = 2;
				}
				break;
			case 2:
				if (pcpu->wheel_rotate_acceleration[i_wheel] > threshold_negative_acceleration){
					pcpu->keep_pressure(pcpu, i_wheel);
					pcpu->braking_stage[i_wheel] = 3;
				}
				break;
			case 3:
				if(pcpu->wheel_rotate_acceleration[i_wheel] > threshold_positive_acceleration)
				{
					pcpu->inc_pressure(pcpu, i_wheel);
				} else {
					pcpu->braking_stage[i_wheel] = 4;
				}
				break;
			case 4:
				if(pcpu->wheel_rotate_acceleration[i_wheel] < threshold_positive_acceleration)
				{
					pcpu->keep_pressure(pcpu, i_wheel);
					pcpu->braking_stage[i_wheel] = 5;
				}
				break;
			case 5:
				if(pcpu->wheel_rotate_acceleration[i_wheel] < -threshold_negative_acceleration)
				{
					pcpu->keep_pressure(pcpu, i_wheel);
					pcpu->braking_stage[i_wheel] = 6;
				}
				break;
			case 6:
				if(pcpu->wheel_rotate_acceleration[i_wheel] > threshold_negative_acceleration)
				{
					pcpu->inc_pressure(pcpu, i_wheel);
					pcpu->braking_stage[i_wheel] = 5;
				} else {
					pcpu->braking_stage[i_wheel] = 0;
				}
	    }
	}
	return 1;
}

int compute_parameters(struct ecpu* pcpu)
{
	//car_speed, acceleration and slide ratio.
	if (pcpu->is_braked)
	{
		pcpu->get_cpu_tick(pcpu);
		pcpu->car_speed = pcpu->origin_car_speed - (pcpu->current_tick - pcpu->brake_start_tick) * speed_slope;
	}

	pcpu->measure_wheel_rotate_speed(pcpu);

	int i_wheel = 0;
	for(i_wheel = 0; i_wheel < 4; ++i_wheel)
	{
		pcpu->wheel_rotate_acceleration[i_wheel] = pcpu->wheel_rotate_speed[i_wheel] - pcpu->wheel_rotate_speed_old[i_wheel];
		pcpu->wheel_rotate_speed_old[i_wheel] = pcpu->wheel_rotate_speed[i_wheel];
	}

	//slide_ratio
	pcpu->measure_slide_ratio(pcpu);

	return 1;
}

int inc_pressure(struct ecpu* pcpu, int i_wheel)
{
	//need implementation
	return 1;
}

int dec_pressure(struct ecpu* pcpu, int i_wheel)
{
	//need implementation
	return 1;
}

int keep_pressure(struct ecpu* pcpu, int i_wheel)
{
	//need implementation
	return 1;
}

int on_idle(struct ecpu* pcpu)
{
	pcpu->get_cpu_tick(pcpu);
	while (pcpu->current_tick - pcpu->last_cycle_tick < ticks_per_cycle)
	{
		pcpu->get_cpu_tick(pcpu);
		//execute nop instruction for makeing cpu works with null load.
	}
	pcpu->last_cycle_tick = pcpu->current_tick;
	return 1;
}
