#ifdef ESP32

void do_draw_clock()
{
Serial.println("do_draw_clock");  
float  alpha=0;
float  x,y;
int color;
byte rr ;
for (int i=1; i<3; i++) tft.drawCircle(CX, CY,R+i,TFT_DARKGREY);
//point
for (int i=0; i<12; i++)
  {
alpha=(30*i+270)*0.0175;
x=CX + (R+3) * cos(alpha);
y=CY + (R+3) * sin(alpha);
if (i%3==0)
{
color=TFT_YELLOW;
rr=3;
}
else
{
color=TFT_CYAN;
rr=2;
}
tft.fillCircle(x,y,rr,color);
  }


tft.setTextColor(TFT_CYAN);
tft.setFreeFont(v9);
tft.setCursor(CX+R+7, CY+8);
tft.print("3");
tft.setCursor(CX-8, CY+R+20);
tft.print("6");
tft.setCursor(CX-R-20, CY+8);
tft.print("9");
tft.setCursor(CX-10, CY-R-10);
tft.print("12");

}



/////////mmmmmmmmmmmmmmmmmmmmm-------------
void do_show_min(byte num,int col)
{

float x,y,x1,y1;
float alpha=(6*num+270)*0.0175;

x=CX +(R*0.1) * cos(alpha);
y=CY + (R*0.1) * sin(alpha);

x1=CX + (R*0.9)  * cos(alpha);
y1=CY + (R*0.9) * sin(alpha);


//ctrelka
//tft.drawLine(CX,CY,x,y,col);
tft.drawLine(x,y,x1,y1,col);


}




//--------------hhhhhhhhhhhhhhhhhhhhhhhhh
void do_show_hour(byte h,byte m,int col)
{
float x,y;
float alpha=(30*h+(m/2)+270)*0.0175;


x=CX + (R*0.5) * cos(alpha);
y=CY + (R*0.5) * sin(alpha);

//hhhhhhhhh
tft.drawLine(CX,CY,x,y,col);
}


#endif
