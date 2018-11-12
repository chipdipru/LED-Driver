
#define   R_PWM_PIN       3
#define   G_PWM_PIN       5
#define   B_PWM_PIN       6
#define   R_ADC_PIN       A0
#define   G_ADC_PIN       A1
#define   B_ADC_PIN       A2
#define   KEY_PIN     4

#define   PWM_COUNT   3

#define   ADCThreshold    30


uint16_t ADCPrevVal[PWM_COUNT] = {0, 0, 0,}; 
uint8_t  PWMPins[PWM_COUNT] = {R_PWM_PIN, G_PWM_PIN, B_PWM_PIN,};
uint8_t  ADCPins[PWM_COUNT] = {R_ADC_PIN, G_ADC_PIN, B_ADC_PIN,};
bool LEDActive = true;

void setup()
{
  pinMode(KEY_PIN, INPUT);
  digitalWrite(KEY_PIN, HIGH);

  for (uint8_t i = 0; i < PWM_COUNT; i++)
    pinMode(PWMPins[i], OUTPUT);
}

void loop()
{
  if (LEDActive)
  {
    for (uint8_t i = 0; i < PWM_COUNT; i++)
    {
      uint16_t ADCNewVal = analogRead(ADCPins[i]);
      if (abs(ADCNewVal - ADCPrevVal[i]) >= ADCThreshold)
      {
        ADCPrevVal[i] = ADCNewVal;
        analogWrite(PWMPins[i], map(ADCPrevVal[i], 0, 1023, 0, 255));
      }
    }
  }

  if (!digitalRead(KEY_PIN))
  {
    delay(70);
    if (!digitalRead(KEY_PIN))
    {
      if (LEDActive)
      {
        LEDActive = false;
        for (uint8_t i = 0; i < PWM_COUNT; i++)
          analogWrite(PWMPins[i], 0);
      }

      else
      {
        LEDActive = true;
        for (uint8_t i = 0; i < PWM_COUNT; i++)
        {
          ADCPrevVal[i] = analogRead(ADCPins[i]);
          analogWrite(PWMPins[i], map(ADCPrevVal[i], 0, 1023, 0, 255));
        }
      }
    }
  }
}



