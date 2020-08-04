// v001: 	* sendDeviceValue for temp+hum implemented

// v002: 	* setSwitchStatus implemented
//			* sendDeviceValue renamed to setTempHumValues
// 			* Migrated from EEPROM to setting file

// v003:	* getDomoticzStatus added
//			* checkDomoticzStatus added

// v004:	* Port to magnatic-esp8266 v009
//			* Added setBarometerValue and setLuxValue

// v005:	* Added getTemp, getRain, getLux, getPressure, getDeviceValue, getData

// v006:	* Usage of getPayloadFromHTTPRequest

// v007:	* Changed from magnatic-esp8266 to magnatic-esp


void setTempHumValues(String deviceID, float temp, float hum);
void setTempValue(String deviceID, float temp);
void setDeviceValue(String deviceID, int value);
void setSwitchStatus(String deviceID, String status);
void setLuxValue(String deviceID, double lux);
void setBarometerValue(String deviceID, float pressure);
void domoticzSetup();
String getCurrentAndNextSwitchStatus(String deviceID);
String getTemp(String sensorID);
String getRain(String sensorID);
String getLux(String sensorID);
String getPressure(String sensorID);
String getDeviceValue(String sensorID, String sensorType);
String getData(String sensorID);
