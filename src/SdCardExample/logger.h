#pragma once

#include <SPI.h>
#include <SD.h>
#include <string.h>

#define LOG_BUFFER_SIZE 50

class Logger {

public:

  Logger(int csPort, char* fileName){
    _logFileName = fileName;
    _csPort = csPort;
    _buffer[0] = '\0';
  }
  
  int Initialize(){
    if (!SD.begin(_csPort)) {
      return -1;
    }
    return 0;
  }
  
  int WriteLine(char* str){
    if (strlen(_buffer)+strlen(str) > LOG_BUFFER_SIZE-1){
      int result = Flush();
      if (result != 0) return result;
    }
    strcat(_buffer, str);
    strcat(_buffer, "\n");
    return 0;
  }
  
  int Flush(){
    File logFile = SD.open(_logFileName, FILE_WRITE);
    Serial.print(logFile);
    //if (!logFile)
    //  return -1;
    logFile.print(_buffer);
    logFile.flush();
    logFile.close();
    _buffer[0] = '\0';
  }
  
private:
  char _buffer[LOG_BUFFER_SIZE];
  char * _logFileName;
  int _csPort;
};

