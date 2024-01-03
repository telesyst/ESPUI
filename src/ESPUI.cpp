#include "ESPUI.h"

#include "dataControlsJS.h"
#include "dataIndexHTML.h"
#include "dataNormalizeCSS.h"
#include "dataSliderJS.h"
#include "dataStyleCSS.h"
#include "dataTabbedcontentJS.h"
#include "dataZeptoJS.h"

#include <ESPAsyncWebServer.h>
#include <StreamUtils.h>
#include <functional>

// CALL PERIODICALLY!!!
void
ESPUIClass::handleClients() {
  for( const auto client: websocketClientToSendVector ) {
    ESPUI.jsonDom( client );
  }
  websocketClientToSendVector.clear();
}

uint16_t Control::idCounter = 0;

// ################# Spiffs functions

void
listDir( const char* dirname, uint8_t levels ) {
  if( ESPUI.verbosity ) {
    Serial.printf( "Listing directory: %s\n", dirname );
  }

  File root = SPIFFS.open( dirname );

  if( !root ) {
    if( ESPUI.verbosity ) {
      Serial.println( "Failed to open directory" );
    }

    return;
  }

  if( !root.isDirectory() ) {
    if( ESPUI.verbosity ) {
      Serial.println( "Not a directory" );
    }

    return;
  }

  File file = root.openNextFile();

  while( file ) {
    if( file.isDirectory() ) {
      if( ESPUI.verbosity ) {
        Serial.print( "  DIR : " );
        Serial.println( file.name() );
      }

      if( levels ) {
        listDir( file.name(), levels - 1 );
      }
    } else {
      if( ESPUI.verbosity ) {
        Serial.print( "  FILE: " );
        Serial.print( file.name() );
        Serial.print( "  SIZE: " );
        Serial.println( file.size() );
      }
    }

    file = root.openNextFile();
  }
}

void
ESPUIClass::list() {
  if( !SPIFFS.begin() ) {
    Serial.println( "SPIFFS Mount Failed" );
    return;
  }

  listDir( "/", 1 );

  Serial.println( SPIFFS.totalBytes() );
  Serial.println( SPIFFS.usedBytes() );
}

void
deleteFile( const char* path ) {
  if( ESPUI.verbosity ) {
    Serial.print( SPIFFS.exists( path ) );
  }

  if( !SPIFFS.exists( path ) ) {
    if( ESPUI.verbosity ) {
      Serial.printf( "File: %s does not exist, not deleting\n", path );
    }

    return;
  }

  if( ESPUI.verbosity ) {
    Serial.printf( "Deleting file: %s\n", path );
  }

  if( SPIFFS.remove( path ) ) {
    if( ESPUI.verbosity ) {
      Serial.println( "File deleted" );
    }
  } else {
    if( ESPUI.verbosity ) {
      Serial.println( "Delete failed" );
    }
  }
}

void
writeFile( const char* path, const char* data ) {
  if( ESPUI.verbosity ) {
    Serial.printf( "Writing file: %s\n", path );
  }

  File file = SPIFFS.open( path, FILE_WRITE );

  if( !file ) {
    if( ESPUI.verbosity ) {
      Serial.println( "Failed to open file for writing" );
    }

    return;
  }

  if( file.print( data ) ) {
    if( ESPUI.verbosity ) {
      Serial.println( "File written" );
    }
  } else {
    if( ESPUI.verbosity ) {
      Serial.println( "Write failed" );
    }
  }
  file.close();
}

// end Spiffs functions

