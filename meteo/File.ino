


//==========================================================================================================
//                        do_read_config_txt
//==========================================================================================================

bool do_read_config_txt()
{

String filename="/config.txt";
bool val_0=false;
scr_show_count=0;

#ifdef pin_sd
Serial.print("SD ");
Serial.println(filename);
File f = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
#else
Serial.print("Spiffs ");
Serial.println(filename);
fs::File f = SPIFFS.open( filename, "r");    // File handle reference for SPIFFS
#endif
 







if (!f) {Serial.println(filename);Serial.println(F(" no open,create"));
return false;}

//----------------------------
String name,val,str;
byte i=0;
#ifdef debug
Serial.println(F("-------config.txt-------------------------------"));  
#endif
//----------------------------------
while (f.available()) {
str = f.readStringUntil('\n');
str.trim();
//Serial.println(str); //Printing for debugging purpose
int tz=str.indexOf("#") ;
if (tz!=0) continue;

//---------------------------
int tz2=str.indexOf(";",tz+1);
if (tz2==-1) continue;
//name
name=str.substring(tz+1,tz2);
name.trim();
//Serial.print("name==");Serial.println(name);

//val-----------------
tz=tz2+1;
tz2=str.indexOf(";",tz);
if (tz2==-1) continue;
val=str.substring(tz,tz2);
val.trim();
if (val=="0") val_0=true;else val_0=false; //если =0 
/*
#ifdef debug
Serial.print("val zero");Serial.println(val_0);
Serial.print("val==");Serial.println(val);
Serial.print("val_toint==");Serial.println(val.toInt());
#endif
*/
//kkkkkkkkkkkkkkkkkkkkkkkkkkkkey
if (name=="key") 
{
if (val.length()>0) appid=val;
else appid="";
#ifdef debug 
Serial.print("key=");
Serial.println(appid);
#endif
}

if (name=="p_min") 
{
if (val.toInt()>0) p_min=val.toInt();
else p_min=0;
#ifdef debug 
Serial.print("p_min=");
Serial.println(p_min);
#endif
}

if (name=="p_max") 
{
if (val.toInt()>0) p_max=val.toInt();
else p_max=10000;
#ifdef debug 
Serial.print("p_max=");
Serial.println(p_max);
#endif
}


if (name=="v_max") 
{
if (val.toInt()>0) v_max=val.toInt();
else v_max=99;
#ifdef debug 
Serial.print("v_max=");
Serial.println(v_max);
#endif
}

if (name=="TIMEZONE") 
{
if (val.length()>0) TIMEZONE=val.toInt();
else TIMEZONE=0;
#ifdef debug 
Serial.print("TIMEZONE=");
Serial.println(TIMEZONE);
#endif
}


if (name=="lat") 
{
if (val.length()>0) lat=val;
else lat="";
#ifdef debug 
Serial.print("lat=");
Serial.println(lat);
#endif
}

if (name=="lon") 
{
if (val.length()>0) lon=val;
else lon="";
#ifdef debug 
Serial.print("lon=");
Serial.println(lon);
#endif
}


if (name=="t_max") 
{
if (val.toInt()!=0||val_0==true) t_max=val.toInt();
else t_max=100;
#ifdef debug 
Serial.print("t_max=");
Serial.println(t_max);
#endif
}


if (name=="t_min") 
{
if (val.toInt()!=0||val_0==true) t_min=val.toInt();
else t_min=-100;
#ifdef debug 
Serial.print("t_min=");
Serial.println(t_min);
#endif
}


if (name=="uv_max") 
{
if (val.toInt()!=0||val_0==true) uv_max=val.toInt();
else uv_max=100;
#ifdef debug 
Serial.print("uv_max=");
Serial.println(uv_max);
#endif
}


if (name=="delta_p") 
{
if (val.toInt()!=0||val_0==true) delta_p=val.toInt();
else delta_p=0;
#ifdef debug 
Serial.print("delta_p=");
Serial.println(delta_p);
#endif
}

if (name=="beep_b") 
{
if (val.toInt()>0||val_0==true) beep_b=val.toInt();
else beep_b=0;
#ifdef debug 
Serial.print("beep_b=");
Serial.println(beep_b);
#endif
}

if (name=="beep_e") 
{
if (val.toInt()>0||val_0==true) beep_e=val.toInt();
else beep_e=0;
#ifdef debug 
Serial.print("beep_e=");
Serial.println(beep_e);
#endif
}


if (name=="beep_mp3_vol") 
{
int vol_mp3=val.toInt();
if (vol_mp3>0&&vol_mp3<101) 
{
beep_mp3_vol=vol_mp3;
if (beep_mp3_vol==100) beep_mp3_vol=99;
  
}
else beep_mp3_vol=0;

#ifdef debug 
Serial.print(F("beep_mp3_vol="));
Serial.println(beep_mp3_vol);
#endif
}



if (name=="t_b") 
{
if (val.toInt()!=0||val_0==true) t_b=val.toInt();
#ifdef debug 
Serial.print(F("t_b="));
Serial.println(t_b);
#endif
}


if (name=="t_e") 
{
if (val.toInt()!=0||val_0==true) t_e=val.toInt();
#ifdef debug 
Serial.print(F("t_e="));
Serial.println(t_e);
#endif
}


if (name=="scr_name_def") 
{
if (val.length()>0) 
{
byte len=val.length()+1; 
char buf[len];
val.toCharArray(buf,len);
//scr_name_def=buf;
strcpy(scr_name_def, buf);
#ifdef debug 
Serial.print(F("scr_name_def="));
Serial.println(scr_name_def);
#endif

}
}


/*
if (name=="scr_name_def2") 
{
#ifdef two_tft
if (val.length()>0) 
{
byte len=val.length()+1; 
char buf[len];
val.toCharArray(buf,len);
//scr_name_def=buf;
strcpy(scr_name_def2, buf);
}
#endif
}

*/
if (name=="esp_restart") 
{
if (val.toInt()>0||val_0==true) esp_restarts=val.toInt();
#ifdef debug 
Serial.print(F("esp_restart="));
Serial.println(esp_restarts);
#endif
}


//scr round

if (name=="S1_show") 
  {
if (val.toInt()>0) 
{
#ifdef S1
t_S1_show=val.toInt();
#ifdef debug 
Serial.print(F("S1_show="));
Serial.println(t_S1_show);
#endif
scr_show_count++;
#endif
}
  }


if (name=="S2_show") 
  {
if (val.toInt()>0) 
{
#ifdef S2
t_S2_show=val.toInt();
#ifdef debug 
Serial.print(F("S2_show="));
Serial.println(t_S2_show);
#endif
scr_show_count++;
#endif
}
  }


if (name=="S3_show") 
  {
  #ifndef  tft2_S3  
if (val.toInt()>0) 
{
#ifdef S3
t_S3_show=val.toInt();
#ifdef debug 
Serial.print(F("S3_show="));
Serial.println(t_S3_show);
#endif
scr_show_count++;
#endif
}
 #endif //tft2_S3
  
  }


if (name=="S4_show") 
  {
     #ifndef  tft2_S4  
if (val.toInt()>0) 
{
#ifdef S4
t_S4_show=val.toInt();
#ifdef debug 
Serial.print(F("S4_show="));
Serial.println(t_S4_show);
#endif
scr_show_count++;
#endif
}
 #endif //tft2_S4
  }


if (name=="S5_show") 
  {
if (val.toInt()>0) 
{
#ifdef S5
t_S5_show=val.toInt();
#ifdef debug 
Serial.print(F("S5_show="));
Serial.println(t_S5_show);
#endif
scr_show_count++;
#endif
}
  }



if (name=="Sf_show") 
  {
if (val.toInt()>0) 
{
#ifdef Sf
t_Sf_show=val.toInt();
#ifdef debug 
Serial.print(F("Sf_show="));
Serial.println(t_Sf_show);
#endif
scr_show_count++;
#endif
}
  }



if (name=="Sg_show") 
  {

         #ifndef  tft2_Sg  
if (val.toInt()>0) 
{
#ifdef Sg
t_Sg_show=val.toInt();
#ifdef debug 
Serial.print(F("Sg_show="));
Serial.println(t_Sg_show);
#endif
scr_show_count++;
#endif
}
 
  #endif //tft2_Sg
  }




if (name=="S0_show") 
  {
if (val.toInt()>0) 
{
#ifndef openw
t_S0_show=val.toInt();
#ifdef debug 
Serial.print(F("S0_show="));
Serial.println(t_S0_show);
#endif
scr_show_count++;
#endif
}
  }




  #ifdef Sf
if (name=="Sf_t_slide") 
  {
if (val.toInt()>0) 
{

Sf_t_slide=val.toInt();
#ifdef debug 
Serial.print(F("Sf_t_slide="));
Serial.println(Sf_t_slide);
#endif

}
  }


  #endif





if (name=="log") //save log 
{
log_file=true;
#ifdef debug 
Serial.print("log_file=");
Serial.println(log_file);
#endif
}




//------------------------IoT-------------------------------------------
#ifdef IoT


//iot_id-------------
if (name=="iot_id"||name=="iot_id_read") 
{
String iot_id_tmp;
if (val.length()>0) 
  {
iot_id_tmp=val;
char **pointer, *stringVar;
unsigned long unsignedVar;
char charBufVar[20];
iot_id_tmp.toCharArray(charBufVar, 20);
stringVar =charBufVar;
unsignedVar = strtoul(stringVar,pointer,10);
if (unsignedVar>0) 
{
if (name=="iot_id") iot_id=unsignedVar;
if (name=="iot_id_read") iot_id_read=unsignedVar;

#ifdef debug 
Serial.print(name+"=");
Serial.println(unsignedVar);
#endif
}
  
  
  } 
}


//const char * iot_key = "";
if (name=="iot_key"||name=="iot_key_read") 
{
if (val.length()>0) 
{
val.trim();

unsigned char* buf = new unsigned char[50];
val.getBytes(buf,50,0);
if (name=="iot_key") iot_key= (const char*)buf;
if (name=="iot_key_read") iot_key_read= (const char*)buf;


#ifdef debug 
Serial.print(name+"=");
if (name=="iot_key") Serial.println(iot_key);
if (name=="iot_key_read") Serial.println(iot_key_read);
#endif


}
else
iot_key="";

}

//period send sec>=20
if (name=="iot_period_send"||name=="iot_period_read") 
{
String iot_period_send_tmp;
if (val.length()>0) 
  {
iot_period_send_tmp=val;
char **pointer, *stringVar;
unsigned long unsignedVar;

char charBufVar[20];
iot_period_send_tmp.toCharArray(charBufVar, 20);

stringVar =charBufVar;
unsignedVar = strtoul(stringVar,pointer,10);//=324234
if (unsignedVar>0) 
{
if (name=="iot_period_send") iot_period_send=unsignedVar;
if (name=="iot_period_read") iot_period_read=unsignedVar;
}

#ifdef debug 
Serial.print(name+"=");
Serial.println(unsignedVar);
#endif
  } 
}



//temp квартира(room);ном поля(num field) bme280 
if (name=="iot_T_fld_send"||name=="iot_T_fld_read") 
{
if (val.toInt()>0&&val.toInt()<10)
{
if (name=="iot_T_fld_send") iot_T_fld_send=val.toInt();
if (name=="iot_T_fld_read") iot_T_fld_read=val.toInt();
}
#ifdef debug 
Serial.print(name+"=");
Serial.println(val.toInt());
#endif
}


//humidity квартира(room) ;ном поля(num field) bme280

if (name=="iot_H_fld_send"||name=="iot_H_fld_read") 
{
if (val.toInt()>0&&val.toInt()<10)
{
if (name=="iot_H_fld_send") iot_H_fld_send=val.toInt();
if (name=="iot_H_fld_read") iot_H_fld_read=val.toInt();
#ifdef debug 
Serial.print(name+"=");
Serial.println(val.toInt());
#endif
}

}


//temp улица(street)
if (name=="iot_T2_fld_send"||name=="iot_T2_fld_read") 
{
if (val.toInt()>0&&val.toInt()<10)
{
if (name=="iot_T2_fld_send") iot_T2_fld_send=val.toInt();
if (name=="iot_T2_fld_read") iot_T2_fld_read=val.toInt();

#ifdef debug 
Serial.print(name+"=");
Serial.println(val.toInt());
#endif
}

}

//давление(pressure)
if (name=="iot_P_fld_send"||name=="iot_P_fld_read") 
{
if (val.toInt()>0&&val.toInt()<10)
{
if (name=="iot_P_fld_send") iot_P_fld_send=val.toInt();
if (name=="iot_P_fld_read") iot_P_fld_read=val.toInt();
#ifdef debug 
Serial.print(name +"=");
Serial.println(val.toInt());
#endif
}

}

//скорость ветра (wind speed)
if (name=="iot_W_fld_send") 
{
if (val.toInt()>0&&val.toInt()<10) 
{
iot_W_fld_send=val.toInt();
#ifdef debug 
Serial.print(name+"=");
Serial.println(iot_W_fld_send);
#endif
}
}


//дождь мм(rain)
if (name=="iot_R_fld_send") 
{
if (val.toInt()>0&&val.toInt()<10) iot_R_fld_send=val.toInt();
#ifdef debug 
Serial.print(F("iot_R_fld_send="));
Serial.println(iot_R_fld_send);
#endif
}









#endif //iot

}

#ifdef debug 
Serial.print(F("scr_show_count="));  
Serial.print(scr_show_count);  
#endif



f.close();
#ifdef debug 
Serial.println(F("-----end--config.txt-----------"));  
#endif

return true;
}


