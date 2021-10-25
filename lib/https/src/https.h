#ifndef HTTPS_H_
#define HTTPS_H_

#include <Arduino.h>
#include <CertStoreBearSSL.h>
#include <LittleFS.h>

boolean loadCerts(BearSSL::CertStore *certStore);
void setClock();

#endif /* HTTPS_H_ */