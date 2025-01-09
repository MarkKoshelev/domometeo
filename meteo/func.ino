//------------------------------------------------------------------------------
//                        do_scr_round
//------------------------------------------------------------------------------

void do_scr_round()
{

static uint32_t t_next=0;
static uint32_t t_start=0;

static uint32_t t_S1_next=0;
static uint32_t t_S2_next=0;
static uint32_t t_S3_next=0;
static uint32_t t_S4_next=0;
static uint32_t t_S5_next=0;
static uint32_t t_Sf_next=0;
static uint32_t t_S0_next=0;
static uint32_t t_Sg_next=0;
//если сейчас на экране кот не учавствует в круге выхожу


//if (day_ch[0]==0) return; //нет данных о погоде

if (t_start>0) //второй проход, считаю дельту
{
t_next=t_next+(millis()-t_start); //поправка на прорисовку экрана,2-4сек
t_start=0;  
}




if (millis()<t_next) return;

Serial.println(F("do_scr_round()"));

//--------------------
  #ifdef openw

//1
#ifdef S1
if(t_S1_show>0&& millis()>t_S1_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S1_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
if (do_find_scr("S1")) scr_num_show(scr_number);
Serial.println(F("S1_show"));
t_next=millis()+t_S1_show*1000;
t_start=millis();

return;
}
#endif


//2
#ifdef S2
if(t_S2_show>0&& millis()>t_S2_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S2_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
if (do_find_scr("S2")) scr_num_show(scr_number);
Serial.println(F("S2_show"));
t_next=millis()+t_S2_show*1000;
t_start=millis();
return;
}
#endif

//3
#ifdef S3
if(t_S3_show>0&& millis()>t_S3_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S3_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
if (do_find_scr("S3")) scr_num_show(scr_number);
Serial.println(F("S3_show"));
t_next=millis()+t_S3_show*1000;
t_start=millis();
return;
}
#endif


//4
#ifdef S4
if(t_S4_show>0&& millis()>t_S4_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S4_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
Serial.println(F("S4_show"));
t_next=millis()+t_S4_show*1000;
t_start=millis();
return;
}
#endif


//5
#ifdef S5
if(t_S5_show>0&& millis()>t_S5_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S5_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
          
if (do_find_scr("S5")) scr_num_show(scr_number);
Serial.println(F("S5_show"));
t_next=millis()+t_S5_show*1000;
t_start=millis();
return;
}
#endif



//Sf
#ifdef Sf
if(t_Sf_show>0&&max_jpg_num>0 && millis()>t_Sf_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_Sf_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
if (do_find_scr("Sf")) scr_num_show(scr_number);
Serial.println(F("Sf_show"));
t_next=millis()+t_Sf_show*1000;
t_start=millis();
return;
}
#endif



//Sg
#ifdef Sg
if(t_Sg_show>0&& millis()>t_Sg_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_Sg_next=millis()+t_S1_show*1000+t_S2_show*1000+t_S3_show*1000+t_S4_show*1000+t_S5_show*1000+t_Sf_show*1000+t_Sg_show*1000;
          
if (do_find_scr("Sg")) scr_num_show(scr_number);
Serial.println(F("Sg_show"));
t_next=millis()+t_Sg_show*1000;
t_start=millis();
return;
}
#endif


  #endif   //openw
//--------------------



//--------------------
  #if !defined (openw) &&   defined (tft_320_240)
//0

if(t_S0_show>0&&max_jpg_num>0 && millis()>t_S0_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S0_next=millis()+t_S0_show*1000+t_Sf_show*1000;
if (do_find_scr("S0")) scr_num_show(scr_number);
Serial.println(F("S0_show"));
t_next=millis()+t_S0_show*1000;
t_start=millis();
return;
}


//F
#ifdef Sf
if(t_Sf_show>0&&max_jpg_num>0 && millis()>t_Sf_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_Sf_next=millis()+t_S0_show*1000+t_Sf_show*1000;
if (do_find_scr("Sf")) scr_num_show(scr_number);
Serial.println(F("Sf_show"));
t_next=millis()+t_Sf_show*1000;
t_start=millis();
return;
}
#endif  

  #endif  //!defined (openw) &&   defined (tft_320_240)
//--------------------



//--------------------
#if !defined (openw) &&   defined (tft_480_320)


if(t_S0_show>0&&max_jpg_num>0 && millis()>t_S0_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_S0_next=millis()+t_S0_show*1000+t_Sf_show*1000;
if (do_find_scr("Sn")) scr_num_show(scr_number);  //Sn=S0
Serial.println(F("S0_show"));
t_next=millis()+t_S0_show*1000;
t_start=millis();
return;
}

//F
#ifdef Sf
if(t_Sf_show>0&&max_jpg_num>0 && millis()>t_Sf_next)  //second(t) чтобы сначало прорисовал минуты >2sec
{
t_Sf_next=millis()+t_S0_show*1000+t_Sf_show*1000;
if (do_find_scr("Sf")) scr_num_show(scr_number);
Serial.println(F("Sf_show"));
t_next=millis()+t_Sf_show*1000;
t_start=millis();
return;
}
#endif  //Sf

#endif //!defined (openw) &&   defined (tft_480_320)
//--------------------


  
}


