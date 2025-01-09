//имя точки доступа и пароль будут читаться
// с ЕСП флеш (/data/wifi), при первом запуске надо с подкл. телефоном к wifi сети ESP_METEO, password = "11111111"
// зайти с ТЕДЕФОНА! на  192.168.11.11 и сохранить ssid и password, 
//(если страница не открывается не загружена папка /data в SPIFFS)
// теперь вы не привязаны  к одной точке, если AP не найдена,
// esp запускается в режиме точки с адресом 192.168.11.11, файл с конфиг на spiffs ->"wifi"
//можно в лоб забить перед загрузкой в SPIFFS(SD) /wifi (enter в конце строки)
//AP/password in the file / data/wifi (at the end of the line ENTER)

//если ESP32 то пины с D.. например D4 надо изменить на 12 (GPIO),  иначе ошибка компиляции
// если настройка или датчик не используется надо закомментировать #define 
//if control or the sensor is not used it is necessary to comment out #define
char  ver[]= "030320";
//--------------------------------

#define debug  //можно закомментировать, будет меньше отладочной инф. и больше памяти

//--------------------------------

//#define only_radio  //ESP32!!! только  интернет радио, один экран радио/only Internet radio+(bme,ds,dht,si), one screen radio+local sensors

//--------------------------------

//=====================================================================|
//#define EN   //lang (by default RU)
//#define hPa  //pressure hPa (by default RU мм/рт.столба)
//---------------------------------------------------------------------


//=====================================================================|
//выбрать разрешение дисплея / to choose resolution of the display     |
//=====================================================================|
#define tft_320_240              //                                    |
//#define tft_480_320            //                                    |

const uint8_t rotation=1; //1,3 3-SD сверху/top
//#define tft_no_invert     //если цвета в инверсии раскомментировать/if the colors in the inversion are uncomment


//=====================================================================|
// если 2 TFT tft_320_240 //if 2 tft_320_240 adafruit lib tft2_Sg,tft2_S3,tft2_S4
//=====================================================================|
//#define  two_tft

#if defined (two_tft) && defined (tft_320_240)
#define tft2_S4 // какой экран, только tft2_Sg,tft2_S3 или  tft2_S4//what screen, only tft2_Sg,tft2_S3 or tft2_S4
const uint8_t rotation2=3; // TFT num=2 // 1,3 3-SD сверху/top

//PIN TFT 1--------------
#define TFT_CLK   18   
#define TFT_MOSI  23   
#define TFT_CS    5
#define TFT_RST   -1 
#define TFT_DC    33
#define TFT_MISO  -1

//PIN TFT 2---------------
#define TFT_CLK2  14   
#define TFT_MOSI2 13   
#define TFT_CS2   15
#define TFT_RST2  -1 
#define TFT_DC2    2
#define TFT_MISO2  -1


#endif
//=====================================================================|






//=====================================================================|
//                    Encoder Module  EC11  KY-040 With Pins           
//
//влево-вправо смена эрана, короткое нажатие старт радио , 
//долгое нажатие-режим цифр, далее короткое старт радио на заданном канале, долгое старт таймера
//если радио--> влево, вправо цифры, далее долгое таймер, короткое переход на канал;
//долгое mute;нажать+влево-вправо громкость; короткое выход из таймера или стоп
//left-right screen change, short press start radio , 
//long press-digit mode, then short start of the radio on the specified channel, long start of the timer
//if radio--> left, right numbers, then long timer, short jump to channel;
//long mute; press + left-right volume; short exit timer or stop



//=====================================================================|
//#define encoder //если есть энкодер раскомм=ть

  #ifdef encoder
#define CLK  16//D2//16
#define DT 17//D1//17
#define SW 4//D0//5  //кнопка 
#define TYPE 1 // 0 или 1 (полушаговый энкодер или полношаговый) более подробно смотри в GyverEncoder.h 
const int t_enc_num_clear=3000; // msec через сколько очищать выбор цифр

#define fav_count 4   //избранные каналы двойной клик /data/i_stat.txt favorite channels Double Click
  
  #endif

//=====================================================================|




//=====================================================================|
//          SD card + FOTO                                              |
//=====================================================================|

//#define pin_sd  32// 32//D2//22 //GPIO card  esp8266 D2

//файлы фото в папке foto на SD и пронумерованы от 1  (1-99999.jpg)    
//важно!!! скопировать все файлы /data/*.jpg (openW) в корневой SD карты
//важно!!! если esp8266 раскомментировать в файле  (if esp8266 in the file uncomment)
//TFT_eSPI\User_Setups\Setupx_xxxxx.h  #define SUPPORT_TRANSACTIONS

