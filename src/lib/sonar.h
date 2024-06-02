#pragma once

#include "customio.h"
#include <stdint.h>

typedef struct {
	uint8_t id;
	IO_t trigpin;
	IO_t echopin;
	int32_t lastResult;
} SONAR_t;


void SonarInit(SONAR_t *sonarObject, IO_t *trigpin, IO_t *echopin);

void SonarGetDistance(SONAR_t *sonarObject);