//voshod zah
void do_sun()
  {
    

  
TimeLord tardis; 

tardis.TimeZone(TIMEZONE * 60);
byte len;
char Str[20]="";
len=lat.length()+1; 
lat.toCharArray(Str,len);    // копирование String в массив myStr8
float latf = atof(Str);  //  преобразование в float
Serial.print ("latf ");
Serial.println (latf);


//Str[20]="";
len=lon.length()+1; 
lon.toCharArray(Str,len);    // копирование String в массив myStr8
float lonf = atof(Str);  //  преобразование в float

Serial.print ("lonf ");
Serial.println (lonf);


  
  tardis.Position(latf,lonf); // tell TimeLord where in the world we are
time_t tm =now(); 
  byte today[] = {  0, 0, 12,day(tm) ,month(tm), year(tm)-2000    }; // store today's date (at noon) in an array for TimeLord to use

if (tardis.SunRise(today)) // if the sun will rise today (it might not, in the [ant]arctic)
  
   {
 // t_sun_v="";
 t_sun_v=do_sun_format(today[tl_hour],today[tl_minute]);

  t_sun_v_hh=today[tl_hour];
/*
  
   if (today[tl_hour]<10) t_sun_v="0";
   t_sun_v=t_sun_v+(String) today[tl_hour]+":";
   
   if (today[tl_minute]<10) t_sun_v=t_sun_v+"0";
      t_sun_v=t_sun_v+(String) today[tl_minute];
  */ 
   }
   
   if (tardis.SunSet(today)) // if the sun will set today (it might not, in the [ant]arctic)
   {
  //t_sun_z="";
  t_sun_z=do_sun_format(today[tl_hour],today[tl_minute]);

  t_sun_z_hh=today[tl_hour];
/*
   if (today[tl_hour]<10) t_sun_z="0";
   t_sun_z=t_sun_z+(String) today[tl_hour]+":";
   
   if (today[tl_minute]<10) t_sun_z=t_sun_z+"0";
      t_sun_z=t_sun_z+(String) today[tl_minute];
  */ 
   }
Serial.println(t_sun_v);
Serial.println(t_sun_z); 

  
 }


//--------------------------------------------------------------
//            do_sun_format()
//--------------------------------------------------------------
String do_sun_format(byte h,byte m)
{
String str="";

   if (h<10) str="0";
   str=str+(String)h+":";
   
   if (m<10) str=str+"0";
      str=str+(String)m;

return str;
  
}


