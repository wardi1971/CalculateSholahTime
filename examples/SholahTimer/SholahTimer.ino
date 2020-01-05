#include <SholahTimeCalulation.h>

void setup() {

  Serial.begin(9600);

  //=============================
  // Construct Object
  //=============================
  SholahTimeCalulation sholat;                                // contruct object using defaul parameter
//  SholahTimeCalulation sholat(-6.175513, 106.827170,7) ;    // contruct object using parameter (latitude, longitude and time zone)
//  SholahTimeCalulation sholat(-6.175513, 106.827170,10,7) ; // contruct object using parameter (latitude, longitude, elevation and time zone)


  //=============================
  // Setting Date and parameter
  //=============================
  sholat.coordinatSet(-6.175513, 106.827170,7);   //====> Set Location Coordinat   coordinatSet(latitude, longitude, timezone);
  sholat.dateSet(2020,1,4);                       //====> Set Date dateSet(YYYY,MM,DD)
  sholat.ihtiyatiSet(3);                          //====> Set Ihtiyati ihtiyatiSet(Minute) 
  sholat.calculate();                             //====> caculate Sholah Times using last data. run this methode after change date dan other parameter.

  //=============================
  // Result of calculation
  //=============================
  
  //Show Sholah Time using float value
  Serial.println("\nSholah time --> Float Number");
  for(int i =0;i < SholatCount;i++)
    {
    Serial.print(sholat.sholahName[i]);
    Serial.print("\t: ");  
    Serial.println(sholat.sholahTime[i]);    
    }

  //Show Sholah Time using char array
  Serial.println("\n\nSholah time --> char array");
  for(int i =0;i < SholatCount;i++)
    {
    char timeString[6];      
    sholat.getTimeString(i,timeString);
    Serial.print(sholat.sholahName[i]);
    Serial.print("\t: ");  
    Serial.println(timeString);
    }

  //Show Sholah Time using int hour and minute part.
  Serial.println("\nSholah time --> integer hour and minute part");
  for(int i =0;i < SholatCount;i++)
    {
    int hour_o;
    int minute_o;
    sholat.getTimePart(i,hour_o, minute_o);
    
    Serial.print(sholat.sholahName[i]);
    Serial.print("\t: ");  
    Serial.print(hour_o);Serial.print("-");Serial.println(minute_o);
    }
}



void loop() {
  // put your main code here, to run repeatedly:

}
