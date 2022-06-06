#pragma once
#define S1_PIN 39
#define S2_PIN 36
#define S3_PIN 02
#define S4_PIN 32
#define S5_PIN 00
#define CLP_PIN 25

byte pins[6] = {S1_PIN, S2_PIN, S3_PIN, S4_PIN, S5_PIN, CLP_PIN};

/**
 * @brief Setup the IR road sensor
 * 
 */
void SetupSensor(){
    pinMode(S1_PIN, INPUT);
    pinMode(S2_PIN, INPUT);
    pinMode(S3_PIN, INPUT);
    pinMode(S4_PIN, INPUT);
    pinMode(S5_PIN, INPUT);
    pinMode(CLP_PIN, INPUT);
}

/**
 * @brief Get the sensor's state.
 * 
 * @return The state of the sensor in binary
 */
unsigned int GetSensorResult(){
    unsigned int resultBuffer = 0;
    for(int i = 0; i < 6; i++){
        resultBuffer = (resultBuffer << 1) + digitalRead(pins[i]);
    } 
    return resultBuffer;
}
/**
 * @brief Get the sensor's state and put it into the resultBuffer param.
 * 
 * @param resultBuffer The buffer that will hold the sensor's state.
 */
void GetSensorResult(unsigned int &resultBuffer){
    resultBuffer >> 6; //Clear the buffer
    for(int i = 0; i < 6; i++){
        resultBuffer = (resultBuffer << 1) + (digitalRead(pins[i]) == LOW ? 0b0 : 0b1);
    } 
} 

