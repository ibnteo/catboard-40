/*
   Keyboard CatBoard-4
   Version: 0.2
   Date: 2020-06-29
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
    {1, 7, 0, 0},
    {2, 8, 0, 0},
    {3, 9, 14, 13},
    {4, 10, 15, 18},
    {5, 11, 16, 19},
    {6, 12, 17, 20}
  },
  {
    {21, 27, 33, 38},
    {22, 28, 34, 39},
    {23, 29, 35, 40},
    {24, 30, 36, 37},
    {25, 31, 0, 0},
    {26, 32, 0, 0}
  }
  /*{
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
  }*/
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

#define LINUX_COMPOSE 0
#define LINUX   1
#define WINDOWS 2
#define MACOS   3
byte os = LINUX;
byte oskey = LINUX;
/*#if OS == MACOS
#define KEY_LEFT_CTRL 0x83
#define KEY_LEFT_GUI  0x80
#endif*/

#define KEY_MODS 0x80
#define MODS  0b11011101
#define CTRL  (1 << (KEY_LEFT_CTRL - KEY_MODS))
#define LALT  (1 << (KEY_LEFT_ALT - KEY_MODS))
#define RALT  (1 << (KEY_RIGHT_ALT - KEY_MODS))
#define SHIFT (1 << (KEY_LEFT_SHIFT - KEY_MODS))
#define WIN   (1 << (KEY_LEFT_GUI - KEY_MODS))
#define IS_MODS(code) (code >= KEY_LEFT_CTRL && code <= KEY_RIGHT_GUI)
#define IS_MOD3(code) (code >= KEY_LEFT_CTRL && code <= KEY_RIGHT_GUI && code != KEY_LEFT_SHIFT && code != KEY_RIGHT_SHIFT)

#define KEY_MOUSE 245
#define KEY_X4    246
#define KEY_MACRO 247
#define KEY_USYM  248
#define KEY_SYM   249
#define KEY_LAY1  250
#define KEY_LAY2  251
#define KEY_FN  252
#define KEY_FN2 253
#define KEY_FN3 254
#define KEY_FN4 255
#define IS_FN(code) (code >= KEY_FN)
#define LAY_FN(lay) (4 + lay - KEY_FN)
#define IS_LAY(code) (code >= KEY_LAY1 && code <= KEY_LAY2)
#define LAY(lay) (lay - KEY_LAY1)

byte layer = 0;
byte mlast  = 0;
byte mlayer = 0;
byte pressed[KEYS] = {};
byte mods = 0;

void layout(byte l) {
  if (layer != l) {
    Keyboard.releaseAll();
    if (oskey == MACOS) {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(' ');
    } else if (oskey == WINDOWS) {
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_LEFT_CTRL);
    } else if (oskey == LINUX) {
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_LEFT_ALT);
    }
    Keyboard.releaseAll();
    mrecover();
  }
  layer = l;
  digitalWrite(LED_LAYER, layer == 0 ? HIGH : LOW); // LOW = light
}

void mrecover() {
  for (byte i = 0; i < KEYS; i++) {
    if (pressed[i] >= KEY_MODS && pressed[i] <= KEY_RIGHT_GUI) {
      Keyboard.press(pressed[i]);
    }
  }
}

const char layers[][KEYS] PROGMEM = {
  { // Layer mods
    '[', 'q', 'w', 'e', 'r', 't',
    KEY_TAB, 'a', 's', 'd', 'f', 'g',
    'z', 'x', 'c', 'v', 'b',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, ' ',
    'y', 'u', 'i', 'o', 'p', ']',
    'h', 'j', 'k', 'l', ';', '\'',
    'n', 'm', ',', '.', '/',
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Layer 1
    '[', 'j', 'c', 'u', 'k', 'e',
    '`', 'f', 'y', 'w', 'a', 'p',
    'q', '/', 's', 'm', 'i',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    'n', 'g', 'h', 'v', 'z', ']',
    'r', 'o', 'l', 'd', ';', '\'',
    't', 'x', 'b', ',', '.',
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Layer 2
    '`', 'q', 'w', 'e', 'r', 't',
    ']', 'a', 's', 'd', 'f', 'g',
    'z', 'x', 'c', 'v', 'b',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    'y', 'u', 'i', 'o', 'p', '[',
    'h', 'j', 'k', 'l', ';', '\'',
    'n', 'm', ',', '.', '/',
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Mods Fn
    KEY_X4, '1', '2', '3', '4', '5',
    KEY_TAB, '6', '7', '8', '9', '0',
    KEY_LAY2, '\\', '=', '-', '`',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_MOUSE, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_PAGE_UP, KEY_ESC,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_PAGE_DOWN, KEY_FN2,
    KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_APPLICATION, KEY_LAY1,
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Fn
    KEY_X4, '1', '2', '3', '4', '5',
    KEY_FN4, '6', '7', '8', '9', '0',
    KEY_LAY2, '/', '+', '-', '.',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_MOUSE, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_PAGE_UP, KEY_ESC,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_PAGE_DOWN, KEY_FN2,
    KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_APPLICATION, KEY_LAY1,
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Fn2
    KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
    KEY_CAPS_LOCK, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_SCROLL_LOCK, KEY_PAUSE, KEY_PRINTSCREEN, KEY_F11, KEY_F12,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_NUM_LOCK, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_MINUS, KEYPAD_SLASH,
    KEYPAD_ENTER, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_PLUS, KEYPAD_ASTERIX,
    KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_PERIOD,
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Fn3
    KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_FN4, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_MOUSE, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_PAGE_UP, KEY_ESC,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_PAGE_DOWN, KEY_FN2,
    KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_APPLICATION, KEY_LAY2,
    ' ', KEY_FN, KEY_RIGHT_ALT
  },
  { // Fn4
    KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO,
    KEY_USYM, KEY_USYM, KEY_USYM, KEY_USYM, KEY_USYM, KEY_USYM,
    KEY_USYM, KEY_USYM, KEY_USYM, KEY_USYM, KEY_USYM,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_BACKSPACE, KEY_DELETE, KEY_SYM, KEY_SYM, KEY_SYM,
    ' ', KEY_FN, KEY_RIGHT_ALT
  }
};

