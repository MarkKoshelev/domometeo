//
bool play=false;

#include "h\color.h"
#include "settings_meteo.h"

const char* ssid     = "PandoraBox";  //точка доступа
const char* password = "abc1221def";


byte t_b=99,t_e=99; //ночные часы беру из config
signed char delta_p=0; //поправка на давление 
int t_max=28,t_min=-10,v_max=7; //сигнализация на экран предельных значений темп и скорости.ветра, уфо
byte uv_max=6; //ультрофиолет 
unsigned int p_max=760,p_min=720 ;//давление для сигнализации в config.txt если есть там первично
byte beep_b=99; // время "с" беру в config.txt 
byte beep_e=99; //"до" беру в config.txt  
//время перезагрузки ESP 
byte esp_restarts=99; 
byte last_hour=99;
byte last_minute=99;//alarm.txt shed
bool log_file=false; //log fie
String log_str="";


//SCR-------------------------------
byte scr_count_pack=0;
signed char scr_number=0;
char *scr_name[scr_count]={""};
char scr_name_def[4];

//#ifdef two_tft
//signed char scr_number2=0;
//#endif

byte scr_number_prev;
byte scr_show_count=0; //если по кругу экраны >1 config.txt
int t_S1_show=0;
int t_S2_show=0;
int t_S3_show=0;
int t_S4_show=0;
int t_S5_show=0;
int t_Sf_show=0;
int t_S0_show=0;
int t_Sg_show=0;
bool scr_round=true;

//NTP--------------------------
signed char TIMEZONE =3;
bool sync_t=false;
bool sync_force=false;
time_t t_ntp_update=0;

byte t_next_shed=99;//T чтения план-ка
byte next_shed_ch=0;
byte ch_prev_alarm=0; //возврат на этот канал после таймера, если уже играло
bool  vol_rotate=false; //если громеость менял, оставляю для всех каналов , до выхода их экр. радио
bool ref_tft=false;
bool show_song=true;



struct alarm_structure {
bool  active=false; //volume
char  label; //тип I,M,J inet,mp3,jpeg
byte  h=99;//hour
byte  m=99; //min
byte  ch_num=0; // ch
String  fname="";
unsigned int t_long=0;//length T millisec
//byte  count=0; //повторов
//byte  interval=0; //min
byte  vol=50; //volume

};
alarm_structure al;
bool play_alarm=false;
byte  beep_mp3_vol=0; //volume

const byte fn_count=6;
unsigned long code[fn_count] = {0};
//char * fn[] = { 
//"play","next","prev","vl+","vl-","mute"};
unsigned long code_btn[10] = {0};

float temp_kv=200;
int pr_kv=200;
byte h_kv=200;
bool ref_kv_th=false;
bool ref_wh=false;
bool ref_wh_now=false;
float temp_u=200;
unsigned long period_ulica=0;//во сколько принял Темп ул.
uint32_t t_read_tk=0;//во сколько принял Темп кв
unsigned int c_tu_frame=TFT_CYAN;
unsigned int c_th_frame=TFT_CYAN;

String appid   = "KEY OPW";  //ключ ген. беру из config.txt
String lat     = "53.900002";
String lon     = "27.566668";
byte max_ch3=40;//&cnt=40 беру из conf, количество 3 часовых записей на 5дней,
// не больше 40 , можно меньше если зависает, просто уменьшится кол-во дней в прогнозе


#include <TimeLib.h>  // day of the week (1-7), Sunday is day 1
#include <TimeLord.h> //moon
TimeLord myLord;


#ifdef encoder
#include "GyverEncoder.h"
Encoder enc(CLK, DT, SW,TYPE);
byte fav_ch[fav_count]={0};
byte fav_count_real=0; //после упаковки если меньше чем задано
#endif
  
//============= domoticz =======================domoticz==============================================
#ifdef domoticz
#include "Domoticz.h"
DomoticzCurrent domoticzNOW;
#include "JsonStreamingParser.h"
#include "JsonListener.h"
JsonStreamingParser pars;
unsigned long lastConnectionTime_domoticz = 0;
unsigned long postingInterval_domoticz = 0;
#endif


//=============openw=============================openw================================================
#ifdef openw
#include "openWeather.h"
OWMfiveForecast    owF5;
#include "OpenWeatherCurrent.h"
OpenWeatherMapCurrent owNOW;
 #include "JsonStreamingParser.h"
#include "JsonListener.h"
JsonStreamingParser pars;

