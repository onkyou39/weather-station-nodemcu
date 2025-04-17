#ifndef RTC_SENSOR_H
#define RTC_SENSOR_H

#include "sensor_base.h"

class RtcSensor : public SensorBase {
public:
    void begin() override;
    void update() override;
    //void setTime(int hour, int minute, int second);
    //void setDate(int day, int month, int year);
    void setTimeUnix(uint32_t unixTime);
    String getTime();
    String getDate();


private:
    String time;
    String date;
};

#endif