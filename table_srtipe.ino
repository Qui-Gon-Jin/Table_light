#include "FastLED.h"
//
#define NUM_LEDS 29
#define STRIPE_PIN 6
//
CRGB leds[NUM_LEDS];
byte counter = 0;
const int button_pin = 4;
int button_state = 0;
byte effect_counter = 0;
bool pulse_direction = true;
//
void setup() {
	FastLED.addLeds<WS2811, STRIPE_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(10);
	pinMode(13, OUTPUT);
	pinMode(button_pin, INPUT);
}
//
void loop() { 

	FastLED.setBrightness(255);
	button_state = digitalRead(button_pin);
	if (button_state == HIGH && effect_counter < 4){
		effect_counter++;
		delay(500);
	}
	else if (button_state == HIGH && effect_counter == 4){
		effect_counter = 0;
		delay(500);
	}
	switch(effect_counter){
		case 0:
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(counter + i * 5, 255, 255);
			}
		break;
		case 1:
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = DirectSunlight;
			}
		break;
		case 2:
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CRGB::BlueViolet;
			}
		case 3:
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(0,0,0);
			}
		break;
	}
	fade();
	//pulsing_low();
	FastLED.show();
	delay(50);
}
void fade(){
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

	counter++;
	if (pulse_direction == true)
	{
		FastLED.setBrightness(counter);
		if (counter == 255)
		{
			pulse_direction = false;
			counter = 200;
		}
	}   
	else
	{
		FastLED.setBrightness((255 - counter));
		if (counter == 255)
		{
			pulse_direction = true;
			counter = 200;
		}
	}
}
