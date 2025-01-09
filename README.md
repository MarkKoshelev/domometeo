Дисплей для отображения метеоданных ( температуры снаружи и внутри помещения) времени и других данных
сделан на базе проекта метеостанции 
Андрея Ушакова
https://drive.google.com/drive/folders/1nht9dprk7TboV0oQjyIuHXSKkqBiuIdQ
версии meteo-030320

заполнить свои данные или перенести / to enter the data
Settings_meteo.h 
/data/config.txt
/data/i_stat.txt
/data/alarm.txt
/data/ik.txt
/data/wifi
!!!важно в Settings_meteo.h выбрать разрешение 
#define tft_320_240 или or #define tft_480_320
настроить драйвер дисплея в файлах библиотеки TFT_ESPI
/User_Setup_Select.h
/User_Setups/Setupxxxx.h pins
если подключена SD (FTP не будет)
для ESP8266 включить #define SUPPORT_TRANSACTIONS в /User_Setups/Setupxxxx.h
для ESP32 SD и TFT должны подключены к VSPI
------------------------------------------------------
------------------------------------------------------


============030320_test.zip=====================
обновление проекта под два дисплея//updating the project for two displays
ESP32+ 2 tft ili9341 320x240 (adafruit lib)
in Settings_meteo.h
===================
#define tft_320_240
#define  two_tft
#define tft2_Sg // какой экран, только tft2_Sg,tft2_S3 или  tft2_S4//what screen, only tft2_Sg,tft2_S3 or tft2_S4
-------------------
#define Sf_show_date//показывать дату на фото  /Show date in photos

rename  #define radio -----> #define only_radio
============020220_test.zip=====================
in Settings_meteo.h
--------------------
1
#define radio  //только  интернет радио+датчики, один экран радио
/only Internet radio, one screen radio+sensors
2
#define  Sg //добавил экран графики погоды /
Added a weather graphics screen   Sg.jpg 
3
rotation=1; //1,3 (3-SD сверху/SD top TFT)
4
#define encoder //см. в setting.

5
#define pin_dht D1   //DHT temp,h room -->DHT11 или DHT22 или DHT21
			   //НЕ ТЕСТИРОВАЛ
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)             




============151219_test.zip=====================
-ESP8266 для SD в /User_Setups/Setupxxxx.h раскомм-ть
#define SUPPORT_TRANSACTIONS
- ESP32 SD и TFT должны подключены к VSPI

Settings_meteo.h
#define pin_sd

config.txt
#Sf_show;10; //длительность показа экрана, если включено xx_show>1 
#Sf_t_slide;10; длительность показа фото

-ik.txt кнопке "0" к остановке показа песни, если режим play,
добавил стоп экраны по кругу, если включено в config.txt

//--------iot read------------------
#iot_id_read;12345567;
#iot_key_read;JNASCSACASCSDCVDS;
#iot_period_read;25;
#iot_T_fld_read;1; темп кв
#iot_H_fld_read;2; влажность кв
#iot_T2_fld_read;3; темп улица
#iot_P_fld_read;4;  давление


============241119_test.zip=====================
Settings_meteo.h
-если ESP32 c параллельным  интерфейсом  и периодически сбиваются часы, раскомментировать
If the parallel interface ESP32 and the clock are periodically lost, uncomment
#define  time_correct 

#define pin_btn_No_touch   PULL_UP кнопка на землю/grounding button GPIOs 34 to 39 don’t have internal pull-ups or pull-down resistors
или or
#define pin_btn_touch только ESP32/ only ESP32


#define c_month 0xB596  //цвет месяца в дате/month color in date
#define c_pr_ow  0x07E0 //цвет давления с opeW / Pressure colour with opeW
#define c_pr_bme 0x8FF8 //цвет давления с BME / Pressure color with BME


- alarm.txt (t begin(hour);t end(h))
период работы канала/period of operation of the channel

- S2,S3 tft 480-320

============301019_test.zip=====================
- перевод на TFT_ESPI для совместимости проектов
- parser исправлен с учетом timezone
- добавлен parser текущего запроса / add parser now
-#log;; (//#log;;) config.txt запись лога за 2 дня (ntp,parse,датчики)/Log entry in 2 days (ntp, parse, sensors)
-#define IoT   в Settings_meteo, передача данных (Ткв Тул Нкв P ск ветра,осадки)
настраивается в config.txt (номер канала,ключ интервал, что передавать) 
#Define IoT in Settings_meteo, data transmission (T1 T2 H P wind,rain mm)
Is configured in config.txt (channel number, key interval, what to transmit)
---------------------------------------------

- экраны по кругу настройка в config.txt
#S1_show;60;#S2_show;60;#S3_show;60;
(screens around control in config.txt)
- PCM1501 DAC смотри в Settings_meteo.h
#define PCM1501

- обновление через http (update http:/your ip/update)
#define http_update 

- esp32 планировщик, заполнить data/alarm.txt по шаблону (esp32 the scheduler to fill /data/alarm.txt on a template)
- esp32 web radio (заполнить i_stat.txt по шаблону)
- esp32 beep.mp3 сигнал каждый час, искл. ночь и ночной экран
(signal each hour, exception night and night screen)
config.txt 


28.06.19--------------------------------------------------
- добавил экран S5 с настройками цвета
added the S5 screen with color settings 
Settings_meteo.h  (S5.jpg)
#define S5

- мелкие исправления / small corrections
