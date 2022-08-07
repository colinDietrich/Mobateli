void activateThingstream(int flag) {
  if (flag == 0 ){
    // reset the Thingstream click
    digitalWrite(resetThingstreamPin, LOW);
    delay(1200);
    digitalWrite(resetThingstreamPin, HIGH);
    Serial.println("DEBUG");
    Serial1.println("AT+IOTDEBUG=0");
  }
  else if(flag == 1){
    Serial.println("CREATE");
    Serial1.println("AT+IOTCREATE");  
  }
  else if(flag == 2){
    Serial.println("CONNECT");
    Serial1.println("AT+IOTCONNECT=true,1440"); 
  }
  else if(flag == 3) {
    Serial.println("SUBSCRIBE");
    Serial1.println("AT+IOTSUBSCRIBE=\"TEST1\",1");
  }
}

int listenToClick(char *res) {
  bool check = true, start = false;
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;
 
  while(check) {
    
    if(millis()*0.001 - timeInit > 20.0) { 
      Serial.println("To Long Time to read command");  
      return 0;
     }
    
     if (Serial1.available()) {
        char st = Serial1.read();
        if(start == false) {
          start = true;
          if(st != '+') {
            check = false;
            return 0;
          }
        } else {
            if(st == '\n') {
                Serial.print("reception message : ");
                Serial.println(String(res));
                Serial.print(" analyse(res) = ");  Serial.println(analyse(res));
                if (analyse(res) ==  1) {
                  return 1;
                } else {
                  return 0;
                }
            } else {
                res[count] = st;  
                res[count+1] = '\0';  
                count += 1; 
            }
        }
     } else if(start == false) {
          check = false;
          return 0;
     }
  }
}