// время показа фото sec ->config.txt->Sf_t_slide
//time of demonstration of a photo sec ->config.txt->Sf_t_slide def=30sec
#define Sf_show_time//показывать время на фото  /Show time in photos
#define Sf_show_date//показывать дату на фото  /Show date in photos
#define Sf_show_Tu//показывать уличная темп. /show street T           
#define Sf_show_icon//показывать иконку погоды. /show icon openW          

#define Sf_show_TH//показывать темп./влажность кв. /show T/H          

#define A0_free //если pin A0 свободен, расскомментируйте для случайного показа фото
                //if pin A0 is free, uncomment for random photo display

const unsigned int Sf_c_clock=TFT_YELLOW; //   цвет часов                       
const unsigned int Sf_c_scr_frame=TFT_YELLOW;    //цвет рамки экрана/color of a frame of the screen

//=====================================================================|



//==============================ESP32==parallel========================|
// если ESP32 c параллельным  интерфейсом  и периодически сбиваются часы, раскомментировать
//If the parallel interface ESP32 and the clock are periodically lost, uncomment
//                                                                     |
//#define  time_correct //only  esp32 parallel                         |
//                                                                     |
//=====================================================================|

 



#define ota_update 
const char ota_name[]="meteo"; 
const unsigned int  t_period_read_alarm_txt=5;//1-59 minute  period read alarm.txt esp32
#define http_update   // ex. http://192.168.100.xx/update
#define ftp           // esp8266/esp8266    //username, password for ftp
//#define IoT          //https://www.thingspeak.com /data/iot.txt



//==============================ESP32===DAC=====================|
      //3.3V from ESP32 -> VCC, 3.3V, XMT                        |
      //GND from ESP32  -> GND, FLT, DMP, FMT                   |
//#define set_audio_mono //ESP32 web radio mono (def stereo)    |
const  byte t_ref_song_period=120;//скорость отрисовки песни    |
//#define PCM5102 //ESP32 external DAC (def internal 25,26 pin) |
#ifdef PCM5102  //pins DAC                                      |
const int bclkPin=16;   //                                      |
const int wclkPin=26;   //                                      | 
const int doutPin=25;   //                                      |
#endif                  //                                      |
//==============================ESP32===========================|


//====================================================================
//              Domoticz
//====================================================================

#define  domoticz
#ifdef domoticz
//http://192.168.1.20:8080/json.htm?type=devices&rid=92";
const String url_domoticzIn="http://192.168.1.20:8080/json.htm?type=command&param=getdevices&rid=92";
//http://192.168.1.20:8080/json.htm?type=devices&rid=104
const String url_domoticzOut="http://192.168.1.20:8080/json.htm?type=command&param=getdevices&rid=104";
long  t_period_domoticz = 60;    // sec частота запросов контроллера domoticz
#endif

//====================================================================
//              openWeatherMap
//====================================================================
        //если есть ключ погоды и он записан  в /data/config.txt!!!
        //If there is a weather key and it is written in/data/config.txt!
        // если нет ключа , закомментировать #define  openw будут просто часы + датчики
        //If there is no key, comment # define openw will simply be a clock+sensors
//#define  openw

#ifdef openw  //if there is openW key. if is not present there will be just hours, to comment out #define openw
long t_period_ch=1200; //частота запросов погоды 1200сек=20мин (openw 1 time 20 min.) 60sec*20
long t_period_now=900; // now

        //RAIN      RAIN        RAIN        RAIN
        // сигн-ция осадков 
        //rain one point<rain_l ;rain_l<two  point <rain_m ; three point>rain_m (for three hours),>rain_m*2 blinks
float rain_l=0.5; //сигнализация точками, если кол-во дождя  меньше 0.5мм одна точка, за 3 часовой период
float rain_m=1; //0.5-1.00мм вкл средний две точки, больше сильный 3т.если >rain_m*2 мигает

#endif //openW
//-----------------------------------------------


//====================================================================
//      NTP       NTP           NTP           NTP
//====================================================================
        //откуда берем время  4 варианта, можно свои
        //where we take the time, you can your servers
		//используем 1 вариант - локальный сервер
const unsigned long t_period_ntp=3600000; //частота запросов NTP 1 час
const char* ntpServerName1 = "192.168.1.20"; 	 // Home IoT sever (domoticz, hass)
const char* ntpServerName2 = "ntp5.stratum2.ru"; //резервный ntp
const char* ntpServerName3 = "time.nist.gov";
const char* ntpServerName4 = "by.pool.ntp.org";
//---------------------------------------------------------




