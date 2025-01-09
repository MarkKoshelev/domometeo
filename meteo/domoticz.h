#pragma once
#include <JsonListener.h>
#include <JsonStreamingParser.h>

typedef struct DomoticzCurrentData {

  float temp;
  uint16_t pressure;
  uint8_t humidity;
  int cod;
 } DomoticzCurrentData;

class DomoticzCurrent: public JsonListener {
  private:
    String currentKey;
    String currentParent;
	DomoticzCurrentData* data;
    bool doUpdate(DomoticzCurrentData* ,const String& );
  
  public:
    DomoticzCurrent();
    bool updateCurrent(DomoticzCurrentData* ,const String& );
	
    virtual void whitespace(char c);

    virtual void startDocument();

    virtual void key(String key);

    virtual void value(String value);

    virtual void endArray();

    virtual void endObject();

    virtual void endDocument();

    virtual void startArray();

    virtual void startObject();
};
