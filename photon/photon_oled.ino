// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

#undef swap
#include <vector>

#define OLED_DC     A1
#define OLED_CS     A2
#define OLED_RESET  A0

#define MAX_MESSAGES 10
#define SEQ_LOOP 5000
#define STARTUP_TEXT1 "                                                                 Embedded Signage         System"
#define STARTUP_TEXT2 "                                                                                                            Created by Adam"

std::vector<String> messages;
int sequence_place = 0;

static Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

// Adds str9jg to the messages vector

int add_message(String text_to_add) {
    int messages_size = messages.size();
    
    if (messages_size >= MAX_MESSAGES) {
        for (int i = 0; i < (messages_size - 1); i++) {
            messages[i] = messages[i + 1];
        }
        
        messages[messages_size -1] = text_to_add;
    }
    else {
        messages.push_back(text_to_add);   
    }
}

// Draws text to the screen at size 1, white in the top left hand corner with wrapping

void draw_string(String text_to_draw) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.setTextWrap(true);
    display.clearDisplay();
    display.print(text_to_draw);
    display.display();
}

// This is the function for the particle function to receive a string from the Particle Cloud API

int api_message(String message_text) {
    add_message(message_text);
    
    return 0;
}

// Loops through the messages string vector in order to display one message at a time in void loop()

void display_sequence() {
    draw_string(messages[sequence_place]);
    
    if (sequence_place == messages.size() - 1) {
        sequence_place = 0;
    }
    else {
        sequence_place ++;
    }
}

// Configure Particle function, start the display and add the two start up messages to the messages sequence

void setup() {
    Particle.function("apimessage", api_message);
    
    display.begin(SSD1306_SWITCHCAPVCC);
    
    add_message(STARTUP_TEXT1);
    add_message(STARTUP_TEXT2);
}

// Void loop goes through the sequence with the delay defined by constant SEQ_LOOP. Account for an extra second between the SEQ_LOOP display because to help avoid OLED screen burn in, there's a 1 second each loop of the screen being blank

void loop() {
    display_sequence();
    delay(SEQ_LOOP);
    display.clearDisplay();
    display.print(" ");
    display.display();
    delay(1000);
}