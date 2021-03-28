#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

int getValue(int nrVals)
{
  int sum = 0;
  for(int i=0; i<nrVals; i++)
  {
    sum += analogRead(A0);
    delay(5);
  }
  return sum/nrVals;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  int starttime = millis();
  int endtime = starttime;
  int isRising = 0;
  int lastValue = getValue(2);
  int nrPulses = 0;
  if(lastValue>900)
  {
    while((endtime - starttime) <= 5000)
    {
      int sensorValue = getValue(2);
      if(sensorValue > lastValue && isRising == 0)
      {
          nrPulses++;
          isRising = 1;
          Serial.println(nrPulses);

      }
      else if(sensorValue < lastValue)
          isRising = 0;
      lastValue = sensorValue;
      endtime = millis();

    }
  }

  lcd.setCursor(0, 1);

  lcd.clear();
}