//====================================================================
//      WI_SEND         WI_SEND       WI_SEND       WI_SEND
//====================================================================
    //передача по WIFI если передавать нечего закомм-ть #define wf_send
    //если есть датчики BME,DS,Si то можно передать на другие станции
    // if there are sensors BME, DS, Si, then you can transmit to other stations

//#define wf_send //temp_kv temp_u h_kv
//------------------
#ifdef wf_send
        //что передавать, закомм-ть что не надо
#define wf_send_Tu  //temp_u Темп улица (the outside)
#define wf_send_Tk  //temp_kv Темп кв если есть bme280 или si7021  (room temperature)
#define wf_send_Hh   //h_kv  влаж кв если есть bme280 или si7021   (room humidity)
//#define wf_send_Cm  //command  просто команда
#endif
//----------------------------------------------------------



//====================================================================
//      WI_READ     WI_READ         WI_READ         WI_READ
//====================================================================
    //приём по WIFI других станций, если не надо принимать по wifi закомментировть #define wf_read
    //какие данные будем слушать что не надо закомм-ть
    //reception from other stations

//#define wf_read  //будем слушать

#ifdef wf_read
#define wf_read_Tu  //temp_u Темп улица, если есть DS или NRF надо закомментир.
#define wf_read_Tk  //temp_kv Темп кв если стоит bme280 или si7021 надо закомм-ть
#define wf_read_Hh   //h_kv  влаж кв если стоит bme280 или si7021 надо закомм-ть
#define wf_read_Cm  //command  просто команда
#endif
//--------------------------------------------------------


//====================================================================
//       WI-FI reconn,esp restart
//====================================================================
const byte ntp_count_rep=5;//количество неуд. попыток синхр. время, до reconnect                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ол-во попыток передачи данных по udp
const unsigned long t_ntp_rep_err=300000;//5мин, время между неудачнывми попытками ntp (время уже синхр)
        //reconnect=ntp_count_rep*t_ntp_rep_err 
const byte wifi_count_rep=3;//количество reconnect, после перегрузить 
        //reboot=reconnect*wifi_count_rep
const unsigned long wifi_rep_t=40000;//время sec попытки соед. с АП, затем запуск как точки доступа
const unsigned long t_stay_ap=600000;//время как точки доступа, потом перегрузить
//---------------WI-FI



//====================================================================
//      кнопка        button        кнопка     button
//====================================================================
    //если нет кнопки можно закомм-ть #pin_btn_No_touch #define pin_btn_touch
    // esp8266,esp32  pin_btn_No_touch кнопка с пина на массу PULL_UP
    // esp32 pin_btn_touch пин на TOUCH PIN, замыкается касанием руки
    // if there is no button you can // #pin_btn_No_touch  pin_btn_touch
    // esp8266,esp32 pin_btn_No_touch  button from pin to ground PULL_UP
    // esp32 pin on the TOUCH PIN, closes with a hand touch

//#define pin_btn_No_touch   17  // PULL_UP esp8266-D2,  esp32-17   кнопка на землю/grounding button GPIOs 34 to 39 don’t have internal pull-ups or pull-down resistors
              // или or
//#define pin_btn_touch  4 //  esp32-4 только ESP32/ only ESP32
              //touch value
const int touch_value=20; //меньше этого значения считаю нажатой (esp32)
//---------------------------------------------------------


//====================================================================
//IR      IR        IR            IR          IR
///====================================================================

      //IR VS1838B ик приемник пин для инет радио или переключения экранов
      // если нет IR приемника закоммент эту строку #define pin_ir 
      // VS1838B IR sensor
      //if there is no IR receiver to comment out this line #define pin_ir

//#define pin_ir D1  ////esp8266 D1, esp32 34 
const int t_ir_sleep=1500; //ms от залипания пульта пауза 
const int t_ir_sleep_short=500;//"vl+""vl-""mute",btn(0-9)
//---------------------------------------------------


//====================================================================
//NRF24     NRF24       NRF24         NRF24
//====================================================================

      //внешняя температура либо NRF либо DS18b20
      //если нет приёма по nrf с закомментировать #define nrf 1  
//#define nrf    //D0,D4 esp8266 
#ifdef nrf
const byte CEnrf=0; //Chip Enable
const byte CSnrf=4; //Chip Select
#endif
//---------------------------------------------------

      //ИЛИ or