void
ESPUIClass::prepareFileSystem() {
  // this function should only be used once

  if( this->verbosity ) {
    Serial.println( "About to prepare filesystem..." );
  }

  SPIFFS.format();

  if( !SPIFFS.begin( true ) ) {
    if( this->verbosity ) {
      Serial.println( "SPIFFS Mount Failed" );
    }

    return;
  }

  if( this->verbosity ) {
    listDir( "/", 1 );
    Serial.println( "SPIFFS Mount ESP32 Done" );
  }

  deleteFile( "/index.htm" );

  deleteFile( "/css/style.css" );
  deleteFile( "/css/normalize.css" );

  deleteFile( "/js/zepto.min.js" );
  deleteFile( "/js/controls.js" );
  deleteFile( "/js/slider.js" );
  deleteFile( "/js/tabbedcontent.js" );

  if( this->verbosity ) {
    Serial.println( "Cleanup done" );
  }

  // Now write
  writeFile( "/index.htm", HTML_INDEX );

  writeFile( "/css/style.css", CSS_STYLE );
  writeFile( "/css/normalize.css", CSS_NORMALIZE );

  writeFile( "/js/zepto.min.js", JS_ZEPTO );
  writeFile( "/js/controls.js", JS_CONTROLS );
  writeFile( "/js/slider.js", JS_SLIDER );
  ;
  writeFile( "/js/tabbedcontent.js", JS_TABBEDCONTENT );

  if( this->verbosity ) {
    Serial.println( "Done Initializing filesystem :-)" );
  }

  if( this->verbosity ) {
    listDir( "/", 1 );
  }

  SPIFFS.end();
}

// Handle Websockets Communication
void
onWsEvent( AsyncWebSocket*       server,
           AsyncWebSocketClient* client,
           AwsEventType          type,
           void*                 arg,
           uint8_t*              data,
           size_t                len ) {
  switch( type ) {
    case WS_EVT_DISCONNECT: {
      if( ESPUI.verbosity ) {
        Serial.printf( "Disconnected!\n" );
      }

      break;
    }

    case WS_EVT_PONG: {
      if( ESPUI.verbosity ) {
        Serial.printf( "Received PONG!\n" );
      }

      break;
    }

    case WS_EVT_ERROR: {
      if( ESPUI.verbosity ) {
        Serial.printf( "WebSocket Error!\n" );
      }

      break;
    }

    case WS_EVT_CONNECT: {
      if( ESPUI.verbosity ) {
        Serial.print( "Connected: " );
        Serial.println( client->id() );
      }

      {
        // defer the answering to handleClients()
        ESPUI.websocketClientToSendVector.push_back( client );
      }

      if( ESPUI.verbosity ) {
        Serial.println( "JSON Data Sent to Client!" );
      }
    } break;

    case WS_EVT_DATA: {
      String msg = "";
      msg.reserve( len + 1 );

      for( size_t i = 0; i < len; i++ ) {
        msg += ( char )data[ i ];
      }

      uint16_t id = msg.substring( msg.lastIndexOf( ':' ) + 1 ).toInt();

      if( ESPUI.verbosity >= Verbosity::VerboseJSON ) {
        Serial.print( "WS rec: " );
        Serial.println( msg );
        Serial.print( "WS recognised ID: " );
        Serial.println( id );
      }

      auto c = ESPUI.getControl( id );

      if( c == ESPUI.controlsTree.end() ) {
        if( ESPUI.verbosity ) {
          Serial.print( "No control found for ID " );
          Serial.println( id );
        }

        return;
      }

      if( c->callback == nullptr ) {
        if( ESPUI.verbosity ) {
          Serial.print( "No callback found for ID " );
          Serial.println( id );
        }

        return;
      }

      if( msg.startsWith( "bdown:" ) ) {
        c->callback( c, B_DOWN );
      } else if( msg.startsWith( "bup:" ) ) {
        c->callback( c, B_UP );
      } else if( msg.startsWith( "pfdown:" ) ) {
        c->callback( c, P_FOR_DOWN );
      } else if( msg.startsWith( "pfup:" ) ) {
        c->callback( c, P_FOR_UP );
      } else if( msg.startsWith( "pldown:" ) ) {
        c->callback( c, P_LEFT_DOWN );
      } else if( msg.startsWith( "plup:" ) ) {
        c->callback( c, P_LEFT_UP );
      } else if( msg.startsWith( "prdown:" ) ) {
        c->callback( c, P_RIGHT_DOWN );
      } else if( msg.startsWith( "prup:" ) ) {
        c->callback( c, P_RIGHT_UP );
      } else if( msg.startsWith( "pbdown:" ) ) {
        c->callback( c, P_BACK_DOWN );
      } else if( msg.startsWith( "pbup:" ) ) {
        c->callback( c, P_BACK_UP );
      } else if( msg.startsWith( "pcdown:" ) ) {
        c->callback( c, P_CENTER_DOWN );
      } else if( msg.startsWith( "pcup:" ) ) {
        c->callback( c, P_CENTER_UP );
      } else if( msg.startsWith( "sactive:" ) ) {
        ESPUI.updateSwitcher( c->id, true );
        c->callback( c, S_ACTIVE );
      } else if( msg.startsWith( "sinactive:" ) ) {
        ESPUI.updateSwitcher( c->id, false );
        c->callback( c, S_INACTIVE );
      } else if( msg.startsWith( "slvalue:" ) ) {
        c->value =
          msg.substring( msg.indexOf( ':' ) + 1, msg.lastIndexOf( ':' ) );
        ESPUI.updateControl( c );
        c->callback( c, SL_VALUE );
      } else if( msg.startsWith( "nvalue:" ) ) {
        c->value =
          msg.substring( msg.indexOf( ':' ) + 1, msg.lastIndexOf( ':' ) );
        c->callback( c, N_VALUE );
      } else if( msg.startsWith( "tvalue:" ) ) {
        c->value =
          msg.substring( msg.indexOf( ':' ) + 1, msg.lastIndexOf( ':' ) );
        c->callback( c, T_VALUE );
      } else if( msg.startsWith( "svalue:" ) ) {
        c->value =
          msg.substring( msg.indexOf( ':' ) + 1, msg.lastIndexOf( ':' ) );
        c->callback( c, S_VALUE );
      } else {
        if( ESPUI.verbosity ) {
          Serial.println( "Malformated message from the websocket" );
        }
      }
    } break;

    default:
      break;
  }
}

