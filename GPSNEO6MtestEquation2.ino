
#include <Wire.h>
#include <Math.h>


//////////////////// variable of GPSNEO6MTiny  //////////////////////
float gpslat , gpslong , gpsfixlat, gpsfixlong ;
///////// variable for change string to number  /////
/////////////////////// Latitude's Variable  /////////////////////////
double Latitude6 , Longitude6 ;

/////////////////////  Calculate Distance Variable  ///////////////
double  Distance3 , Distance4 , acos1 , gpsfixlatsend,gpsfixlongsend;
double Phi1, Phi2 ,Lamda1, Lamda2 , DeltaPhi , DeltaLamda ;
double RadiusE = 6371000 ;  /// Radius in m
double Phi1inr,Phi2inr,Lamda1inr,Lamda2inr ,pi22 ,pi7,p180 ,p10 ;
double DeltaPhid2 , DeltaLamdad2, DeltaPhim2 , xs3 , ys3 ,xys3 ;
double sn2del = 0.0 ,sn2lam = 0.0 , sn2inv , distances4 ;

void setup() {
  Serial.begin(115200);
 ////////////// end setup loop
}

void loop() {

/////////////// GPS fix ///////////////////////////
// GPS Lat , Long start point 
Latitude6 = 10.47401 ; 
Longitude6 = 98.81137 ;

// GPS Lat , Long  second point
gpsfixlat = 10.47535 ;
gpsfixlong = 98.81175 ;


   Serial.print("Latitude * 10^6 and Longitude * 10^6 ");
   Serial.print("\n");
   Serial.print(Latitude6,6);
   Serial.print("\t");
   Serial.print(Longitude6,6);
   Serial.print("\n");

  //////// set GPS and define GPS at School  ///////////////////

    gpsfixlat = 10.47274;
    gpsfixlong = 98.81150  ;
      // gpslat = 10.472874 ;  ////  this lat and long to fix point is 1 m
   // gpslong = 98.811189 ; 

  ///////////////  Calculate Distance for GPS Fix to GPS  /////////////////
  ////       Right Distance = 53.62 m
   
 // Δ = Delta ,φ = Phi = Latitude , λ = lamda = Longitude 
 // formula a = sin^2(Δ(φ/2)) + cos φ1 * cos φ2 * sin^2(Δλ/2) 
 //         c = 2 * atan * 2 * (root a, root (1-a) 
 //         d = R * C           
 //         R = 6.371 * 10^3 km Earth's Radius

/////////////////////  solution 1  ////////////////////////
  /////////// φ1 = lat1* Pi/180 , φ2 = lat2* Pi/180 //////////////
   Phi1 =  gpsfixlat ;
   Phi2 = Latitude6 ;
   pi22 = 22 ;
   pi7 =  7;
   p180 = 180 ;
   Phi1inr = Phi1 * (pi22/pi7) / p180 ;  /// 32.91410
   Phi2inr = Phi2 * (pi22/pi7) / p180 ;
 ////////////  Δφ = (lat2-lat1) * Pi/180 =   ////////////////////
   DeltaPhi = (Phi2 - Phi1)* (pi22/pi7) / p180 ;
   DeltaPhid2 = DeltaPhi/2 ; 
   DeltaPhim2 = ((Phi2 + Phi1)* (pi22/pi7) / p180)/2 ;
   
/////////// λ1 = long1* Pi/180 , λ2 = long2* Pi/180 //////////////
   Lamda1 = gpsfixlong ;
   Lamda2 = Longitude6  ;
   Lamda1inr = Lamda1 * (pi22/pi7) / p180;
   Lamda2inr = Lamda2 * (pi22/pi7) / p180 ;
      
 ////////////  Δλ = (long2-long1) * Pi/180 =   ////////////////////
   DeltaLamda = (Lamda2 - Lamda1)* (pi22/pi7) / p180 ;
   /////////// 


  Serial.print(" show Phi  before solution") ;
  Serial.print("\n");
  Serial.print(Phi1,6) ;
  Serial.print("\t");
  Serial.print(Phi2,6) ;
  Serial.print("\n") ;
  Serial.print(" show Lamda before solution") ;
  Serial.print("\n");
  Serial.print(Lamda1,6) ;
  Serial.print("\t");
  Serial.print(Lamda2,6) ;
  Serial.print("\n") ;


  ////////////////////////////////  solution 2 ////////////////////////
  acos1 = sin( Phi1inr ) * sin (Phi2inr) + cos(Phi1inr) * cos (Phi2inr) * cos( DeltaLamda) ;
  Distance3 = ( acos (acos1)) * RadiusE ;
  

  
  Serial.print(" show acos1 and Distance3 ") ;
  Serial.print("\n");
  Serial.print(acos1,6) ;
  Serial.print("\t");
  Serial.print(Distance3,6) ;
  Serial.print("\n") ;
  Serial.print(" RadiusE solution2 ") ;
  Serial.print("\n");
  Serial.print(RadiusE,6) ;
  Serial.print("\n");
  
///////////////////////////////////////////////////////////////////////

////////////////////////////////// solution 3 /////////////////////
 /// x =  Δλ * cos (Δφ )
 /// y = Δφ 
 //  d = R * sqrt(,x^2+y^2) 
  xs3 = DeltaLamda * cos(DeltaPhim2) ;
  ys3 = DeltaPhi ;
  xys3 = (xs3*xs3) + (ys3 *ys3) ;
  Distance4 = RadiusE  * sqrt(xys3) ;

  Serial.print(" show xs3 and ys3 ") ;
  Serial.print("\n");
  Serial.print(xs3,6) ;
  Serial.print("\t");
  Serial.print(ys3,6) ;
  Serial.print("\n") ;

  Serial.print(" RadiusE solution3 ") ;
  Serial.print("\n");
  Serial.print(RadiusE,6) ;

   //////// clear data  ///////////////
   Phi1 = 0 ;
   Phi2 = 0 ;
   Lamda1 = 0 ;
   Lamda2 = 0 ;
   Phi1inr = 0 ;
   Phi2inr = 0 ;
   Lamda1inr = 0 ;
   Lamda2inr = 0 ;
   DeltaLamda = 0 ;
   DeltaPhi  = 0 ;
   DeltaPhim2 = 0 ;
   acos1 = 0 ;
   xs3 = 0 ;
   ys3 = 0 ;
   Serial.print("Distance from solution 2");
  Serial.print("\n");
  Serial.print(Distance3,6) ;
  Serial.print("\n");
    Serial.print("Distance from solution 3");
  Serial.print("\n");
  Serial.print(Distance4,6) ;
  Serial.print("\n");
  


// precise formular 
// d = 2R × sin⁻¹(√[sin²((θ₂ - θ₁)/2) + cosθ₁ × cosθ₂ × sin²((φ₂ - φ₁)/2)])
// where:
// θ₁, φ₁ – First point latitude and longitude coordinates;
// θ₂, φ₂ – Second point latitude and longitude coordinates;
// R – Earth's radius (R = 6371 km); and
// d – Distance between them along Earth's surface.
// sin^-1 x equal arcsin x , arcsin x = asin x in arduino
//  1. sin^2 x equal result sin x multiply result sin x
//  2. sin^2 x equal result sin x square 2
///////////////////////////////////////////////////////////////
// old formular
 // Δ = Delta ,φ = Phi = Latitude , λ = lamda = Longitude 
 // formula a = sin^2(Δ(φ/2)) + cos φ1 * cos φ2 * sin^2(Δλ/2) 
 //         c = 2 * atan * 2 * (root a, root (1-a) 
 //         d = R * C           
 //         R = 6.371 * 10^3 km Earth's Radius
  //////////////////////////////////////////////////////////

//////////////////////////////////////////////
// d = 2R × sin⁻¹(√[sin²((θ₂ - θ₁)/2) + cosθ₁ × cosθ₂ × sin²((φ₂ - φ₁)/2)])
// where:
// θ₁, φ₁ – First point latitude and longitude coordinates;
// θ₂, φ₂ – Second point latitude and longitude coordinates;
// R – Earth's radius (R = 6371 km); and
// d – Distance between them along Earth's surface.
//////////////////////////////////////////

  Serial.print("Distance from solution 4");
  Serial.print("\n");

 /////////// θ₁ = lat1* Pi/180 , θ₂ = lat2* Pi/180 //////////////
   Phi1 =  gpsfixlat ;
   Phi2 = Latitude6 ;
   pi22 = 22.00 ;
   pi7 =  7.00 ;
   p180 = 180.00 ;
   Phi1inr = Phi1 * (22/7) / 180 ;  /// 32.91410
   Phi2inr = Phi2 * (22/7) / 180 ;
 ////////////  (θ₂ - θ₁)/2 = ((lat2-lat1) * Pi/180)/2 =   ////////////////////
   DeltaPhi = ( Phi2inr- Phi1inr)/2 ;

   
/////////// φ₁ = long1* Pi/180 , φ₂ = long2* Pi/180 //////////////
   Lamda1 = gpsfixlong ;
   Lamda2 = Longitude6  ;
   Lamda1inr = Lamda1 * (22/7) / 180;
   Lamda2inr = Lamda2 * (22/7) / 180 ;
      
 ////////////  (φ₂ - φ₁)/2 = ((long2-long1) * Pi/180)/2 =   ////////////////////
   DeltaLamda = (Lamda2inr - Lamda1inr )/2 ;
 
////////// sin²((θ₂ - θ₁)/2)
  sn2del = (DeltaPhi) * (DeltaPhi) ;
////////// sin²((φ₂ - φ₁)/2
  sn2lam = (DeltaLamda) * (DeltaLamda) ;
////////// (√[sin²((θ₂ - θ₁)/2) + cosθ₁ × cosθ₂ × sin²((φ₂ - φ₁)/2)]) 
  sn2inv = sqrt( ( sn2del + cos (Phi1inr ) * cos(Phi2inr) * sn2lam)) ;
//////////  d = 2R × sin⁻¹() 
  distances4 = 2 * RadiusE * asin (sn2inv) ; 
 Serial.print("Distance between 2 point GPS in Solution 4 is ") ;
 Serial.print("\n") ;
 Serial.print(distances4,6) ;
 Serial.print("\n") ;


delay(2000);  /// delay(500)
   //////////// end loop find GPS

 ////////////// ////////// end void loop   /////////////  
}



