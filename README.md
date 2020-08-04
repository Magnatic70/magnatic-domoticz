# magnatic-domoticz
A simple library for communication with Domoticz.

This library depends on the [magnatic-esp](https://github.com/Magnatic70/magnatic-esp) library and the ArduinoJson-library.

## void domoticzSetup()
Use this function in your void setup(), after espSetup()

## void setTempHumValues(String deviceID, float temp, float hum)
Sets temperature and humidity values for a device.

## void setTempValue(String deviceID, float temp)
Sets temperature value for a device

## void setDeviceValue(String deviceID, int value)
Sets an integer value for a device

## void setSwitchStatus(String deviceID, String status)
Switches a device On or Off

## void setLuxValue(String deviceID, double lux)
Sets lux value for a device

## void setBarometerValue(String deviceID, float pressure)
Sets mbar for a device

## String getCurrentAndNextSwitchStatus(String deviceID)
Gets the current switch status and the value needed to toggle the switch. "===" is used as a separator between these values

## String getTemp(String sensorID)
Gets the current temperature for a device

## String getRain(String sensorID)
Gets the current rain-amount for a devce

## String getLux(String sensorID)
Gets the current lux value for a device

## String getPressure(String sensorID)
Gets the current mbar value for a device

## String getDeviceValue(String sensorID, String sensorType)
Wrapper for getTemp, getRain, getLux and getPressure (sensorType resp. "Temp", "Rain", "Lux", "Barometer")

## String getData(String sensorID)
Returns the raw data part of the JSON-response from Domoticz