ControlTreeIterator
ESPUIClass::addControl( ControlType  type,
                        const char*  label,
                        String       value,
                        ControlColor color,
                        void ( *callback )( ControlTreeIterator, int ) ) {
  return controlsTree.insert( controlsTree.end(),
                              Control( type, label, callback, value, color ) );
}

ControlTreeIterator
ESPUIClass::addControl( ControlTreeIterator parentNode,
                        ControlType         type,
                        const char*         label,
                        String              value,
                        ControlColor        color,
                        void ( *callback )( ControlTreeIterator, int ) ) {
  return controlsTree.append_child(
    parentNode, Control( type, label, callback, value, color ) );
}

ControlTreeIterator
ESPUIClass::getControl( uint16_t id ) {
  // auto node =

  ControlTreeIterator it = controlsTree.begin(), end = controlsTree.end();
  while( it != end ) {
    if( it->id == id ) {
      return it;
    }
    ++it;
  }

  return end;
}

void
ESPUIClass::updateControlAsyncTransmit( int clientId ) {
  DynamicJsonDocument jsonBufferPacket( 1400 );
  jsonBufferPacket[ "t" ] = ( int )ControlType::BatchUpdate;
  JsonArray items         = jsonBufferPacket.createNestedArray( "controls" );

  auto control = controlsTree.begin();
  auto end     = controlsTree.end();

  while( control != end ) {
    if( control->dirty ) {
      DynamicJsonDocument item( 1400 );

      item[ "t" ] = ( int )control->type + ControlType::UpdateOffset;
      item[ "v" ] = control->value;
      item[ "i" ] = control->id;
      item[ "c" ] = ( int )control->color;

      if( !items.add( item ) ) {
        sendToConnectedClientsOfWebsocket( clientId, jsonBufferPacket );

        jsonBufferPacket.clear();

        jsonBufferPacket[ "t" ] = ( int )ControlType::BatchUpdate;
        items = jsonBufferPacket.createNestedArray( "controls" );

        items.add( item );
      }

      control->dirty = false;
    }

    ++control;
  }

  sendToConnectedClientsOfWebsocket( clientId, jsonBufferPacket );
}

