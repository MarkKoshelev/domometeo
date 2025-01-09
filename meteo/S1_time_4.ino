#if defined (S1) && defined(tft_480_320)&& defined (openw) 

void S1_time()
{
static byte last_min=99;//чтобы не перирис минуты
static byte last_h=99;



//time_t mil=millis()/1000;

if (t%2==0)
{
if (err_ntp==0) 
tft.fillCircle(135,105,4,TFT_GREENYELLOW);
else
tft.fillCircle(135,105,4,TFT_RED);

S1_alert(false);

}
else
{
S1_alert(true);
 //sec
tft.fillCircle(135,105,4,TFT_BLACK);
}


if(refresh_all==true||ref_wh==true)
{
S1_show_now();
S1_wh_ch();    
S1_show_7day();
S1_graf_t();
S1_graf_davlenie();
}else
if (ref_temp_u==true||ref_wh_now==true) //есть данные с улицы
{
S1_show_now();

}

S1_th_moon(428,97);


//если мин не изм  и не надо все обновить выходим
//t =now(); 
if (last_min==minute(t)&&refresh_all==false) {return;}

//-----------------------------------------------------------------


last_min=minute(t);

last_h=hour(t);
//-------------------

//hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
String st,fileName ;

if (hour(t)<10) 
{
fileName="/n0_112.jpg";

drawJpeg(fileName,0,0);//220

fileName="/n"+String(hour(t))+"_112.jpg";


drawJpeg(fileName,64,0);//220
  }
else
{
st=String(hour(t));
fileName="/n"+st.substring(0,1)+"_112.jpg";

drawJpeg(fileName,0,0);//220

fileName="/n"+st.substring(1)+"_112.jpg";

drawJpeg(fileName,64,0);//220
 
}





//////////////////min///////////////////////////////

if (minute(t)<10) 
{
fileName="/n0_112.jpg";

drawJpeg(fileName,140,0);//220
S1_clear_min();
fileName="/n"+String(minute(t))+"_112.jpg";

drawJpeg(fileName,204,0);//220

  }
else
{
st=String(minute(t));
fileName="/n"+st.substring(0,1)+"_112.jpg";


drawJpeg(fileName,140,0);//220
fileName="/n"+st.substring(1)+"_112.jpg";

S1_clear_min();

drawJpeg(fileName,204,0);

}

//полоса поперек времени, если не надо закомм. след. 2 строки
//tft.drawFastHLine(0,55,270,TFT_BLACK) ;  
//tft.drawFastHLine(0,56,270,TFT_BLACK) ; 




//дата DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
if (refresh_all==false) 
  return;

/////day
tft.fillRect(0,115,280,44,TFT_BLACK);
tft.drawFastHLine(0,115,280,TFT_WHITE) ; 
tft.setTextColor(c_date);
tft.setFreeFont(v24);

String str="";
if (day(t)<10) 
str="0"+String(day(t));
else
str=String(day(t));


tft.setCursor(0,155);
tft.print(str);

if (month(t)<10) 
str="0"+String(month(t));
else
str=String(month(t));
tft.setFreeFont(v18b);
tft.setTextColor(c_month);
str="."+str;
tft.print(str);

//день недели-------------------------


byte wd=weekday(t)-1;
if (wd==0) wd=7;

#ifdef EN
drawJpeg("/w"+String(wd)+"e.jpg",132,124);//220
#else
drawJpeg("/w"+String(wd)+".jpg",132,124);//220
#endif
//zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz 
tft.drawFastVLine(190,115,45,0x07E0) ;
tft.setFreeFont(v9);
tft.setTextColor(TFT_YELLOW);
tft.setCursor(210,133);
tft.print(t_sun_v);
//zahod
tft.setTextColor(TFT_ORANGE);
tft.setCursor(210,153);
tft.print(t_sun_z);

}





//--------------------------------------------------------------
//        S1_th_moon()
//--------------------------------------------------------------
void S1_th_moon(int x,int y)
{
static uint32_t t_next_moon=0;
static uint32_t t_next_th=0;
static bool ref_moon=true;
static bool ref_th=true;
static bool show_moon=true; 

if (refresh_all==true||ref_temp_u==true||ref_wh_now==true||ref_wh==true) 
{
String fileName=do_phasemoon()+"_32.jpg";;
drawJpeg(fileName,x+10,y+10);  
t_next_moon=0;
t_next_th=0;
//if (S_t_moon==0) 
ref_th=true;
//if (S_t_bme==0||(temp_kv==200&&h_kv==200)) 
ref_moon=true;
show_moon=true; 
return;
}

//--------------------------------


if (millis()>t_next_th&&(temp_kv!=200||h_kv!=200)&&S_t_bme>0&&ref_th==true) 
  {
if (S_t_moon>0&&show_moon==true) 
{
S1_clear_moon(x,y);
S_show_th_room(x,y);
}
t_next_moon=millis()+S_t_bme*1000;
ref_th=false;
ref_moon=true;
show_moon=false; 
Serial.print(F( "t_next_moon==")); 
Serial.println(t_next_moon);

return;
  }

//MOON mmmmmmmmmmmmmmmm
if (millis()>t_next_moon&&S_t_moon>0&&ref_moon==true) 
  {
if (S_t_bme>0&&(show_moon==false))
{
S1_clear_moon(x,y);
String fileName=do_phasemoon()+"_32.jpg";;
drawJpeg(fileName,x+10,y+10);  
}
t_next_th=millis()+S_t_moon*1000;
ref_th=true;
ref_moon=false;
show_moon=true;
Serial.print(F( "t_next_th==")); 
Serial.println(t_next_th);

  }




}


