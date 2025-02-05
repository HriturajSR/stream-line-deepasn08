#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "Receiver.h"
#include "Sensor_Data_sender.h"

TEST_CASE("Tests to check whether sensor data is read from console and also to check whether correct Max, Min and SMA values of sensor parameters are printed on console") 
{
  float Temperature_value[readings_count] = {0};
  float SOC_value[readings_count] = {0};
  float observedMaxValue, observedMinValue, observedSMAValue, expectedMaxValue, expectedMinValue, expectedSMAValue;
  receiveAndProcessSensorData(&Temperature_value[0],&SOC_value[0]);
  float expectedoutput[2][2] = {{10,10}, {11,20}};
  for(int i=0;i<2;i++)
  {
    REQUIRE(Temperature_value[i] == expectedoutput[i][0]);
    REQUIRE(SOC_value[i] == expectedoutput[i][1]);
  }
  //To check Max, Min and SMA values of Temperature
  expectedMaxValue = 59;
  expectedMinValue = 10;
  expectedSMAValue = 57;
  observedMaxValue = fetchMaxValue(&Temperature_value[0]);
  observedMinValue = fetchMinValue(&Temperature_value[0]);
  observedSMAValue = calculateMovingAverage(&Temperature_value[0]);
  REQUIRE(observedMaxValue == expectedMaxValue);
  REQUIRE(observedMinValue == expectedMinValue);
  REQUIRE(observedSMAValue == expectedSMAValue);
  
  //To check print to console function
  REQUIRE(printReceivedDataToConsole(&Temperature_value[0],59,10,57) == 1);
          
  //To check Max, Min and SMA values of SOC
  expectedMaxValue = 500;
  expectedMinValue = 10;
  expectedSMAValue = 480;
  observedMaxValue = fetchMaxValue(&SOC_value[0]);
  observedMinValue = fetchMinValue(&SOC_value[0]);
  observedSMAValue = calculateMovingAverage(&SOC_value[0]);
  REQUIRE(observedMaxValue == expectedMaxValue);
  REQUIRE(observedMinValue == expectedMinValue);
  REQUIRE(observedSMAValue == expectedSMAValue);
  
  //To check print to console function
  REQUIRE(printReceivedDataToConsole(&SOC_value[0],500,10,480) == 1);
}
