#include "cyberpi.h"

CyberPi cyber;

void render_lcd()
{
    Serial.println("render_lcd");
    cyber.clean_lcd();
    int font_size = 16;
    Bitmap *bitmap = cyber.create_text(L"hello Alex",0xffff,font_size);
    // x and y are 0 to 127
    cyber.set_bitmap(4,44,bitmap);
    cyber.render_lcd();
}

void data_recv(uint8_t* samples,int len)
{
    cyber.clean_lcd();
    for(int i=0;i<len;i+=16)
    {
      int current = samples[i+1];
      cyber.set_lcd_pixel(i/16,current-64,0xffff);
    }
    cyber.render_lcd();
}

int lo[7] = {48,50,52,53,55,57,59};
int mo[7] = {60,62,64,65,67,69,71};
int ho[7] = {72,74,76,77,79,81,83};

void play_sounds()
{
for(int i=0;i<14;i++)
    {
        cyber.set_instrument(i);
        int idx = 0;
        while(idx<7)
        {
            cyber.set_pitch(0,lo[idx],100);
            delay(600);
            idx++;
        }
        idx = 0;
        while(idx<7)
        {
            cyber.set_pitch(0,mo[idx],100);
            delay(600);
            idx++;
        }
        idx = 0;
        while(idx<7)
        {
            cyber.set_pitch(0,ho[idx],100);
            delay(600);
            idx++;
        }
    }
}

void setup()
{
    cyber.begin();
    Serial.begin(112500);

    Serial.println("setup");
    // render_lcd();
    cyber.on_sound_data(data_recv);
    // play_sounds();
    // int _loudness = cyber.get_loudness(); // of the microphone
    // Serial.print("loudness: ");
    // Serial.println(_loudness);
    int _vol = cyber.get_vol(0); // of the speaker
    Serial.print("vol: ");
    Serial.println(_vol);
    cyber.set_pitch(1,lo[0],100);
    delay(600);
    cyber.set_pitch(0,65,1000);
}
float j, f, k;

void loop()
{ 
    // Serial.print("loop\n");
    for(uint8_t t = 0; t < 5; t++)
    {
        uint8_t red	= 32 * (1 + sin(t / 2.0 + j / 4.0) );
        uint8_t green = 32 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
        uint8_t blue = 32 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
        cyber.set_rgb(t, red, green, blue);
    }
    j += random(1, 6) / 6.0;
    f += random(1, 6) / 6.0;
    k += random(1, 6) / 6.0;
    delay(10);
}