signed char delta_tz=0; //для выравнивания т зоны к 3 часам запроса


String url_ch="";
String url_now="";
String url_uv="";

 #ifndef EN
const String url_ch_b ="http://api.openweathermap.org/data/2.5/forecast?lang=RU&units=metric&lat=";
const String url_now_b="http://api.openweathermap.org/data/2.5/weather?lang=RU&units=metric&lat=";
  #else
const String url_ch_b ="http://api.openweathermap.org/data/2.5/forecast?lang=EN&units=metric&lat=";
const String url_now_b="http://api.openweathermap.org/data/2.5/weather?lang=EN&units=metric&lat=";
  #endif //EN


const String url_uv_b="http://api.openweathermap.org/data/2.5/uvi?appid=";


float rain_mm=0;//количество осадков за день
int davlenie7[8]; 
int temperatura7[8];
int temperatura7n[8];
int p7_max=200,p7_min=2000;

byte day7[8];//
String icon7[8];// 
byte holiday7[8];//выходные
float rain7[8];//осадки
byte veter7[8]; //скор ветра
String wind_ico="";
int v_gr_7[8];
byte weekday7[8];



byte entries =0; //count ret ch openW
// 3-часовой
#ifdef Sg 
const byte ch_count=41; 
#elif (defined (S4) &&  defined(tft_320_240))||(defined (S3) && defined(tft_480_320))
const byte ch_count=27; //
#else
const byte ch_count=6;
#endif


int temperatura_ch[ch_count];
byte day_ch[ch_count];//
String icon_ch[ch_count];// 
int v_gr_ch[ch_count];
byte v_ch[ch_count];
float rain_ch[ch_count]; //данные о дожде мм

#ifdef Sg
int p_ch[ch_count];//давление
byte h_ch[ch_count];//влажность
int c_wind=0;  //color wind

#endif

String descript_now="";
int temp_ch_n=200;
uint last_7day=0;
int davlenie0=200;


unsigned long lastConnectionTime_now = 0;
unsigned long postingInterval_now = 0;

unsigned long lastConnectionTime_ch = 0;
unsigned long postingInterval_ch = 0;
unsigned long lastConnectionTime_uv = 0;
unsigned long postingInterval_uv = 0;

float uv=-1;
//String httpData_uv,httpData_ch;
#endif



//FTP================================
#ifdef ftp
#include <ESP8266FtpServer.h>
FtpServer ftpSrv;
#endif


#define FS_NO_GLOBALS //allow spiffs to coexist with SD card, define BEFORE including FS.h
#include <FS.h> //spiff file system

#ifdef pin_sd
#include "SD.h"
unsigned int max_jpg_num=0;
int Sf_t_slide=30; //config.txt
#endif

#ifdef ESP32
#include "SPIFFS.h" // Needed for ESP32 only
#endif


//==========ESP8266============ESP8266===============ESP8266==================ESP8266=========ESP8266
#ifdef ESP8266
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

ESP8266WebServer  server(80);
#ifdef http_update
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;
#define update_path "/update"
#endif

#endif


//===========ESP32=======================ESP32==================ESP32=================ESP32
#ifdef ESP32
#include <WebServer.h>
#include <WiFi.h>
#include <HTTPClient.h>
WebServer server(80);
  #ifdef http_update
#include <Update.h>
#define update_path "/update"

const char* serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
 "<div id='prg'>progress: 0%</div>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')" 
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";

  #endif

#endif
///--------------------IoT
#ifdef IoT
#include "ThingSpeak.h"
WiFiClient  client_iot;

unsigned long iot_id =0;
const char * iot_key = "";
unsigned long iot_period_send=0; //period send sec>=20
byte iot_T_fld_send=0;  //temp квартира(room);ном поля(num field) bme280 
byte iot_H_fld_send=0;  //humidity квартира(room) ;ном поля(num field) bme280
byte iot_T2_fld_send=0; //temp улица(street)
byte iot_P_fld_send=0; //давление(pressure)
byte iot_W_fld_send=0; //скорость ветра (wind speed)
byte iot_R_fld_send=0; //дождь мм(rain)


//read

unsigned long iot_id_read =0;
const char * iot_key_read = "";
unsigned long iot_period_read=0; //period send sec>=20
byte iot_T_fld_read=0;  //temp квартира(room);ном поля(num field) bme280 
byte iot_H_fld_read=0;  //humidity квартира(room) ;ном поля(num field) bme280
byte iot_T2_fld_read=0; //temp улица(street)
byte iot_P_fld_read=0; //давление(pressure)

