#if defined (S3) && defined(tft_480_320)&& defined (openw) 


//--------------------------------------------------------
//		 S3_time
//--------------------------------------------------------

void S3_time()
{
static byte last_min=99;//чтобы не перирис минуты

if (t%2==0)
{

S3_alert(false);
//ntp
if (err_ntp==0) 
tft.fillCircle(71,22,2,TFT_GREENYELLOW);
else
tft.fillCircle(71,22,2,TFT_RED);
} //sec black------------------------------------
else
{
S3_alert(true);
 //sec
tft.fillCircle(71,22,2,TFT_BLACK);
}


if (ref_temp_u==true||ref_wh_now==true||refresh_all==true) //есть данные с улицы
S3_show_now();


if (ref_kv_th==true||refresh_all==true) S_show_th_room(420,10);



if (refresh_all==true||ref_wh==true) S3_3ch();

 

//time_t t =now(); 

if (last_min==minute(t)&&refresh_all==false) return ; 


if (minute(t)==0) 
tft.fillRect(0,0,8,42,TFT_BLACK);
else
if (minute(t)%10==0) 
tft.fillRect(80,0,68,42,TFT_BLACK);
else
tft.fillRect(112,0,36,42,TFT_BLACK);



//////////////hour///hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
String st;
tft.setTextColor(S3_color_clock);
tft.setFreeFont(v24b);

if (refresh_all||minute(t)==0)
        {


if (hour(t)<10) 
st="0"+String(hour(t));
else
st=String(hour(t));

tft.setCursor(0,40);           
tft.print(st);
        }

        
///min mmmmmmmmmmmmmmmmmmmmmmmmmmm
if (refresh_all||minute(t)==0||minute(t)%10==0)
        {
if (minute(t)<10) 
st="0"+String(minute(t));
else
st=String(minute(t));
tft.setCursor(80,40);           
        }
        else
        {
if (minute(t)<10) 
st=String(minute(t));
else
st=String(minute(t)%10);

for (int i=1; i <= 3; i++)
{
tft.fillRect(112,0,36,42,TFT_BLACK);    
if (i==1) tft.setFreeFont(v18);
if (i==2) tft.setFreeFont(v12);
if (i==3) tft.setFreeFont(v9);
tft.setCursor(112,40); 
tft.print(last_min%10);
delay(200);
}

for (int i=1; i <= 3; i++)
{
tft.fillRect(112,0,36,42,TFT_BLACK);    
if (i==1) tft.setFreeFont(v9);
if (i==2) tft.setFreeFont(v12);
if (i==3) tft.setFreeFont(v18);
tft.setCursor(112,40); 
tft.print(st);
delay(200);
}

delay(50);

tft.fillRect(112,0,36,42,TFT_BLACK);
tft.setFreeFont(v24b);
tft.setCursor(112,40);          

        }

  
tft.print(st);


last_min=minute(t);


//dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
if (!refresh_all&&year(t)>2015) 
  return;

//tft.drawFastHLine(0,44,149,TFT_LIGHTGREY) ;
//tft.drawFastHLine(0,80,320,TFT_GREENYELLOW) ;
//tft.drawFastHLine(0,81,320,TFT_GREENYELLOW) ;



//dddddddddddddddddddddddddddddddddddddddddddddddddd
tft.setFreeFont(v18b);
String str="";
if (day(t)<10) 
str="0"+String(day(t));
else
str=String(day(t));

tft.setTextColor(c_date);
tft.setCursor(10,75);   
tft.print(str);


//tft.setFreeFont(v9b);
tft.setFreeFont(v9);
tft.print(".");
if (month(t)<10) 
str="0"+String(month(t));
else
str=String(month(t));
tft.setTextColor(c_month);
tft.print(str);


//день недели------wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
draw_week_day(95,47);


tft.drawFastVLine(150,0,80,TFT_CYAN) ;

//moon
String fileName=do_phasemoon()+"_32.jpg";
drawJpeg(fileName,165,47);

//zzzzzzzzzzzzzzzzzzz
tft.setFreeFont(v9);
tft.setTextColor(TFT_YELLOW);
tft.setCursor(160,20);
tft.print(t_sun_v);
//zahod
tft.setTextColor(TFT_ORANGE);
tft.setCursor(160,42);
tft.print(t_sun_z);


}