void
ESPUIClass::sendToConnectedClientsOfWebsocket( int           clientId,
                                               JsonDocument& jsonBuffer ) {
  if( clientId > 0 ) {
    // This is a hacky workaround because ESPAsyncWebServer does not have a
    // function like this and it's clients array is private
    int tryId = 0;

    for( int count = 0; count < this->ws->count(); ) {
      if( this->ws->hasClient( tryId ) ) {
        if( clientId != tryId ) {
          if( this->verbosity >= Verbosity::VerboseJSON ) {
            WriteBufferingStream bufferedStream( Serial, 1400 );
            Serial.print( "updateControl(), " );
            Serial.println( clientId );
            serializeJson( jsonBuffer, bufferedStream );
            Serial.println();
          }
          {
            AsyncWebSocketClientStream stream( this->ws->client( tryId ),
                                               true );
            WriteBufferingStream       bufferedStream( stream, 1400 );
            serializeJson( jsonBuffer, bufferedStream );
            delay( 10 );
          }
        }

        count++;
      }

      tryId++;
    }
  } else {
    if( this->verbosity >= Verbosity::VerboseJSON ) {
      WriteBufferingStream bufferedStream( Serial, 1400 );
      Serial.print( "updateControl(), textAll()" );
      serializeJson( jsonBuffer, bufferedStream );
      Serial.println();
    }
    {
      AsyncWebSocketStream stream( this->ws );
      WriteBufferingStream bufferedStream( stream, 1400 );
      serializeJson( jsonBuffer, bufferedStream );
      delay( 10 );
    }
  }
}

void
ESPUIClass::updateControl( ControlTreeIterator control, int clientId ) {
  if( control != controlsTree.end() ) {
    DynamicJsonDocument jsonBuffer( 1400 );

    jsonBuffer[ "t" ] = ( int )control->type + ControlType::UpdateOffset;
    jsonBuffer[ "v" ] = control->value;
    jsonBuffer[ "i" ] = control->id;
    jsonBuffer[ "c" ] = ( int )control->color;

    sendToConnectedClientsOfWebsocket( clientId, jsonBuffer );
  }
}

void
ESPUIClass::updateControl( uint16_t id, int clientId ) {
  updateControl( getControl( id ), clientId );
}

void
ESPUIClass::updateControl( ControlTreeIterator control,
                           String              value,
                           int                 clientId ) {
  if( control != controlsTree.end() ) {
    control->value = value;
    updateControl( control, clientId );
  }
}

void
ESPUIClass::updateControl( uint16_t id, String value, int clientId ) {
  updateControl( getControl( id ), value, clientId );
}

void
ESPUIClass::updateControlAsync( ControlTreeIterator control ) {
  if( control != controlsTree.end() ) {
    control->dirty = true;
  }
}

void
ESPUIClass::updateControlAsync( uint16_t id ) {
  updateControlAsync( getControl( id ) );
}

void
ESPUIClass::updateSwitcher( uint16_t id, bool nValue, int clientId ) {
  updateControl( id, String( nValue ? "1" : "0" ), clientId );
}

/*
Convert & Transfer Arduino elements to JSON elements
Initially this function used to send the control element data individually.
Due to a change in the ESPAsyncWebserver library this had to be changed to be
sent as one blob at the beginning. Therefore a new type is used as well
*/
void
ESPUIClass::jsonDom( AsyncWebSocketClient* client ) {
  DynamicJsonDocument jsonBufferPacket( 1400 );

  jsonBufferPacket[ "t" ] = ( int )ControlType::InitialGui;
  JsonArray items         = jsonBufferPacket.createNestedArray( "controls" );

  {
    JsonObject item = items.createNestedObject();
    item[ "t" ]     = ( int )ControlType::Title;
    item[ "l" ]     = ui_title;
  }

  ControlTreeIterator control = controlsTree.begin();
  ControlTreeIterator end     = controlsTree.end();
  while( control != end ) {
    DynamicJsonDocument item( 1400 );

    item[ "i" ] = control->id;
    item[ "t" ] = ( int )control->type;
    item[ "l" ] = control->label;
    item[ "v" ] = control->value;

    if( controlsTree.is_valid( control.node->parent ) ) {
      item[ "p" ] = control.node->parent->data.id;
    }

    if( ( control->type >= ControlType::Option &&
          control->type <= ControlType::Step ) ) {
      // item[ "p" ] = control.node->parent->data.id;

      if( ( control->type == ControlType::Option ) &&
          controlsTree.is_valid( control.node->parent ) ) {
        if( control.node->parent->data.value == control.node->data.value ) {
          item[ "s" ] = "selected";
        } else {
          item[ "s" ] = "";
        }
      }
    } else {
      item[ "c" ] = ( int )control->color;
    }

    if( ( ( jsonBufferPacket.memoryUsage() + item.memoryUsage() ) >
          ( jsonBufferPacket.capacity() - 50 ) ) ) {
      {
        AsyncWebSocketClientStream stream( client, true );
        WriteBufferingStream       bufferedStream( stream, 1400 );
        serializeJson( jsonBufferPacket, bufferedStream );
      }

      jsonBufferPacket.clear();

      jsonBufferPacket[ "t" ] = ( int )ControlType::InitialGui;
      items = jsonBufferPacket.createNestedArray( "controls" );
    }

    items.add( item );

    ++control;
  }

  {
    AsyncWebSocketClientStream stream( client, true );
    WriteBufferingStream       bufferedStream( stream, 1450 );
    serializeJson( jsonBufferPacket, bufferedStream );

    delay( 10 );
  }
}