#endif



#if defined (ESP32)
#include "h\iradio.h"
#endif

//=================================================================================================


 
#ifdef ota_update
#include <ArduinoOTA.h>
#endif



bool play_mp3=false;
String fn_cmd="";//stop play next prev  
//---------------------------------


//IR ESP8266========================================
#if defined(pin_ir) && defined(ESP8266) 
//IR========================================
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
IRrecv irrecv(pin_ir); // указываем вывод, к которому подключен приемник
decode_results results;
unsigned long ir_code; 
#endif

//IR ESP32========================================

#if defined(pin_ir) && defined(ESP32) 
//IR==============================================
#include <IRremote.h>
IRrecv irrecv(pin_ir); // указываем вывод, к которому подключен приемник
decode_results results;
unsigned long ir_code; 
#endif
//---------------------------------------------


uint32_t t_timer=0; //play radio timer onf


#include "SPI.h"
#include <JPEGDecoder.h>
//#define FORMAT_SPIFFS_IF_FAILED true


const char* password_ap = "11111111";//ap
const char* ssid_ap = "ESP_METEO";//ap
const char* passw_new = "";//ap
const char* ssid_new = "";//ap
IPAddress local_ip(192,168,11,11);
IPAddress gateway(192,168,11,1);
IPAddress netmask(255,255,255,0);


//=================================================================================
//              display
//=================================================================================
bool tft2_act=false; //метка что в данный момент активет tft 2 для jpeg 

#if defined (two_tft) && defined (tft_320_240)
#include "Adafruit_GFX.h"
#include <Adafruit_ILI9341.h>
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Adafruit_ILI9341 tft2 = Adafruit_ILI9341(TFT_CS2, TFT_DC2, TFT_MOSI2, TFT_CLK2, TFT_RST2, TFT_MISO2);

#define setFreeFont  setFont
#else
#include "TFT_eSPI.h"
  #ifdef tft_480_320
  TFT_eSPI tft = TFT_eSPI(320,480); 
  #else 
  TFT_eSPI tft = TFT_eSPI(240,320); 
  #endif  

#endif






#include "h\verdana9b.h"
#include "h\verdana24b.h"
#include "h\verdana9.h"
#include "h\verdana12.h"
#include "h\verdana18.h"
#include "h\verdana6all.h"
#include "h\verdana18b.h"
#include "h\verdana24.h"


#if defined (ESP32) || defined (EN)||defined(pin_sd)
  #ifdef two_tft 
  #include "h\FreeMono9pt7b.h"
  #endif
#define v9mono &FreeMono9pt7b
#endif


#define v9b &verdanab9pt7b
#define v9 &verdana9pt7b
#define v12 &verdana12pt7b
#define v18 &verdana18pt7b
#define v6 &verdana6pt7b
#define v18b &verdanab18pt7b
#define v24 &verdana24pt7b
#define v24b &verdanab24pt7b



//=========================================
#ifdef pin_dht
//=========================================
#include "DHT.h"
DHT dht(pin_dht,DHTTYPE);
#endif
//------------------------------------------



//=========================================
#ifdef si7021
//=========================================
#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>
Weather sensor_si;
#endif
//------------------------------------------

//=========================================
#ifdef bme280
//=========================================
#include <Wire.h>
#include <BME280I2C.h>
BME280I2C sensor_bme;    // Default : forced mode, standby time = 1000 ms
#endif
//------------------------------------------


//=========================================
#ifdef pin_ds1820
//=========================================
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(pin_ds1820);                                       // вход датчиков 18b20, аналоговый А1, он же 15 цифровой 
DallasTemperature ds(&oneWire);    
#endif
//-------------------------------------------



bool ref_temp_u=false;
//=========================================
#ifdef nrf
//=========================================
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(CEnrf,CSnrf); // "создать" модуль на пинах 9 и 10 Для Уно
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб
#endif
//------------------------------------------



IPAddress timeServerIP; 

///NTP===========================================
#include <WiFiUdp.h>
///NTP===========================================

byte err_ntp=1;
byte ntp_count=0;
unsigned int  localPort = 2390;      // local port to listen for UDP packets
unsigned long  ntp_time = 0;
const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[ NTP_PACKET_SIZE]; 
byte ntp_num=1;
String t_sun_v="",t_sun_z="";
int t_sun_v_hh=99,t_sun_z_hh=99;