//--------------------------------------------------------------------
//                     do_phasemoon
//--------------------------------------------------------------------
String do_phasemoon()
{

time_t t =now();   
byte the_time_moon[] = {0, 0, 0, day(t),month(t), year(t)-2000};
float ph=myLord.MoonPhase(the_time_moon);



byte f;
if (ph<0.02085) f=23;
else
if (ph<0.06255) f=0;
else
if (ph<0.10425) f=1;
else
if (ph<0.14595) f=2;
else
if (ph<0.18765) f=3;
else
if (ph<0.22935) f=4;
else
if (ph<0.27105) f=5;
else
if (ph<0.31275) f=6;
else
if (ph<0.35445) f=7;
else
if (ph<0.39615) f=8;
else
if (ph<0.43785) f=9;
else
if (ph<0.47955) f=10;
else
if (ph<0.52125) f=11;
else
if (ph<0.56295) f=12;
else
if (ph<0.60465) f=13;
else
if (ph<0.64635) f=14;
else
if (ph<0.68805) f=15;
else
if (ph<0.72975) f=16;
else
if (ph<0.77145) f=17;
else
if (ph<0.81315) f=18;
else
if (ph<0.85485) f=19;
else
if (ph<0.89655) f=20;
else
if (ph<0.93825) f=21;
else
if (ph<0.97995) f=22;
else
f=23;

String fl="/m"+String(f);

return fl;
}



///////////////////////////
//цвет температуры
unsigned int  color_t(int c) 
{
unsigned int col=0;;
if (c>t4) col=t4_color;
else
if (c>t3) col=t3_color;
else
if (c>t2) col=t2_color;
else
if (c>t1) col=t1_color;
else
if (c>t0) col=t0_color; //>0
else
if (c>t_1) col=t_1_color;
else
if (c>t_2) col=t_2_color;
else
col=t_3_color;
return col;
}






#ifdef pin_beep
//==========================================================
void do_beep(unsigned int Fr,unsigned int Dur)
{

#ifdef beep_act
   digitalWrite(pin_beep,HIGH ); // включаем пьезоизлучатель
    delay(Dur);  // на 1000 мс (1 сек),
   digitalWrite(pin_beep,LOW );
return;
#endif

#ifdef beep_pass
noTone(pin_beep);
tone (pin_beep,Fr); 
delay(Dur);
noTone(pin_beep);
#endif  


}


#endif




//==============================================================
//                    scr_num_show
//==============================================================

void scr_num_show(signed char num)
{

if (num==scr_count_pack)
scr_number=0;
else
if (num<0)
scr_number=scr_count_pack-1;
else
scr_number=num;

refresh_all=true;  
tft.fillScreen(TFT_BLACK);
#ifdef debug
Serial.print(F("scr_number=="));
Serial.println(scr_number);
#endif

}


//====================================================
//                    scr_pack()
//===================================================
void scr_pack( )
{
Serial.println(F("void scr_pack"));
Serial.println(F("init scr"));
char *scr_name_tmp[scr_count]={""}; //def  

for (byte i=0; i < scr_count; i++)
{
scr_name[i]="";
scr_name_tmp[i]="";
}

#ifdef S0 
scr_name[0]="S0";
Serial.println(F("scr_name[0]=S0"));
#endif



#ifdef S1 
scr_name[1]="S1";
Serial.println(F("scr_name[1]=S1"));
#endif

#ifdef S2 
scr_name[2]="S2";
Serial.println(F("scr_name[2]=S2"));
#endif

#ifdef S3 
#ifndef tft2_S3
scr_name[3]="S3";
Serial.println(F("scr_name[3]=S3"));
#endif
#endif

#ifdef S4
#ifndef tft2_S4
scr_name[4]="S4";
Serial.println(F("scr_name[4]=S4"));
#endif
#endif

#ifdef S5
scr_name[5]="S5";
Serial.println(F("scr_name[5]=S5"));
#endif


#if defined (pin_sd) && defined (Sf)
scr_name[6]="Sf";
Serial.println(F("scr_name[6]=Sf"));
#endif



#ifdef Sg 
#ifndef tft2_Sg
scr_name[7]="Sg";
Serial.println(F("scr_name[7]=Sg"));
#endif
#endif


#ifdef Sn //last
scr_name[9]="Sn";
Serial.println(F("scr_name[9]=Sn"));
#endif


byte i_in=0;


for (byte i=0; i < scr_count; i++)
{
//#ifdef debug
//Serial.print(F("scr_name=="));
//Serial.println(scr_name[i]);
//Serial.print(F(" i="));
//Serial.println(i);
//#endif

if (scr_name[i]!="") 
{
//Serial.println("ADD");
scr_name_tmp[i_in]= scr_name[i];
i_in++;
scr_count_pack=i_in;

}

scr_name[i]="";
}  

#ifdef debug
Serial.print("scr_count_pack=");
Serial.println(scr_count_pack);
#endif
for (byte i=0; i < scr_count; i++)
{
scr_name[i]=scr_name_tmp[i];
Serial.print("SCR[");Serial.print(i);Serial.print("]=");
Serial.println(scr_name[i]);
}  


}




