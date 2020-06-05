/*
   Keyboard CatBoard-40 (for CatBoard-2)
   Version: 0.11
   Date: 2020-06-05
   Author: Vladimir Romanovich <ibnteo@gmail.com>
   License: MIT
   Controller: ProMicro (Arduino Leonardo)
*/
#include <Keyboard.h>
#include <Keypad.h>

/*
   ProMicro Pins
   Row2 = 2     21 = Col11
   Col1 = 3     20 = Col12
   Col3 = 4     19 = Row3
   Col4 = 5     18 = Col10
   Col5 = 6     15 = Col7
   Col2 = 7     14 = Row4
   Col6 = 8     16 = Col9
   Col8 = 9     10 = Row5
*/
#define COLS 6
#define ROWS 4
#define KEYS 40
#define KEYPADS 2

byte colPinsL[COLS] = {3, 7, 4, 8, 6, 5};
byte colPinsR[COLS] = {15, 9, 16, 18, 21, 20};
byte rowPins[ROWS] = {2, 19, 14, 10};
const char keys[KEYPADS][COLS][ROWS] = {
  {
    {1, 13, 0, 0},
    {2, 14, 0, 0},
    {3, 15, 26, 25},
    {4, 16, 27, 35},
    {5, 17, 28, 36},
    {6, 18, 29, 37}
  },
  {
    {7, 19, 30, 38},
    {8, 20, 31, 39},
    {9, 21, 32, 40},
    {10, 22, 33, 34},
    {11, 23, 0, 0},
    {12, 24, 0, 0}
  }
};
Keypad keypad[KEYPADS] = {
  Keypad(makeKeymap(keys[0]), colPinsL, rowPins, COLS, ROWS),
  Keypad(makeKeymap(keys[1]), colPinsR, rowPins, COLS, ROWS)
};

#define KEY_PRINTSCREEN 0xCE
#define KEY_SCROLL_LOCK 0xCF
#define KEY_PAUSE 0xD0
#define KEY_NUM_LOCK 0xDB
#define KEYPAD_SLASH 0xDC
#define KEYPAD_ASTERIX 0xDD
#define KEYPAD_MINUS 0xDE
#define KEYPAD_PLUS 0xDF
#define KEYPAD_ENTER 0xE0
#define KEYPAD_1 0xE1
#define KEYPAD_2 0xE2
#define KEYPAD_3 0xE3
#define KEYPAD_4 0xE4
#define KEYPAD_5 0xE5
#define KEYPAD_6 0xE6
#define KEYPAD_7 0xE7
#define KEYPAD_8 0xE8
#define KEYPAD_9 0xE9
#define KEYPAD_0 0xEA
#define KEYPAD_PERIOD 0xEB
#define KEY_NONUS_BSLASH 0xEC
#define KEY_APPLICATION 0xED

#define LED_LAYER LED_BUILTIN_RX

#define KEY_LAY1 252
#define KEY_LAY2 253

#define KEY_NAV  254
#define KEY_NUM  255

#define LAYERS 4
#define LAYOUTS 2
#define MOD_LAYER 1
byte layer = 0;
const char layers[LAYERS][KEYS] PROGMEM = {
  { // JCUKEN layer
    '[', 'j', 'c', 'u', 'k', 'e','n', 'g', 'h', 'v', 'z', ']',
    '`', 'f', 'y', 'w', 'a', 'p', 'r', 'o', 'l', 'd', ';', '\'',
    'q', '/', 's', 'm', 'i', 't', 'x', 'b', ',', '.',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, ' ', KEY_NAV, KEY_RIGHT_ALT
  },
  { // QWERTY layer (for ЙЦУКЕН and Ctrl/Alt/GUI+)
    '`', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',
    ']', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, ' ', KEY_NAV, KEY_RIGHT_ALT
  },
  { // Nav
    KEY_ESC, '1', '2', '3', '4', '5', 0, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_PAGE_UP, KEY_ESC,
    KEY_TAB, '0', '9', '8', '7', '6', KEY_RETURN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_PAGE_DOWN, KEY_NUM,
    '|', '=', '+', '-', '_', KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_APPLICATION, '\\',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, ' ', KEY_NAV, KEY_LEFT_GUI
  },
  { // Num
    0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_SCROLL_LOCK, KEY_NUM_LOCK, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_MINUS, KEYPAD_SLASH,
    KEY_CAPS_LOCK, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_PRINTSCREEN, KEYPAD_ENTER, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_PLUS, KEYPAD_ASTERIX,
    KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PAUSE, KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_PERIOD,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, ' ', KEY_NUM, KEY_LEFT_GUI
  },
};

byte modifiers = 0;
byte modLast = 0;
byte modLay = 0;

#define LINUX   0
#define WINDOWS 1
#define MACOS   2
#define OS LINUX
void change_layout(byte lay) {
  if ((layer == 1 || lay == 1) && layer != lay) {
    modifiers = 0;
    Keyboard.releaseAll();
#if OS == MACOS
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(' ');
#elif OS == WINDOWS
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_CTRL);
#else
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
#endif
    Keyboard.releaseAll();
  }
  layer = lay;
  digitalWrite(LED_LAYER, layer == 0 ? HIGH : LOW); // LOW = light
}

