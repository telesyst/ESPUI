set(includedirs src)

set(req arduino ESPAsyncWebServer ArduinoJson ArduinoStreamUtils)

idf_component_register(
	INCLUDE_DIRS ${includedirs} 
	SRC_DIRS src
	REQUIRES ${req})
