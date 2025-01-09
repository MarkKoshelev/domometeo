#if defined (openw) && defined (Sg)

#if defined (two_tft) && defined (tft2_Sg)
  #define tft tft2 
#endif

//---------------------------------------------------------------------
//                            Sg_show
//---------------------------------------------------------------------
void  Sg_show()
{

  if  (entries==0) return;  


int x,y;

const byte par=4; //кол параметров для графика T,P,H(+rain),V
#ifdef tft_480_320
const byte y_ch=10; //под часы
x=479;
y=319;
const byte w=int(x/39)   ;
const byte h=int((y-y_ch)/par);
#endif

#ifdef tft_320_240
const byte y_ch=4; //под часы
x=319;
y=239;
const byte w=int(x/39)   ;
const byte h=int((y-y_ch)/par);
#endif

//tft.fillCircle(158,185,5,TFT_BLACK);
//tft.fillRect(0,0,18,12,TFT_BLACK);

if (tft2_act) tft.fillScreen(TFT_BLACK);




//3ch
draw_3ch_num(y_ch,w,y);//top string clock



  
for (byte i=0; i <par; i++) //4
{


int y_line=y-i*h;
if (i!=0) tft.drawFastHLine(0,y_line,x,0xC618) ; 
if (i==par-1) Sf_graf_t(y_line,w,h); //Ttttttttttttttttttttttttt
if (i==par-2) Sf_graf_p(y_line,w,h); //Ppppppppppppppppppppppppp
if (i==par-3) Sf_graf_v(y_line,w,h);  //vv
if (i==par-4) Sf_graf_h(y_line,w,h);  //hh
}


//tft.drawRect(0,0,x,y,TFT_YELLOW);  
}






//===================================================================================
//                               Sf_graf_t
//===================================================================================
void Sf_graf_t(int y,byte w, byte h)
{

unsigned int col;
int x=0;
int t_min_l=200;
int t_max_l=-200;
bool today=true;
int t_min_d=200;
int t_max_d=-200;
byte count_3ch=0  ;
byte k=2;

byte h_mid=int(h/2);
 for (byte i=1; i <=entries+1; i++) 
{
if (temperatura_ch[i]==200) break;
if (t_min_l>temperatura_ch[i]) t_min_l=temperatura_ch[i];
if (t_max_l<temperatura_ch[i]) t_max_l=temperatura_ch[i];
}

#ifdef tft_480_320
byte val=25;
#endif

#ifdef tft_320_240
byte val=15;
#endif


if (t_max_l-t_min_l>val) k=1;

/*
Serial.println("-------------------------");
Serial.print("t_min_l=");
Serial.println(t_min_l);
Serial.print("t_max_l=");
Serial.println(t_max_l);
*/
int t_mid=int((t_max_l+t_min_l)/2);
/*
Serial.print("t_mid=");
Serial.println(t_mid);
Serial.println("-------------------------");
*/
 for (byte i=1; i <=entries+1; i++) 
{

//begin day
if (day_ch[i]+delta_tz==0&&x>0||i==entries+1) 
  {

if (count_3ch>3)
{
byte b=int(w*5); //all
if (i==entries+1||today) b=35; //last


tft.setFreeFont(v6);
tft.setCursor(x-b,y-5);
col=color_t(t_min_d);
tft.setTextColor(col);
tft.print(t_min_d);

#ifdef tft_480_320
tft.setFreeFont(v9);
#endif

tft.setCursor(x-b,y-h+15);
col=color_t(t_max_d);
tft.setTextColor(col);
tft.print(t_max_d);

if (i==entries+1) Serial.print("i==entries+1_x=");
Serial.println(x);

  
}
/*
Serial.print("entries_ch=");
Serial.println(entries+1);
Serial.print("count_3ch_entries=");
Serial.println(count_3ch);
*/
t_min_d=200;
t_max_d=-200;
count_3ch=0;
today=false;
  }

if (t_min_d>temperatura_ch[i]) t_min_d=temperatura_ch[i];
if (t_max_d<temperatura_ch[i]) t_max_d=temperatura_ch[i];
count_3ch++;

Serial.print("count_3ch=");
Serial.println(count_3ch);

if (i <entries+1)
{
col=color_t(temperatura_ch[i]);

tft.drawLine(x,y-h_mid+(t_mid-temperatura_ch[i])*k,x+w,y-h_mid+(t_mid-temperatura_ch[i+1])*k,col);
tft.drawLine(x,y-1-h_mid+(t_mid-temperatura_ch[i])*k,x+w,y-1-h_mid+(t_mid-temperatura_ch[i+1])*k,col);
if (temperatura_ch[i]>=t_max||temperatura_ch[i]<=t_min) tft.fillCircle(x,y-h_mid+(t_mid-temperatura_ch[i])*k,3,col);

Serial.println("draw_T");


}
/*
Serial.print("temperatura_ch=");
Serial.println(temperatura_ch[i]);
Serial.print("x=");
Serial.println(x);
Serial.println(i);
*/

x=x+w;

} 
}