//=========================================================
//                        do_find_scr
//=========================================================

bool do_find_scr(char sname[ ] ) 
{
bool fnd=false;
Serial.print("do_find_scr=");Serial.println(sname);
Serial.print("sizeoff sname =");Serial.println(sizeof(sname));
for (byte i = 0; i < scr_count; ++i) 
{ 
//#ifdef debug
//Serial.print("scr_name[i] =");Serial.println(sizeof(scr_name[i]));
//#endif
if ( strcmp(scr_name[i],sname) == 0 )
      {
fnd=true;
Serial.print("Scr find=");Serial.println(i);

scr_number=i;

break;
      }

}
if (!fnd) Serial.print(F("NO find scr_name "));
Serial.println(sname);


return fnd;
}



//--------------------------------------------------------------------
//        draw_week_day
//--------------------------------------------------------------------

void draw_week_day(int x,int y)
{
//день недели-------------------------
//t=now();
byte wd=weekday(t)-1;
if (wd==0) wd=7;

#ifdef EN
drawJpeg("/w"+String(wd)+"e.jpg",x,y);//220
#else
drawJpeg("/w"+String(wd)+".jpg",x,y);//220
#endif
}

//--------------------------------------------------------------------
//        draw_tr_up
//--------------------------------------------------------------------
void draw_tr_up(int x,int y)
{
#ifdef tft_320_240 
tft.drawTriangle(x,y,x+6,y,x+3,y-10,TFT_YELLOW);
#endif

#ifdef tft_480_320
tft.drawTriangle(x,y,x+6,y,x+3,y-12,TFT_YELLOW);
#endif
  
}


//--------------------------------------------------------------------
//        draw_tr_down
//--------------------------------------------------------------------
void draw_tr_down(int x,int y)
{
#ifdef tft_320_240 
tft.drawTriangle(x+3,y,x,y-10,x+6,y-10,TFT_CYAN);
#endif

#ifdef tft_480_320
tft.drawTriangle(x+3,y,x,y-12,x+6,y-12,TFT_CYAN);
#endif

  
}








//=====================================================================
//                            show_time_start
//=====================================================================

#ifdef debug
void show_time_start()
{
Serial.print(F("start esp="));
int time=millis()/1000;
if (time/60/60<10) { Serial.print ("0"); }
Serial.print (time/60/60);
Serial.print (":");
if (time/60%60<10) { Serial.print ("0"); }
Serial.print ((time/60)%60);
Serial.print (":");
if (time%60<10) { Serial.print ("0"); }
Serial.println (time%60);
}
#endif




//=====================================================================
//                            draw_next
//=====================================================================
void draw_next()
{
if (play) tft.fillTriangle(120,65,105,60,105,70,TFT_GREEN);
else
tft.fillTriangle(20,10,5,5,5,15,TFT_GREEN);
 
}



//=====================================================================
//                            draw_prev
//=====================================================================

void draw_prev()
{
if (play) tft.fillTriangle(120,60,120,70,105,65,TFT_YELLOW);
else
tft.fillTriangle(20,5,20,15,5,10,TFT_YELLOW);
} 





//=====================================================================
//                            draw_stop
//=====================================================================

void  draw_stop()
{

tft.fillCircle(120,65,4,TFT_RED);    

}



//=====================================================================
//                            draw_play
//=====================================================================