void
ESPUIClass::beginSPIFFS( const char* _title,
                         const char* username,
                         const char* password ) {
  ui_title                = _title;
  this->basicAuthUsername = username;
  this->basicAuthPassword = password;

  if( username == nullptr && password == nullptr ) {
    basicAuth = false;
  } else {
    basicAuth = true;
  }

  server = new AsyncWebServer( 80 );
  ws     = new AsyncWebSocket( "/ws" );

  if( !SPIFFS.begin() ) {
    if( ESPUI.verbosity ) {
      Serial.println( "SPIFFS Mount Failed, PLEASE CHECK THE README ON HOW TO "
                      "PREPARE YOUR ESP!!!!!!!" );
    }

    return;
  }

  if( ESPUI.verbosity ) {
    listDir( "/", 1 );
  }

  if( !SPIFFS.exists( "/index.htm" ) ) {
    if( ESPUI.verbosity ) {
      Serial.println( "Please read the README!!!!!!!, Make sure to "
                      "ESPUI.prepareFileSystem() once in an empty sketch" );
    }

    return;
  }

  ws->onEvent( onWsEvent );
  server->addHandler( ws );

  if( basicAuth ) {

    if( WS_AUTHENTICATION ) {
      ws->setAuthentication( ESPUI.basicAuthUsername, ESPUI.basicAuthPassword );
    }

    server->serveStatic( "/", SPIFFS, "/" )
      .setDefaultFile( "index.htm" )
      .setAuthentication( username, password );
  } else {
    server->serveStatic( "/", SPIFFS, "/" ).setDefaultFile( "index.htm" );
  }

  // Heap for general Servertest
  server->on( "/heap", HTTP_GET, []( AsyncWebServerRequest* request ) {
    if( ESPUI.basicAuth && !request->authenticate( ESPUI.basicAuthUsername,
                                                   ESPUI.basicAuthPassword ) ) {
      return request->requestAuthentication();
    }

    request->send(
      200, "text/plain", String( ESP.getFreeHeap() ) + " In SPIFFSmode" );
  } );

  server->onNotFound(
    []( AsyncWebServerRequest* request ) { request->send( 404 ); } );

  server->begin();

  if( this->verbosity ) {
    Serial.println( "UI Initialized" );
  }
}

