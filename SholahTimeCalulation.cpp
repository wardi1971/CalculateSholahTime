#include <SholahTimeCalulation.h>
#include <stdio.h>
#include <math.h>


//===========================
//   Constructor
//===========================
SholahTimeCalulation::SholahTimeCalulation()
  { }
  
SholahTimeCalulation::SholahTimeCalulation(float latitude, float longitude, int timezone)
  { _latitude = latitude; _longitude = longitude;  _elevation = 0; _timezone = (float)timezone;  }

SholahTimeCalulation::SholahTimeCalulation(float latitude, float longitude, float elevation, int timezone )
  { _latitude = latitude; _longitude = longitude;  _elevation = elevation; _timezone = (float)timezone; }

//===========================
//Public Methode
//===========================
void SholahTimeCalulation::dateSet(int year,int month,int date)
  { _year = year;  _month = month;  _date = date;} 
  
void SholahTimeCalulation::coordinatSet(float latitude, float longitude, int timezone)
  { _latitude = latitude; _longitude = longitude; _timezone = (float)timezone; }

void SholahTimeCalulation::elevationSet( float elevation)
  { _elevation = elevation; }  

void SholahTimeCalulation::ihtiyatiSet(int ihtiyati)
  { _intiyati = ihtiyati; }

void SholahTimeCalulation::calculate()
  {
   _Julian_date();
   _EqT_SuD();

   // Dzuhur
    float BaseTime = fix_hour((float)12+_timezone-(_longitude/15)-_EqT);
    sholahTime[Dhuhur] = BaseTime + (float)_intiyati/60;

    // Ashr
    float alfa =r2d(-atan(1 / (1+tan(d2r(fabs(_latitude-_SuD))))));
    float HA = _HourAngle(alfa);
    sholahTime[Ashr] = BaseTime + HA + (float)_intiyati/60;

    // Maghrib
    alfa = 0.8333f+0.0347f*sqrt(_elevation);
    HA = _HourAngle(alfa);
    sholahTime[Maghrib] = BaseTime + HA + (float)_intiyati/60;
    
    // Terbit
    sholahTime[Terbit] = BaseTime - HA;

    // Isya
    HA = _HourAngle((float)18);
    sholahTime[Isya] = BaseTime + HA + (float)_intiyati/60;

    // Shubuh
    HA = _HourAngle((float)20);
    sholahTime[Shubuh] = BaseTime - HA + (float)_intiyati/60;
    
    // Imsak
    sholahTime[Imsak] = sholahTime[Shubuh] - (float)10/60; 

    // Dhuha
    HA = _HourAngle((float)-4.5);
    sholahTime[Dhuha] = BaseTime - HA; 
  }

void SholahTimeCalulation::getTimePart(int idShol,int& hourPart, int& minutePart) 
  {
    float timeShol  = fix_hour(sholahTime[idShol] + 0.5 / 60);   // add 0.5 minutes to round
    hourPart        = floor(timeShol);
    minutePart      = floor((timeShol - (float)hourPart) * 60);
  }

void SholahTimeCalulation::getTimeString(int idShol,char* stringTime)
  {
    int hourPart,minutePart;
    getTimePart(idShol,hourPart,minutePart);
    sprintf(stringTime,"%02d:%02d",hourPart,minutePart);
  }

  
//===========================
//Protected Methode
//===========================
//Julian Date at GMT mid day
  void SholahTimeCalulation::_Julian_date()
    {
		int cyear 	=_year;
		int cmonth = _month;
		int cdate  = _date;
		
		if (cmonth <= 2) {  cyear -= 1; cmonth += 12; }

		float A = floor(((float)cyear/100.0));
		float B = 2 - A + floor(A/4.0);
		float CLong = _longitude/(float)(15 * 24);

		_JD = floor(365.25 *(float)(cyear+ 4716)) 
              - 2451545 + floor(30.6001 * (float)(cmonth + 1)) 
              + (float)cdate + B - 1524.5 -CLong;
    }

//Equation of Time and Sun Deqlinations
  void SholahTimeCalulation::_EqT_SuD() 
    {
      float g = fix_angle(357.529f + 0.98560028f* _JD);
      float q = fix_angle(280.459f + 0.98564736f* _JD);
      float L = fix_angle(q + 1.915* sin(d2r(g)) + 0.020* sin(d2r(2*g)));
      float e = (23.439f - 0.00000036f* _JD);

      float RA = r2d(atan2(cos(d2r(e))* sin(d2r(L)), cos(d2r(L))))/ 15;
      _EqT =(q/15-fix_hour(RA));
      _SuD = r2d(asin(sin(d2r(e))* sin(d2r(L)))); 
    }

//Hour Angle
  float SholahTimeCalulation::_HourAngle(float Alfa)
    {
     float rn =acos( (-sin(d2r(Alfa))-sin(d2r(_latitude))*sin(d2r(_SuD)))
                      / (cos(d2r(_latitude))*cos(d2r(_SuD)))
                   ) /15;
     return r2d(rn);
    }    

//Aditional Tools
float SholahTimeCalulation::fix_hour(float a)
  {
    a = a - (float)24.0 * floor(a / 24.0);
    a = a < 0.0 ? a + 24.0 : a;
    return a;
  }

float SholahTimeCalulation::fix_angle(float a)
  {
    a = a - (float)360.0 * floor(a / 360.0);
    a = a < 0.0 ? a + 360.0 : a;
    return a;
  }
