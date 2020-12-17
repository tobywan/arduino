// cycle through the colours of an rgb led

const int RED = 6;
const int GREEN = 7;
const int BLUE = 8;

struct RGB {
  byte red;
  byte blue;
  byte green;
};

struct HSL {
  double hue; // degrees [0 to 360) inc
  double sat; // from [0 to 1] inc
  double lum; // from [0 to 1] inc
};



void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  cycleHue(100);
}



void setColor(byte red, byte green, byte blue)
{
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}

void setColor(RGB& rgb)
{
  setColor(rgb.red, rgb.green, rgb.blue);
}

void debugHue( int hue, RGB& rgb) {
  char buf[17];
  sprintf (buf,"H%d R%dG%dB%d", hue, rgb.red, rgb.green, rgb.blue);
  Serial.println(buf);
}

void cycleHue(unsigned long dwMs)
{
  RGB rgb;
  HSL hsl;
  
  hsl.lum = 0.5;
  hsl.sat = 1.0;
  for (double hue = 0; hue < 360; hue += 1) {
    hsl.hue = hue;
    rgb = hsl2rgb(hsl);
    setColor(rgb);

    debugHue(hue, rgb);

    delay(dwMs);

  }
}

void slowAllVals(unsigned long dwMs)
{
  for (int r = 0; r < 255; r++)
  { // loop from 0 to 254 (fade in)
    for (int g = 0; g < 255; g++)
    { // loop from 0 to 254 (fade in)
      for (int b = 0; b < 255; b++)
      { // loop from 0 to 254 (fade in)
      setColor(r,g,b);
      delay(dwMs);
      }
    }
  }
}

void fade(int delayms, int color)
{

  for (int i = 255; i > 0; i--)
  {                        // loop from 255 to 1 (fade out)
    analogWrite(color, i); // set the LED brightness
    delay(delayms);        // Wait 10ms
  }
}

/*
Conversion taken from 
https://www.rapidtables.com/convert/color/hsl-to-rgb.html
*/
RGB hsl2rgb(HSL& hsl) 
{
  struct RGB ret;
  int h = hsl.hue;
  if (h >= 360) {
    return ret;
  }

  double c = (1 - abs(2.0 * hsl.lum - 1)) * hsl.sat;
  double x = c * ( 1.0 - abs((h / 60) % 2 - 1.0));
  double m = hsl.lum - c / 2.0;
  
  double r;
  double g;
  double b;

  if (h < 60) {
    r = c;
    g = x;
    b = 0;
  }
  else if (h < 120) {
    r = x;
    g = c;
    b = 0;
  }
  else if (h < 180) {
    r = 0;
    g = c;
    b = x;
  }
  else if (h < 240) {
    r = 0;
    g = x;
    b = c;
  }
  else if (h < 300) {
    r = x;
    g = 0;
    b = c;
  }
  else if (h < 360) {
    r = c;
    g = 0;
    b = x;
  }
  
  ret.red = (r + m) * 255;
  ret.green = (g + m) * 255;
  ret.blue = (b + m) * 255;

  return ret;
}