void  draw_play() //на главном экране
{
if (play)
tft.fillCircle(135,20,4,TFT_RED);
else
tft.fillCircle(15,15,4,TFT_RED);   

}




//=====================================================================
//                            draw_stop_round
//=====================================================================
void draw_stop_round()
{

#ifdef tft_320_240
if (scr_round) 
tft.fillTriangle(300,0,319,0,319,10,TFT_BLACK);
else
tft.fillTriangle(300,0,319,0,319,10,TFT_RED);
#endif



#ifdef tft_480_320
if (scr_round) 
tft.fillTriangle(460,0,479,0,479,10,TFT_BLACK);
else
tft.fillTriangle(460,0,479,0,479,10,TFT_RED);
#endif
  


}





//==========================================================================================
//  tft_320_240          S_show_th_room
//==========================================================================================
#if defined(tft_320_240)
void S_show_th_room(int x,int y)
{
if (temp_kv==200&&h_kv==200) return;

tft.fillRect(x,y,44,38,TFT_BLACK);
tft.drawRoundRect(x,y,44,38,3,c_th_frame);

tft.setTextColor(TFT_YELLOW);
if (temp_kv!=200) //bme 270,73
  {
tft.setFreeFont(v9);
tft.setCursor(x+4,y+16);
tft.print(temp_kv);
tft.setFreeFont(v6);
tft.setTextColor(TFT_WHITE);
tft.print("c");
  }
if (h_kv!=200) //bme
  {  
tft.setFreeFont(v9);
tft.setTextColor(TFT_CYAN);
tft.setCursor(x+4,y+33);
tft.print(h_kv);
tft.setFreeFont(v6);
tft.setTextColor(TFT_WHITE);
tft.print("%");
  }


}

#endif





//====================================================
// tft_480_320        S_show_th_room
//====================================================
#if defined(tft_480_320)
void S_show_th_room(int x,int y)
{


if (temp_kv==200&&h_kv==200) return; //нет данных bme


tft.fillRect(x,y,52,57,TFT_BLACK);
tft.drawRoundRect(x,y,52,57,4,c_th_frame);
tft.setTextColor(TFT_YELLOW);
tft.setFreeFont(v12);

if (temp_kv!=200) //bme
{
tft.setCursor(x+5,y+23);
tft.print(temp_kv);
tft.setTextColor(TFT_WHITE);
tft.setFreeFont(v6);
tft.print("C");
}
if (h_kv!=200) //bme
  {
tft.setTextColor(TFT_CYAN);
tft.setFreeFont(v12);
tft.setCursor(x+5,y+52);
tft.print(h_kv);
tft.setTextColor(TFT_WHITE);
tft.setFreeFont(v6);
tft.print("%");
  }

}
#endif



//------------------------------------------------------------------------------------------
//                              do_c_frame          
//------------------------------------------------------------------------------------------
void do_c_frame() //color frame
{

if (period_ulica==0) c_tu_frame=TFT_CYAN;
else
if (millis()>period_ulica+t_ds_ref*1000L*2)  c_tu_frame=TFT_RED;
else
c_tu_frame=TFT_YELLOW;



if (t_read_tk==0) c_tu_frame=TFT_CYAN;
else
if (millis()>t_read_tk+t_bme_ref*1000L*3)  c_th_frame=TFT_RED;
else
c_th_frame=TFT_YELLOW;


}




