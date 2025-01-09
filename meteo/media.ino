#ifdef ESP32
//======================================================================================
//                    do_select_num_st
//======================================================================================
bool do_select_num_st(byte num_find)
{


String filename="/i_stat.txt";

#ifdef pin_sd
Serial.print("SD ");
Serial.println(filename);
File f = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 #else
Serial.print("Spiffs ");
Serial.println(filename);
fs::File f = SPIFFS.open( filename, "r");    // File handle reference for SPIFFS
#endif


if (!f) {Serial.print(filename);Serial.println(F(" no open,create"));return false;}
//----------------------------
String name="";
String url="";
bool find_num=false; 
bool find_ch=false; 
byte num_tmp=254;

const byte y_begin=75;
int x=133;

#ifdef tft_320_240
const byte y_step=14;
const byte x_step=93;
const int w=320;
const int h=200;
tft.setFreeFont(v6);
#endif
//--------------------------
#ifdef tft_480_320
tft.setFreeFont(v9mono);
const byte y_step=18;
const byte x_step=173;
const int w=480;
const int h=250;

#endif
byte y=y_begin+14;


byte vol=200;
String str;
ch_next=254;
ch_prev=0;

static int x_ch_old=0;
static int y_ch_old=0;
static byte ch_old=0;
static int x_ch=0;
static int y_ch=0;


#ifdef debug
Serial.println(F("----------------i_stat.txt----------------------"));
Serial.println(filename);

#endif
//---------------------------------------------------------
while (f.available()) {
yield();  
str = f.readStringUntil('\n');
//Serial.println(str); 
//if (str.indexOf("{")>=0) (Serial.print("{=");Serial.println(str.indexOf("{"))); 
if (str.indexOf("{")==0&&refresh_all) 
{
#if defined(ESP32) && defined(encoder)
do_fav_ch(str); //start play
continue;
#endif
}
if (str.indexOf("#")!=0) continue;
int tz=0;
int tz2=0;
find_num=false;
//tz=str.indexOf("#");
//Serial.println("#");
//Serial.println(tz);

name="";
url="";
         
//num------------------------
tz2=str.indexOf(";",tz+1);
if (tz>0)
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{
num_tmp=str.substring(tz+1,tz2).toInt();
//Serial.println(num_tmp);
//max
if (ch_max<num_tmp) ch_max=num_tmp;
//min
if (ch_min>num_tmp) ch_min=num_tmp;
//next
if (num_tmp>num_find) //в случае неудачи будет след канал
{
if (ch_next>num_tmp)
    {
      ch_next=num_tmp;

    }  
}

//prev
if (num_tmp<num_find) //в случае неудачи будет след канал
{
if (ch_prev<num_tmp)
    {
      ch_prev=num_tmp;

    }  
}


//ffffffffffffff
if (num_tmp==num_find) 
{
ch=num_tmp;
#ifdef debug 
Serial.print("find=====");
Serial.println(num_tmp);
#endif

find_num=true;
}
//name --------------------------------
tz=tz2;
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{
//Serial.println(str.substring(tz+1,tz2));
name=str.substring(tz+1,tz2);
}
else
{
Serial.println(F("not found name ch"));
find_num=false; 
continue; 
}
///url -------------------------------
tz=tz2;
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{
//Serial.println(str.substring(tz+1,tz2));
url=str.substring(tz+1,tz2);
}
else
{
Serial.println(F("not found name URL ch"));
find_num=false;  
continue; 
}

//volume vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
tz=tz2;
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{
String str_vol=str.substring(tz+1,tz2);
vol=str_vol.toInt();
if (vol>0&&vol<101);//оставляю
else vol=vol_def;
}


//2 колонки не заполнены
//----------------------------------------------------------------------------------
if (x<w&&refresh_all) //2 колонки не заполнены
 
  {
tft.setCursor(x,y);
tft.setTextColor(c_channel);
tft.print(num_tmp);
if (num_tmp<10) tft.print(" ");
tft.print(name);
Serial.print(num_tmp);
Serial.println(name);

  }

//ffffffffffffffffffffffffffffffffffffffffffffffffffff
if (find_num)
{
x_ch=x;
y_ch=y;

if (x_ch_old!=0&y_ch_old!=0)
{
tft.setCursor(x_ch_old,y_ch_old);
tft.setTextColor(TFT_LIGHTGREY,TFT_BLACK);
tft.print(ch_old);
tft.drawFastHLine(x_ch_old,y_ch_old+3,x_step-10,TFT_BLACK) ;
}
tft.setCursor(x_ch,y_ch);
tft.setTextColor(TFT_YELLOW,TFT_RED);
tft.print(ch);
tft.drawFastHLine(x_ch,y_ch+3,x_step-10,c_ch_line) ;
x_ch_old=x_ch;
y_ch_old=y_ch;
ch_old=ch;

ch_url=url;
ch_name=name;
find_ch=true;
if (!vol_rotate) //если крутил громкость, оставляю как есть
{
if (al.active&&al.vol!=0) vol=al.vol;//если alarn  активный беру из него
volume=vol*4;
if (volume>=400) volume=399;
}

}


          }

y=y+y_step;

if (y>h-3) //очищаю под вторую колонку каналов
{
y=y_begin+y_step;
x=x+x_step;
if (x<w-30&&refresh_all)
{
tft.fillRect(x,y,w-x,h-y_begin,TFT_BLACK) ;//ch
tft.drawFastVLine(x-1,y_begin,h-y_begin,TFT_LIGHTGREY) ;//ch
}
 

}

 
     

}
f.close();
#ifdef debug
Serial.print(F("ch=="));
Serial.println(ch);
Serial.print(F("ch_name=="));
Serial.println(ch_name);
Serial.print(F("url=="));
Serial.println(url);
Serial.print(F("vol=="));
Serial.println(vol);
Serial.print(F("ch_max=="));
Serial.print(F("============"));

Serial.println(ch_max);
Serial.print(F("ch_min=="));
Serial.println(ch_min);
Serial.print(F("ch_prev=="));
Serial.println(ch_prev);
Serial.print(F("ch_next=="));
Serial.println(ch_next);

#endif

if (ch_next>ch_max) ch_next=ch_min;
if (ch_prev<ch_min) ch_prev=ch_max;

if (!find_ch&&ch_old!=0) ch=ch_old;
return find_ch; 
}







