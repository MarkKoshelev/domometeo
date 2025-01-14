//The MIT License (MIT)
#ifndef OpenWeather_h
#define OpenWeather_h

#include <JsonListener.h>
#include <JsonStreamingParser.h>

//------------------------------------------ Universal weather request parcer for opewWeatherMap site ---------
#define OWM_max_layers 4
class OWMrequest: public JsonListener {
  public:
    void init(void);
    OWMrequest() : JsonListener()                   { }
    virtual void key(String key)                    { currentKey = String(key); }
    virtual void endObject();
    virtual void startObject();
    virtual void whitespace(char c)                 { }
    virtual void startDocument()                    { }
    virtual void endArray()                         { }
    virtual void endDocument()                      { }
    virtual void startArray()                       { }
  protected:
    void   doUpdate(String url, byte maxForecasts = 0);
    String currentKey;
    String currentParent;
    String p_key[OWM_max_layers];
};


//------------------------------------------ Five day forecast from openweatrhermap.org -----------------------
typedef struct sOWM_fiveForecast {
  String dt;
  int temp;
  int pressure;
  String description;
  String icon;
  int w_speed;
  int w_deg;
  float rain;                                      // conditions: cloud, rain, snow
  float snow;
  byte  h;  //scr Sg
} OWM_fiveForecast;

class OWMfiveForecast : public OWMrequest {
  public:
    OWMfiveForecast()                               { }
    byte    updateForecast(OWM_fiveForecast *forecasts, byte maxForecasts, String url_my);
    virtual void value(String value);

  private:
    byte     index;
    uint32_t timestamp;
    byte     max_forecasts;
    OWM_fiveForecast *forecasts;
};

#endif
