#ifdef ESP32
//===============================================================================================================
//                  do_scr_play()
//===============================================================================================================

void do_scr_play()
{
static byte ch_tmp=254; //init ch
static time_t t_pause_song=0;

//////////////////////////////////////////
if (refresh_all) //первое вкл экрана
{
ch_tmp=254;
show_song=true;
#ifdef tft_480_320 
tft.drawFastHLine(0,50,479,TFT_LIGHTGREY);//под песней
tft.drawFastHLine(130,75,349,TFT_LIGHTGREY) ;//ch
#endif
#ifdef tft_320_240 
tft.drawFastHLine(0,50,319,TFT_LIGHTGREY);//под песней
tft.drawFastHLine(130,75,189,TFT_LIGHTGREY) ;//ch
#endif



tft.drawFastVLine(130,50,150,TFT_LIGHTGREY);
#ifdef tft_480_320 
tft.drawFastHLine(0,200,130,TFT_LIGHTGREY) ; //под часами
#endif
#ifdef tft_320_240 
tft.drawFastHLine(0,200,320,TFT_LIGHTGREY) ; //под часами
#endif
do_draw_clock();
do_draw_h_m();


#if defined(tft_320_240)&& defined (openw) 
do_show_th_play_ow();
#elif defined(tft_320_240)
do_show_th_no_ow();
#elif defined(tft_480_320)
do_show_th_n();
#endif


draw_vol();
draw_mem();


}



//канал смена ccccccccccccccccccccccccccc
if (ch_tmp!=ch)
{

Serial.println("ch_tmp!=ch");
tft.fillRect(131,51,189,23,TFT_BLACK);//ch
tft.setFreeFont(v9mono);
tft.setTextColor(TFT_YELLOW);
tft.setCursor(134,68);
tft.setTextColor(TFT_WHITE);
tft.print(ch);tft.print(F(". "));
tft.setTextColor(c_ch_fnd);

tft.print(ch_name.substring(0,14));
draw_mem();
ch_tmp=ch;
draw_vol();


#if defined(tft_320_240)&& defined (openw) 
do_show_th_play_ow();
#elif defined(tft_320_240)
do_show_th_no_ow();
#elif defined(tft_480_320)
do_show_th_n();
#endif

//pause show song
t_pause_song=millis()+7000;


}


//--ssssssssssssssssssssssssssssssssssssssssssssss
//что играет
if (millis()>t_pause_song )
do_draw_song();

//hh:mm
do_draw_h_m();


 
 }




//==============================================================
//              do_draw_song()
//==============================================================
  
void do_draw_song()
{

static byte play_g_ch=0,play_s_ch=0;
static byte x1=0,x2=0;
static String play_g="",play_s="";
static unsigned long t_ref_song=0;
static bool begin_draw=true,song_find;


if (millis()<t_ref_song) return;
if (new_song==false&&begin_draw==false) return;
if (new_song==true) begin_draw=false;//сброс начинаю рисовать с нуля
if (begin_draw==false)
            {
//init
begin_draw=true;
new_song=false;
play_s_ch=0;
play_g_ch=0;
play_g="",play_s="";
//xx=0;
x1=0;
x2=0;

int zn=play_song.indexOf(" - ");//есть группа и песня
if (zn>0)
{
play_g=play_song.substring(0,zn);
play_g.trim();
play_g=play_g.substring(0,32);

play_s=play_song.substring(zn+3);
play_s.trim();
play_s=play_s.substring(0,32);

#ifdef debug
Serial.print("play_g=");
Serial.println(play_g);
Serial.print("play_s=");
Serial.println(play_s);
#endif

song_find=true;
       }
       else //делю пополам
       {
play_g=play_song.substring(0,32);
play_s=play_song.substring(32);

song_find=false;        
       }
       



          }//init

//-----------------------------


if (show_song==false) 
{
return;
}


tft.setFreeFont(v9mono);
t_ref_song=millis()+t_ref_song_period;


if (x1<32) //закраска 
{
tft.fillRect(x1*10,0,10,22,TFT_BLACK);
x1++;
yield();
return;
}


//группа
if (play_g_ch<play_g.length())
{
tft.setCursor(play_g_ch*10,20);
tft.setTextColor(c_gr,TFT_BLACK);
tft.print(play_g.substring(play_g_ch,play_g_ch+1));
play_g_ch++; 
yield();
return;
}




if (x2<32) //закраска 
{
tft.fillRect(x2*10,22,10,25,TFT_BLACK);
x2++;
yield();
return;
}

//song
if (song_find) tft.setTextColor(c_song,TFT_BLACK);
if (play_s_ch<play_s.length())
{
tft.setCursor(play_s_ch*10,40);
tft.print(play_s.substring(play_s_ch,play_s_ch+1));
play_s_ch++; 
yield();
return;
}

//if (xx<32) return;//дозакраска
if (x1<32||x2<32) return;//дозакраска



begin_draw=false;//

}//-------------------------------


 
//=============================================================
//                          do_draw_h_m()
//=============================================================