#ifdef pin_ir
//==========================================================================================================
//                              do_read_file_ik
//==========================================================================================================
bool do_read_file_ik()
{
bool find=false; 
String filename="/ik.txt";

#ifdef pin_sd
Serial.print("SD ");
Serial.println(filename);
File f = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 #else
Serial.print("Spiffs ");
Serial.println(filename);
fs::File f = SPIFFS.open( filename, "r");    // File handle reference for SPIFFS
#endif
 
if (!f) {Serial.println(F("/ik.txt no open,create"));return find;}




Serial.println(F("open /ik.txt   IR code"));
String str="";
//-------------------
while (f.available()) {
str = f.readStringUntil('\n');
Serial.println(str);
if (str.indexOf("//")==0) continue;
if (str=="") continue; 
char **pointer;
char buf[11];
int tz=0;
int tz2=0;
String func="";
ir_code=0;
//---------------
tz=str.indexOf("#");
//Serial.println("#");
//Serial.println(tz);
if (tz>=0)
       {
         
//func------------------------
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{
func=str.substring(tz+1,tz2);
//Serial.println(func);
}

//code ir-----------------
tz=tz2;
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{
//Serial.println(str.substring(tz+1,tz2));
String code=str.substring(tz+1,tz2);
//Serial.println(code);
code.toCharArray(buf,sizeof(buf));
ir_code= atoll(buf);


#ifdef debug
Serial.println(func);
Serial.println(ir_code);
#endif 
}
if (func!=""&&ir_code!=0)
  {
//если кнопка
if (func.substring(0,2)=="bt")
{
String func_btn=func.substring(2);
int num_btn=func_btn.toInt();
if (num_btn<10&&num_btn>=0) code_btn[num_btn]=ir_code;
Serial.print ("num_btn="); Serial.println(num_btn);
continue;
}

//ищу фун
      for (int i = 0; i < fn_count; i++) {
        if (func == fn[i]) {
            code[i]=ir_code;
            Serial.print (func); Serial.print("====FIND=======");
            Serial.println(code[i]);
            find=true;   
        }
      }
   }
 } 
}
f.close();
return find;
}