//====================================================================
//      DS18B20       DS18B20           DS18B20
//====================================================================

      //DS18B20 температура с датчика DS18B20 улица
      //если нет надо можно закомм-ть #define pin_ds1820
      //outdoor temperature
//#define pin_ds1820  D4  //D4
const unsigned int t_ds_ref=300 ;//DS18B20, DomoticzOut, sec T ref sensor, период обновления датчика
//---------------------------------------------------


//====================================================================
//BME280 or HTU21D or SI7021 or DHT      BME280 or HTU21D or SI7021    or DHT
//====================================================================
      //Si7021  если нет датчика закомментировать #define si7021

//#define si7021 1  //room
      //ИЛИ OR
      //bme280 если нет датчика bme(bmp) закомментировать #define bme280 
//#define bme280 1   //room
       //ИЛИ OR
//#define pin_dht D1   //room   выьрать ниже DHTTYPE (DHT 11 or DHT 22 or DHT 21)

  #ifdef pin_dht
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22     // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)             
  #endif

                      // Digital pin connected to the DHT sensor
                      // Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
                      // Pin 15 can work but DHT must be disconnected during program upload.




const unsigned int t_bme_ref=300 ;//sec T ref sensor, период обновления датчика SI,BME,DHT,DomoticzIn 5min def
//------------------------------------------------




//====================================================================
//    BEEP          BEEP              BEEP    BEEP
//====================================================================

      //BEEP any pin если не будем использовать зуммер, #define pin_beep закомментировать 

//#define pin_beep D0 

      //пассивный ИЛИ  активный зуммер
#ifdef pin_beep //passive or active
//#define beep_pass //пассивный sound buzzer passive
#define beep_act  //активный  sound buzzer active
#endif
      //beep настройка пасс зумм. если #define pin_beep не закоммент., каждый час (с beep_b,по beep_e) 0-23
unsigned int fr=900; //частота
unsigned int dur=70; //длит
//---------------------------------------------------




//====================================================================
//                  Screen
//====================================================================
      //если не надо закомментировать #define  Sxx (if no screen is needed then //#define Sxx)
//S0 - 320_240 no openW; S1-S9 - if openW ;Sf - if SD; Sn - night; 
		#ifdef openw
#define  S1 // clock 3ч/5d  S1.jpg
const byte S_t_bme=255; //0-255sec (Scr1)сколько показывать темп,влаж bme280 /how many seconds to show bme280
const byte S_t_moon=5; //sec луна how many seconds to show moon
#define  S2 //big clock  S2.jpg
#define  S3 //график diagram 3ч/5d  S3.jpg 320-240, 3h 480-320

#define  S4 //график 3x18=54hour S4.jpg

#define  S5 // litle clock 4day/3h S5.jpg
#ifdef S5
const byte S5_t_ch=20; //сколько секунд показывать 3 часовой прогноз на S5 , дальше на 4 дня 
      //how many seconds to show 3 hour forecast for S5, 4 days further
const byte S5_t_day=30; //сколько секунд показывать дневной прогноз
#endif
#define  Sg //графики /graphics Sg.jpg 

                       
		#endif //openW


#define  Sn //ночь и основной экран для 480_320 если нет openW, night and main screen for 480_320 if not #define openw for 480_320
#define Sf //фоторамка, если #define pin_sd /photo frame if #define pin_sd


#ifndef openw  //если нет openW будет экран по умолчанию, часы +датчики/if there is no openW there will be a default screen, clock +sensors
  #ifdef tft_320_240
#define  S0 //big clock NO OPENW S0.jpg
  #endif
#endif

const byte scr_count=10;
const byte t_ref_tft=30; //scrsaver  min 0<t_ref_tft<60 обновление экрана /updating of the screen scrsaver minute(t)%t_ref_tft==0
//-----------------------------------------------------



//====================================================================
//      COLOR         COLOR             COLOR
//====================================================================
      // цвета описание
#define c_pr_ow  0x07E0 //цвет давления с opeW / Pressure colour with opeW

#define c_pr_bme 0x8FF8 //цвет давления с BME / Pressure color with BME
      //если проблема с бме, будет показано давление с openw, по цвету будет видно
#define c_holiday TFT_ORANGE  //цвет выходных в графике и календаре день недели
#define c_working 0x87E0 //цвет рабочих дней //color of the working days
#define c_date 0xB7FF  //цвет, DD
#define c_month 0xE720  //цвет, MM


