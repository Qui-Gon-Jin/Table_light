#include "FastLED.h"
//
#define NUM_LEDS 29
#define STRIPE_PIN 6
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
	FastLED.addLeds<WS2811, STRIPE_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(10);
	pinMode(13, OUTPUT);
	pinMode(button_pin, INPUT);
}
//
void loop() { 
	button = digitalRead(button_pin);
	if (button == true && button_flag == false && millis() - last_press > 50)
	{
		button_flag = true;
		last_press = millis();
		effect_counter++;
		if (effect_counter >= 6)
			effect_counter = 0;
	}
	if (button == false && button_flag == true)
		button_flag = false;

	switch(effect_counter){
		case 0:
		//rainbow
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(counter + i * 5, 255, 255);
			}
		break;
		case 1:
		//sun
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = DirectSunlight;
			}
		break;
		case 2:
		//light violet and blue
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CRGB::BlueViolet;
			}
		break;
		case 3:
		//epileptic rainbow
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(0,0,0);
			}
			FastLED.show();
			delay(100);
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(counter + i * 15, 255, 255);
			}
		break;
		case 4:
		//cyberpanky boi
		//pink - hsv 250
		//blue - rgb 10,111,250
		//green - hsv 150
		color_diff = (200 - 170)/NUM_LEDS;
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(170 + color_diff * i, 255, 255);
			}
		break;
		case 5:
		//void
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(0,0,0);
			}
		break;
	}
	//fade();
	pulsing_low();
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
	//delay(25);
}
