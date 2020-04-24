#include "FastLED.h"
//
#define NUM_LEDS 29
#define STRIPE_PIN 6
//
CRGB leds[NUM_LEDS];
byte previous_led[NUM_LEDS];
const int button_pin = 4;
int color_diff;
int button_state = 0;
byte effect_counter = 0, counter = 0, color = 0; 
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
				//cyberpanky boi
		//pink 250, blue 180, green 150
		color_diff = (200 - 170)/NUM_LEDS;
		if(previous_led[0] == 0)
		{
			for (int i = 0; i < NUM_LEDS; i++ ){
				if (i == 0){
					color = random(150, 250);
					leds[i] = CHSV(color , 255, 255);
					previous_led[i] = color;
				}
				else{
					color = random(previous_led[i-1] - 15, previous_led[i-1] + 15);
					leds[i] = CHSV(color , 255, 255);
					previous_led[i] = color;
				}
			}
		}
		else{
			for (int i = 0; i < NUM_LEDS; i++ ){
				color = random(previous_led[i] - 10, previous_led[i] + 10);
				if (color <= 150)
					color = 250;
				if (color >= 250)
					color = 150;

				leds[i] = CHSV(color, 255, 255);
				previous_led[i] = leds[i];
			}

		}
		break;
		case 1:
		//sun
			for (int i = 0; i < NUM_LEDS; i++ )
				leds[i] = DirectSunlight;
		break;
		case 2:
		//light violet and blue
			for (int i = 0; i < NUM_LEDS; i++ )
				leds[i] = CRGB::BlueViolet;
		break;
		case 3:
		//rainbow
			for (int i = 0; i < NUM_LEDS; i++ )
				leds[i] = CHSV(counter + i * 5, 255, 255);
		break;
		case 4:
		//void
			for (int i = 0; i < NUM_LEDS; i++ )
				leds[i] = CHSV(0,0,0);
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
		if (counter == 100)
			pulse_direction = true;
	}
	FastLED.setBrightness(counter);
}