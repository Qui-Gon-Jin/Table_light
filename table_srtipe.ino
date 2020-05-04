#define NUM_LEDS 29
#define STRIPE_PIN 6
// настройки пламени
#define HUE_GAP 80      // шаг в стороны по hue
#define FIRE_STEP 15    // шаг огня
#define HUE_START 150   // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define MIN_BRIGHT 70   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 245     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность
// для разработчиков
#include <FastLED.h>
#define ORDER_GRB       // порядок цветов ORDER_GRB / ORDER_RGB / ORDER_BRG
#define COLOR_DEBTH 2
#define PIN 6
// ВНИМАНИЕ! define настройки (ORDER_GRB и COLOR_DEBTH) делаются до подключения библиотеки!
#include <microLED.h>

LEDdata fire_leds[NUM_LEDS];  // буфер ленты типа LEDdata (размер зависит от COLOR_DEBTH)
microLED strip(fire_leds, NUM_LEDS, STRIPE_PIN);  // объект лента
int fire_counter = 0;
//
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)
//
CRGB leds[NUM_LEDS];

byte counter = 0;
const int button_pin = 4;
int color_diff;
int button_state = 0;
byte effect_counter = 0; 
boolean pulse_direction = true, button_flag = false, button;
unsigned long last_press;
//
void setup() {
  strip.setBrightness(255);

  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);

  pinMode(4, INPUT_PULLUP);
}

void loop() {

  button = digitalRead(4);
  if (button == 1 && button_flag == 0){
    button_flag = 1;
    if (effect_counter <= 4)
      effect_counter++;
    else
      effect_counter = 0;
    delay(50);
  }
  if (button == 0 && button_flag == 1){
    button_flag = 0;
  }

	switch(effect_counter){
		case 0:
    fireTick();
		break;
		case 1:
      for (int i = 0; i < NUM_LEDS; i++ ){
        leds[i] = CHSV(counter + i * 5, 255, 255);
      }
      FastLED.show();
		break;
		case 2:
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CRGB::BlueViolet;
			}
      FastLED.show();
		break;
		case 3:
    for (int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB::White;
      }
      FastLED.show();
		break;
		case 4:
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(0,0,0);
			}
      FastLED.show();
		break;
	}
  delay(30);
	pulsing();
	//pulsing_low();
  //pulsing_high();
}

void fireTick() {
  static uint32_t prevTime;
  // двигаем пламя
  if (millis() - prevTime > 20) {
    prevTime = millis();
    int thisPos = 0, lastPos = 0;
    FOR_i(0, NUM_LEDS) {
      fire_leds[i] = getFireColor((inoise8(i * FIRE_STEP, fire_counter)));
    }
    fire_counter += 20;
    strip.show();
  }
}
// возвращает цвет огня для одного пикселя
LEDdata getFireColor(int val) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return mHSV(
           HUE_START + map(val, 0, 255, 0, HUE_GAP),                    // H
           constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}

void pulsing(){
	counter++;
	if (pulse_direction == true)
	{
		FastLED.setBrightness(counter);
		if (counter == 255)
			pulse_direction = false;
	}   
	else
	{
		FastLED.setBrightness((255 - counter));
		if (counter == 255)
		{
			pulse_direction = true;
		}
	}
}
void pulsing_low(){
	if (pulse_direction == true)
	{
		counter++;
		if (counter == 20)
			pulse_direction = false;
	}   
	else
	{
		counter--;
		if (counter == 0)
			pulse_direction = true;
	}
	FastLED.setBrightness(counter);
}
void pulsing_high(){
	if (pulse_direction == true)
	{
		counter++;
		if (counter == 255)
			pulse_direction = false;
	}   
	else
	{
		counter--;
		if (counter == 150)
			pulse_direction = true;
	}
	FastLED.setBrightness(counter);
}