void
ESPUIClass::begin( const char* _title,
                   const char* username,
                   const char* password ) {
  basicAuthUsername = username;
  basicAuthPassword = password;

  if( username != nullptr && password != nullptr ) {
    basicAuth = true;
  } else {
    basicAuth = false;
  }

  ui_title = _title;

  server = new AsyncWebServer( 80 );
  ws     = new AsyncWebSocket( "/ws" );

  ws->onEvent( onWsEvent );
  server->addHandler( ws );

  if( basicAuth && WS_AUTHENTICATION ) {
    ws->setAuthentication( username, password );
}

  server->on( "/", HTTP_GET, []( AsyncWebServerRequest* request ) {
    if( ESPUI.basicAuth && !request->authenticate( ESPUI.basicAuthUsername,
                                                   ESPUI.basicAuthPassword ) ) {
      return request->requestAuthentication();
    }

    AsyncWebServerResponse* response =
      request->beginResponse_P( 200, "text/html", HTML_INDEX );
    request->send( response );
  } );

  // Javascript files

  server->on(
    "/js/zepto.min.js", HTTP_GET, []( AsyncWebServerRequest* request ) {
      if( ESPUI.basicAuth &&
          !request->authenticate( ESPUI.basicAuthUsername,
                                  ESPUI.basicAuthPassword ) ) {
        return request->requestAuthentication();
      }

      AsyncWebServerResponse* response = request->beginResponse_P(
        200, "application/javascript", JS_ZEPTO_GZIP, sizeof( JS_ZEPTO_GZIP ) );
      response->addHeader( "Content-Encoding", "gzip" );
      request->send( response );
    } );

  server->on(
    "/js/controls.js", HTTP_GET, []( AsyncWebServerRequest* request ) {
      if( ESPUI.basicAuth &&
          !request->authenticate( ESPUI.basicAuthUsername,
                                  ESPUI.basicAuthPassword ) ) {
        return request->requestAuthentication();
      }

      AsyncWebServerResponse* response =
        request->beginResponse_P( 200,
                                  "application/javascript",
                                  JS_CONTROLS_GZIP,
                                  sizeof( JS_CONTROLS_GZIP ) );
      response->addHeader( "Content-Encoding", "gzip" );
      request->send( response );
    } );

  server->on( "/js/slider.js", HTTP_GET, []( AsyncWebServerRequest* request ) {
    if( ESPUI.basicAuth && !request->authenticate( ESPUI.basicAuthUsername,
                                                   ESPUI.basicAuthPassword ) ) {
      return request->requestAuthentication();
    }

    AsyncWebServerResponse* response = request->beginResponse_P(
      200, "application/javascript", JS_SLIDER_GZIP, sizeof( JS_SLIDER_GZIP ) );
    response->addHeader( "Content-Encoding", "gzip" );
    request->send( response );
  } );

  server->on(
    "/js/tabbedcontent.js", HTTP_GET, []( AsyncWebServerRequest* request ) {
      if( ESPUI.basicAuth &&
          !request->authenticate( ESPUI.basicAuthUsername,
                                  ESPUI.basicAuthPassword ) ) {
        return request->requestAuthentication();
      }

      AsyncWebServerResponse* response =
        request->beginResponse_P( 200,
                                  "application/javascript",
                                  JS_TABBEDCONTENT_GZIP,
                                  sizeof( JS_TABBEDCONTENT_GZIP ) );
      response->addHeader( "Content-Encoding", "gzip" );
      request->send( response );
    } );

  // Stylesheets

  server->on( "/css/style.css", HTTP_GET, []( AsyncWebServerRequest* request ) {
    if( ESPUI.basicAuth && !request->authenticate( ESPUI.basicAuthUsername,
                                                   ESPUI.basicAuthPassword ) ) {
      return request->requestAuthentication();
    }

    AsyncWebServerResponse* response = request->beginResponse_P(
      200, "text/css", CSS_STYLE_GZIP, sizeof( CSS_STYLE_GZIP ) );
    response->addHeader( "Content-Encoding", "gzip" );
    request->send( response );
  } );

  server->on(
    "/css/normalize.css", HTTP_GET, []( AsyncWebServerRequest* request ) {
      if( ESPUI.basicAuth &&
          !request->authenticate( ESPUI.basicAuthUsername,
                                  ESPUI.basicAuthPassword ) ) {
        return request->requestAuthentication();
      }

      AsyncWebServerResponse* response = request->beginResponse_P(
        200, "text/css", CSS_NORMALIZE_GZIP, sizeof( CSS_NORMALIZE_GZIP ) );
      response->addHeader( "Content-Encoding", "gzip" );
      request->send( response );
    } );

  // Heap for general Servertest
  server->on( "/heap", HTTP_GET, []( AsyncWebServerRequest* request ) {
    if( ESPUI.basicAuth && !request->authenticate( ESPUI.basicAuthUsername,
                                                   ESPUI.basicAuthPassword ) ) {
      return request->requestAuthentication();
    }

    request->send(
      200, "text/plain", String( ESP.getFreeHeap() ) + " In Memorymode" );
  } );

  server->onNotFound(
    []( AsyncWebServerRequest* request ) { request->send( 404 ); } );

  server->begin();

  if( this->verbosity ) {
    Serial.println( "UI Initialized" );
  }
}
