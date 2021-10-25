#ifndef OTAUPDATE_H_
#define OTAUPDATE_H_
#include <CertStoreBearSSL.h>
#include <ESP8266httpUpdate.h>

void checkForUpdate(BearSSL::CertStore *certStore, const String& url);

#endif /* OTAUPDATE_H_ */