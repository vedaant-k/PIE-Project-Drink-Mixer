
// Adapted from the "Teensy User Interface" library documentation that can be found at:
//    https://github.com/Stan-Reifel/TeensyUserInterface



#include <TeensyUserInterface.h>
#include <font_Arial.h>
#include <font_ArialBold.h>
#include <Adafruit_NeoPixel.h>

#define PIN      19
#define N_LEDS 30

// Create Adafruit strip object.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Create the user interface object.
TeensyUserInterface ui;

// Defining digital output pins for each drink.
const uint8_t PIN_A = 6; // Pin 6 controls water.
const uint8_t PIN_B = 5; // Pin 5 controls apple juice (placeholder).  
const uint8_t PIN_C = 4; // Pin 4 controls lemonade (placeholder).  
const uint8_t PIN_D = 3; // Pin 3 controls orange juice (placeholder).  
const uint8_t PIN_E = 2; // Pin 2 controls mango juice (placeholder).    



void setup() 
{
  // Initialize the user interface, including setting the screen orientation and font.
  ui.begin(LCD_ORIENTATION_LANDSCAPE_4PIN_RIGHT, Arial_9_Bold);
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);

  strip.begin();
  strip.show();
} 


// Forward define each menu.
extern MENU_ITEM mainMenu[];
extern MENU_ITEM drinksMenu[];
extern MENU_ITEM cupCheckMenu[];
extern MENU_ITEM cupPromptMenu[];



// Introduction main menu.
MENU_ITEM mainMenu[] = {
  {MENU_ITEM_TYPE_MAIN_MENU_HEADER,  "Welcome to the PIE Drink Machine!",  MENU_COLUMNS_1,      mainMenu},
  {MENU_ITEM_TYPE_SUB_MENU,          "Touch to get started!",                   NULL,                cupCheckMenu},
  {MENU_ITEM_TYPE_END_OF_MENU,       "",                           NULL,                NULL}
};

// Menu to check if the cup is placed.
MENU_ITEM cupCheckMenu[] = {
  {MENU_ITEM_TYPE_SUB_MENU_HEADER,  "Is there an EMPTY cup in the holder?",  MENU_COLUMNS_1,      mainMenu},
  {MENU_ITEM_TYPE_SUB_MENU,          "Yes",                   NULL,                drinksMenu},
  {MENU_ITEM_TYPE_SUB_MENU,          "No",                   NULL,                cupPromptMenu},
  {MENU_ITEM_TYPE_END_OF_MENU,       "",                           NULL,                NULL}
};

// Menu to prompt the user to place the cup.
MENU_ITEM cupPromptMenu[] = {
  {MENU_ITEM_TYPE_SUB_MENU_HEADER,  "Place a cup in the cup holder!",  MENU_COLUMNS_1,      cupCheckMenu},
  {MENU_ITEM_TYPE_SUB_MENU,          "I have placed a cup!",                   NULL,                drinksMenu},
  {MENU_ITEM_TYPE_END_OF_MENU,       "",                           NULL,                NULL}
};

// Menu to display and select the drink.
MENU_ITEM drinksMenu[] = {
  {MENU_ITEM_TYPE_SUB_MENU_HEADER,    "Choose your Drink!",               MENU_COLUMNS_1,              cupCheckMenu},
  {MENU_ITEM_TYPE_COMMAND,           "Water",          water,                        NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Apple Juice",          apple_juice,                        NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Lemonade",          lemonade,                        NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Orange Juice",          orange_juice,                        NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Mango Juice",          mango_juice,                        NULL},
  {MENU_ITEM_TYPE_END_OF_MENU,        "",                          NULL,                        NULL}
};


uint32_t magenta = strip.Color(255, 0, 255);
uint32_t black = strip.Color(0, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);

// Display the introduction menu.
void loop() 
{  
  chase(strip.Color(255, 0, 0)); // Red
  chase(strip.Color(0, 255, 0)); // Green
  chase(strip.Color(0, 0, 255)); // Blue
  strip.fill(magenta, 0, 30);
  strip.show();
  
  ui.displayAndExecuteMenu(mainMenu);
}


// Function to pour the water.
void water(void)
{  
  ui.drawTitleBar("Pouring Water...");
  flash(red);
  digitalWrite(PIN_A, HIGH);
//  showCount(4);
  ui.clearDisplaySpace();
  delay(10000);
  digitalWrite(PIN_A, LOW);
  
  // Display that drink has been poured.
  thank_you();
}

// Function to pour apple juice.
void apple_juice(void)
{  
  ui.drawTitleBar("Pouring Apple Juice...");
  flash(red);
  digitalWrite(PIN_B, HIGH);
//  showCount(4);
  ui.clearDisplaySpace();
  delay(10000);
  digitalWrite(PIN_B, LOW);

  // Display that drink has been poured.
  thank_you();
}

// Function to pour lemonade.
void lemonade(void)
{  
  ui.drawTitleBar("Pouring Lemonade...");
  flash(red);
  digitalWrite(PIN_C, HIGH);
//  showCount(4);
  ui.clearDisplaySpace();
  delay(10000);
  digitalWrite(PIN_C, LOW);

  // Display that drink has been poured.
  thank_you();
  
}

// Function to pour orange juice.
void orange_juice(void)
{  
  ui.drawTitleBar("Pouring Orange Juice");
  flash(red);
  digitalWrite(PIN_D, HIGH);
//  showCount(4);
  ui.clearDisplaySpace();
  delay(10000);
  digitalWrite(PIN_D, LOW);

  // Display that drink has been poured.
  thank_you();
}

// Function to pour mango juice.
void mango_juice(void)
{  
  ui.drawTitleBar("Pouring Mango Juice");
  flash(red);
  digitalWrite(PIN_E, HIGH);
//  showCount(4);
  ui.clearDisplaySpace();
  delay(10000);
  digitalWrite(PIN_E, LOW);

  // Display that drink has been poured.
  thank_you();
}

// Function to tell user that their drink has been poured.
void thank_you(void)
{
  ui.drawTitleBar("");
  ui.clearDisplaySpace();
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 10);
  ui.lcdPrintCentered("Your drink has been poured!");

  flash(green);
  delay(2000);
  strip.fill(magenta, 0, 30);
  strip.show();
  
  // Re-enter main menu and start over.
  ui.displayAndExecuteMenu(mainMenu);
}

static void flash(uint32_t color){
  strip.fill(color, 0, 30);
  strip.show();
  delay(500);
  strip.fill(black, 0, 30);
  strip.show();
  delay(500);
  strip.fill(color, 0, 30);
  strip.show();
  delay(500);
  strip.fill(black, 0, 30);
  strip.show();
  delay(500);
  strip.fill(color, 0, 30);
  strip.show();
}
// Function to run LEDs.
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}
