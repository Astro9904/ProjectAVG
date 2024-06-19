#pragma once

int main();

void init(void);
void AGV_Loop();
void PFM_Loop();
void init_motoren(void);
void linker_motor_snelheid(int snelheid);
void rechter_motor_snelheid(int snelheid);
void linker_motor_vooruit(void);
void linker_motor_achteruit(void);
void linker_motor_uit(void);
void rechter_motor_achteruit(void);
void rechter_motor_vooruit(void);
void rechter_motor_uit(void);

int SonarSensorenDetectie(void);


enum modeSelectorModes {
	AGV = 0,
	PFM = 1 
};
