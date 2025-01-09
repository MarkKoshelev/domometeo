//-----------------------------------
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h" 
#include "AudioGeneratorMP3.h" 

	#ifdef pin_sd
#include "SD.h"
#include "AudioFileSourceSD.h"
	#else
#ifdef ESP32
#include "SPIFFS.h"
#endif
#include "AudioFileSourceSPIFFS.h"
	#endif



#if defined (ESP32) or defined (PCM5102)
#include "AudioOutputI2S.h" 
#else
#include "AudioOutputI2SNoDAC.h"
#endif







AudioGeneratorMP3 *mp3 = NULL;
AudioFileSourceICYStream *file = NULL;
AudioFileSourceBuffer *buff = NULL;


	#ifdef pin_sd
AudioFileSourceSD *file_mp3= NULL;	
	#else
AudioFileSourceSPIFFS *file_mp3= NULL;
	#endif


#if defined (ESP32) or defined (PCM5102)
AudioOutputI2S *out = NULL;
#else
AudioOutputI2SNoDAC *out = NULL;
#endif

#ifdef ESP8266
const int preallocateBufferSize = 5*1024;
const int preallocateCodecSize = 29192; // MP3 codec max mem needed
#else
const int preallocateBufferSize = 16*1024;
const int preallocateCodecSize = 85332; // AAC+SBR codec max mem needed
#endif
void *preallocateBuffer = NULL;
void *preallocateCodec = NULL;



//clock
const int CX=63;
const int CY=122;
const byte R=40;
//----------


int volume = 200;
const int vol_def=30 ;//громкость по умолчанию если не указана в файле
byte ch=1; //ном канала №1 начальный
byte ch_min=254; //номер п.п 1 станции
byte ch_max=0; //номер п.п последней станции
byte ch_next=0; //
byte ch_prev=0; //
bool new_song=true;
String ch_name="";
String ch_url="";


String play_song="";
const byte rep_count=3; //сколько попыток при ошибке открытия сайта

int retryms = 0; 



//-----------------------------------

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void) isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
char s1[32], s2[64];
String play_tit;
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2)-1]=0;
//Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);

play_tit=String(s1);
if (play_tit.indexOf("StreamTitle")>=0)
{
play_song= (const char*) s2;
play_song.trim();
if (play_song=="-") play_song="";
new_song=true;

}
// Serial.flush();
}

/*
// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void StatusCallback(void *cbData, int code, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
//  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
//  Serial.flush();
}

*/