#endif //pin_ir


//-----------------------------------------------------------------------------
//               do_log()
//-----------------------------------------------------------------------------

void do_log()
{
if (!log_file||log_str=="") return;


//t=now();
String filename;

if (!sync_t)  filename="/log_b.txt";
else
if (day(t)%2==0) filename="/log0.txt";
else
filename="/log1.txt";


  #ifdef pin_sd
Serial.print("SD ");
Serial.println(filename);
#ifdef ESP32
fs::FS &fs = SD;
File f = fs.open(filename, FILE_APPEND);
#endif
#ifdef ESP8266
File  f = SD.open( filename, FILE_WRITE);  // or, file handle reference for SD library
#endif
#else
Serial.print("Spiffs ");
Serial.println(filename);
fs::File   f = SPIFFS.open( filename, "a+");    // File handle reference for SPIFFS

  #endif





if (!f) {Serial.println(filename);Serial.println(F(" log_file no open,create"));return;}

//t=now();
String t_str="";
if (hour(t) <10) t_str="0"+String(hour(t));
else
t_str=String(hour(t));

if (minute(t) <10) t_str=t_str+":0"+String(minute(t));
else
t_str=t_str+":"+String(minute(t));

if (second(t) <10) t_str=t_str+":0"+String(second(t));
else
t_str=t_str+":"+String(second(t));



log_str=t_str+";"+log_str;
#ifdef debug
Serial.print(F("log_str=="));
Serial.println(log_str);
#endif
f.println(log_str);
f.close();
log_str=""; 
  }









