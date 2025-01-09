
#ifdef encoder
//=======================================================
//                encoder
//=======================================================
void do_encoder()
{
static int num=-99;
static byte fav=0;

static uint32_t t_num=0; //разница при вращении, обнуляю при остановке
enc.tick();

#ifdef ESP32

//clear num
if (millis()-t_num>t_enc_num_clear&&num!=-99)
{
draw_num(0,'C');
Serial.println("enc t_num=-99");  
num=-99;  
}




//play----------PLAY------------PLAY------------PLAY------------PLAY------------PLAY-------
if (play) 
  {


//Right
if (enc.isRight()) 
{
if (num==-99) num=ch;
num++;
if (num>ch_max) num=ch_min;
draw_num(num,'C');  
Serial.println("enc Righ num++");         
t_num=millis();
return;
}

//Left
if (enc.isLeft()) 
{
if (num==-99) num=ch;
num--;
if (num<1) num=ch_max;
draw_num(num,'C');  
Serial.println("enc Left num--");
t_num=millis();
return;

} 



//Volume vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 if (enc.isRightH())  //isRightH holded
 {
 fn_cmd="vl+"; //
Serial.println("enc fn_cmd=vl+");  
 }

 if (enc.isLeftH()) //isLeftH holded
 {
 fn_cmd="vl-"; //
Serial.println("enc fn_cmd=vl-");  
 }

 



//hold start timer-------------------------
 if (enc.isHolded()) 
   {
if (num!=-99)
{
Serial.println("Holded Timer"); 
t_timer=millis()+60000*num;
draw_num(num,'T');  
draw_num(0,'C'); //clear num
Serial.println("TIMER begin");
num=-99;
}
else
{
Serial.println("Holded mute"); 
 fn_cmd="mute"; //
}
}

//isHolded

 //favorite fffffffffffffffffffffffffffff
if (enc.isDouble()&&fav_count_real>0)    //>=2        
  {
Serial.println("enc isDouble");
if (num==-99) 
{
if (ch==fav_ch[fav]) {fav++;if (fav>=fav_count_real) fav=0; } //если в данный момент играет избр.

ch=fav_ch[fav];
fav++; if (fav>=fav_count_real) fav=0;
fn_cmd="play";  
Serial.print("favor=");     
Serial.println(ch);    

}

  } //isDouble


//isClick
 if (enc.isSingle()) //isClick()) 
 {
  
Serial.println("enc play isSingle");  
if (num!=-99) //выбор канала
{
if (ch!=num)
{
ch=num; //выбор канала
fn_cmd="play";
}
draw_num(0,'C');  
Serial.println("enc t_num!=-99 play num");  
num=-99;  
}
else
if (t_timer!=0)   //, иначе стоп таймер
{
timer_stop();
Serial.print("enc TIMER stop=");Serial.println(t_timer);
fn_cmd="";
}
else
{
fn_cmd="stop"; //STOP если канал не выбран и нет таймера
Serial.println("enc fn_cmd=stop");  
}

 } //isSingle





    
  } //play

#endif //esp32



//-----------NOT PLAY---------------NOT PLAY------------------NOT PLAY-----------------
 if (!play) 
  {

if (num==-99) //not timer
{
if (enc.isRight()) fn_cmd="next";
if (enc.isLeft())  fn_cmd="prev";
if (enc.isSingle()) 
{

  
  
  
  #ifdef ESP32
if (t_timer>0) //stop T
timer_stop();
else
fn_cmd="play";
  #endif //ESP32

#ifdef ESP8266
if (scr_show_count>1) //scr_round
{
scr_round=!scr_round;
draw_stop_round();
//return;
}
#endif
  
} //isClick

#ifdef ESP32
 if (enc.isHolded()) 
{
Serial.println("Holded mode timer"); 
num=1;
draw_num(num,'C');  
t_num=millis();
}
#endif //esp32


} //==-99

//!=99
#ifdef ESP32 // use timer
if (num!=-99) //--------------------------
{
 if (enc.isHolded()) 
{
Serial.println("Holded start timer"); 
t_timer=millis()+60000*num;
draw_num(num,'T');  
Serial.println("TIMER begin");
num=-99;
} //isHolded



//num++ --
//Right
if (enc.isRight()) 
{
Serial.println("enc  Right T");      
num++;
draw_num(num,'C');    
t_num=millis();
}

//Left
if (enc.isLeft()) 
{
Serial.println("enc  Left T");    
num--;
if (num<1) num=1;
draw_num(num,'C');    
t_num=millis();
//return;

} 

if (enc.isSingle()) 
{
ch=num;
fn_cmd="play";
}



} //!=-99
#endif //esp32
 } //E not play-------------eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee



#ifdef ESP32

if (fn_cmd!="")
    {
do_fn_btn_ir();
//Serial.print(F("fn_cmd_enc="));Serial.println(fn_cmd);
fn_cmd="";
  }
#endif //ESP32



#ifdef ESP8266
//next SCR
if (fn_cmd=="next"&&!play) //след. станция если уже играет
  {
scr_number++;
scr_num_show(scr_number);
  }

 //prev SCR
if (fn_cmd=="prev"&&!play) //след. станция если уже играет
  {
scr_number--;
scr_num_show(scr_number);

  }
fn_cmd=""; 
#endif //ESP8266


}


