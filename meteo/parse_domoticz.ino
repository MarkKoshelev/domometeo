
/* 
byte temp_kv=200; // inside temp
int  pr_kv=200;   // pressue
byte h_kv=200;    // inside humidity 

bool ref_kv_th=false;  // refresh inside
bool ref_wh=false;     // ow wether request
bool ref_wh_now=false; // ow wether request now

int temp_u=200;        // outside temp   
*/

//unsigned long period_ulica=0;//во сколько принял Темп ул.
//uint32_t t_read_tk=0;        //во сколько принял Темп кв

//unsigned int c_tu_frame=TFT_CYAN; t > period_ulica+t_ds_ref*1000L*2 
//unsigned int c_th_frame=TFT_CYAN; t > t_read_tk+t_bme_ref*1000L*3


#ifdef domoticz

bool do_parse_domoticz_out() 
{
	bool find = false;

	DomoticzCurrentData dataOut;
    Serial.println("do_parse_domoticz_out");

	if (domoticzNOW.updateCurrent(&dataOut, url_domoticzOut)==true)
//		if (dataOut.cod!=0) 
		{
  Serial.printf("temp: %3.1f\n", dataOut.temp );
			if (dataOut.temp<60&&dataOut.temp>-60){
				if (temp_u != dataOut.temp){
					ref_temp_u=true;
					temp_u = dataOut.temp;
		//			dataOut.humidity;
		//			period_ulica = dataOut.last_time_read;
					find = true;
				}
			} //cod==200
		}
	postingInterval_domoticz = find ? t_period_domoticz * 1000L : 180L * 1000L;
	lastConnectionTime_domoticz = millis();
	return find;  
}//do_parse_ch


	//------------------------------------------------
bool do_parse_domoticz_in() 
{
	bool find = false;

	DomoticzCurrentData dataIn;
    Serial.println("do_parse_domoticz_in");

	if (domoticzNOW.updateCurrent(&dataIn, url_domoticzIn)==true)
//		if (dataIn.cod!=0) 
		{
  Serial.printf("temp: %3.1f, hum: %d\n", dataIn.temp, dataIn.humidity );
			temp_kv = dataIn.temp;
	//		pr_kv   = dataIn.pressue;
	//      t_read_tk = dataIn.last_time_read;
			h_kv    = dataIn.humidity;
			find = true;
			
			if (temp_kv<-50||temp_kv>70) temp_kv=200;
			if (h_kv<0||h_kv>100)  h_kv=200;
			if (temp_kv!=200){
				ref_kv_th=true;
			}
		} //cod==200

	postingInterval_domoticz = find ? t_period_domoticz * 1000L : 180L * 1000L;
	lastConnectionTime_domoticz = millis();
	return find;  
}



#endif
