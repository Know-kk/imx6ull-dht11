#ifndef SENSOR_H
#define SENSOR_H
#define DATA_FILE "./data/sensor.dat"
typedef struct
    {
        float temperature;
        float humidity;
    }SensorData;
    
void add_data(SensorData *data);
void browse_data(SensorData *data);
void browse_previous_data(SensorData *temp);
void statistics(SensorData *temp);
void clear_data(SensorData *data);
void input_data(SensorData *data,unsigned char *buf);


#endif