#endif //enc

#if defined(ESP32) && defined(encoder)
//======================================================================================
//                    do_fav_ch
//======================================================================================
void do_fav_ch(String str)
{
String s;
fav_count_real=0;
//{1;4;13;20;}
int val=-1;
int tz=str.indexOf("{");
int tz2=str.indexOf("}");
s=str.substring(tz+1,tz2)  ;
Serial.print("do_fav_ch=");
Serial.println(s);
tz++;
tz2=tz;
tz2=str.indexOf(";",tz+1);
//-----------------------------------
while (tz2>0) 
{
s=str.substring(tz,tz2);
Serial.print("s=");
Serial.println(s);
val=s.toInt();
Serial.print("val=");

if (val>0&&val<256) 
{
Serial.println(val);
fav_ch[fav_count_real]=val;
fav_count_real++;
if (fav_count_real>=fav_count) break;
}
else
{
Serial.print(" ERR=");  Serial.println(val); 
}

tz=tz2+1;
tz2=str.indexOf(";",tz);
Serial.println(tz); Serial.println(tz2);
}   //wh

}

#endif //esp32 enc

//==================================================================================================
//                      do_read_ir32
//==================================================================================================

#if defined (pin_ir) && defined (ESP32)
void do_read_ir32()
{
static time_t next_time=0; 
unsigned long code_ir_tmp;
static int bt1=99,bt2=99,bt3=99,btn=0;
static unsigned long t_start_bt1=0;

fn_cmd="";



if (millis()<next_time) 
{  

if ( irrecv.decode( &results ))
irrecv.resume(); // принимаем следующую команду


return;
}




if(btn!=0&&millis()-t_start_bt1>10000) // канал стираю 
{
bt1=99,bt2=99,bt3=99,btn=0;
draw_num(0,'C');
}

//IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
if ( irrecv.decode( &results )) { // если данные пришли
 
code_ir_tmp=results.value;

Serial.print(F( "IR==")); 
Serial.println(code_ir_tmp);


//ищу код в массиве
 for (int i=0; i <fn_count; i++)
{
if (code[i]!=code_ir_tmp) continue; //не нашёл код

//нашел
fn_cmd= fn[i];
Serial.print("find ir code===");
Serial.println(fn_cmd);
break;
}


//SCR  PLAY--------SCR  PLAY---------------SCR  PLAY---------------SCR  PLAY--------------------          
if (play&&fn_cmd!="")
        {
//-------fn_cmd=="play"----fn_cmd=="play"--------fn_cmd=="play"
if (fn_cmd=="play")
        {
if (btn==0)
  {
if (t_timer==0)fn_cmd="stop"; //STOP если канал не выбран и нет таймера
if (t_timer!=0)   //, иначе стоп таймер
{
fn_cmd="";
timer_stop();
Serial.print("TIMER stop");
}

  }


if (btn>0&&ch!=btn)//выбор канала
ch=btn;


            }

//TIMER start------   TIMER start------------TIMER start
if (fn_cmd=="vl-"&&btn>0) 
   {
t_timer=millis()+60000*btn;
draw_num(btn,'T');  
draw_num(0,'C'); //clear num
Serial.println("TIMER begin");
fn_cmd="timer";
bt1=99,bt2=99,bt3=99,btn=0;
   }


      
        
        }//E play---------------------------------------------------------- 





// SCR NOT PLAY-------SCR NOT PLAY--------SCR NOT PLAY--------SCR NOT PLAY-------
if (!play&&fn_cmd!="")
                  {
#ifdef debug
Serial.print(F("btn="));Serial.println(btn);
Serial.print(F("TIMER="));Serial.println(t_timer);
#endif
//TIMER ------   ttttttttttttttttttttttttttttttttttt
if (fn_cmd=="vl-"&&btn>0) 
   {
t_timer=millis()+60000*btn;
draw_num(btn,'T');  
Serial.print("TIMER begin==");Serial.println(btn);
fn_cmd="timer";
draw_num(0,'C');     
   }
else
if (fn_cmd=="play"&&btn>0)  //запуск выбранного канала 
   {
if (ch!=btn) //ищу канал
ch=btn;
timer_stop(); //если play сброс таймера
Serial.println(F("TIMER stop"));
  }
else

if (fn_cmd=="play"&&t_timer>0&&btn==0) //сброс таймера если запущен и нажать play
{
timer_stop();
fn_cmd="";
bt1=99,bt2=99,bt3=99,btn=0;
}



          

                  } //E !play



if (fn_cmd==""||fn_cmd=="vl+"||fn_cmd=="vl-"||fn_cmd=="mute"||btn>0) 
next_time=millis()+t_ir_sleep_short;
else
next_time=millis()+t_ir_sleep;



if (fn_cmd!="")
{
do_fn_btn_ir();
bt1=99;bt2=99;bt3=99;btn=0;
//if (play) draw_num(0,'C');
irrecv.resume(); // принимаем следующую команду
fn_cmd="";
return;
}

//---------BTN---------BTN---------BTN---------BTN---------BTN---------BTN---------BTN---------BTN---------
//не нашел в функц ищу в кнопках 0-9

if (fn_cmd=="") 
        { //b
 for (byte i=0; i <10; i++)
        {
if (code_btn[i]!=code_ir_tmp) continue; //не нашёл код
Serial.print("bt=");
Serial.println(i);

if (bt1==99&&i==0&&!play)  //stop around scr
{
scr_round=!scr_round;
draw_stop_round();
break; 
}

if (bt1==99&&i==0&&play) //откл. показ группы песни 
{
draw_no_song();
break;
}

if (bt1==99) 
{
bt1=i;
t_start_bt1=millis();
}
else
if (bt2==99) bt2=i;
else
if (bt3==99) bt3=i;


if (bt1!=99) 
          {
if (bt3!=99) btn=bt1*100+bt2*10+bt3;
else
if (bt2!=99) btn=bt1*10+bt2;
else
btn=bt1;
          }

#ifdef debug
Serial.print("bt1=");
Serial.println(bt1);
Serial.print("bt2=");
Serial.println(bt2);
Serial.print("bt3=");
Serial.println(bt3);
Serial.print("btn=");
Serial.println(btn);
#endif


draw_num(btn,'C');  

break;//нашел

}


    
        } //e





fn_cmd="";
irrecv.resume(); // принимаем следующую команду

}



                            }

