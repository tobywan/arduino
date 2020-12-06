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
  fade(5, RED);
  fade(10, GREEN);
  fade(20, BLUE);
}

void fade(int delayms, int color)
{

  for (int i = 0; i < 255; i++)
  {                        // loop from 0 to 254 (fade in)
    analogWrite(color, i); // set the LED brightness
    delay(delayms);        // Wait 10ms because analogWrite
    // is instantaneous and we would
    // not see any change
  }
  for (int i = 255; i > 0; i--)
  {                        // loop from 255 to 1 (fade out)
    analogWrite(color, i); // set the LED brightness
    delay(delayms);        // Wait 10ms
  }
}
