#ifndef ESPUI_h
#define ESPUI_h

#define WS_AUTHENTICATION false

#include "Arduino.h"
#include "ArduinoJson.h"
#include "FS.h"
#include "stdlib_noniso.h"

#include "SPIFFS.h"
#include "WiFi.h"

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "tree.hh"

// Message Types (and control types)

enum ControlType : uint8_t {
  // fixed controls
  Title = 0,

  // updatable controls
  Pad,
  PadWithCenter,
  Button,
  Label,
  Switcher,
  Slider,
  Number,
  Text,
  Graph,
  GraphPoint,
  Tab,
  Select,
  Option,
  Min,
  Max,
  Step,

  UpdateOffset = 100,
  UpdatePad    = 101,
  UpdatePadWithCenter,
  ButtonButton,
  UpdateLabel,
  UpdateSwitcher,
  UpdateSlider,
  UpdateNumber,
  UpdateText,
  ClearGraph,
  UpdateTab,
  UpdateSelection,
  UpdateOption,
  UpdateMin,
  UpdateMax,
  UpdateStep,

  InitialGui  = 200,
  BatchUpdate = 201,
  NoneType    = 255
};

// Colors
enum ControlColor : uint8_t {
  Turquoise,
  Emerald,
  Peterriver,
  Wetasphalt,
  Sunflower,
  Carrot,
  Alizarin,
  Dark,
  NoneColor = 0xFF
};

class Control;
typedef tree< Control >           ControlTree;
typedef tree< Control >::iterator ControlTreeIterator;

class Control {
public:
  uint16_t     id    = 0;
  ControlType  type  = ControlType::NoneType;
  const char*  label = nullptr;
  String       value;
  ControlColor color                             = ControlColor::Turquoise;
  void ( *callback )( ControlTreeIterator, int ) = nullptr;
  bool dirty                                     = false;

  Control( ControlType type,
           const char* label,
           void ( *callback )( ControlTreeIterator, int ),
           String       value,
           ControlColor color )
      : type( type )
      , label( label )
      , value( value )
      , color( color )
      , callback( callback ) {
    id = idCounter++;
  }

  Control( const Control& control )
      : id( control.id )
      , type( control.type )
      , label( control.label )
      , value( control.value )
      , color( control.color )
      , callback( control.callback ) {}

  Control() { id = idCounter++; }

private:
  static uint16_t idCounter;
};

// Values
#define B_DOWN -1
#define B_UP   1

#define P_LEFT_DOWN   -2
#define P_LEFT_UP     2
#define P_RIGHT_DOWN  -3
#define P_RIGHT_UP    3
#define P_FOR_DOWN    -4
#define P_FOR_UP      4
#define P_BACK_DOWN   -5
#define P_BACK_UP     5
#define P_CENTER_DOWN -6
#define P_CENTER_UP   6

#define S_ACTIVE   -7
#define S_INACTIVE 7

#define SL_VALUE 8
#define N_VALUE  9
#define T_VALUE  10
#define S_VALUE  11

enum Verbosity : uint8_t { Quiet = 0, Verbose, VerboseJSON };

class ESPUIClass {
public:
  ESPUIClass( Verbosity verbosity = Verbosity::Quiet )
      : verbosity( verbosity ) {
    controlsTop = controlsTree.begin();
  }

  //     servers and page in Memorymode
  void begin( const char* _title,
              const char* username = nullptr,
              const char* password = nullptr );

  //     Setup servers and page in SPIFFSmode
  void beginSPIFFS( const char* _title,
                    const char* username = nullptr,
                    const char* password = nullptr );

  void prepareFileSystem(); // Initially preps the filesystem and loads a lot
  // of stuff into SPIFFS
  void list();
  // Creating Elements

  ControlTreeIterator addControl( ControlTreeIterator parentNode,
                                  ControlType         type,
                                  const char*         label,
                                  String              value = String( "" ),
                                  ControlColor color = ControlColor::Turquoise,
                                  void ( *callback )( ControlTreeIterator,
                                                      int ) = nullptr );

  ControlTreeIterator addControl( ControlType  type,
                                  const char*  label,
                                  String       value = String( "" ),
                                  ControlColor color = ControlColor::Turquoise,
                                  void ( *callback )( ControlTreeIterator,
                                                      int ) = nullptr );

  // Update Elements

  ControlTreeIterator getControl( uint16_t id );

  // Update Elements
  void updateControl( uint16_t id, String value, int clientId = -1 );
  void
  updateControl( ControlTreeIterator control, String value, int clientId = -1 );
  void updateControl( uint16_t id, int clientId = -1 );
  void updateControl( ControlTreeIterator control, int clientId = -1 );

  void updateControlAsync( ControlTreeIterator control );
  void updateControlAsync( uint16_t id );
  void updateControlAsyncTransmit( int clientId = -1 );

  void updateSwitcher( uint16_t id, bool nValue, int clientId = -1 );

  void handleClients();

  // Variables ---
  const char* ui_title = "ESPUI"; // Store UI Title and Header Name

  ControlTree         controlsTree;
  ControlTreeIterator controlsTop;

  void jsonDom( AsyncWebSocketClient* client );

  Verbosity verbosity;

  enum class ObjectIndex : uint8_t {
    Type = 0,
    Value,
    Id,
    Color,
    ParentControl,
    Label,
    Selected
  };

private:
  void sendToConnectedClientsOfWebsocket( int           clientId,
                                          JsonDocument& jsonBuffer );

private:
  const char* basicAuthUsername = nullptr;
  const char* basicAuthPassword = nullptr;
  bool        basicAuth         = true;

public:
  AsyncWebServer*                      server;
  AsyncWebSocket*                      ws;
  std::vector< AsyncWebSocketClient* > websocketClientToSendVector;
};

extern ESPUIClass ESPUI;

class AsyncWebSocketClientStream : public Stream {
public:
  AsyncWebSocketClientStream( AsyncWebSocketClient* client, bool wait = false )
      : client( client )
      , wait( wait ) {}

  virtual size_t write( uint8_t data ) override {
    if( wait ) {
      while( !client->canSend() ) {
        delay( 100 );
      }
    }
    client->text( &data, 1 );

    return 1;
  }

  virtual size_t write( const uint8_t* buffer, size_t size ) override {
    if( wait ) {
      while( !client->canSend() ) {
        delay( 100 );
      }
    }
    client->text( ( uint8_t* )buffer, size );

    return size;
  }

  virtual int  available() { return 0; }
  virtual int  read() { return 0; }
  virtual int  peek() { return 0; }
  virtual void flush() {}

private:
  AsyncWebSocketClient* client = nullptr;

  bool wait = false;
};

class AsyncWebSocketStream : public Stream {
public:
  AsyncWebSocketStream( AsyncWebSocket* socket )
      : socket( socket ) {}

  virtual size_t write( uint8_t data ) override {
    socket->textAll( &data, 1 );

    return 1;
  }

  virtual size_t write( const uint8_t* buffer, size_t size ) override {
    socket->textAll( ( uint8_t* )buffer, size );

    return size;
  }

  virtual int  available() { return 0; }
  virtual int  read() { return 0; }
  virtual int  peek() { return 0; }
  virtual void flush() {}

private:
  AsyncWebSocket* socket = nullptr;
};

#endif