void press(byte keyNum) {
  byte layer1 = layer ;
  if (modLay) layer1 = modLay - KEY_NAV + LAYERS - LAYOUTS;
  //if (layer1 < LAYOUTS && (modifiers & 0b11011101)) layer1 = MOD_LAYER;
  byte keyCode = pgm_read_byte(&layers[layer1][keyNum - 1]);
  if (keyCode >= KEY_LEFT_CTRL && keyCode <= KEY_RIGHT_GUI) {
    if (keyCode == KEY_LEFT_ALT && (modifiers & (1 << (KEY_RIGHT_ALT - KEY_LEFT_CTRL)))) {
      keyCode = KEY_LEFT_GUI;
      Keyboard.release(KEY_RIGHT_ALT);
      modifiers &= ~ (1 << (KEY_RIGHT_ALT - KEY_LEFT_CTRL));
    } else if (keyCode == KEY_RIGHT_ALT && (modifiers & (1 << (KEY_LEFT_ALT - KEY_LEFT_CTRL)))) {
      keyCode = KEY_LEFT_GUI;
      Keyboard.release(KEY_LEFT_ALT);
      modifiers &= ~ (1 << (KEY_LEFT_ALT - KEY_LEFT_CTRL));
    }
    modifiers |= (1 << (keyCode - KEY_LEFT_CTRL));
    Keyboard.press(keyCode);
    modLast = keyCode;
  } else if (keyCode >= KEY_NAV) {
    Keyboard.releaseAll();
    modRecover();
    modLast = keyCode;
    modLay = keyCode;
  } else if (keyCode >= KEY_LAY1) {
    change_layout(keyCode - KEY_LAY1);
    modLast = 0;
  } else if (keyNum == 13 && (modifiers & (1 << (KEY_LEFT_ALT - KEY_LEFT_CTRL)))) {
    Keyboard.write(KEY_TAB);
    modLast = 0;
  } else if (keyCode >= KEY_CAPS_LOCK && keyCode <= KEY_F12) {
    Keyboard.write(keyCode);
    modLast = 0;
    modLay = KEY_NAV;
  } else if (layer1 < LAYOUTS && (modifiers & 0b11011101)) {
    keyCode = pgm_read_byte(&layers[MOD_LAYER][keyNum - 1]);
    if (keyCode) Keyboard.write(keyCode);
    modLast = 0;
  } else {
    Keyboard.press(keyCode);
    modLast = 0;
  }
}

void release(byte keyNum) {
  byte layer1 = layer;
  if (modLay) layer1 = modLay - KEY_NAV + LAYERS - LAYOUTS;
  //if (layer1 < LAYOUTS && (modifiers & 0b11011101)) layer1 = MOD_LAYER;
  byte keyCode = pgm_read_byte(&layers[layer1][keyNum - 1]);
  Serial.println(keyCode, DEC);
  if (modLast) {
    if (modLast == KEY_NAV) {
      Keyboard.releaseAll();
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
      modifiers = 0;
    } else if (modLast == KEY_NUM) {
      modLay = KEY_NAV;
    } else if (modLast == KEY_LEFT_SHIFT && modLay == KEY_NAV) {
      change_layout(1);
    } else if (modLast == KEY_LEFT_CTRL && modLay == KEY_NAV) {
      change_layout(0);
    } else if (modLast == KEY_LEFT_CTRL) {
      Keyboard.releaseAll();
      Keyboard.write(KEY_DELETE);
      modifiers = 0;
    } else if (modLast == KEY_LEFT_ALT) {
      Keyboard.write(KEY_RETURN);
    } else if (modLast == KEY_RIGHT_ALT) {
      Keyboard.releaseAll();
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write(KEY_BACKSPACE);
      Keyboard.releaseAll();
      modifiers = 0;
    } else if (modLast == KEY_LEFT_SHIFT) {
      Keyboard.write(' ');
    }
    modLast = 0;
  }
  if (keyCode >= KEY_LEFT_CTRL && keyCode <= KEY_RIGHT_GUI) {
    if (keyCode == KEY_LEFT_ALT && (modifiers & (1 << (KEY_LEFT_GUI - KEY_LEFT_CTRL)))) {
      keyCode = KEY_LEFT_GUI;
      Keyboard.press(KEY_RIGHT_ALT);
      modifiers |= (1 << (KEY_RIGHT_ALT - KEY_LEFT_CTRL));
    } else if (keyCode == KEY_RIGHT_ALT && (modifiers & (1 << (KEY_LEFT_GUI - KEY_LEFT_CTRL)))) {
      keyCode = KEY_LEFT_GUI;
      Keyboard.press(KEY_LEFT_ALT);
      modifiers |= (1 << (KEY_LEFT_ALT - KEY_LEFT_CTRL));
    }
    modifiers &= ~ (1 << (keyCode - KEY_LEFT_CTRL));
    Keyboard.release(keyCode);
  } else if (keyCode >= KEY_NAV) {
    Keyboard.releaseAll();
    modRecover();
    modLay = 0;
  } else if (keyCode >= KEY_LAY1) {
    Keyboard.releaseAll();
  } else {
    Keyboard.release(keyCode);
  }
}

void modRecover() {
  for (byte i=0; i<8; i++) {
    if (modifiers & (1 << i)) {
      Keyboard.press(KEY_LEFT_CTRL + i);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN_TX, INPUT); // disable LED TX
  pinMode(LED_LAYER, OUTPUT);
  Keyboard.begin();
  change_layout(layer);
}

void loop() {
  for (byte k = 0; k < 2; k++) {
    if (keypad[k].getKeys()) {
      for (int i = 0; i < LIST_MAX; i++) {
        if (keypad[k].key[i].stateChanged) {
          if (keypad[k].key[i].kstate == PRESSED) {
            if (keypad[k].key[i].kchar) press(keypad[k].key[i].kchar);
          } else if (keypad[k].key[i].kstate == RELEASED) {
            if (keypad[k].key[i].kchar) release(keypad[k].key[i].kchar);
          } else if (keypad[k].key[i].kstate == HOLD) {
            modLast = 0;
          }
        }
      }
    }
  }
}