int analyse (String st) {
  // Arret de la publication si le mot STOP est reçu par le Click
  int res = 1;  
  if(st.indexOf("GO") > 0 || st.indexOf("SUCCESS") > 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res; 
}

void createMessage(char *message, int nbBatteries, double *VH, double *IH, double *SH, double *PH, double *PSPH, double *VSPH, double *ISPH, int *hourDay, int *minuteDay, int *hourDaySP, int *minuteDaySP, int day, int month, int year, double *VMean, double *IMean, double *SMean, double *TMean, double VSPMean, double *PMean, double PSPMean) {
    sprintf(message, "\0");
    char res[500];
    sprintf(res, "AT+IOTPUBLISH=\"Cameskin\",1,\"{'batteries':[");
    strcat(message, res);
    int n = 5*5;
    sprintf(res, "{'id':%d,'S':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],", 0, SH[n+0], SH[n+1], SH[n+2], SH[n+3], SH[n+4], SMean[5]);
    strcat(message, res);
    sprintf(res, "'V':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],", VH[n+0], VH[n+1], VH[n+2], VH[n+3], VH[n+4], VMean[5]);
    strcat(message, res);
    sprintf(res, "'I':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],", IH[n+0], IH[n+1], IH[n+2], IH[n+3], IH[n+4], IH[n+5], IMean[0]);
    strcat(message, res);
    sprintf(res, "'P':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f]", PH[n+0], PH[n+1], PH[n+2], PH[n+3], PH[n+4], PH[n+5], abs(PMean[5]));
    strcat(message, res);
    sprintf(res, ",'H':[%d,%d,%d,%d,%d],'T':%0.1f,'D':'%d$%d$%d'},", hourDay[0], hourDay[1], hourDay[2], hourDay[3], hourDay[4], TMean[5], day, month, year);
    strcat(message, res);
    
    for(int i = 0; i < 5; i++) {
      n = i*5;
      sprintf(res, "{'id':%d,'S':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],", i+1, SH[n+0], SH[n+1], SH[n+2], SH[n+3], SH[n+4], SMean[i]);
      strcat(message, res);
      sprintf(res, "'V':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],", VH[n+0], VH[n+1], VH[n+2], VH[n+3], VH[n+4], VMean[i]);
      strcat(message, res);
      sprintf(res, "'I':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],", IH[n+0], IH[n+1], IH[n+2], IH[n+3], IH[n+4], IH[n+5], IMean[0]);
      strcat(message, res);
      sprintf(res, "'P':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f]", PH[n+0], PH[n+1], PH[n+2], PH[n+3], PH[n+4], PH[n+5], abs(PMean[i]));
      strcat(message, res);
      if(i == 4) {
        sprintf(res, ",'T':%0.1f}", TMean[i]);
      }
      else {
        sprintf(res, ",'T':%0.1f},", TMean[i]);
      }
      strcat(message, res);
    }
    sprintf(res, "],'solarPannels':[{'D':'%d$%d$%d','I':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],'V':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f],'P':[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f]}]}\"", day, month, year, ISPH[0], ISPH[1], ISPH[2], ISPH[3], ISPH[4], ISPH[5], ISPH[6], ISPH[7], ISPH[8], VSPH[0], VSPH[1], VSPH[2], VSPH[3], VSPH[4], VSPH[5], VSPH[6], VSPH[7], VSPH[8], PSPH[0], PSPH[1], PSPH[2], PSPH[3], PSPH[4], PSPH[5], PSPH[6], PSPH[7], PSPH[8]);
    strcat(message, res);
    Serial.println("message :");
    Serial.println(message);
}

//detect if an alert needs to be sent and end it 
void detect_alertes(int nb_batteries, double *tension, double *SOC, double *temperature, int resetThingstreamPin, int *counter_alerts, bool *check, bool clickAvailable, double *VTreshold){

  boolean need_alert = false;
  char message[10000] = "\0";
  char res[500];
  sprintf(res, "AT+IOTPUBLISH=\"Alertes\",1,\"");
  strcat(message, res);
  for(int i = 0; i < nbBatteries; i++) { 
    if (SOC[2*i] < 0.3) {
      if(counter_alerts[3*i] < 21) {
        counter_alerts[3*i] += 1;
      }
      if (counter_alerts[3*i] == 20 && !check[3*i]) {
        check[3*i] = true;
        need_alert = true;
        sprintf(res, "Batterie %d : %2.1f pourcent", i+1, 100*SOC[2*i]);
        strcat(message, res);
      }
    }
    else if(counter_alerts[3*i] > 0) {
      counter_alerts[3*i] -= 1;
    } else {
       check[3*i] = false;
    }

    if (temperature[i] > 35) {
      if(counter_alerts[3*i+1] < 21) {
        counter_alerts[3*i+1] += 1;
      }
      if (counter_alerts[3*i+1] == 20 && !check[3*i+1]) {
        need_alert = true;
        check[3*i+1] = true;
        sprintf(res, "Temperature batterie %d : %0.2f degrés", i+1, temperature[i]);
        strcat(message, res);
      }
    }
    else if(counter_alerts[3*i+1] > 0) {
      counter_alerts[3*i+1] -= 1;
    } else {
       check[3*i+1] = false;
    }
    
    if (tension[i] < VTreshold[i]){
      if(counter_alerts[3*i+2] < 21) {
        counter_alerts[3*i+2] += 1;
      }
      if (counter_alerts[3*i+2] == 20 && !check[3*i+2]) {
        need_alert = true;
        check[3*i+2] = true;
        sprintf(res, "Tension batterie %d : %0.2f volt", i+1, tension[i]);
        strcat(message, res);
      }
    }
    else if(counter_alerts[3*i+2] > 0){
      counter_alerts[3*i+2] -= 1;
    } else {
       check[3*i+2] = false;
    }
  } 
  if (need_alert){
   sprintf(res, "\"");
   strcat(message, res);
   Serial.println("alerte :");
   Serial.println(message);
   if(clickAvailable) {
    Serial.println(" => publised !");
    Serial1.println(message);
   }
  }
}