//==========================================================================================================
//                         do_fn_btn_ir
//==========================================================================================================

void do_fn_btn_ir()
{


bool ch_fnd=false; 
Serial.print(F("fh cmd=======")) ;Serial.println(fn_cmd) ;

if (fn_cmd=="") return;
if (fn_cmd=="vl+"&&play)//volume
 {
volume=volume+20;
if(volume>399) volume=399;
#ifdef debug 
Serial.print("volume=") ;Serial.println(volume) ;
#endif
out->SetGain(((float)volume)/100.0);
draw_vol();
vol_rotate=true;
return; 
 }

 if (fn_cmd=="vl-"&&play)//volume
 {
volume=volume-20;
if(volume<0) volume=0;
#ifdef debug 
Serial.print("volume=") ;Serial.println(volume) ;
#endif
out->SetGain(((float)volume)/100.0);
draw_vol();
vol_rotate=true;
return; 
 }

if (fn_cmd=="mute"&&play)//volume
 {
do_mute();
return; 
 }

if (fn_cmd=="stop"&&play)//stop
 {
ch_prev_alarm=0;
vol_rotate=false;  
#ifndef only_radio
draw_stop();
StopPlaying(); //off
play=false;
scr_num_show(scr_number);
return;
#else
fn_cmd="next";
Serial.print(F("only radio ")) ;
Serial.println(fn_cmd) ;

#endif



}

//next SCR
if (fn_cmd=="next"&&!play) //след. станция если уже играет
  {
scr_number++;
scr_num_show(scr_number);
return;
  }

 //prev SCR
if (fn_cmd=="prev"&&!play) //след. станция если уже играет
  {
scr_number--;
scr_num_show(scr_number);

return;
  }
 

//--------------------------

//----------------PLAY---------------------------------------------------------------
if (fn_cmd=="play"&&!play)//play on
  {
tft.fillScreen(TFT_BLACK);
play=true;
refresh_all=true; //первый запуск
draw_vol();
  }
else 
//prev stat.
if (fn_cmd=="prev"&&play) //prev. станция если уже играет
  {
draw_prev();
if (ch==ch_min)
ch=ch_max;
else
ch=ch_prev;
  }
else
//next stat.
if (fn_cmd=="next"&&play) //след. станция если уже играет
  {
draw_next();    
if (ch==ch_max) 
ch=ch_min;
else
ch=ch_next;
  }
  else
  if (fn_cmd=="play"&&play) ;//play ch btn
  else
  return; 

 
ch_fnd=do_select_num_st(ch);
if (!ch_fnd)
{
Serial.print(F("ch not found==")) ;
Serial.println(ch);
draw_num(0,'C');
return;
}


    
do_create_http();
draw_num(0,'C');       

}



