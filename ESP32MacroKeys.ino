#include <BleKeyboard.h>


BleKeyboard bleKeyboard("ESP32 Keyboard", "ESP32", 100);

#define BUTTON_PIN_WIN_E 27  // Open File Explorer
#define BUTTON_PIN_TASK_MANAGER 14  // Open Task Manager
#define BUTTON_PIN_SCREENSHOT 26  // Take a Screenshot
#define BUTTON_PIN_ALT_F4 25  // End Task on current application

const int debounceDelay = 250;

unsigned long lastDebounceTimeWinE = 0;
unsigned long lastDebounceTimeTaskManager = 0;
unsigned long lastDebounceTimeScreenshot = 0;
unsigned long lastDebounceTimeAltF4 = 0;

bool lastButtonStateWinE = HIGH;
bool lastButtonStateTaskManager = HIGH;
bool lastButtonStateScreenshot = HIGH;
bool lastButtonStateAltF4 = HIGH;

void setup() {
  
  Serial.begin(115200);

  bleKeyboard.begin();

  pinMode(BUTTON_PIN_WIN_E, INPUT_PULLUP);
  pinMode(BUTTON_PIN_TASK_MANAGER, INPUT_PULLUP);
  pinMode(BUTTON_PIN_SCREENSHOT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_ALT_F4, INPUT_PULLUP);

  Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
  
  if (bleKeyboard.isConnected()) {
    unsigned long currentTime = millis();

    bool buttonStateWinE = digitalRead(BUTTON_PIN_WIN_E);
    if (buttonStateWinE == LOW && lastButtonStateWinE == HIGH &&
        (currentTime - lastDebounceTimeWinE > debounceDelay)) {
      bleKeyboard.press(KEY_LEFT_GUI); 
      bleKeyboard.press('e');        
      delay(100);                     
      bleKeyboard.releaseAll();       
      lastDebounceTimeWinE = currentTime;
    }
    lastButtonStateWinE = buttonStateWinE;

    
    bool buttonStateTaskManager = digitalRead(BUTTON_PIN_TASK_MANAGER);
    if (buttonStateTaskManager == LOW && lastButtonStateTaskManager == HIGH &&
        (currentTime - lastDebounceTimeTaskManager > debounceDelay)) {
      bleKeyboard.press(KEY_LEFT_CTRL);     
      bleKeyboard.press(KEY_LEFT_SHIFT);   
      bleKeyboard.press(KEY_ESC);         
      delay(100);                          
      bleKeyboard.releaseAll();           
      lastDebounceTimeTaskManager = currentTime;
    }
    lastButtonStateTaskManager = buttonStateTaskManager;

    bool buttonStateScreenshot = digitalRead(BUTTON_PIN_SCREENSHOT);
    if (buttonStateScreenshot == LOW && lastButtonStateScreenshot == HIGH &&
      (currentTime - lastDebounceTimeScreenshot > debounceDelay)) {
        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press(KEY_LEFT_SHIFT);
        bleKeyboard.press('s');
        delay(100);
        bleKeyboard.releaseAll();
        lastDebounceTimeScreenshot = currentTime;
      }
      lastButtonStateScreenshot = buttonStateScreenshot;

    bool buttonStateAltF4 = digitalRead(BUTTON_PIN_ALT_F4);
    if (buttonStateAltF4 == LOW && lastButtonStateAltF4 == HIGH &&
      (currentTime - lastDebounceTimeAltF4 > debounceDelay)) {
        bleKeyboard.press(KEY_LEFT_ALT);
        bleKeyboard.press(KEY_F4);
        delay(100);
        bleKeyboard.releaseAll();
        lastDebounceTimeAltF4 = currentTime;
      }
      lastButtonStateAltF4 = buttonStateAltF4;
  }
}
