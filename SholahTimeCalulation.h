#ifndef SholahTimeCalulation_h
#define SholahTimeCalulation_h

#define d2r(x) x*M_PI/180
#define r2d(x) x*180/M_PI

enum SholahID
  {
    Imsak,
    Shubuh,
    Terbit,
    Dhuha,
    Dhuhur,
    Ashr,
    Maghrib,
    Isya,
    SholatCount
  };
  
class SholahTimeCalulation
  {
    public    :
		float sholahTime[SholatCount];
		char  sholahName[8][10]  ={"Imsak", 
									"Subuh",
									"Terbit",
									"Dhuha",
									"Dzuhur",
									"Ashar",
									"Maghrib",
									"Isya"};
	  
		SholahTimeCalulation(float latitude, float longitude, float elevation,int timezone);
		SholahTimeCalulation(float latitude, float longitude, int timezone);
		SholahTimeCalulation();
      
		void 	coordinatSet(float latitude, float longitude, int timezone);
		void 	elevationSet(float elevation);
		void 	dateSet(int year,int month,int date);
		void 	ihtiyatiSet(int ihtiyati);
		void 	calculate();
		void 	calculate(float latitude, float longitude, float elevation,int timezone,int year,int month,int date);
		void 	getTimePart(int idShol,int& hourPart, int& minutePart);
		void 	getTimePart(int idShol,int& hourPart, int& minutePart,int& secondPart);
		void 	getTimeString(int idShol,char* stringTime);
		void 	getTimeString_long(int idShol,char* stringTime);
      
    protected:
		float _latitude   	= -6.175513;		//Default Coordinat --> Jakarta (Monas - National Monument)	
		float _longitude  	= 106.827170;
		float _elevation 	= 0; 			//Default Elevation --> 0 (Sea Level)
		int   _timezone   	= 7;			//Default Time Zone +7 (Jakarta West Part of Indonesia)
		int   _intiyati   	= 0;			//Default 0 
		int   _date       	= 1;			
		int   _month      	= 1;
		int   _year       	= 2020;

		float _JD;        //Julian Date
		float _EqT;       //Equation of Time
		float _SuD;       //Sun Deqlinations
		void  _Julian_date();
		void  _EqT_SuD();
		float _HourAngle(float Alfa) ;
		float fix_hour(float a);
		float fix_angle(float a);
  };
#endif  