#endif //esp32 + ir  

#ifdef ESP32
//======================================================================================
//                   do_timer     
//======================================================================================

void do_timer()
{

static uint32_t t_ref=0;
static byte mnt_old=99;
static byte scr_n=99;
if (millis()>=t_timer)   //START or STOP
{
t_timer=0;
t_ref=0;
scr_n=99;
if (play) 
{
timer_stop();

if (ch_prev_alarm!=0) //если до таймера уже играло возврат на канал
  {
if (ch!=ch_prev_alarm)
{
ch=ch_prev_alarm;  
fn_cmd="play";  
}
  }
else
{
#ifndef only_radio // если только радио остаюсь на канале иначе выход
fn_cmd="stop";//по таймеру
#endif
}

al.active=false;

}

else
{

fn_cmd="play";//по таймеру radio no ow
}
do_fn_btn_ir();
fn_cmd="";

return;
}
//-----------------------------------
if (scr_n!=scr_number||refresh_all) t_ref=0; //если перекл экран обновить таймер
if (millis()>t_ref)
{


t_ref=millis()+10000;


scr_n=scr_number;

uint32_t mn=int((t_timer-millis())/60000);
if (mnt_old!=mn||refresh_all)
{
mnt_old=mn;
draw_num(mn+1,'T');  
}

}




  
}


#endif //esp32




//===============================================================
//                  do_touch_btn()
//===============================================================
#if (defined (pin_btn_touch)||defined(pin_btn_No_touch)) && defined (ESP32)


