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
		//cyberpanky boi
		//pink 250, blue 180, green 150
		color_diff = (200 - 170)/NUM_LEDS;
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(170 + color_diff * i, 255, 255);
			}
		break;
		case 4:
		//void
			for (int i = 0; i < NUM_LEDS; i++ ){
				leds[i] = CHSV(0,0,0);
			}
		break;
	}
	//pulsing();
	//pulsing_low();
	pulsing_high();
	FastLED.show();
	delay(25);
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