//===================================================================================================
///                S3_show_now
//===================================================================================================
void S3_show_now()
{


int x=220;
byte y=0;


tft.fillRect(x+1,y,239,79,TFT_BLACK);

drawJpeg(icon_ch[0]+"48.jpg",x+12,y);
//tft.drawFastVLine(x+60,0,79,TFT_LIGHTGREY);


//rain snowrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr

do_draw_rain(x+5,y+30,rain_ch[0],TFT_CYAN);



//tttttttttttttttttttttttttttttttttttt

int temp;
temp=temperatura_ch[0];

if (temp_u!=200) 
{
temp=temp_u;
ref_temp_u=false;

}


tft.drawFastVLine(x,0,79,c_tu_frame) ;
tft.drawFastVLine(x-1,0,79,c_tu_frame) ;



tft.setTextColor(color_t(temp));
tft.setFreeFont(v18b);


if (temp>=0&&temp<10)
tft.setCursor(x+80,y+40);
else
if (temp<-10)
tft.setCursor(x+55,y+40);
else
tft.setCursor(x+65,y+40);
tft.print(temp);


//nnnnnnnnnnnnnnnnnnnnnnnn
if (temp_ch_n!=200)
{
  
tft.setTextColor(color_t(temp_ch_n));
tft.setFreeFont(v12);

if (temp_ch_n>=0&&temp_ch_n<10)
tft.setCursor(x+80,y+72);
else
if (temp_ch_n<-10)
tft.setCursor(x+60,y+72);
else
tft.setCursor(x+70,y+72);
tft.print(temp_ch_n);
}

//------------------------
x=x+125;
tft.drawFastVLine(x,0,79,TFT_LIGHTGREY);


byte b;

if (temp_kv==200&&h_kv==200) b=30;
else
{
b=0;
S_show_th_room(420,10);
}




//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
float gr=int(v_gr_ch[0]);
do_deg(gr);

drawJpeg(wind_ico,x+1+b,y);

tft.setFreeFont(v9);
tft.setTextColor(TFT_CYAN);
tft.setCursor(x+32+b,y+32);
tft.print(v_ch[0]);

//ppppppppppppppppppppppppppppppppppppppppppppppppppppppp

if (davlenie0!=200) 
{

if (davlenie0<davlenie7[1]) 
draw_tr_up(x+3+b,72);
if (davlenie0>davlenie7[1])
draw_tr_down(x+3+b,72);
 
#ifndef hPa
tft.setFreeFont(v12);
#else
tft.setFreeFont(v9);
#endif

tft.setTextColor(c_pr_ow);
tft.setCursor(x+15+b,72);           

if (pr_kv!=200) 
{
tft.setTextColor(c_pr_bme);  
tft.print(pr_kv);
}
else
tft.print(davlenie0);

}




S3_graf_davlenie();
}
  




//------------------------------------------------------------------------------
//                      S3_3ch
//------------------------------------------------------------------------------

void S3_3ch()
{


byte y=80;
int x=0; 
int n;
String s="";
byte step=36;

tft.fillRect(x,y,479,239,TFT_BLACK); 

tft.drawFastHLine(0,y,480,TFT_WHITE) ;
tft.drawFastHLine(0,y+15,480,TFT_WHITE) ;

//----------------------------------
for (byte i=1;i<27;i++)
    {  
if (temperatura_ch[i]==200) continue;


//ddddddddddddddddddddddddddddddddddddddddddd
if (day_ch[i]<10)
s=(" 0");
else
s=(" ");
s=s+String(day_ch[i]);
if (day_ch[i]>=t_sun_v_hh&&day_ch[i]<t_sun_z_hh)
{
tft.drawRect(x+1,y+1,step-1,14,TFT_YELLOW);
tft.setTextColor(TFT_YELLOW);
}
else
tft.setTextColor(TFT_WHITE);

tft.setFreeFont(v6);
tft.setCursor(x+8,y+12);           
tft.print(s);


if ((day_ch[i]==0||day_ch[i]==1||day_ch[i]==2)&&x>0) 
{
tft.drawFastVLine(x,y,113,TFT_WHITE) ;  //верт разд линия
tft.drawFastVLine(x-1,y,113,TFT_WHITE) ;  //верт разд линия
}
else
if ((day_ch[i]==12||day_ch[i]==13||day_ch[i]==14)&&x>0) //поправка на разные пояса
{
tft.drawFastVLine(x,y,118,TFT_YELLOW) ;  //верт разд линия
tft.drawFastVLine(x-1,y,118,TFT_YELLOW) ;  //верт разд линия
}
else
if (x>0) tft.drawFastVLine(x,y,65,TFT_LIGHTGREY) ;  //верт разд линия


//jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
drawJpeg(icon_ch[i]+"32.jpg",x+4,y+22);


//rain snowrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
do_draw_rain(x+4,y+22,rain_ch[i],TFT_CYAN);
if (rain_ch[i]>=rain_l)
do_draw_rain_mm(x+5,y+58, rain_ch[i],TFT_CYAN);

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
float gr=int(v_gr_ch[i]);
do_deg(gr);
if (wind_ico!="")
{
drawJpeg(wind_ico,x+1,y+81);
}
tft.setFreeFont(v6);
tft.setTextColor(TFT_CYAN);
if (wind_ico=="/wind_10.jpg"||wind_ico=="/wind_2.jpg")
tft.setCursor(x+18,y+113); 
else
tft.setCursor(x+3,y+113);           
tft.print(v_ch[i]);



//TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
unsigned int col;
col=color_t(temperatura_ch[i]);
tft.setTextColor(col);
int tt=temperatura_ch[i];
tft.setFreeFont(v9); 
if (tt<-9)
tft.setCursor(x,y+81);           
else
tft.setCursor(x+7,y+81);    
tft.print(tt);



x=x+step;
if (x+step>479)
{
x=0;
//y=117;  
y=200;
tft.drawFastHLine(0,y,480,TFT_WHITE) ;  //half
tft.drawFastHLine(0,y+15,480,TFT_WHITE) ;  //half
}


                      
      }




//tft.drawFastHLine(0,239,480,TFT_WHITE) ;  

}      








