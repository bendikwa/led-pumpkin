#include "https.h"

boolean loadCerts(BearSSL::CertStore *certStore)
{
    LittleFS.begin();
    int numCerts = certStore->initCertStore(LittleFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
    Serial.printf("https:          Number of CA certs read: %d\n", numCerts);
    if (numCerts == 0)
    {
        Serial.printf("https:          No certs found. Did you run certs-from-mozilla.py and upload the LittleFS directory before running?\n");
        return false;
    }
    else
    {
        return true;
    }
    LittleFS.end();
}

// Set time via NTP, as required for x.509 validation
void setClock()
{
    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print("https:          Waiting for NTP time sync: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.printf("https:          Current time: %s\n", asctime(&timeinfo));
}