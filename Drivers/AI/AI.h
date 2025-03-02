/*
 * AI.h
 *
 *  Created on: Feb 28, 2025
 *      Author: Ayoub
 */

#ifndef AI_AI_H_
#define AI_AI_H_
#include "Accelerometer.h"
#include "NanoEdgeAI.h"
#include "string.h"
#define AXIS 6
#define SAMPLES 256

extern const float knowledge[];

//  Buffer for AI model input (corrected)
static float neai_buffer[AXIS_NUMBER * DATA_INPUT_USER]; // AXIS * SAMPLES

//  Buffer for model output
static float output_class_buffer[CLASS_NUMBER];

//  ID for detected class
static uint16_t id_class = 0;

//  Pointer tracking buffer position
static uint16_t neai_buffer_ptr = 0;

const char *id2class[CLASS_NUMBER + 1] = { // Buffer for mapping class id to class name
	"unknown",
	"haut_poser_sur_table",
	"pas_bouger_test",
	"serpent_sur_table",
};

void InitializeNanoEdgeAI(void);
void RunNanoEdgeAI(AccelerometerData *accelData, GyroscopeData *gyroData);


#endif /* AI_AI_H_ */