//==========================================================================================
//                          S3_alert
//===========================================================================================
void S3_alert(bool sh)
{
byte b;
if (temp_kv==200&&h_kv==200)
 b=30;
else
b=0;





if (sh==true) 
{

//alert  ttttttttttttttttttttttttttttttttttttttttttt
if (temperatura_ch[0]!=200)
{
if (temperatura_ch[0]>=t_max||temperatura_ch[1]>=t_max||temp_ch_n>=t_max) //t alert
tft.fillRect(295,45,35,3,TFT_YELLOW);
if (temperatura_ch[0]<=t_min||temperatura_ch[1]<=t_min||temperatura_ch[2]<=t_min||temp_ch_n<=t_min) //t alert
tft.fillRect(295,45,35,3,TFT_CYAN);
}

//vvvvvvvvvvvvvvvvvvvvvvvvvvv
if (v_ch[0]!=200)
{
if (v_ch[0]>=v_max||v_ch[1]>=v_max) //1,2 период по 3ч
tft.fillRect(377+b,35,20,3,TFT_CYAN);

}

//ppppppppppppppppppppppppppppppppppp
int pp;
if (pr_kv!=200) pp=pr_kv;
else
pp=davlenie0;

if (pp!=200)
{
if (pp>=p_max||pp<=p_min)
tft.fillRect(360+b,75,45,3,TFT_GREEN);
}

//////uv
if (uv>=uv_max)
//S1_show_uv(false); //не показ значка uv
S_show_uv( false,221,0);

 
}
else //------------------------------------------------------------------
{

//////uv///////////////
S_show_uv( true,221,0);
//ppppppppppppppppppppppppppppppppp
tft.fillRect(360+b,75,45,3,TFT_BLACK);
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
tft.fillRect(377+b,35,20,3,TFT_BLACK);

//tttttttttttttttttttttttttttttttttttt
tft.fillRect(295,45,35,3,TFT_BLACK);
}

  
}



//-------------------------------------------------------------------------------
//                  S3_graf_davlenie
//-------------------------------------------------------------------------------

void S3_graf_davlenie()
{


int y=75;
int x=220;
int x_pmin=x;
int davlenie_x=1000;

if (davlenie7[0]==200||davlenie0==200) return; 
tft.drawLine(x,y-((davlenie0-davlenie7[0])*2),x+8,y-(davlenie7[1]-davlenie7[0])*2,0x07E0);
x=x+8;

 for (byte i=1; i <= 4; i++) 
{



if (davlenie7[i]>=p_max||davlenie7[i]<=p_min)
tft.fillCircle(x,y-((davlenie7[i]-davlenie7[0])*2),2,0x07E0);

if (davlenie_x>davlenie7[i]) 
{
davlenie_x=davlenie7[i];
x_pmin=x;
}
if (davlenie7[i+1]==200) break; 




tft.drawLine(x,y-((davlenie7[i]-davlenie7[0])*2),x+16,y-(davlenie7[i+1]-davlenie7[0])*2,0x07E0);

x=x+16;
} 

}



#endif //openw
