/*
   Keyboard CatBoard-40 (for CatBoard-2)
   Version: 0.3
   Date: 2020-06-11
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
#define KEY_MODS 0x80
#define CTRL  (1 << (KEY_LEFT_CTRL - KEY_MODS))
#define LALT  (1 << (KEY_LEFT_ALT - KEY_MODS))
#define RALT  (1 << (KEY_RIGHT_ALT - KEY_MODS))
#define SHIFT (1 << (KEY_LEFT_SHIFT - KEY_MODS))
#define WIN   (1 << (KEY_LEFT_GUI - KEY_MODS))

#define LINUX   0
#define WINDOWS 1
#define MACOS   2
#define OS LINUX
#if OS == MACOS
#define KEY_LEFT_CTRL 0x83
#define KEY_LEFT_GUI  0x80
#endif

#define KEY_CTRL_ALT 248
#define KEY_ALT_TAB  249
#define KEY_ESC2  250
#define KEY_LAY1  251
#define KEY_LAY2  252
#define KEY_RAISE 253
#define KEY_FUNC  254
#define KEY_LOWER 255

#define LAYERS 5
#define LAYOUTS 2
#define MOD_LAYER 2
byte layer = 0;
const char layers[LAYERS][KEYS] PROGMEM = {
  { // JCUKEN layer
    '[', 'j', 'c', 'u', 'k', 'e',
    'n', 'g', 'h', 'v', 'z', ']',
    '`', 'f', 'y', 'w', 'a', 'p',
    'r', 'o', 'l', 'd', ';', '\'',
    'q', '/', 's', 'm', 'i',
    't', 'x', 'b', ',', '.',
    KEY_LEFT_CTRL, KEY_LOWER, KEY_LEFT_SHIFT,
    ' ', KEY_RAISE, KEY_RIGHT_ALT
  },
  { // QWERTY layer (for ЙЦУКЕН)
    '`', 'q', 'w', 'e', 'r', 't',
    'y', 'u', 'i', 'o', 'p', '[',
    ']', 'a', 's', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', ';', '\'',
    'z', 'x', 'c', 'v', 'b',
    'n', 'm', ',', '.', '/',
    KEY_LEFT_CTRL, KEY_LOWER, KEY_LEFT_SHIFT,
    ' ', KEY_RAISE, KEY_RIGHT_ALT
  },
  { // QWERTY layer (for Ctrl/Alt/GUI+)
    '[', 'q', 'w', 'e', 'r', 't',
    'y', 'u', 'i', 'o', 'p', ']',
    '`', 'a', 's', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', ';', '\'',
    'z', 'x', 'c', 'v', 'b',
    'n', 'm', ',', '.', '/',
    KEY_LEFT_CTRL, KEY_LOWER, KEY_LEFT_SHIFT,
    ' ', KEY_RAISE, KEY_RIGHT_ALT
  },
  { // Raise
    KEY_ESC2, '1', '2', '3', '4', '5',
    0, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_PAGE_UP, KEY_ESC,
    KEY_TAB, '6', '7', '8', '9', '0',
    KEY_RETURN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_PAGE_DOWN, KEY_FUNC,
    KEY_LEFT_GUI, '\\', '+', '-', ' ',
    KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_APPLICATION, KEY_RIGHT_GUI,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    ' ', KEY_RAISE, KEY_RIGHT_ALT
  },
  { // Func
    KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
    KEY_NUM_LOCK, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_MINUS, KEYPAD_SLASH,
    KEY_CAPS_LOCK, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEYPAD_ENTER, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_PLUS, KEYPAD_ASTERIX,
    KEY_SCROLL_LOCK, KEY_PAUSE, KEY_PRINTSCREEN, KEY_F11, KEY_F12,
    KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_PERIOD,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    ' ', KEY_RAISE, KEY_RIGHT_ALT
  }
};

const char lower[KEYS][LAYOUTS] PROGMEM = {
  {KEY_ESC, KEY_ESC}, {'!', '!'}, {'@', 0}, {'#', 0}, {'$', 0}, {'%', '%'},
  {0, 0}, {'?', '&'}, {'{', 0}, {'}', 0}, {';', '$'}, {0, 0},
  {KEY_ALT_TAB, KEY_ALT_TAB}, {'^', 0}, {'&', 0}, {'*', '*'}, {'(', '('}, {')', ')'},
  {'`', 0}, {'\'', 0}, {'[', 0}, {']', 0}, {':', '^'}, {'"', '@'},
  {KEY_LEFT_GUI, KEY_LEFT_GUI}, {'/', '|'}, {'=', '='}, {'_', '_'}, {'|', 0},
  {'~', 0}, {0, '#'}, {'<', 0}, {'>', 0}, {KEY_RIGHT_GUI, KEY_RIGHT_GUI},
  {KEY_CTRL_ALT, KEY_CTRL_ALT}, {KEY_LOWER, KEY_LOWER}, {KEY_LEFT_SHIFT, KEY_LEFT_SHIFT},
  {' ', ' '}, {KEY_RAISE, KEY_RAISE}, {KEY_RIGHT_ALT, KEY_RIGHT_ALT}
};

byte modifiers = 0;
byte modLast = 0;
byte modLay = 0;

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

void modRecover(byte lay) {
  modifiers = 0;
  for (byte k = 0; k < 2; k++) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (keypad[k].key[i].kstate == PRESSED || keypad[k].key[i].kstate == HOLD) {
        byte keyCode = pgm_read_byte(&layers[lay][keypad[k].key[i].kchar - 1]);
        if (keyCode >= KEY_MODS && keyCode <= KEY_RIGHT_GUI) {
          modifiers |= (1 << (keyCode - KEY_MODS));
          Keyboard.press(keyCode);
        }
      }
    }
  }
}

void press(byte keyNum) {
  byte lay = layer;
  if (modLay >= KEY_LOWER) {
    lay = LAYOUTS;
  } else if (modLay == KEY_RAISE) {
    char key = 24;
    if (keyNum != key && keypad[1].findInList(key) >= 0) modLay = KEY_FUNC;
    lay = modLay - KEY_RAISE + MOD_LAYER + 1;
  } else if (modLay) {
    lay = modLay - KEY_RAISE + MOD_LAYER + 1;
  }
  byte keyCode = 0;
  bool changeLayout = false;
  bool keyRelease = false;
  if (modLay == KEY_LOWER) {
    keyRelease = true;
    keyCode = pgm_read_byte(&lower[keyNum - 1][layer]);
    if (! keyCode) {
      keyCode = pgm_read_byte(&lower[keyNum - 1][1 - layer]);
      if (keyCode) {
        change_layout(1 - layer);
        changeLayout = true;
      }
    }
  } else {
    keyCode = pgm_read_byte(&layers[lay][keyNum - 1]);
  }
  modLast = 0;
  if (keyCode >= KEY_MODS && keyCode <= KEY_RIGHT_GUI) {
    modifiers |= (1 << (keyCode - KEY_MODS));
    Keyboard.press(keyCode);
    modLast = keyCode;
  } else if (keyCode >= KEY_RAISE) {
    Keyboard.releaseAll();
    modRecover(lay);
    modLast = keyCode;
    modLay = keyCode;
  } else if (keyCode >= KEY_LAY1) {
    change_layout(keyCode - KEY_LAY1);
  } else if (keyCode == KEY_CTRL_ALT) {
    modifiers |= (CTRL & LALT);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
  } else if (keyCode == KEY_ALT_TAB) {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.write(KEY_TAB);
  } else if (keyCode == KEY_ESC2) {
    Keyboard.write(KEY_ESC);
    Keyboard.write(KEY_ESC);
  } else if (keyCode >= KEY_CAPS_LOCK && keyCode <= KEY_F12) {
    Keyboard.write(keyCode);
    modLay = KEY_RAISE;
  } else if (lay < LAYOUTS && (modifiers & 0b11011101)) {
    keyCode = pgm_read_byte(&layers[MOD_LAYER][keyNum - 1]);
    if (keyCode) Keyboard.write(keyCode);
  } else if (keyCode) {
    if (keyRelease) {
      Keyboard.write(keyCode);
    } else {
      Keyboard.press(keyCode);
    }
  }
  if (changeLayout) change_layout(1 - layer);
}

void release(byte keyNum) {
  byte lay = layer;
  if (modLay >= KEY_LOWER) {
    lay = LAYOUTS;
  } else if (modLay) {
    lay = modLay - KEY_RAISE + MOD_LAYER + 1;
  }
  byte keyCode = 0;
  if (modLay == KEY_LOWER) {
    keyCode = pgm_read_byte(&lower[keyNum - 1][layer]);
  } else {
    keyCode = pgm_read_byte(&layers[lay][keyNum - 1]);
  }
  if (keyCode >= KEY_MODS && keyCode <= KEY_RIGHT_GUI) {
    if (keyCode == KEY_LEFT_ALT && (modifiers & WIN)) {
      keyCode = KEY_LEFT_GUI;
    } else if (keyCode == KEY_RIGHT_ALT && (modifiers & WIN)) {
      keyCode = KEY_LEFT_GUI;
    }
    modifiers &= ~ (1 << (keyCode - KEY_MODS));
    Keyboard.release(keyCode);
  } else if (keyCode == KEY_CTRL_ALT) {
    modifiers &= ~ (CTRL & LALT);
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release(KEY_LEFT_ALT);
  } else if (keyCode == KEY_LOWER) {
    Keyboard.releaseAll();
    modRecover(lay);
    modLay = 0;
  } else if (keyCode == KEY_RAISE) {
    Keyboard.releaseAll();
    modRecover(lay);
    modLay = 0;
  } else if (keyCode == KEY_FUNC) {
  } else if (keyCode >= KEY_LAY1) {
    Keyboard.releaseAll();
    modLay = 0;
  } else if (modLay == KEY_LOWER) {
  } else {
    Keyboard.release(keyCode);
  }
  if (modLast) {
    if (modLast == KEY_RAISE && keyCode == KEY_RAISE) {
      Keyboard.releaseAll();
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
      modifiers = 0;
    } else if (modLast == KEY_LEFT_GUI && keyCode == KEY_LEFT_GUI) {
      change_layout(1);
    } else if (modLast == KEY_RIGHT_GUI && keyCode == KEY_RIGHT_GUI) {
      change_layout(0);
    } else if (modLast == KEY_LOWER && keyCode == KEY_LOWER) {
      Keyboard.releaseAll();
      Keyboard.write(KEY_DELETE);
      modifiers = 0;
    } else if (modLast == KEY_LEFT_CTRL && keyCode == KEY_LEFT_CTRL) {
      Keyboard.write(KEY_RETURN);
    } else if (modLast == KEY_RIGHT_ALT && keyCode == KEY_RIGHT_ALT) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write(KEY_BACKSPACE);
      if (! modifiers & CTRL) Keyboard.release(KEY_LEFT_CTRL);
    } else if (modLast == KEY_LEFT_SHIFT && keyCode == KEY_LEFT_SHIFT) {
      Keyboard.write(' ');
    }
  }
  modLast = 0;
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