#ifdef debug
//------------------------------------------------------------------------------------------
//                              do_show_define          
//------------------------------------------------------------------------------------------
void do_show_define()
{


Serial.println( "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__);
Serial.print(F( "Arduino IDE version: "));Serial.println( ARDUINO, DEC);
print_define (ver,0);


#ifdef ESP8266
print_define ("ESP8266",0);
#endif


#ifdef ESP32
print_define ("ESP32",0);
#endif


#ifdef debug
print_define ("debug",0);
#endif


#ifdef tft_320_240
print_define ("tft_320_240",0);
#endif

#ifdef tft_480_320
print_define ("tft_480_320",0);
#endif



#if defined (two_tft) && defined (tft_320_240) && defined (tft2_S3) 
print_define ("two_tft tft2_S3",0);
#endif



#if defined (two_tft) && defined (tft_320_240) && defined (tft2_S4) 
print_define ("two_tft tft2_S4",0);
#endif


#if defined (two_tft) && defined (tft_320_240) && defined (tft2_Sg) 
print_define ("two_tft tft2_Sg",0);
#endif



#ifdef only_radio
print_define ("only_radio",0);
#endif


#ifdef pin_sd
print_define ("pin_sd",pin_sd);
#endif


#ifdef ota_update
print_define ("ota_update",0);
#endif




#ifdef http_update
print_define ("http_update",0);
#endif


#ifdef ftp
print_define ("ftp",0);
#endif


#ifdef IoT
print_define ("IoT",0);
#endif


#ifdef PCM5102
print_define ("PCM5102",0);
#endif

#ifdef openw
print_define ("openw",0);
#endif

  #ifdef wf_send
print_define ("wf_send",0);
#ifdef wf_send_Tu
print_define ("wf_send_Tu",0);
#endif  
#ifdef wf_send_Tk
print_define ("wf_send_Tk",0);
#endif  
#ifdef wf_send_Hh
print_define ("wf_send_Hh",0);
#endif  

  #endif

  #ifdef wf_read
print_define ("wf_read",0);
#ifdef wf_read_Tu
print_define ("wf_read_Tu",0);
#endif  
#ifdef wf_read_Tk
print_define ("wf_read_Tk",0);
#endif  
#ifdef wf_read_Hh
print_define ("wf_read_Hh",0);
#endif  
  #endif

#ifdef pin_btn_No_touch
print_define ("pin_btn_No_touch",pin_btn_No_touch);
#endif


#ifdef pin_btn_touch
print_define ("pin_btn_touch",pin_btn_touch);
#endif

#ifdef pin_ir
print_define ("pin_ir",pin_ir);
#endif

#ifdef nrf
pin_btn_touch ("nrf",0);
#endif

#ifdef pin_ds1820
print_define ("pin_ds1820",pin_ds1820);
#endif

#ifdef si7021
print_define ("si7021",0);
#endif

#ifdef bme280
print_define ("bme280",0);
#endif


#ifdef pin_dht
print_define ("pin_dht",pin_dht);
#endif



#ifdef pin_beep
print_define ("pin_beep",pin_beep);
#endif



#ifdef encoder
print_define ("enc_CLK",CLK);
print_define ("enc_DT",DT);
print_define ("enc_SW",SW);
print_define ("enc_TYPE",TYPE);
#endif



#ifdef only_radio
print_define ("only radio",0);

#endif


}

//------------------------------------------------------------------------------------------
//                              print_define          
//------------------------------------------------------------------------------------------
void print_define(char * n_def,byte pin)
{
static byte x=0;
static byte y=15;
static byte n=1;

if (pin==0) 
{
Serial.print(F("#define "));
Serial.println(n_def);
tft.setCursor(x,y);
tft.setTextColor(TFT_LIGHTGREY);
tft.print("# ");
tft.println(n_def);

}
else
{
Serial.print(F("#define "));
Serial.print(n_def);
Serial.print(F(" pin="));
Serial.println(pin);
tft.setCursor(x,y);
tft.setTextColor(TFT_LIGHTGREY);
tft.print("# ");
tft.print(n_def);
tft.setTextColor(TFT_CYAN);
tft.print(" pin=");
tft.println(pin);
}
n++;
if (n%2==0) 
{
x=155;

  
}
else
{
y=y+15;
x=0;  
}

  
}

#endif //debug




//------------------------------------------------------------------------------------------
//                              read_sensors_radio          
//------------------------------------------------------------------------------------------


#ifdef only_radio //если  одно радио опрос лок. сенсоров
void read_sensors_radio()
{
///OTA
#ifdef ota_update
if (WiFi.status() == WL_CONNECTED) ArduinoOTA.handle();
#endif

//ntp
do_ntp();

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
  
}

#endif
