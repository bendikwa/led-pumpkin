#include "otaUpdate.h"

void checkForUpdate(BearSSL::CertStore *certStore, const String& url){
  BearSSL::WiFiClientSecure bear;
  bear.setCertStore(certStore);
  t_httpUpdate_return ret = ESPhttpUpdate.update(bear, url);
  
  switch(ret) {
      case HTTP_UPDATE_FAILED:
          Serial.println("otaUpdate:      Update failed.");
          break;
      case HTTP_UPDATE_NO_UPDATES:
          Serial.println("otaUpdate:      Update no Update.");
          break;
      case HTTP_UPDATE_OK:
          Serial.println("otaUpdate:      Update ok."); // may not be called since we reboot the ESP
          break;
  }
}