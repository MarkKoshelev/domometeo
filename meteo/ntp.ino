
bool do_ntp()
{


static uint32_t t_ntp_sync=0;

int t_repeat;
static time_t err_ntp_t=0;
if (sync_t==true&&sync_force==false) t_repeat=t_ntp_rep_err; //уже было время синх.
else
t_repeat=5000;

//повтор запроса через 5с при ошибке если если не было синхр. 
if (millis()<err_ntp_t) return false;
err_ntp_t=millis()+t_repeat; //повтор



if (millis()<t_ntp_sync&&err_ntp==0&&WiFi.status() == WL_CONNECTED&&sync_force==false) return true;  



err_ntp=1;
while (udp.parsePacket() > 0) ; // discard any previously received packets

if (ntp_num==5)ntp_num=1;
if (ntp_num==1)
WiFi.hostByName(ntpServerName1, timeServerIP); 
if (ntp_num==2)
WiFi.hostByName(ntpServerName2, timeServerIP); 
if (ntp_num==3)
WiFi.hostByName(ntpServerName3, timeServerIP); 
if (ntp_num==4)
WiFi.hostByName(ntpServerName4, timeServerIP); 
Serial.print("ntp=");Serial.println(ntp_num);

//------------------------------------------
sendNTPpacket(timeServerIP); 
 // Wait till data is there or timeout...
  byte timeout = 0;
  int  size  = 0;
  do {
    delay ( 10 );
    size = udp.parsePacket();
    if (timeout > 100) break; // timeout after 1000 ms
    timeout++;
  } while (size == 0);



 // TRUE ntp-----------------------------
    if (size >= NTP_PACKET_SIZE) {

t_ntp_update = millis() - (10 * (timeout + 1)); // Account for delay in reading the time
Serial.print("t_ntp_update=");Serial.println(t_ntp_update);     
//      Serial.println("Receive NTP Response");
      udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
ntp_time =  secsSince1900 - 2208988800UL + TIMEZONE * SECS_PER_HOUR;    
setTime(ntp_time);
Serial.print("ntp_time=");Serial.println(ntp_time);

sync_t=true;
sync_force=false;
ntp_count=0;
err_ntp=0;
t_ntp_sync=millis()+t_period_ntp;
#ifndef openw //заход - восх расчитываю если не с openw
do_sun();  
#endif
refresh_all=true;


if (log_file)
{
log_str="NTP OK ntp_num="+String(ntp_num);
do_log();  
}
Serial.println(F("NTP OK"));
return true;
//-----OK----------------OK----------------OK---------------------------------------
    
    
    }
 


//false
//-----------------------------------------------   
ntp_count++; 
Serial.println("No packet yet ");
#ifdef debug
Serial.print(F("ERR ntp_count/num="));
Serial.print(ntp_count);
Serial.print("/");
Serial.println(ntp_num);
#endif

if (log_file)
{
log_str="NTP ERR ntp_count="+String(ntp_count)+" ntp_num="+String(ntp_num);
if (WiFi.status() != WL_CONNECTED)
log_str=log_str+" WIFI NOT CONNECTED";
do_log();  
}


//на половине ошибок делаю реконнект
if (ntp_count>ntp_count_rep) 
    {

if (log_file)
{
log_str=(F("NTP ERR  WIFI reconn"));
do_log();  
}

Serial.println(F("-------WIFIntp reconnect"));;
wifiConnect();
ntp_count=0;
if (WiFi.status() == WL_CONNECTED)
{
err_ntp=0;
return true;
}
    }





ntp_num++; //следующ. ntp

err_ntp=1;





return false;

  }





//====================================================
//                  sendNTPpacket
//====================================================
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}




//====================================================
//                  now_correct
//====================================================
#ifdef  time_correct 

time_t now_correct() 
{

if (!sync_t) return 0;
    
time_t tm=ntp_time+(millis() - t_ntp_update)/ 1000;
time_t delta=0;
if (t>tm) delta=t-tm;
if (tm>t)  delta=tm-t;
//ERR ttttttttttttttttttttttttttt
if (delta< 200) return t;
#ifdef debug
Serial.print("delta=");
Serial.println(delta);
Serial.print("t now=");
Serial.println(t);
Serial.print("NTP now=");
Serial.println(tm);
#endif
setTime(tm);
t=now();
sync_force=true;
#ifdef debug
Serial.println(F("!!!!!!!!now_correct!!!!!!!!!!!!!!"));  
Serial.print("ntp now=");
Serial.println(tm);
Serial.print("hour=");
Serial.println(hour(tm));
Serial.print("min=");
Serial.println(minute(tm));
Serial.print("day=");
Serial.println(day(tm));
Serial.print("month=");
Serial.println(month(tm));
Serial.print("year=");
Serial.println(year(tm));
Serial.println(F("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));  


if (log_file)
{
log_str="ERR do now_correct delta="+delta;
do_log();  
}



#endif
return tm ;
}
#endif //time_correct
