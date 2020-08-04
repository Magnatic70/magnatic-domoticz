#include "magnatic-esp.h"
#include "magnatic-domoticz.h"

#include <ArduinoJson.h>

String libraryTimeDomoticz=__TIMESTAMP__;

void setLuxValue(String deviceID, double lux){
	if(deviceID!="0" && deviceID!="Undefined"){ // Only do this when a deviceID is defined
		Serial.println(getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
			"/json.htm?type=command&param=udevice&idx="+deviceID+"&nvalue=0&svalue="+String(lux)));
	}
}

void setBarometerValue(String deviceID, float pressure){
	if(deviceID!="0" && deviceID!="Undefined"){ // Only do this when a deviceID is defined
		Serial.println(getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
			"/json.htm?type=command&param=udevice&idx="+deviceID+"&nvalue=0&svalue="+String(pressure)+";5"));
	}
}

void setTempHumValues(String deviceID, float temp, float hum){
	if(deviceID!="0" && deviceID!="Undefined"){ // Only do this when a deviceID is defined
		Serial.println(getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
			"/json.htm?type=command&param=udevice&idx="+deviceID+"&nvalue=0&svalue="+String(temp)+";"+String(hum)+";0"));
	}
}

void setSwitchStatus(String deviceID, String status){
	if(deviceID!="0" && deviceID!="Undefined"){ // Only do this when a deviceID is defined
		Serial.println(getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
			"/json.htm?type=command&param=switchlight&idx="+deviceID+"&switchcmd="+status));
	}
}

String getDeviceData(String deviceID){
	return getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
		"/json.htm?type=devices&rid="+deviceID);
}

String getCurrentAndNextSwitchStatus(String deviceID){
	String domoticzDeviceCurrentAndNextStatus="undefined";
	String deviceData=getDeviceData(deviceID);
	int statusPos=deviceData.indexOf("\"Status");
	Serial.println(deviceData.substring(statusPos+9,statusPos+12));
	if(deviceData.charAt(statusPos+12)=='O' && deviceData.charAt(statusPos+13)=='n'){ // On
		domoticzDeviceCurrentAndNextStatus="On===Off";
	}
	if(deviceData.charAt(statusPos+12)=='C' && deviceData.charAt(statusPos+13)=='l'){ // Closed
		domoticzDeviceCurrentAndNextStatus="Closed===Off";
	}
	if(deviceData.charAt(statusPos+12)=='O' && deviceData.charAt(statusPos+13)=='f'){ // Off
		domoticzDeviceCurrentAndNextStatus="Off===On";
	}
	if(deviceData.charAt(statusPos+12)=='O' && deviceData.charAt(statusPos+13)=='p'){ // Open
		domoticzDeviceCurrentAndNextStatus="Open===On";
	}
	return domoticzDeviceCurrentAndNextStatus;
}

bool checkDomoticzStatus(){
	bool check=false;
	Serial.print(F("Checking domoticz alive status: "));
	String payload=getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
		"/json.htm?type=command&param=getversion");
	int statusPos=payload.indexOf("\"version");
	if(statusPos>-1){
		check=true;
	}
	if(check){
		Serial.println(F("OK"));
	}
	else{
		Serial.println(F("NOK"));
	}
	return check;
}

String getDeviceValue(String sensorID, String sensorType){
	if(sensorType=="Temp"){
		return getTemp(sensorID);
	}
	else if(sensorType=="Lux"){
		return getLux(sensorID);
	}
	else if(sensorType=="Rain"){
		return getRain(sensorID);
	}
	else if(sensorType=="Barometer"){
		return getPressure(sensorID);
	}
	else{
		return getData(sensorID);
	}
}

String getData(String sensorID){
	DynamicJsonDocument doc(2048);
	deserializeJson(doc,getDeviceData(sensorID));
	String data=doc["result"][0]["Data"];
	return data;
}
		
String getTemp(String sensorID){
	DynamicJsonDocument doc(2048);
	deserializeJson(doc,getDeviceData(sensorID));
	float temp=doc["result"][0]["Temp"];
	return String(temp,1);
}

String getRain(String sensorID){
	DynamicJsonDocument doc(2048);
	deserializeJson(doc,getDeviceData(sensorID));
	float rain=doc["result"][0]["Rain"];
	return String(rain,1);
}

String getLux(String sensorID){
	DynamicJsonDocument doc(2048);
	deserializeJson(doc,getDeviceData(sensorID));
	String lux=doc["result"][0]["Data"];
	lux.replace(" Lux","");
	return lux;
}

String getPressure(String sensorID){
	DynamicJsonDocument doc(2048);
	deserializeJson(doc,getDeviceData(sensorID));
	float pressure=doc["result"][0]["Barometer"];
	return String(pressure,0);
}

void setTempValue(String deviceID, float temp){
	if(deviceID!="0" && deviceID!="Undefined"){ // Only do this when a deviceID is defined
		Serial.println(getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
			"/json.htm?type=command&param=udevice&idx="+deviceID+"&nvalue=0&svalue="+String(temp)));
	}
}

void setDeviceValue(String deviceID, int value){
	if(deviceID!="0" && deviceID!="Undefined"){ // Only do this when a deviceID is defined
		Serial.println(getPayloadFromHttpRequest("http://"+readStringFromSettingFile("DomoticzIP")+":"+readStringFromSettingFile("DomoticzPort")+
			"/json.htm?type=command&param=udevice&idx="+deviceID+"&nvalue=0&svalue="+String(value)));
	}
}

void domoticzSetup(){
	// Add config parameters
	addConfigParameter(F("DomoticzIP"),F("IP-address of Domoticz server"),F("192.168.1.180"),MainConfigPage,false,1);
	addConfigParameter(F("DomoticzPort"),F("Port of Domoticz service"),F("8080"),MainConfigPage,false,1);
	server.on("/sourceinfo/domoticz",[](){server.send(200,"text/plain",libraryTimeDomoticz);});
}