void do_touch_btn(byte touch_or_btn)
{
static byte touch_count=0;
static uint32_t t_next_touchRead=0;
const byte press_count_play=10;
const byte press_count_esc=14;
const byte press_count_next=3;
const byte press_count_prev=7;
static char fn_cmd_touch='0'; //N,P,S,E 

if (t_next_touchRead>millis()) return;
int touch_value_read=999;



        
#ifdef pin_btn_touch
if (touch_or_btn==1) touch_value_read=touchRead(pin_btn_touch);
#endif //pin_btn_touch


#ifdef pin_btn_No_touch
if (touch_or_btn==2&&digitalRead(pin_btn_No_touch)==LOW)
  {
touch_value_read=touch_value;
Serial.print(F("pin_btn_No_touch="));
Serial.println(touch_value_read);
  }
#endif //pin_btn_No_touch


//нажата----------------------------------------------

if ( touch_value_read<=touch_value)   
     
    { 

touch_count++;
t_next_touchRead=millis()+300;    


#ifdef debug
if (touch_count>1) //ложные искл.
{
Serial.print(F("touch_value_read="));
Serial.println(touch_value_read);
Serial.print(F("touch_count==="));
Serial.println(touch_count);
}
#endif



if (touch_count>press_count_esc) //отмена
  {
//if (play)
draw_num(0,'C');
//else //not pl
//{
//if (scr_name[scr_number]=="S0") tft.fillCircle(158,185,5,TFT_BLACK);
//else
// tft.fillRect(0,0,18,12,TFT_BLACK);
//}

touch_count=0;
fn_cmd_touch='0';
return;
  }
//-----------------------------------------------------  

if (touch_count>=press_count_play&&play)  //stop
{
if (touch_count==press_count_play) draw_num(0,'C');
else draw_stop();
fn_cmd_touch='s';
return;
}

if (touch_count>=press_count_play&&!play)  //do play
{
if (touch_count==press_count_play) draw_num(0,'C');
draw_play();

fn_cmd_touch='P';

return;
}

//----------prev----------------
if (touch_count>=press_count_prev)
{
if (touch_count==press_count_prev) draw_num(0,'C');

draw_prev();
fn_cmd_touch='p';
return;

}


//---------next----------------------
if (touch_count>=press_count_next) //или экран или станция
{

if (touch_count==press_count_next) draw_num(0,'C');

draw_next();
fn_cmd_touch='n';
return;
}



return;
    }

    
///отпущена--------------------------------------------------

if (fn_cmd_touch=='n') fn_cmd="next";
if (fn_cmd_touch=='p') fn_cmd="prev";
if (fn_cmd_touch=='P') {fn_cmd="play";timer_stop();}
if (fn_cmd_touch=='s') {fn_cmd="stop";timer_stop();}


if (touch_count>1&&fn_cmd!="")
    {
do_fn_btn_ir();
Serial.print(F("fn_cmd_touch="));Serial.println(fn_cmd_touch);
fn_cmd="";
if (play) draw_num(0,'C');
    }

touch_count=0;   
fn_cmd_touch='0';


}

#endif



//================================================================================================
//==============================================================
//                      do_read_ir8266
//==============================================================


#if defined (pin_ir) && defined (ESP8266)
void do_read_ir8266()
{
static uint32_t next_time=0; 
unsigned long code_ir_tmp;

if (millis()<next_time) 
{
irrecv.resume(); // принимаем следующую команду
return;
}


//IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
if ( irrecv.decode( &results )) { // если данные пришли
fn_cmd="";

Serial.print(F( "IR==")); 
Print64(results.value);
code_ir_tmp=results.value;
//ищу код в массиве
 for (int i=0; i <fn_count; i++)
{
if (code[i]!=code_ir_tmp) continue; //не нашёл код

//нашел
fn_cmd= fn[i];
Serial.print("find ir code===");
Serial.println(fn_cmd);
break;
}

if (fn_cmd!="")
{

if (fn_cmd=="next")
{
scr_number++;
scr_num_show(scr_number);
}

if (fn_cmd=="prev")
{
scr_number--;
scr_num_show(scr_number);
}
}  //!=""
else
//BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
//ищу в кнопках
 for (byte i=0; i <10; i++)
        {
if (code_btn[i]!=code_ir_tmp) continue; //не нашёл код
Serial.print("bt=");
Serial.println(code_btn[i]);

if (i==0&&!play)  //stop around scr
{
scr_round=!scr_round;
draw_stop_round();
break; 
}


if (i<=scr_count_pack &&scr_number!=i-1) scr_num_show(i-1);

        }





if (fn_cmd==""||fn_cmd=="vl+"||fn_cmd=="vl-"||fn_cmd=="mute") 
next_time=millis()+t_ir_sleep_short;
else
next_time=millis()+t_ir_sleep; 

fn_cmd= "";  


irrecv.resume(); // принимаем следующую команду
}



                            }




  



//======================================================================
//              Print64
//=====================================================================






void Print64(uint64_t num) {

  char rev[128]; 
  char *p = rev+1;

  while (num > 0) {
    *p++ = '0' + ( num % 10);
    num/= 10;
  }
  p--;
  /*Print the number which is now in reverse*/
  while (p > rev) {
    Serial.print(*p--);
  }
  Serial.println();
}



#endif