//===================================================================================
//                                  Sf_graf_p
//===================================================================================
void Sf_graf_p(int y,byte w, byte h)
{


unsigned int col;
int x=0;
int p_min_l=20000;
int p_max_l=1;
byte k=2;

int p_min_d=20000;
int p_max_d=-1;
byte count_3ch=0;
bool today=true;

byte h_mid=int(h/2);
 for (byte i=1; i <=entries+1; i++) 
{
if (p_ch[i]==0) break;
if (p_min_l>p_ch[i]) p_min_l=p_ch[i];
if (p_max_l<p_ch[i]) p_max_l=p_ch[i];
}

#ifdef tft_480_320
byte val=25;
#endif
#ifdef tft_320_240
byte val=15;
#endif


if (p_max_l-p_min_l>val) k=1;
/*
Serial.println(F("-------------------------"));
Serial.print("p_min_l=");
Serial.println(p_min_l);
Serial.print("p_max_l=");
Serial.println(p_max_l);
Serial.println(F("-------------------------")); 
*/
int p_mid=int((p_max_l+p_min_l)/2);
/*
Serial.print("p_mid=");
Serial.println(p_mid);
*/

 for (byte i=1; i <=entries+1; i++) 
{

//begin day
if (day_ch[i]+delta_tz==0&&x>0||i==entries+1) 
  {


if (count_3ch>3)
{
byte b=int(w*5); //all
if (i==entries+1||today) b=35; //last



tft.setFreeFont(v6);
tft.setCursor(x-b,y-5);
tft.setTextColor(c_pr_ow);
tft.print(p_min_d);


tft.setCursor(x-b,y-h+15);
tft.setTextColor(c_pr_ow);
tft.print(p_max_d);

  
}

p_min_d=20000;
p_max_d=-1;
count_3ch=0;
today=false;
  }


if (p_min_d>p_ch[i]) p_min_d=p_ch[i];
if (p_max_d<p_ch[i]) p_max_d=p_ch[i];
count_3ch++;



if (i <entries+1)
{

tft.drawLine(x,y-h_mid+(p_mid-p_ch[i])*k,x+w,y-h_mid+(p_mid-p_ch[i+1])*k,c_pr_ow);
if (p_ch[i]>=p_max||p_ch[i]<=p_min) tft.fillCircle(x,y-h_mid+(p_mid-p_ch[i])*k,2,c_pr_ow);


Serial.println("draw_P");

}
/*
Serial.print("p_ch=");
Serial.println(p_ch[i]);
Serial.print("x=");
Serial.println(x);
Serial.println(i);
*/

x=x+w;

} 
}



//===================================================================================
//                                 Sf_graf_v
//===================================================================================
void Sf_graf_v(int y,byte w, byte h)
{


#ifdef tft_480_320
 byte k=3;
#endif

#ifdef tft_320_240
byte k=2;
#endif

byte v_min_d=200;
byte v_max_d=-0;
byte count_3ch=0;
bool today=true;

unsigned int col;
int x=0;
byte v_min_l=200;
byte v_max_l=0;
byte count=0;
//byte h_mid=int(h/2);

//int v_gr_ch[ch_count];

 for (byte i=1; i <=entries+1; i++) 
{
if (v_min_l>v_ch[i]) v_min_l=v_ch[i];
if (v_max_l<v_ch[i]) v_max_l=v_ch[i];
/*
Serial.print("v=");
Serial.println(v_ch[i]);
Serial.print(count);
*/
count++;
}
/*
Serial.println("-------------------------");
Serial.print("v_min_l=");
Serial.println(v_min_l);
Serial.print("v_max_l=");
Serial.println(v_max_l);
Serial.println(count);
*/
int v_mid=int((v_max_l+v_min_l)/2);
/*
Serial.print("v_mid=");
Serial.println(v_mid);
Serial.println("-------------------------");
*/

if (v_max_l*k<h/2) k++;
Serial.print("k=");
Serial.println(k);

 for (byte i=1; i <=entries+1; i++) 
{



//begin day
if (day_ch[i]+delta_tz==0&&x>0||i==entries+1) 
  {

if (count_3ch>3)
{
byte b=int(w*5); //all
if (i==entries+1||today) b=45; //last
 
tft.setFreeFont(v6);
tft.setCursor(x-b ,y-h+20);
tft.setTextColor(TFT_CYAN);
tft.print(v_min_d);
tft.setTextColor(TFT_WHITE);
tft.print("-");
tft.setTextColor(TFT_CYAN);
tft.print(v_max_d);
tft.setTextColor(TFT_WHITE);
tft.print("m");
  
}

v_min_d=200;
v_max_d=-0;
count_3ch=0;
today=false;
  }

if (v_min_d>v_ch[i]) v_min_d=v_ch[i];
if (v_max_d<v_ch[i]) v_max_d=v_ch[i];
count_3ch++;





if (i <entries+1)
{
float gr=int(v_gr_ch[i]);
do_deg(gr);
tft.drawLine(x,y-1-v_ch[i]*k,x+w,y-1-v_ch[i+1]*k,c_wind);
if (v_ch[i]>=v_max)
{
tft.drawCircle(x,y-1-v_ch[i]*k,2,c_wind);
}
}
/*
Serial.print("v_ch=");
Serial.println(v_ch[i]);
Serial.print("x=");
Serial.println(x);
Serial.println(i);
*/
x=x+w;

} 
}