WiFiUDP udp;


//send WIFI read--------------------------------
//=====================================
#if defined (wf_send)||  defined (wf_read)
//=====================================
IPAddress broadcastAddress;
WiFiUDP udp_wf;
#endif
//---------------------------------------


bool nigth=false;
time_t t;
bool refresh_all=true; //флаг что есть новые данными надо перерисовать 


//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void setup() {

Serial.begin(115200);


#ifdef pin_sd
digitalWrite(TFT_CS, HIGH); // TFT screen chip select
digitalWrite( pin_sd, HIGH); // SD card chips select
#endif


tft.begin();
tft.fillScreen(TFT_BLACK );
tft.setRotation(rotation); 
tft.setTextWrap(0);
tft.setCursor(0,10);
tft.setFreeFont(v6);
tft.setTextColor(0x07E0);



//#ifdef debug
do_show_define();
delay(3000);
tft.setTextColor(0x07E0);
tft.fillScreen(TFT_BLACK );
tft.setCursor(0,10);
//#endif



  #ifdef pin_sd

while (!SD.begin(pin_sd)) 
  {
tft.setTextColor(TFT_RED);
tft.setCursor(10,20);
Serial.println(F("SD ERR"));
tft.println("SD ERR");
tft.setTextColor(0x07E0);
delay(5000);
  }
Serial.println(F("SD ok"));
tft.println(F("SD ok"));
#ifdef Sf
max_jpg_num=do_maxnum_file();
Serial.print(F("max jpeg num="));
Serial.println(max_jpg_num);
tft.print("max jpeg num=");

if (max_jpg_num==0) 
{
Serial.print(F("ERR no Foto"));
tft.setTextColor(TFT_RED);
tft.println("ERR no Foto");
}
else tft.println(max_jpg_num);
#endif //Sf
  #else
SPIFFS.begin();
  #endif



#ifdef  two_tft
tft2.begin();
tft2.fillScreen(TFT_BLACK );
tft2.setRotation(rotation2); 
tft2.setCursor(150,120);
tft2.setFreeFont(v9mono);
tft2.setTextColor(TFT_YELLOW);
tft2.println("TFT 2");
tft2.setFreeFont(v6);
#endif



//tft.fillScreen(TFT_BLACK );
tft.setTextColor(0x07E0);
tft.print("read config.txt");
if (do_read_config_txt())
tft.println("  OK");
else
{
tft.setTextColor(TFT_RED);
tft.println("   ERR ");
tft.setTextColor(0x07E0);
delay(5000);
}



if (log_file)
{
log_str=(F("--------------ESP--boot"));
do_log();  
}


#ifdef ESP32 //radio
 // First, preallocate all the memory needed for the buffering and codecs, never to be freed
preallocateBuffer = malloc(preallocateBufferSize);
preallocateCodec = malloc(preallocateCodecSize);
if (!preallocateBuffer || !preallocateCodec)
{
   
    Serial.printf_P(PSTR("FATAL ERROR:  Unable to preallocate %d bytes for app\n"), preallocateBufferSize+preallocateCodecSize);
    while (1) delay(1000); // Infinite halt
} 

  #ifdef PCM5102 
out = new AudioOutputI2S(0,0); //dac
out->SetPinout(bclkPin,wclkPin,doutPin);
Serial.println(F("PCM5102 EXT. DAC"));
tft.println(F("PCM5102 EXT. DAC"));
if (log_file)
{
log_str=(F("PCM5102"));
do_log();  
}
  #else
out = new AudioOutputI2S(0, 1);
Serial.println(F("ESP32  internal DAC"));
tft.println(F("internal DAC"));

if (log_file)
{
log_str=(F("internal DAC"));
do_log();  
}

  #endif




file = NULL;
buff = NULL;
mp3 = NULL;
file_mp3 = NULL;

#endif //ESP32
 
//-----------------------------


#ifdef pin_btn_No_touch
pinMode(pin_btn_No_touch,  INPUT_PULLUP);
if (log_file)
{
log_str=("pin_btn_No_touch=")+String(pin_btn_No_touch);
do_log();  
}
#endif


#ifdef pin_btn_touch
if (log_file)
{
log_str=("pin_btn_touch=")+String(pin_btn_touch);
do_log();  
}

#endif


//==================================
#ifdef pin_rele
//==================================
pinMode(pin_rele,OUTPUT);
digitalWrite(pin_rele,rele_on_off);
Serial.println ("RELE ok");
if (log_file)
{
log_str=(F("pin_rele="))+String(pin_rele);
do_log();  
}
#endif  
//----------------------------------


