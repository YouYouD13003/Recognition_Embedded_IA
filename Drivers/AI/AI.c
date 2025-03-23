/*
 * AI.c
 *
 *  Created on: Feb 28, 2025
 *      Author: Ayoub
 */


#include "AI.h"
#include "main.h"


void InitializeNanoEdgeAI(void) {
    if (neai_classification_init(knowledge) != NEAI_OK) {
        printf(" NanoEdge AI Initialization Failed!\n");
    } else {
        printf(" NanoEdge AI Model Loaded Successfully!\n");
    }
}

void RunNanoEdgeAI(AccelerometerData *accelData, GyroscopeData *gyroData) {
    //  Store IMU data in AI buffer
    neai_buffer[AXIS * neai_buffer_ptr] = accelData->x;
    neai_buffer[(AXIS * neai_buffer_ptr) + 1] = accelData->y;
    neai_buffer[(AXIS * neai_buffer_ptr) + 2] = accelData->z;
    neai_buffer[(AXIS * neai_buffer_ptr) + 3] = gyroData->x;
    neai_buffer[(AXIS * neai_buffer_ptr) + 4] = gyroData->y;
    neai_buffer[(AXIS * neai_buffer_ptr) + 5] = gyroData->z;

    neai_buffer_ptr++;

    //  Run classification when buffer is full
    if (neai_buffer_ptr >= SAMPLES) {
        printf("\n Running NanoEdge AI Classification...\n");

        if (neai_classification(neai_buffer, output_class_buffer, &id_class) == NEAI_OK) {
            printf(" Classified as: %s (Class ID: %d)\n", id2class[id_class], id_class);
            //JMO
            ia = id_class;
        } else {
            printf(" Classification Error!\n");
            ia = 8; //nb qui n'est pas possible par l'IA -> erreur
        }

        // Reset buffer for next batch
        neai_buffer_ptr = 0;
        memset(neai_buffer, 0.0, AXIS * SAMPLES * sizeof(float));
    }
}