void do_draw_h_m()
{
//static unsigned long next_mill=0;
static byte last_min=0;
static byte last_hour=0;
static byte  a_m,a_ch;

//time_t t =now();

if (last_min==minute(t)&&!refresh_all) {return;} 
do_show_min(last_min,TFT_BLACK);
do_show_min(minute(t),TFT_CYAN);

//////////////hour
do_show_hour(last_hour,last_min,TFT_BLACK);
do_show_hour(hour(t),minute(t),TFT_YELLOW);


last_min=minute(t);
last_hour=hour(t);

if (refresh_all)
{
a_m=99;a_ch=0;
}

byte t_next=99;
byte ch_next=0;

if (al.m>last_min) {t_next=al.m;ch_next=al.ch_num; } //еще не стартовал план.
else 
if (t_next_shed!=99) {t_next=t_next_shed;ch_next=next_shed_ch;} //есть след план.
else
{
t_next=99;
ch_next=0;
}

if(a_m!=t_next&&t_next!=99)
{
a_m=t_next;a_ch=ch_next;
tft.setFreeFont(v6);
tft.fillRect(0,170,36,12,TFT_BLACK); 

tft.setTextColor(TFT_WHITE);
tft.setCursor(0,181);
if (last_hour<10) tft.print("0");
tft.print(last_hour);tft.print(":");
if (a_m<10) tft.print("0");
tft.print(a_m);
tft.print(" ");
tft.setTextColor(TFT_YELLOW,TFT_RED);
tft.print(a_ch);
  
}


if (last_min==0&&last_hour==0) //начало суток обн дату
{
refresh_all=true;

#if defined(tft_320_240)&& defined (openw) 
do_show_th_play_ow();
#elif defined(tft_320_240)
do_show_th_no_ow();
#elif defined(tft_480_320)
do_show_th_n();
#endif

 refresh_all=false; 
}

  
}




//====================================================================
//                      do_show_th_play_ow openw 
//====================================================================
#if defined(tft_320_240)&& defined (openw) 
void do_show_th_play_ow()
{
Serial.println("do_show_th_play openW");  
int  temp;
if (refresh_all)  tft.fillRect(0,201,320,38, TFT_BLACK);
temp=temperatura_ch[0];


if (temp_u!=200)
{
temp=temp_u;
}

 

tft.drawFastVLine(113,200,39,c_tu_frame) ;



///ttttttttttttttttttttttttttttt
tft.setFreeFont(v18);
tft.setTextColor(color_t(temp));
if (!refresh_all) tft.fillRect(160,201,70,39,TFT_BLACK);
tft.setCursor(160,235);
if (temp!=200) tft.print(temp);
if (ref_temp_u) ref_temp_u=false;
if (!refresh_all) return;  



String st="";
if (day(t)<10) 
st="0"+String(day(t));
else
st=String(day(t));

tft.setFreeFont(v12);
tft.setTextColor(c_date);
tft.setCursor(0,230);
tft.print(st);

if (month(t)<10) 
st="0"+String(month(t));
else
st=String(month(t));
st="."+st;
tft.setFreeFont(v9);
tft.setTextColor(c_month);
tft.print(st);

//weekwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

draw_week_day(63,207);



//rrrrrrrrrrrrrrrrrrrrrrrrrrrrr
do_draw_rain(120,210,rain_ch[0],TFT_CYAN);

//icon 
drawJpeg(icon_ch[0]+"32.jpg",125,205);// текущая погода




//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int gr=int(v_gr_ch[0]);
do_deg(gr);
tft.drawFastVLine(229,200,39,TFT_LIGHTGREY) ;
drawJpeg(wind_ico,230,205);
tft.setFreeFont(v6);
tft.setCursor(254,238);
tft.setTextColor(TFT_CYAN);
tft.print(v_ch[0]);
//hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
S_show_th_room(272,202);

}
#endif //openw




