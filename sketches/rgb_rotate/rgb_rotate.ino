// cycle through the colours of an rgb led

const int RED = 6;
const int GREEN = 7;
const int BLUE = 8;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  cycle(5);
}

void setColor(byte red, byte green, byte blue)
{
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}

void cycle(unsigned long dwMs)
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