//---------------------------------------------------------
//                  do_play
//---------------------------------------------------------
void do_play()
{

 if (mp3) {
  if (mp3->isRunning()) 
  {
       if (!mp3->loop()) 
       {
       StopPlaying();
      Serial.println("!mp3->loop()");      
       
       }
  }
           } else {


if (millis()>retryms) {
retryms = 0;
Serial.println("if (millis()>retryms)");    
do_create_http();
 }
    
  }


}


//==========================================================
//			do_create_http
//==========================================================

void do_create_http()
{
static byte rep=0;

if (rep>rep_count) //3 попытки проигрывания, если неудача играю след.
  {
rep=0;
Serial.println("if (rep>rep_count) ");    

do_select_num_st(ch_next);
  }
else
StopPlaying();  

//file = new AudioFileSourceHTTPStream;
file = new AudioFileSourceICYStream;
file->RegisterMetadataCB(MDCallback, (void*)"ICY");
delay(500);

bool f_open=file->open(ch_url.c_str());


if (f_open==true) {
Serial.println("f_open==true "); 
buff = new AudioFileSourceBuffer(file, preallocateBuffer, preallocateBufferSize);
mp3 = new AudioGeneratorMP3(preallocateCodec, preallocateCodecSize);
mp3->begin(buff, out);
 if (!mp3->isRunning()) {
    Serial.println(F("Can't connect to URL"));
     Serial.println(ch_url);
tft.fillCircle(120,65,4,TFT_YELLOW);  
    StopPlaying();
    retryms = millis() + 3000;
    rep++;
 return;
  }
out->SetGain(((float)volume)/100.0);
#ifdef set_audio_mono
out->SetOutputModeMono(true) ; 
tft.fillCircle(120,65,4,TFT_BLACK);    
#endif    
          } 
          else
          {  //error open
Serial.println(F("Can't open file->URL"));
rep++;
tft.fillCircle(120,65,4,TFT_YELLOW);  
StopPlaying();
retryms = millis() + 3000;
          }

#ifdef debug
Serial.print(F("rep_count="));           
Serial.println(rep);           
    
#endif


          }
         
//=======================================================
//			StopPlaying
//=======================================================

void StopPlaying()
{
#ifdef debug
Serial.print(F("begin StopPlaying()="));
Serial.println( ESP.getFreeHeap());  
#endif
 
  if (mp3) {
out->SetGain(0);
    mp3->stop();
    delete mp3;
    mp3 = NULL;
// Serial.println("delete mp3");
  }
 
  if (buff) {
    buff->close();
    delete buff;
    buff = NULL;
// Serial.println("delete buff");
  }
  if (file) {
    file->close();
    delete file;
    file = NULL;
// Serial.println("delete file");
  }

     if (file_mp3) {
    file_mp3->close();
    delete file_mp3;
    file_mp3 = NULL;
// Serial.println("delete file_mp3");
  }

play_mp3=false;   



   

#ifdef debug
Serial.print(F("end StopPlaying()="));
Serial.println( ESP.getFreeHeap());
#endif

if (WiFi.status() != WL_CONNECTED) 
{
play=false;
t_timer=0;
scr_num_show(scr_number);

  
}


}



//=========================================================================
//                    do_play_mp3
//=========================================================================
void  do_play_mp3()
{

if (play_mp3) 
  {
 if (mp3) 
  if (mp3->isRunning()) 
  
 if (!mp3->loop()) 
{
StopPlaying();
 
}
 
  }


  
}


//=========================================================================
//                    do_create_mp3
//=========================================================================

void do_create_mp3()
{
play_mp3=false;

#ifdef pin_sd
Serial.print("SD ");
file_mp3 = new AudioFileSourceSD();
bool f_open=file_mp3->open("/beep.mp3");
 #else
Serial.print("Spiffs ");
file_mp3 = new AudioFileSourceSPIFFS;
bool f_open=file_mp3->open("/beep.mp3");
#endif




if (!f_open) 
{

Serial.println(F(" Can't open /beep.mp3"));
StopPlaying();
return;  
}



buff = new AudioFileSourceBuffer(file_mp3, preallocateBuffer, preallocateBufferSize);
mp3 = new AudioGeneratorMP3(preallocateCodec, preallocateCodecSize);
mp3->begin(buff, out);

 if (!mp3->isRunning()) {
    Serial.println(F("Can't play_mp3"));
    StopPlaying();
    return;
  }

  out->SetGain(((float)beep_mp3_vol*4)/100.0);

play_mp3=true;
//Serial.println(F("play_mp3=true"));
}





#endif