//==================================
#ifdef nrf
//==================================
radio.begin(); //активировать модуль
  radio.setAutoAck(0);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openReadingPipe(1,address[0]);      //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)
  radio.setPALevel (RF24_PA_LOW); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  
  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
Serial.println ("nrf start");
tft.println(F("nrf start"));
if (log_file)
{
log_str=(F("nrf"));
do_log();  
}

#endif


//==================================
#ifdef pin_dht
//==================================
dht.begin();
Serial.print(F("DHT pin="));
Serial.println(pin_dht);
#endif


//==================================
#ifdef bme280
//==================================
Wire.begin();
for (int i=0; i <= 5; i++){
if (!sensor_bme.begin())
{
    Serial.println(F("Could not find BME280 sensor!"));
    delay(2000);
tft.println(F("Could not find BME280"));
if (log_file)
{
log_str=(F("BME280 ERROR"));
do_log();  
}


}
else
{
if (log_file)
{
tft.println(F("BME280 OK"));  
log_str=(F("BME280 OK"));
do_log();  
}

break;

}
}
//==================================
#elif si7021
//==================================
Wire.begin();
if (sensor_si.begin()) 
{
Serial.println (F("si7021 "));
tft.println(F("si7021"));  
if (log_file)
{
log_str=(F("si7021 OK"));
do_log();  
}

}
else
if (log_file)
{
log_str=(F("si7021 ERR"));
do_log();  
}
#endif



//==================================
#ifdef ds1820
//==================================
ds.begin(); 
delay(500);
if (log_file)
{
log_str=(F("ds1820"));
do_log();  
}
#endif
//-----------------------------------



//==================================
#ifdef pin_ir
//==================================
irrecv.enableIRIn(); // запускаем прием
tft.print("pin_ir=");  tft.println(pin_ir); 
tft.print("read ik.txt");
if (do_read_file_ik()) 
{
tft.println("OK");  
Serial.println (F("Ir  OK"));
log_str=(F("ir Ok"));
}
else
{
tft.setTextColor(TFT_RED);
tft.println("read ik.txt   ERR ");
tft.setTextColor(0x07E0);
log_str=(F("read ik.txt   ERR"));
delay(3000);
  
}
if (log_file) do_log();  
#endif


//------------------------------------
//==================================
#ifdef pin_beep
//==================================
pinMode(pin_beep, OUTPUT); //объявляем пин beep как выход
digitalWrite(pin_beep,LOW );
if (log_file)
{
log_str=(F("beep"));
do_log();  
}

#endif
//----------------------------------


#ifdef openw
url_ch=url_ch_b+lat+"&lon="+lon+"&appid=" + appid+"&cnt="+String(max_ch3);
url_now=url_now_b+lat+"&lon="+lon+"&appid=" + appid;
//UV
url_uv=url_uv_b+ appid+ "&lat=" +lat+"&lon="+lon;



#ifdef debug
Serial.print(F("url_ch="));
Serial.println(url_ch);
Serial.print(F("url_now="));
Serial.println(url_now);
Serial.print(F("url_uv=")); 
Serial.println(url_uv);
#endif

#endif

delay(2000);
tft.setCursor(0,20);
tft.fillScreen(TFT_BLACK);



//WIFI=======WIFI=======WIFI=======WIFI=======WIFI=======WIFI=======WIFI=======
wifiConnect();
//WIFI=======WIFI=======WIFI=======WIFI=======WIFI=======WIFI=======WIFI=======


//===========IoT==============IoT==================IoT
#ifdef IoT
ThingSpeak.begin(client_iot);  // Initialize ThingSpeak
if (log_file)
{
log_str=(F("IoT"));
do_log();  
}
#endif



#if defined (http_update) && defined(ESP8266)
httpUpdater.setup(&server, update_path);
#endif