//===================================================================================
//                                 Sf_graf_H
//===================================================================================
void Sf_graf_h(int y,byte w, byte h)
{



bool today=true;
unsigned int col;
int x=0;
byte h_min_l=200;
byte h_max_l=0;
float r_mm=0;
bool r_mm_max=false;  //пищу mm если было > среднего осадков за сутки
byte count_3ch=0;
 for (byte i=1; i <=entries+1; i++) 
{
if (h_min_l>h_ch[i]) h_min_l=h_ch[i];
if (h_max_l<h_ch[i]) h_max_l=h_ch[i];
//Serial.print("h=");
//Serial.println(h_ch[i]);
}
/*
Serial.println("-------------------------");
Serial.print("h_min_l=");
Serial.println(h_min_l);
Serial.print("h_max_l=");
Serial.println(h_max_l);
*/
int h_mid=int((h_max_l+h_min_l)/2);
/*
Serial.print("h_mid=");
Serial.println(h_mid);
Serial.println("-------------------------");
*/
 for (byte i=1; i <=entries; i++) 
{


//begin day
if (day_ch[i]+delta_tz==0&&x>0||i==entries+1) 
  {

if (count_3ch>3&&r_mm_max)
{
byte b=int(w*5); //all
if (i==entries+1||today) b=35; //last

tft.setFreeFont(v6);
tft.setCursor(x-b,y-1);
tft.setTextColor(TFT_BLUE);
do_draw_rain_mm(x-b,y-7,r_mm,TFT_CYAN);

  }

r_mm=0;
r_mm_max=false;
count_3ch=0;
today=false;

  } //day_ch
count_3ch++;

if (rain_ch[i]>rain_l)
{r_mm_max=true;
Serial.print("r_mm_max=true");
}

r_mm=r_mm+rain_ch[i];

/*
Serial.print("rain_ch=");
Serial.println(rain_ch[i]);
Serial.print("r_mm=");
Serial.println(r_mm);
*/


if (h_ch[i]<50) col= 0x879F;
else col= 0x041F;

tft.drawLine(x,y-h+2+h_max_l-h_ch[i],x+w,y-h+2+h_max_l-h_ch[i+1],col);

 #ifdef tft_320_240
byte xx=3;
#endif

#ifdef tft_480_320
byte xx=5;
#endif
do_draw_rain(x+xx,y-37,rain_ch[i],TFT_CYAN);

/*
Serial.print("h_ch=");
Serial.println(h_ch[i]);
Serial.print("x=");
Serial.println(x);
Serial.println(i);

*/
x=x+w;

} 
}




//===================================================================================
//                                  g draw_3ch_num
//===================================================================================
void draw_3ch_num(byte y,byte w,int h_scr)//top string clock
{


//day//dddddddddddddddddddddddddddddddddddd
int x=0;
int col;
tft.drawFastHLine(0,y,x,TFT_LIGHTGREY) ; //под 3ч

for (byte i=1; i <=entries; i++) 
{
if (day_ch[i]>=t_sun_v_hh&&day_ch[i]<t_sun_z_hh)
{
col=0xCC26;
}
else
{
col=TFT_BLACK;
}
tft.fillRect(x,0,w,y,col);

tft.fillRect(x,h_scr-4,w,4,col); //низ день

if (day_ch[i]+delta_tz==0&&x>0) 
{
tft.drawFastVLine(x,0,h_scr,TFT_WHITE) ;  //верт разд линия 00-00

}
else
{
if (x>0) 
{
tft.drawFastVLine(x,0,y,TFT_LIGHTGREY) ;  //верт разд линия 
tft.drawFastVLine(x,h_scr-4,4,TFT_LIGHTGREY) ; //bott
}
}

x=x+w;
} //for

  
}


#if defined (two_tft) && defined (tft2_Sg)
  #undef tft tft2 
#endif



#endif
