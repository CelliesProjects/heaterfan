//heaterfan

//pins
const byte redLed   = D1;
const byte greenLed = D2;
const byte blueLed  = D3;

const byte fan_1 = D4;
const byte fan_2 = D5;

const int PWMdepth = 10240; //10 x PWMRANGE

float coldTemp = 15; //only blue light at this temp
float niceTemp = 20; //only green light at this temp
float warmTemp = 25; //only red light at this temp

float measuredTemp = 21.5;

void setup() {
  pinMode( redLed , OUTPUT );
  pinMode( greenLed , OUTPUT );
  pinMode( blueLed , OUTPUT );
  pinMode( fan_1 , OUTPUT );
  pinMode( fan_2 , OUTPUT );

  analogWriteRange( PWMdepth );
  
  Serial.begin( 115200 );
  Serial.println();

}

void loop() {

  static float temp = 14;

  if ( temp > 26 ) temp = 14;
  Serial.println(  temp );
  analogWrite( redLed, redValue( temp ) );
  analogWrite( greenLed, greenValue( temp ) );
  analogWrite( blueLed, blueValue( temp ) );
  temp += .01;
  delay(10);
}

int blueValue( const float temp ){    
  if ( temp <= coldTemp ) return PWMdepth;
  if ( temp >= niceTemp ) return 0;
  return mapFloat( temp, coldTemp, niceTemp, PWMdepth, 0 );
}

int greenValue( const float temp ) {
  if ( temp <= coldTemp || temp >= warmTemp ) return 0;
  if ( temp > coldTemp && temp < niceTemp ) return mapFloat( temp, coldTemp, niceTemp, 0, PWMdepth );
  return mapFloat( temp, niceTemp, warmTemp, PWMdepth, 0 );
}

int redValue( const float temp ) {
  if ( temp <= niceTemp ) return 0;
  if ( temp >= warmTemp ) return PWMdepth;
  return mapFloat( temp, niceTemp, warmTemp, 0, PWMdepth );
}


float mapFloat( const double x, const double in_min, const double in_max, const double out_min, const double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