#if defined (http_update) && defined(ESP32)
  server.on(update_path, HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  #endif


 
server.on("/",handleRoot);
server.onNotFound(handleNotFound);


server.begin();
Serial.println(F("HTTP server started"));

if (WiFi.getMode()==WIFI_AP)
goto end_setup;

//===========================================
delay(2000);


#ifdef ota_update
 //=====OTA==========================================================
 ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
ArduinoOTA.setHostname(ota_name);
ArduinoOTA.begin();

#endif


//====FTP================================================
#ifdef ftp
ftpSrv.begin("esp8266","esp8266");    //username, password for ftp. 
Serial.println(F("ftp server started"));
tft.println("ftp esp8266/esp8266");
tft.println();
delay(1000);
//-----------------------------------------------------
#endif


tft.setTextColor(0x07E0);


//===UDP SEND READ====================================
#if defined (wf_send)||  defined (wf_read)
broadcastAddress = (uint32_t)WiFi.localIP() | ~((uint32_t)WiFi.subnetMask());
Serial.print(F("Broadcast address: "));
Serial.println(broadcastAddress);
tft.println();
tft.print(F("bct="));
tft.setTextColor(TFT_YELLOW);
tft.println(broadcastAddress);
tft.print("port=");
tft.println(localPort_wf);
udp_wf.begin(localPort_wf);
#endif
//-------------------------------------------

tft.setTextColor(0x07E0);  
Serial.println(F("Starting NTP"));


//NTP=======================================
udp.begin(localPort);
delay(1000);
tft.print("ntp=");
if (do_ntp()== true)
tft.println("OK");
else
{
tft.setTextColor(TFT_RED);
tft.println(" NTP  ERR ");
tft.setTextColor(0x07E0);
}
tft.println("===============");
delay(1000);
//--------------------------------------------



scr_pack( );

#ifndef openw 
  #ifdef tft_320_240
do_find_scr("S0"); //big clock no openw
  #endif 

  #ifdef tft_480_320
do_find_scr("Sn"); //big clock no openw
  #endif 

#endif  //openw

#ifdef openw 
if (!do_find_scr(scr_name_def))
scr_number=0;
/*
#ifdef two_tft
if (!do_find_scr(scr_name_def2,2))
scr_number2=0;
#endif 
*/

#endif 

scr_num_show(scr_number);

  #ifdef pin_sd
#ifdef A0_free
randomSeed(analogRead(A0));
#else
randomSeed(millis() );
#endif
  #endif
tft.fillScreen(TFT_BLACK);


#ifdef only_radio
fn_cmd="play";
do_fn_btn_ir();
#endif

#ifdef openw
do_delta_tz();//поправка TZ для начала суток, если TZ не кратна 3
#endif

end_setup:;

#ifdef tft_no_invert
tft.invertDisplay( false );
#endif

tft.setTextSize(1);
if (log_file)
{
log_str=(F("-----------end setup"));
do_log();  
}




}



// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL 
//                                lOOP
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL 
void loop() {

//wwww
if (!play) 
server.handleClient();


if (WiFi.getMode()==WIFI_AP){
	if (millis() >t_stay_ap){
		if (log_file){
			log_str=(F("ESP reboot after WIFI AP"));
			do_log();  
		}
		ESP.restart(); 
	}
//если по какой то причине сразу не приконн.
//перегр через 700sec.
	goto skip_all;
} 
//--------------------------------------

#ifdef ESP32
//begin-stop play 
if (t_timer!=0)
	do_timer();
#endif

//WIFI read data
#ifdef wf_read
if (WiFi.status() == WL_CONNECTED) do_wf_read();
#endif


//-------------------Sensors------------- --------------

//IR----------------------
#if defined (pin_ir) && defined (ESP32)
do_read_ir32();
#endif

#ifdef encoder
do_encoder();
#endif


#if defined (pin_ir) && defined (ESP8266)
do_read_ir8266();
#endif


//pin_btn------------------------
#if defined (pin_btn_touch) && defined( ESP32)
do_touch_btn(1);
#endif


#if defined (pin_btn_No_touch) && defined(ESP8266)
if (digitalRead(pin_btn_No_touch)==LOW)
{
scr_number++;
scr_num_show(scr_number);
}
#endif //ESP8266 pin_btn_No_touch


#if defined (pin_btn_No_touch) && defined( ESP32)
do_touch_btn(2);
#endif //ESP32 pin_btn_No_touch

//FTP
#ifdef ftp
if (WiFi.status() == WL_CONNECTED)
	ftpSrv.handleFTP();   
#endif

//ntp not sync
if (!sync_t||sync_force==true)
	do_ntp();

 // openw  before t=now()---------------
#ifdef openw
if (!play&&!play_mp3)  do_openw(); //zapros openW
#endif  //ow

#ifdef domoticz
if (!play&&!play_mp3)  do_domoticz(); //zapros domoticz
#endif  //ow

//--------------- раз в минуту   ---------------------------   
if (sync_t)  
{
	t=now();
#ifdef  time_correct 
	now_correct() ;
#endif
	do_every_min();  //shed,beep,scr_sav,restart  t=now();
}

#ifdef only_radio //если  одно радио опрос лок. сенсоров
	read_sensors_radio();
#endif //radio

//========================================================================
//            IF  NOT PLAY
//========================================================================
#ifndef only_radio //если  одно радио этот блок искл.

if (!play&&!play_mp3)      
                    {

//ioT  ThingSpeak send
#ifdef IoT
if (iot_id>0&&WiFi.status() == WL_CONNECTED) do_send_iot();  
#endif

//ioT  ThingSpeak read
#ifdef IoT
if (iot_id_read>0&&WiFi.status() == WL_CONNECTED) do_read_iot();  
#endif


///OTA
#ifdef ota_update
if (WiFi.status() == WL_CONNECTED) ArduinoOTA.handle();
#endif
                      

//ntp
do_ntp();

   
#ifdef nrf
do_read_ulica();   
#endif
#ifdef  pin_ds1820
do_read_ds1820();
#endif
#ifdef bme280
do_read_bme();
#endif
#ifdef si7021
do_read_si7021();
#endif          


#ifdef pin_dht
do_read_dht();
#endif   

#ifdef wf_send
if (WiFi.status() == WL_CONNECTED) do_wf_send();
#endif

//-----------scr saver----------------------
if (t_ref_tft>0&&t_ref_tft<60&&minute(t)%t_ref_tft==0) 
    {
		if (ref_tft==true)
		{
		ref_tft=false;
		//scr_num_show(scr_number); 
		refresh_all=true;  
		tft.fillScreen(TFT_BLACK);

		}
    }  else ref_tft=true  ;
//----------------


#ifdef Sn
//nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
if ((hour(t)>=t_b && hour(t)<t_e&&t_b<t_e)||(hour(t)>=t_b && hour(t)>t_e&&t_b>t_e)||(hour(t)<t_b && hour(t)<t_e&&t_b>t_e))
  {
if (nigth==false)  //1 raz
      {

if (scr_name[scr_number]=="Sn" )
do_find_scr(scr_name_def);// //если найдет будет по умолч иначе ночной останется
scr_number_prev=scr_number; 

nigth=true;
if (do_find_scr("Sn")) scr_num_show(scr_number);//refresh tft
      }
 
  }
    else   //день

if (nigth==true)
{  
//выход с ноч часов
nigth=false;
scr_num_show(scr_number_prev);
}
#endif 

//экраны по кругу----RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
#ifdef  openw
if(!nigth&&scr_name[scr_number]!="Sn"&& scr_show_count>1&&scr_round)
do_scr_round();
#endif


#if !defined (openw) &&   defined (tft_320_240)
if(!nigth&&scr_name[scr_number]!="Sn"&& scr_show_count>1 && scr_round)
do_scr_round();
#endif

#if !defined (openw) &&   defined (tft_480_320)
if(!nigth&&scr_show_count>1&&scr_round)
do_scr_round();
#endif


//sssssssssssssssssssssssssssssssssssssssssssssss
#if defined (S1) && defined (openw) 
if (scr_name[scr_number]=="S1") S1_time(); 
#endif

#if defined (S2) && defined (openw) 
if (scr_name[scr_number]=="S2") S2_time(); 
#endif

//--------S3-----------------tft_320_240
#if defined (S3) && defined (openw) && defined(tft_320_240)
#if defined (tft2_S3) 
if (ref_wh==true)
{
tft2_act=true;
S3_show();
tft2_act=false;
}
//#endif
#else

if (scr_name[scr_number]=="S3"&&(ref_wh==true||refresh_all==true))
{
S3_show();
}
#endif


#endif //S3 tft_320_240


//tft_480_320 S3
#if defined (S3) && defined (openw) && defined(tft_480_320)
if (scr_name[scr_number]=="S3")
{
S3_time(); 
}
#endif //tft_480_320 S3


//-------------S4--------tft_320_240
#if defined (S4) && defined (openw) && defined(tft_320_240)
#if defined (tft2_S4) 
if (ref_wh==true)
{
tft2_act=true;
S4_show_ch();
tft2_act=false;
}
//#endif
#else

if (scr_name[scr_number]=="S4"&&(ref_wh==true||refresh_all==true))
S4_show_ch();

#endif

#endif //S4


#if defined (S0) && defined(tft_320_240) && !defined (openw) 
if (scr_name[scr_number]=="S0") S0_time(); 
#endif

#if defined (S5) && defined (openw) && defined(tft_320_240)
if (scr_name[scr_number]=="S5") S5_time(); 
#endif

#if defined (Sn)
if (scr_name[scr_number]=="Sn") Sn_time();
#endif

#if defined (pin_sd) && defined (Sf)
if (scr_name[scr_number]=="Sf") Sf_time(); 
#endif

//-------------------Sg----------------------------------
#if defined (Sg) && defined (openw)

//#if defined (two_tft) && defined (tft_320_240)
#ifdef tft2_Sg
if (ref_wh==true)
{
tft2_act=true;
Sg_show();
tft2_act=false;
}
//#endif
#else
if (scr_name[scr_number]=="Sg"&&(ref_wh==true||refresh_all==true))
Sg_show();
#endif


#endif //Sg



//-------------------scr_round----------------------------------
if (!scr_round&&second(t)%5==0 ) draw_stop_round(); //draw stop around 
}
//---------------------IF  NOT PLAY

#endif //not radio




//===============================================
//radio
//===============================================
#ifdef ESP32  

if (play_mp3) do_play_mp3();//beep mp3

if (!play_mp3&&play_alarm) //после сигнала запуск радио по расп.
  {
  play_alarm=false;
  do_alarm_i(); 
  }


if (play) 
  {
do_scr_play();
do_play();
  }

#endif  //esp32
            
#ifdef pin_ir
if (refresh_all)
{
irrecv.resume(); // принимаем следующую команду

}
#endif


refresh_all=false;
ref_kv_th=false;
ref_wh=false;
ref_wh_now=false;

               
skip_all:;

}

