



#ifdef nrf 

//=======================================================
//                nrf24
//=======================================================
void do_read_ulica() 
{

static uint32_t t_fn=0;
byte pipeNo;

if (millis()-period_ulica<600000&&period_ulica!=0) 
{
return; 
}

if (millis()-t_fn<1000) 
{
return; 
}
t_fn=millis();


if (millis()-period_ulica>t_ds_ref*1000L)
temp_u=200;
//Serial.println("read ulica");
 if ( radio.available(&pipeNo)) // Non-blocking
    {

uint8_t buff[32];
uint8_t len = sizeof(buff);

int i;  
radio.read( &buff, sizeof(buff) ); 
 
String strth= (const char*) buff;
Serial.println(strth);
////////////////////////определяю пакет

if (strth.substring(0,6)=="25UTH;")
{

if (strth.indexOf(";",7)!=9&& strth.indexOf(";",10)!=13)
{
Serial.println(F("ошибка разбора"));
delay(500);
}
else
{

Serial.print(F("ulica="));
Serial.println(strth);
//ppppp
String sth=strth.substring(6,9); //3 simv 
if (sth.toInt()>150&&sth.toInt()<260)
 {
  
if (temp_u!= sth.toInt()-200) 
ref_temp_u=true;    

temp_u=sth.toInt()-200;
period_ulica=millis();

if (log_file)
{
log_str="nrf24 do_read_ulica temp_u="+String(temp_u);
do_log();  
}


 }

 
  }

  




}
  
  } 
   
    }
     
#endif



//================================================================
//                        ds1820
//================================================================
#ifdef pin_ds1820
void do_read_ds1820()
{
static uint32_t t_period_ds=0;

if (millis()<t_period_ds&&temp_u!=200) //уже были данные
return; 
t_period_ds=millis()+10000; 



ds.requestTemperatures();                               // считываем температуру с датчиков, на это требуется 750мс
#ifdef  debug
Serial.print(F("ds== ")); 
Serial.println(ds.getTempCByIndex(0));                    // отправляем температуру
#endif  
int tmp_u=int(round(ds.getTempCByIndex(0)));


if (tmp_u<60&&tmp_u>-60)
{
if (temp_u!=tmp_u) ref_temp_u=true;

temp_u=tmp_u;
period_ulica=millis();

if (log_file)
{
log_str="ds1820 ="+String(temp_u);
do_log();  
}


t_period_ds=millis()+t_ds_ref*1000; //5min

}
else
{
temp_u=200;
if (log_file)
{
log_str=(F("ds1820 ERR"));
do_log();  
}
}

}
#endif

//================================================================
//                        domoticz
//================================================================

#ifdef t_sensor_domoticz

void do_read_domoticz()
{
static uint32_t t_period_domoticz=0;

if (millis()<t_period_domoticz) //уже были данные
	return;
	
t_period_domoticz=millis()+10000; 

//ds.requestTemperatures();                         // считываем температуру с датчиков

#ifdef  debug
//Serial.print(F("== ")); 
//Serial.println(ds.getTempCByIndex(0));                    // отправляем температуру
#endif  

int tmp_u=0; //int(round(ds.getTempCByIndex(0)));


if (tmp_u<60&&tmp_u>-60)
{
if (temp_u!=tmp_u) ref_temp_u=true;

temp_u=tmp_u;
period_ulica=millis();

t_period_domoticz=millis()+t_domoticz_ref*1000; //5min

}
else {
	temp_u=200;
}

}
#endif


//================================================================
//                    bme280
//================================================================
#ifdef bme280
void do_read_bme()
{
static time_t t_period_bme=0;

if (millis()<t_period_bme&&temp_kv!=200) return; //5min

t_period_bme=millis()+10000; 


//float temp(NAN), hum(NAN), pres(NAN);
float temp=200, hum=200, pres=200;

BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_hPa);
sensor_bme.read(pres, temp, hum, tempUnit, presUnit);

#ifndef hPa
pr_kv=round(pres*0.75);
#else
pr_kv=pres;
#endif




if (pr_kv>10000) 
{	


if (log_file)
	{
log_str="bme280 ERR P="+String(pr_kv);
do_log();  
	}

pr_kv=200;//err
}



temp_kv=round(temp);
h_kv=round(hum);

#ifdef debug
Serial.println(F("bme------------------"));
Serial.println(pr_kv);
Serial.println(temp_kv);
Serial.println(h_kv);
#endif 

if (temp_kv<-50||temp_kv>70) temp_kv=200;
if (h_kv<0||h_kv>100)  h_kv=200;
if (temp_kv!=200)
{
ref_kv_th=true;
t_read_tk=millis();
t_period_bme=millis()+t_bme_ref*1000; //5min
}
}
#endif

//================================================================
//                        si7021
//================================================================
#ifdef si7021
void do_read_si7021()
{
static time_t t_period_bme=0;

if (millis()<t_period_bme&&temp_kv!=200) return; //5min
t_period_bme=millis()+10000; 
float hum= sensor_si.getRH();
float temp = (sensor_si.getTempF()-32)/1.8;
temp_kv=round(temp);
h_kv=round(hum);

#ifdef debug
Serial.println(F("si------------------"));
Serial.println(temp_kv);
Serial.println(h_kv);
#endif debug


if (temp_kv<-50||temp_kv>70) 
	{

if (log_file)
{
log_str="si7021 ERR temp_kv="+String(temp_kv);
do_log();  
}

temp_kv=200;
	}
	
if (h_kv<0||h_kv>100)  
	{

if (log_file)
{
log_str="si7021 ERR H="+String(h_kv);
do_log();  
}
		
h_kv=200;
	}

if (temp_kv!=200) 
{
ref_kv_th=true;
t_read_tk=millis();
t_period_bme=millis()+t_bme_ref*1000; //5min
}


}
#endif





//================================================================
//                        DHT
//================================================================
#ifdef pin_dht
void do_read_dht()
{
static time_t t_period_bme=0;

if (millis()<t_period_bme&&temp_kv!=200) return; //5min
t_period_bme=millis()+10000; 
float hum= dht.readHumidity();
float temp = dht.readTemperature();
temp_kv=round(temp);
h_kv=round(hum);



#ifdef debug
Serial.println(F("si------------------"));
Serial.println(temp_kv);
Serial.println(h_kv);
#endif debug


if (temp_kv<-50||temp_kv>70) 
  {

if (log_file)
{
log_str="DHT  ERR temp_kv="+String(temp_kv);
do_log();  
}

temp_kv=200;
  }
  
if (h_kv<0||h_kv>100)  
  {

if (log_file)
{
log_str="DHT ERR H="+String(h_kv);
do_log();  
}
    
h_kv=200;
  }

if (temp_kv!=200) 
{
ref_kv_th=true;
t_read_tk=millis();
t_period_bme=millis()+t_bme_ref*1000; //5min
}


}
#endif
