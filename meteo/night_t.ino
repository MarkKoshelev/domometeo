#if defined (Sn) && defined(tft_320_240)

void Sn_time()
{
static byte last_min=99;//чтобы не перирис минуты

if (refresh_all==true)
tft.fillScreen(TFT_BLACK);


//if (millis()-last_time<1000) return;
//last_time=millis();


if (t%2==0)
{
if (err_ntp==0) 
{
tft.fillRect(100,60,15,15,Sn_color_sec);
tft.fillRect(100,180,15,15,Sn_color_sec);
}
else
{
tft.fillRect(100,60,15,15,TFT_RED);
tft.fillRect(100,180,15,15,TFT_RED);

}

}
else
{
tft.fillRect(100,60,15,15,TFT_BLACK);
tft.fillRect(100,180,15,15,TFT_BLACK);  
}



if (last_min==minute(t)&&refresh_all==false) {return;} 
last_min=minute(t);



String st;
String fileName;
/////hour  hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
if (refresh_all||minute(t)==0)
        {

if (hour(t)<10)
{
fileName="/n"+String(hour(t))+"n.jpg";
drawJpeg(fileName,0,0);
}
else
{
tft.setFreeFont(v18b);
tft.setTextSize(2);
tft.setTextColor(TFT_GREEN);
tft.setCursor(0,150); 
tft.print(hour(t));
tft.setTextSize(1);  
}

        }


        
//////////////////min///////////////////////////

if (minute(t)<10) 
{
fileName="/n0n.jpg";
drawJpeg(fileName,120,0);//220

fileName="/n"+String(minute(t))+"n.jpg";
do_clear_min_n();
drawJpeg(fileName,220,0);//220

  }
else
{
st=String(minute(t));
fileName="/n"+st.substring(0,1)+"n.jpg";
drawJpeg(fileName,120,0);//220

fileName="/n"+st.substring(1)+"n.jpg";
do_clear_min_n();
drawJpeg(fileName,220,0);

}

 }





 
//------------------------------------------------------------------
////////////////////////////ночь мин
void do_clear_min_n()
{

for (int f=0; f<241; f++) 
{
tft.drawFastHLine(220,0+f,100,TFT_BLACK) ;
tft.drawFastHLine(220,240-f,100,TFT_BLACK) ;
}

}

#endif