#ifdef ESP32 

//==========================================================================================================
//              do_read_file_shed
//==========================================================================================================
bool do_read_file_shed()
{
Serial.println("do_read_file_shed");
String filename="/alarm.txt";
#ifdef pin_sd
Serial.print("SD ");
Serial.println(filename);
File  f = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 #else
Serial.print("Spiffs ");
Serial.println(filename);
fs::File   f = SPIFFS.open( filename, "r");    // File handle reference for SPIFFS
#endif

if (!f) {Serial.println(filename);Serial.println(F(" no open,create"));return false;}
//----------------------------


al.active=false;
al.label='x'; //��� I,M,J inet,mp3,jpeg
al.h=99;//hour
al.m=99; //min
al.ch_num=0; // ch
al.fname="";
al.t_long=0;//length T millisec
al.vol=0; //volume
t_next_shed=99;
next_shed_ch=0;




String P,str;
byte i=0;
int tz2=0;

int h=-1,m=-1;
int t_long=-1;
int ch_num=-1;
//int count=-1,interval=-1,vol_up=-1;
int vol=-1;
String label="",fname="";
bool parse_line=false;
byte t_e_ch=0, t_b_ch=0; 
//t=now();
//----------------------------------
while (f.available()) {
str = f.readStringUntil('\n');

yield();

str.trim();
#ifdef debug
Serial.println(str); //Printing for debugging purpose
#endif

int tz=-1;
tz=str.indexOf("#");
if (tz!=0)continue;


tz2=0;
h=-1;m=-1;
t_long=-1;
ch_num=-1;
vol=-1;
label="";
fname="";
t_e_ch=0; t_b_ch=0; 
tz2=tz+2;          
//label
P=str.substring(tz+1,tz2);

#ifdef debug
Serial.print("P_Type=");
Serial.println(P);
#endif

if (P!="I"&&P!="i") continue;

label=P;
tz=tz2; 
i=1;
//------------------------------------------------
parse_line=false;
while (str.indexOf(";",tz+1)>=0) 
{
  
P="";
tz2=str.indexOf(";",tz+1);
if (tz2>0) 
{

P=str.substring(tz+1,tz2);
P.trim();
if (P=="") P="*";
#ifdef debug
Serial.print("P");Serial.print(i);Serial.print("==");
Serial.println(P);
#endif
//hhhhhhhhhhhhhhhhhhhhhhhhhh
if (i==1)
{
if (P=="*") h=hour(t);
else
if (P.toInt()>=0&&P.toInt()==hour(t)) h=P.toInt(); //������� ���
else
{
#ifdef debug  
Serial.println(F("break  Hour")); 
#endif
break;
}
}

//MINUTE mmmmmmmmmmmmmmm
if (i==2)
{
if (P.toInt()>=0&&P.toInt()>=minute(t)) m=P.toInt();
else
{
#ifdef debug  
Serial.println(F("break  Minute")); 
#endif
break;
}
}




//Day DDDDDDDDDDDDDDDDDDDDDDDDD
if (i==3)
{
if (P=="*") ;//today
else
if (P.toInt()>0&&P.toInt()==day(t)) ; //today
else
{
#ifdef debug  
Serial.println(F("break  Day")); 
#endif
break;
}
}



//Week WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
if (i==4)
{
byte w;
if (weekday(t)==1)w=7; //RU 1-7
else w=weekday(t)-1;
if (P=="*") ; //today
else
if (P.toInt()>0&&P.toInt()==w) ; //today
else
{
#ifdef debug
Serial.println(F("break  WEEK")); 
#endif

break;
}
}




//  CH-----CH--------CH-------file-  cccccccccccccccccccccccccccccc
if (i==5)
  {
if (label=="I"||label=="i")
{
if (P.toInt()>0) ch_num=P.toInt();
else
{
#ifdef debug
Serial.println("break  ch_num"); 
#endif
break;
}
}

else
//mp3 jpg ----------------------
if (label=="M"||label=="J"||label=="m"||label=="j")
{
if (P.length()>0) fname=P; 
else
{
#ifdef debug  
Serial.println("break  fname"); 
#endif
break;
}
}
else
{
#ifdef debug
Serial.println(F("break  ch/fname not found")); 
#endif
break;  
}
parse_line=true; //minimum
}
  



//volume vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
if (i==6)
{
if (P.toInt()>0&&P.toInt()<101) vol=P.toInt();
else
{
#ifdef debug
Serial.println("break  vol"); 
#endif
break;
}
}



 

//long llllllllllllllllllllllll
if (i==7)
  {
int k=-1;
if (P.substring(0,1)=="s") k=1000;
else
if (P.substring(0,1)=="m") k=60000;
else
{
#ifdef debug
Serial.println(F("break long sec/min")); 
#endif
break;
}


P=P.substring(1);
if (P.toInt()>0) t_long=P.toInt()*k; //today
else
{
#ifdef debug  
Serial.println(F("break  t_long")); 
#endif
break;
}
 
  
  
  }



//t_b ch--------------------------------------------
if (i==8)
{
if (P.toInt()>=0&&P.toInt()<24) t_b_ch=P.toInt();
else
{
#ifdef debug
Serial.println("break  t_b ch"); 
#endif
break;
}
}




//t_e ch--------------------------------------------
if (i==9)
  {
if (P.toInt()>=0&&P.toInt()<24) 
{
t_e_ch=P.toInt();
if (t_e_ch==0) t_e_ch=24;
}
else
{
#ifdef debug
Serial.println("break  t_e ch"); 
#endif
break;
}
  }




i++;
tz=tz2;
}

              } //;while ";"---------------------------



//control t_b_ch t_e_ch
if (t_e_ch>t_b_ch)
  {
if (hour(t)>=t_b_ch&&hour(t)<t_e_ch)
{
Serial.println(F("ch ON"));   
}
else
{
Serial.println(F("ch OFF, clock"));
parse_line=false;  //   

}
  } 



#ifdef debug
Serial.println(F("-------end line-----"));  
#endif


//--------------ALARM fill ------------------------------------
if (parse_line&&al.m>m) 
    {

if (al.m!=99&&(label=="I"||label=="i")) 
{
t_next_shed=al.m;// ���� ����� ����.
next_shed_ch=al.ch_num;
 
}

al.label=label.charAt(0); //��� I,M,J inet,mp3,jpeg
al.h=h;//hour
al.m=m; //min
if (label=="I"||label=="i") al.ch_num=ch_num; // ch
if (label=="M"||label=="J"||label=="m"||label=="j" ) al.fname=fname; // ch

// ������ ���� ����� ���� �� ��������� � alarm.txt, �������
if (t_long!=-1) al.t_long=t_long;//length T millisec
else al.t_long=0;

if (vol!=-1) al.vol=vol; //volume
else al.vol=0;

do_print_alarm();
       
    }
else
if (parse_line)
{
if (t_next_shed>m&&(label=="I"||label=="i"))
{
t_next_shed=m;// ���� ����� ����.
next_shed_ch=ch_num;

}

}





                    }//FILE

if (al.h!=99)     do_print_alarm();                 
f.close();

}












