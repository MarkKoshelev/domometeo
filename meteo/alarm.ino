#ifdef ESP32  

//==========================================================================================================
//              do_alarm
//==========================================================================================================
void do_alarm_i()
{

if (al.label=='i'&&(nigth==true||scr_name[scr_number]=="Sn")) return; //i -низкий приоритет для ночи и  экрана ноч.

if (al.label=='i'&&t_timer!=0&&!play)  return;// i - низкий приоритет для уже запущ. таймера для запуска радио
//start



timer_stop();


if (play)
{
ch_prev_alarm=ch;   //возврат нп этогт канал если play
}


ch=al.ch_num;
fn_cmd="play";

if (al.t_long>0) 
{
t_timer=millis()+al.t_long; 
al.active=true;
//al.t_long=t_timer; //end shed
}

#ifdef debug
Serial.println(F("alrm start-------------------------"));
Serial.print(F("alarm min="));Serial.println(al.m);
Serial.print(F("al.ch_num="));Serial.println(ch);
Serial.print(F("al.t_long="));Serial.println(al.t_long);
Serial.print(F("volume="));Serial.println(volume);
#endif


do_fn_btn_ir();

 
}


#endif //esp32