const char syms[KEYS][2] PROGMEM = {
  {'`', 0}, {'!', '!'}, {'@', 0}, {'#', 0}, {'$', 0}, {'%', '%'},
  {'~', 0}, {'^', 0}, {'&', 0}, {'*', '*'}, {'(', '('}, {')', ')'},
  {'|', 0}, {'\\', '\\'}, {'=', '='}, {'_', '_'}, {',', '?'},
  {0, 0}, {0, 0}, {0, 0},
  {0, '#'}, {'?', '&'}, {'{', 0}, {'}', 0}, {';', '$'}, {'\'', 0},
  {0, 0}, {0, 0}, {'[', 0}, {']', 0}, {':', '^'}, {'"', '@'},
  {0, 0}, {0, 0}, {'<', 0}, {'>', 0}, {0, 0},
  {' ', ' '}, {0, 0}, {0, 0}
};

void symbols(byte k) {
  byte l = layer;
  byte code = pgm_read_byte(&syms[k - 1][layer]);
  if (code) {
    Keyboard.write(code);
  } else {
    code = pgm_read_byte(&syms[k - 1][1 - layer]);
    if (code) {
      layout(1 - layer);
      Keyboard.write(code);
    }
  }
  layout(l);
}

String macros(byte k) {
  if (k == 1 && layer == 0) return "Youtube";
  if (k == 1 && layer == 1) return "djpvj;yj"; // возможно

  if (k == 2 && layer == 0) return "length";
  if (k == 2 && layer == 1) return "wbjyy"; // ционн
  
  if (k == 3 && layer == 0) return "return";
  if (k == 3 && layer == 1) return "cnjhjy"; // сторон
  
  if (k == 4 && layer == 0) return "foreach";
  if (k == 4 && layer == 1) return "ghj,ktv"; // проблем
  
  if (k == 5 && layer == 0) return "function";
  if (k == 5 && layer == 1) return "xtkjdt"; // челове
  
  if (k == 6 && layer == 0) return "right";
  if (k == 6 && layer == 1) return "jnyjityb"; // отношени
  
  return "";
}

String usyms(byte k) {
  if (k == 8 && os <= LINUX) return os == LINUX_COMPOSE ? "<<" : "0301";
  else if (k == 8 && os == WINDOWS) return "0301";

  else if (k == 9 && os <= LINUX) return os == LINUX_COMPOSE ? "<<" : "00ab";
  else if (k == 9 && os == WINDOWS) return "0171";

  else if (k == 10 && os <= LINUX) return os == LINUX_COMPOSE ? ">>" : "00bb";
  else if (k == 10 && os == WINDOWS) return "0187";

  else if (k == 11 && os <= LINUX) return os == LINUX_COMPOSE ? ">>" : "00a0";
  else if (k == 11 && os == WINDOWS) return "0160";

  else if (k == 12 && os <= LINUX) return os == LINUX_COMPOSE ? ">>" : "00b0";
  else if (k == 12 && os == WINDOWS) return "0176";

  else if (k == 15 && os <= LINUX) return os == LINUX_COMPOSE ? "x" : "00d7";
  else if (k == 15 && os == WINDOWS) return "0215";

  else if (k == 16 && os <= LINUX) return os == LINUX_COMPOSE ? "--" : "2013";
  else if (k == 16 && os == WINDOWS) return "2013";

  else if (k == 17 && os <= LINUX) return os == LINUX_COMPOSE ? "---" : "2014";
  else if (k == 17 && os == WINDOWS) return "2014";

  return "";
}