//==========================================================================================================
//              do_print_alarm
//==========================================================================================================

void do_print_alarm()
{
#ifdef debug
Serial.println(F("-------ACTUAL-----ALARM----------------"));
Serial.print(F("al.label="));
Serial.println(al.label);
Serial.print(F("al.h="));
Serial.println(al.h);
Serial.print(F("al.m="));
Serial.println(al.m);
Serial.print(F("al.ch_num="));
Serial.println(al.ch_num);
Serial.print(F("al.fname="));
Serial.println(al.fname);
Serial.print(F("al.t_long="));
Serial.println(al.t_long);
//Serial.print(F("al.count="));
//Serial.println(al.count);
//Serial.print(F("al.interval="));
//Serial.println(al.interval);
Serial.print(F("al.vol="));
Serial.println(al.vol);
//Serial.print(F("al.vol_up="));
//Serial.println(al.vol_up);
if (t_next_shed!=99)
{
Serial.print(F("t_next_shed="));
Serial.println(t_next_shed);
Serial.print(F("next_shed_ch="));
Serial.println(next_shed_ch);
}
Serial.println(F("------End---ALARM----------------"));


#endif

  
}
#endif  //esp32


//--------------------------------------------------------
//                      do_maxnum_file
//--------------------------------------------------------
#ifdef pin_sd
unsigned int do_maxnum_file()
{
unsigned int max_num=0;
String s_fname="";
byte n1,n2;
unsigned int max_num_tmp;
String s_fname_num;
String dir_tmp="";
 
File fname;
File dir;  
dir =SD.open("/");

Serial.println(F("maxnum /foto/*j.pg"));
tft.println(F("search max_num /foto/*j.pg"));

  
  while (true) {
File fname=dir.openNextFile();
    if (! fname)      break;      // no more files

    if (fname.isDirectory())
    {
dir_tmp=fname.name();
if (dir_tmp.indexOf("foto") ==-1) 
{
fname.close();
continue;
} 
Serial.print("dir===FOTO==find=========");
Serial.println(dir_tmp); 
fname.close();
break;
    }

              } //while




if (dir_tmp=="") 
{
Serial.println("NO dir /foto/");
tft.println("NO dir /foto/");
return 0;
}


dir=SD.open(dir_tmp);

 while (true) 
                  {
  


if (max_num_tmp%3==0)
tft.fillCircle(180,10,4,TFT_YELLOW);
else tft.fillCircle(180,10,4,TFT_BLACK);

fname =  dir.openNextFile();
if (! fname)       break;

s_fname=fname.name();
n1=s_fname.lastIndexOf("/");
if (n1==-1) n1=0; else n1++;
n2=s_fname.lastIndexOf(".");

s_fname_num=s_fname.substring(n1,n2);

max_num_tmp=s_fname_num.toInt();
if (max_num_tmp>max_num) max_num=max_num_tmp;

//Serial.println(s_fname);
//Serial.println(s_fname_num);
//Serial.println(s_fname_num.toInt());
//Serial.println(max_num);

fname.close();




                 }

tft.fillCircle(180,10,4,TFT_BLACK);
return max_num;



}
#endif  //pin_sd