//scr5 color 320-240
#if defined (S5) && defined(tft_320_240) 
const int S5_color_clock=0xFFF1; //цвет часов на S5 //color of hours on S5
#endif

 //scr3 color 480_320
#if defined (S3) && defined(tft_480_320)
const int S3_color_clock=0xFFF9; //цвет часов на S3 //color of hours on S5
#endif

#if defined (Sg) //цвет ветра восток,запад на графике/color of wind East, West
const int Sg_c_wing_E=TFT_LIGHTGREY; //восточный ветер
const int Sg_c_wing_W=TFT_GREEN; //западный

#endif


//nigth
const int Sn_color_sec=0x87F0; //цвет секунд scr nigth

      //webradio
//#define c_channel TFT_LIGHTGREY //цвет списка каналов webradio/ color of the list of channels
#define c_channel TFT_LIGHTGREY //цвет списка каналов webradio/ color of the list of channels
#define c_ch_line TFT_YELLOW // подчеркивание найденного канала /underlining of the found channel
#define c_ch_fnd TFT_YELLOW // цвет найденного канала в заголовке /Color of the found channel in the header

#define c_song TFT_YELLOW//цвет песни/ song
#define c_gr TFT_CYAN// //цвет группы/ groups


#ifdef openw
//-------UV------UV----------UV---------UV------------
      //цвета по диапазонам ультрафиолета
      //colors by UV range
const byte  uv1=3;
const int   uv1_color=TFT_GREEN; //< uv1<=3;
      //3<uv2<=6;
const byte  uv2=6;
const int   uv2_color=TFT_GREENYELLOW;
      //6<uv3<=8
const byte  uv3=8;
const int   uv3_color=TFT_YELLOW;
      //8<uv4<=11
const byte  uv4=11;
const int   uv4_color=TFT_RED;
      //11<uv3<=20
const byte  uv5=20;
const int   uv5_color=TFT_PURPLE;

#endif //openw

//============Temp=======Temp========Temp=========Temp=========
      //диапазоны и цвет температуры
      //temperature ranges and color
signed char t4=30;
const int   t4_color=0xFA28; //temp>+30

signed char t3=25;
const int   t3_color=0xFCC6;//+30>temp>+25

signed char t2=17;
const int   t2_color=0xFFE0;//temp>+17

signed char t1=10;
const int   t1_color=0xFFF0; //temp>+10

signed char t0=0;
const int   t0_color=0xFFF9; //temp>0

signed char t_1=-10;
const int   t_1_color=0x07DF; //temp>-10

signed char t_2=-15;
const int   t_2_color=0x067F; //temp>-15

const int   t_3_color=TFT_BLUE; //temp=<t_1
//-----------------------------------------------------



//====================================================================
//    wifi_const      wifi_const         wifi_const
//====================================================================
#if defined (wf_send)||defined (wf_read)
const uint32_t wf_step = 15000; //с какой частотой прд прм wifi
const uint16_t localPort_wf = 54333; // Local port wifi
      //заголовки передачи
const String k_temp_u="25Tu;"; // T улица
const String k_temp_kv="25Tk;"; // T кв
const String k_h_kv="25Hh;";    // влажность
const String k_cmd="25Cm;"; //своя команда
String cmd="";//команда для примера сделал  Sn-след экран (для ver.IK), bp-beep,bp2->2 раза beep, rl реле
#endif
//---------------------------------------------------



//-----------------------------------------------------
//для примера управления по wifi реле
//-----------------------------------------------------
//
//#define pin_rele D0 //
#ifdef pin_rele
bool rele_on_off =false;
#endif
//-----------------------------------------------------


#if defined (S4) && defined(tft_480_320)&& defined (openw) 
#undef S4
#endif

#if defined (S5) && defined(tft_480_320)&& defined (openw) 
#undef S5
#endif


#ifdef ESP8266
#undef only_radio   
#endif



#ifdef pin_sd
#undef ftp   //no spiffs
#endif

#ifndef pin_sd
#undef Sf
#endif


#ifdef only_radio
#undef openw
#undef Sn
#undef S0
#undef Sf
#endif


  #if defined (two_tft) &&  !defined (tft_320_240)
#error " ERROR #define two_tft and not  #define tft_320_240"
  #endif
 #if defined (two_tft) && !defined (ESP32)
#error " ERROR #define two_tft only for ESP32"
  #endif

#if defined (two_tft) && defined (only_radio)
#error " ERROR conflict #define two_tft and  #define only_radio"
 #endif