void unicode(String str, bool compose) {
  if (str != "") {
    byte l = layer;
    Keyboard.releaseAll();
    if (os == LINUX_COMPOSE && compose) { // Compose (Right Win)
      layout(0);
      Keyboard.press(KEY_RIGHT_GUI);
      Keyboard.print(str);
      Keyboard.releaseAll();
      layout(l);
    } else if (os <= LINUX) { // Ctrl+U <code> <Enter>
      layout(0);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.write('U');
      Keyboard.releaseAll();
      Keyboard.print(str);
      Keyboard.write(KEY_RETURN);
      layout(l);
    } else if (os == WINDOWS) { // Alt+<code-NumBlock>
      Keyboard.press(KEY_RIGHT_ALT);
      for (byte i = 0; i < str.length(); i++) {
        byte s = str.charAt(i) - '1' + KEYPAD_1;
        if (s < KEYPAD_1 || s > KEYPAD_9) s = KEYPAD_0;
        Keyboard.write(s);
      }
      Keyboard.releaseAll();
    } else if (os == MACOS) {
      // TODO:
    }
    mrecover();
  }
}


void press(byte k) {
  byte l = layer + 1;
  if (IS_FN(mlayer)) {
    l = LAY_FN(mlayer);
  }
  byte code = pgm_read_byte(&layers[l][k - 1]);

  bool is_mods = false;
  bool is_shift = false;
  bool is_fn2 = false;
  for (byte i = 0; i < KEYS; i++) {
    if (IS_MOD3(pressed[i])) {
      is_mods = true;
    }
    if (pressed[i] == KEY_LEFT_SHIFT) {
      is_shift = true;
    }
    if (pressed[i] == KEY_FN2) {
      is_fn2 = true;
    }
  }

  if (is_shift && mlayer == KEY_FN && k <= 20) { // Fn + Shift
    Keyboard.release(KEY_LEFT_SHIFT);
    l = LAY_FN(mlayer + 2);
    code = pgm_read_byte(&layers[l][k - 1]);
  }
  
  if (IS_FN(code)) { // Fn
    mlayer = code;
    byte l2 = LAY_FN(mlayer);
    for (byte i = 0; i < KEYS; i++) {
      if (IS_MODS(pressed[i])) { // Mods release, Fn press
        byte code2 = pgm_read_byte(&layers[l2][i - 1]);
        if (IS_FN(code2)) {
          Keyboard.release(pressed[i]);
          pressed[i] = code2;
          mlayer = code2;
        }
      }
    }
  
  } else if (! is_fn2 && mlayer == KEY_FN2 && code >= KEY_CAPS_LOCK && code <= KEY_F12) { // Func once
    mlayer = KEY_FN;
    Keyboard.press(code);
    
  } else if (code == KEY_LEFT_ALT || code == KEY_RIGHT_ALT) { // Alt + AltGr = Win
    for (byte i = 0; i < KEYS; i++) {
      if (pressed[i] == KEY_LEFT_ALT || pressed[i] == KEY_RIGHT_ALT) {
        Keyboard.release(pressed[i]);
        pressed[i] = KEY_LEFT_GUI;
        Keyboard.press(pressed[i]);
        code = 0;
        break;
      }
    }
    if (code) {
      Keyboard.press(code);
    }

  } else if (IS_LAY(code)) { // Layout
    layout(LAY(code));
  
  } else if (code == KEY_SYM) { // Symbol
    symbols(k);
  
  } else if (code == KEY_USYM) { // Unicode Symbol
    unicode(usyms(k), true);

  } else if (code == KEY_MACRO) { // Macros
    Keyboard.print(macros(k));

  } else if (mlayer == KEY_FN && is_mods) { // Fn mods
    l = LAY_FN(KEY_FN - 1);
    code = pgm_read_byte(&layers[l][k - 1]);
    Keyboard.press(code);

  } else if (is_mods) { // Layer mods
    code = pgm_read_byte(&layers[0][k - 1]);
    Keyboard.press(code);
  
  } else {
    Keyboard.press(code);
  }
  if (is_shift) {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  pressed[k] = code;
  mlast = code;
}

void release(byte k) {
  byte l = layer + 1;
  if (IS_FN(mlayer)) {
    l = LAY_FN(mlayer);
  }
  byte code = pressed[k];
  pressed[k] = 0;
  if (IS_FN(code) && code != KEY_FN2) { // Fn
    mlayer = 0;
    for (byte i = 0; i < KEYS; i++) {
      if (IS_FN(pressed[i])) {
        mlayer = pressed[i];
        byte code2 = pgm_read_byte(&layers[LAY_FN(mlayer)][i - 1]);
        if (IS_MODS(code2)) {
          mlayer = 0;
          Keyboard.press(code2);
          pressed[i] = code2;
        }
      }
    }
  }
  if (code == mlast && (IS_MODS(code) || IS_FN(code)) && code != KEY_FN2) { // Mods click
    Keyboard.release(code);
    code = pgm_read_byte(&layers[0][k - 1]);
    if (! IS_MODS(code) && ! IS_FN(code)) {
      Keyboard.write(code);
    }
  } else {
    Keyboard.release(code);
  }
}

void setup() {
  pinMode(LED_BUILTIN_TX, INPUT); // disable LED TX
  pinMode(LED_LAYER, OUTPUT);
  Keyboard.begin();
  layout(layer);
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
            mlast = 0;
          }
        }
      }
    }
  }
}
