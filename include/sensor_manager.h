#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "sensor_base.h"
#include <vector>

class SensorManager {
public:
    /*void addSensor(SensorBase* sensor);
    void beginAll();
    void logAll(); // выводит значения в Serial
    //void printAll(); //выводит значения на lcd*/

private:
    std::vector<SensorBase*> sensors;
};

#endif