//=====================================================================
//                            draw_vol
//=====================================================================
void draw_vol()
{
tft.drawFastVLine(124,119,80,TFT_BLACK);
tft.drawFastVLine(126,119,80,TFT_BLACK);

int color;
if (volume>300) color=TFT_MAGENTA;
else
if (volume>150) color=TFT_YELLOW;
else color=TFT_GREEN;


int vol=volume/8;
tft.drawFastVLine(124,199-vol,vol,color);
tft.drawFastVLine(126,199-vol,vol,color);

//------------
tft.fillRect(93,180,30,16,TFT_BLACK);
tft.setFreeFont(v9mono);

if (volume>0) 
{
tft.setTextColor(color);
tft.setCursor(94,195);
tft.print(int(volume/4));
}
else
{
tft.setTextColor(TFT_RED);
tft.setCursor(94,195);
tft.print("M");  
}

  
}



//=====================================================================
//                            timer_stop
//=====================================================================
void timer_stop()
{
t_timer=0;
draw_num(0,'T');

}

//=====================================================================
//                            draw_num
//=====================================================================
void draw_num(int b,char c)
{

int color;
byte x,y;
if (c=='T') //отрисовка таймера
color=TFT_RED;//timer
else
color=TFT_WHITE;//ch



if (play&&c=='T') 
{
tft.fillRect(5,58,35,14,TFT_BLACK);
x=5,y=70;  
}
else
if (play&&c=='C')  
{
x=95,y=70;   
tft.fillRect(95,58,32,14,TFT_BLACK);
}
else
if (!play)//все остальные экраны
{
x=0,y=15;  
tft.fillRect(0,0,35,20,TFT_BLACK);
//tft.drawRoundRect(x,y,30,20,3,color);
}


if (b==0) return; //просто стереть цифры

tft.setTextColor(color);
tft.setFreeFont(v9);
tft.setCursor(x,y);
tft.print(b);
}



//=====================================================================
//                            do_mute
//=====================================================================
void do_mute()
{
static int volume_tmp; //до mute
static bool mute=false; 
  
if (!mute)//mute on
  {
volume_tmp=volume;
volume=0;
  }
  else
 volume=volume_tmp;
 
mute=!mute;
out->SetGain(((float)volume)/100.0);
draw_vol();
 
}


//=====================================================================
//                            draw_mem
//=====================================================================
void draw_mem()
{
//mem
tft.setFreeFont(v6);
uint32_t mem_esp=ESP.getFreeHeap();
int color;
if (mem_esp>125000) color=TFT_GREEN;
else
if (mem_esp>90000) color=TFT_YELLOW;
else
if (mem_esp>0) color=TFT_RED;
tft.fillRect(0,185,90,12,TFT_BLACK); //mem
tft.setCursor(0,194);
tft.setTextColor(TFT_WHITE,TFT_BLACK);
tft.print("mem=");
tft.setTextColor(color,TFT_BLACK);
tft.print(String(mem_esp));
  
}



//=====================================================================
//                            draw_no_song
//=====================================================================
void draw_no_song()
{
show_song=!show_song;

#ifdef tft_320_240
if (show_song) 
tft.fillTriangle(300,0,319,0,319,10,TFT_BLACK);
else
tft.fillTriangle(300,0,319,0,319,10,TFT_RED);
#endif



#ifdef tft_480_320
if (show_song) 
tft.fillTriangle(460,0,479,0,479,10,TFT_BLACK);
else
tft.fillTriangle(460,0,479,0,479,10,TFT_RED);
#endif
  


}



#endif //ESP32
 