// E---loop---EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE


//------------------------------------------------------------------------------------
//                        do_every_min
//------------------------------------------------------------------------------------

void do_every_min()
{
byte mm=minute(t); 
byte hh=hour(t); 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
if (last_minute!=mm)
          { 
  
last_minute=mm;
#ifdef debug
show_time_start();
#endif

do_c_frame() ;//color frame Tu Tkv


//в начале часа принудительно обновляю погоду
#ifdef openw
if (WiFi.status() == WL_CONNECTED) 
{
if (mm==7) lastConnectionTime_ch = 0;
if (mm==6) lastConnectionTime_now = 0;
}
#endif //openw


//radio ESP32
#ifdef ESP32   
//read file shed alarm
if (mm==0||last_minute==99||mm>=t_next_shed)
do_read_file_shed();
else
if (!play&& mm%t_period_read_alarm_txt==0)
do_read_file_shed();


if (beep_mp3_vol!=0&&!nigth&&scr_name[scr_number]!="Sn"&&mm==0) //искл ночь и ночной экран
{
if (beep_b<beep_e&&hh>=beep_b&&hh<=beep_e) do_create_mp3();
}




//--------------- раз в минуту      
if (WiFi.status() == WL_CONNECTED) 
  {       
//do alarm web radio or mp3
if (al.m==mm && (al.label=='I'||al.label=='i') )
  { 
if (play_mp3) play_alarm=true; //если играет сигнал стартую после него
else 
do_alarm_i(); 
  
  }
         
         
  }       //WL_CONNECTED  
            



#endif //esp32 
      }
      



//hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh

if (last_hour!=hh) //раз в час и была синхр-я
                    {
last_hour=hh;
//начало суток, удаляю старый лог
if (log_file&&mm==0&&hh==0)
  {
 String fileName;
if (day(t)%2==0) fileName="/log0.txt";
else
fileName="/log1.txt";
SPIFFS.remove(fileName);
SPIFFS.remove("/log.txt");
//Serial.println("log_file remove");
  }


//beep
#ifdef pin_beep

if (beep_b<beep_e&&mm==0&&hh>=beep_b&&hh<=beep_e&&!nigth&&scr_name[scr_number]!="Sn" )
do_beep(fr,dur);
#endif




//reset раз в сутки в 2 ч ночи чтобы работало надо после прошивки вручную сделать reset
if(millis()>600000&&hh==esp_restarts&&mm<5&&t_timer==0) //раз в сутки
  {
Serial.println(F("ESP.reset()"));
if (log_file)
{
log_str=(F("ESP reboot sheduler"));
do_log();  
}


#ifdef ESP8266
ESP.reset();
#endif
#ifdef ESP32
ESP.restart();
#endif

  }


                        }
            
                    }