//-------------------------------------------------------------
//                  S1_clear_moon
///-------------------------------------------------------------


void S1_clear_moon(int x,int y)
{

for (int i=0; i <51 ; i++){
tft.drawFastVLine(x+i+1,y,57,TFT_CYAN) ;
tft.drawFastVLine(x+i,y,57,TFT_BLACK) ;
delay(10);
tft.drawFastVLine(479-i-1,y,57,TFT_CYAN) ;
tft.drawFastVLine(479-i,y,57,TFT_BLACK) ;
delay(10);
}
tft.fillRect(x,y,52,57,TFT_BLACK);


}


//-------------------------------------------------------------------
//                        S1_alert
//-------------------------------------------------------------------
void S1_alert(bool sh)
{

if (sh==true) 
{

//alert  ttttttttttttttttttttttttttttttttttttttttttt
if (temperatura_ch[0]!=200)
{

if (temperatura_ch[0]>=t_max||temperatura_ch[1]>=t_max||temp_ch_n>=t_max) //t alert
tft.fillRect(315,150,54,3,TFT_YELLOW);

if (temperatura_ch[0]<=t_min||temperatura_ch[1]<=t_min||temperatura_ch[2]<=t_min||temp_ch_n<=t_min) //t alert
tft.fillRect(315,150,54,3,TFT_CYAN);


}

//vvvvvvvvvvvvvvvvvvvvvvvvvvv
if (v_ch[0]!=200)
{
if (v_ch[0]>=v_max) //1,2 период по 3ч
tft.fillRect(435,46,30,3,TFT_CYAN);

}

//ppppppppppppppppppppppppppppppppppp
int pp;
if (pr_kv!=200) pp=pr_kv;
else
pp=davlenie0;
if (pp!=200)
{
if (pp>=p_max||pp<=p_min)
tft.fillRect(405,83,44,3,TFT_GREEN);
}

//////uv
if (uv>=uv_max)
 S_show_uv( false,287,0);
 
}
else //------------------------------------------------------
{

//////uv///////////////
S_show_uv( true,287,0);


//ppppppppppppppppppppppppppppppppp

tft.fillRect(405,83,44,3,TFT_BLACK);

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

tft.fillRect(435,46,30,3,TFT_BLACK);


//tttttttttttt
tft.fillRect(315,150,54,3,TFT_BLACK);

 
}

  
}


//---------------------------------------------------------------
//                S1_clear_min()
//---------------------------------------------------------------
void S1_clear_min()
{
for (byte f=0; f<112; f++) //62 низ
{
tft.drawFastHLine(204,f,64,TFT_BLACK) ;
tft.drawFastHLine(204,112-f,64,TFT_BLACK) ;
delay(7);
}

}


//-------------------------------------------------------------
//                  s1_graf_t
///-------------------------------------------------------------
void S1_graf_t()
{
if (temperatura7[0]==200) return; 

unsigned int col;

int y=307;
int x=240;
int y_min;
if (temperatura_ch[0]<temperatura7[0])
y_min=temperatura_ch[0];
else
y_min=temperatura7[0];
col=color_t(temperatura_ch[0]); 
tft.drawLine(x,y-2*((temperatura_ch[0]-y_min)),x+30,y-2*((temperatura7[1]-y_min)),col);
x=x+30;


 for (byte i=1; i <= 4; i++) 
{
col=color_t(temperatura7[i]);
 
if (temperatura7[i]>=t_max||temperatura7[i]<=t_min)
tft.fillCircle(x,y-2*((temperatura7[i]-y_min)),3,col);

if (temperatura7[i+1]==200) break;


//col=TFT_YELLOW;

tft.drawLine(x,y-2*((temperatura7[i]-y_min)),x+60,y-2*((temperatura7[i+1]-y_min)),col);


x=x+60;

} 
}


   

//-------------------------------------------------------------
//                  S1_graf_davlenie
///-------------------------------------------------------------

void S1_graf_davlenie()
{


int y=317;
int x=240;
int x_pmin=x;
int davlenie_x=1000;

if (davlenie7[0]==200||davlenie0==200) return; 
tft.drawLine(x,y-((davlenie0-davlenie7[0])),x+30,y-(davlenie7[1]-davlenie7[0]),0x07E0);
x=x+30;

 for (byte i=1; i <= 4; i++) 
{



if (davlenie7[i]>=p_max||davlenie7[i]<=p_min)
tft.fillCircle(x,y-((davlenie7[i]-davlenie7[0])),2,0x07E0);

if (davlenie_x>davlenie7[i]) 
{
davlenie_x=davlenie7[i];
x_pmin=x;
}
if (davlenie7[i+1]==200) break; 




tft.drawLine(x,y-((davlenie7[i]-davlenie7[0])),x+60,y-(davlenie7[i+1]-davlenie7[0]),0x07E0);

x=x+60;
} 
tft.setTextColor(0x07E0);
tft.setFreeFont(v6);
tft.setCursor(x_pmin,y-20);           
tft.print(p7_max);
tft.setCursor(x_pmin,y-5);           
tft.print(p7_min);


}




#endif //S1
