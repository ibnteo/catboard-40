/*
   Keyboard K4 (CatBoard-4)
   Version: 0.2
   Date: 2020-06-13
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

#define KEY_ENTER  KEY_RETURN
#define KEY_LEFT_WIN  KEY_LEFT_GUI
#define KEY_RIGHT_WIN KEY_RIGHT_GUI
#define CTRL  (1 << (KEY_LEFT_CTRL - KEY_LEFT_CTRL))
#define LALT  (1 << (KEY_LEFT_ALT - KEY_LEFT_CTRL))
#define RALT  (1 << (KEY_RIGHT_ALT - KEY_LEFT_CTRL))
#define SHIFT (1 << (KEY_LEFT_SHIFT - KEY_LEFT_CTRL))
#define WIN   (1 << (KEY_LEFT_WIN - KEY_LEFT_CTRL))
#define MODS  0b11011101

#define LED_LAYER LED_BUILTIN_RX

#define LINUX   0
#define WINDOWS 1
#define MACOS   2
#define OS LINUX
#if OS == MACOS
#define KEY_LEFT_CTRL 0x83
#define KEY_LEFT_WIN  0x80
#endif

#define KEY_FUNC    255
#define KEY_LSYM    254
#define KEY_NUM     253
#define KEY_QUASI   252
#define KEY_TYPO    251
#define KEY_UMLT    250
#define KEY_SYM     249
#define KEY_MACRO   248
//#define KEY_ALT_TAB 247
#define KEY_ESC2    246
#define KEY_LAY1    245
#define KEY_LAY2    244

#define LAYOUTS 2
const char layers[LAYOUTS + 7][KEYS] PROGMEM = {
  { // Mods
    '[', 'q', 'w', 'e', 'r', 't',
    KEY_TAB, 'a', 's', 'd', 'f', 'g',
    'z', 'x', 'c', 'v', 'b',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    'y', 'u', 'i', 'o', 'p', ']',
    'h', 'j', 'k', 'l', ';', '\'',
    'n', 'm', ',', '.', '/',
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Eng
    '[', 'j', 'c', 'u', 'k', 'e',
    '`', 'f', 'y', 'w', 'a', 'p',
    'q', '/', 's', 'm', 'i',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    'n', 'g', 'h', 'v', 'z', ']',
    'r', 'o', 'l', 'd', ';', '\'',
    't', 'x', 'b', ',', '.',
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Rus
    '`', 'q', 'w', 'e', 'r', 't',
    ']', 'a', 's', 'd', 'f', 'g',
    'z', 'x', 'c', 'v', 'b',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    'y', 'u', 'i', 'o', 'p', '[',
    'h', 'j', 'k', 'l', ';', '\'',
    'n', 'm', ',', '.', '/',
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Nav
    KEY_ESC2, '1', '2', '3', '4', '5',
    KEY_TAB, '6', '7', '8', '9', '0',
    KEY_LAY2, '\\', '+', '-', '`',
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    0, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_PAGE_UP, KEY_ESC,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_PAGE_DOWN, 0,
    KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_APPLICATION, KEY_LAY1,
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Num
    KEY_ESC, KEYPAD_SLASH, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_MINUS,
    KEY_TAB, KEYPAD_ASTERIX, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_PLUS,
    KEYPAD_PERIOD, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_NUM_LOCK, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_MINUS, KEYPAD_SLASH,
    KEYPAD_ENTER, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_PLUS, KEYPAD_ASTERIX,
    KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_PERIOD,
    KEY_NUM, KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Sym
    KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_TAB, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    KEY_BACKSPACE, KEY_SYM, KEY_SYM, KEY_SYM, KEY_SYM,
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Func
    KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
    KEY_SCROLL_LOCK, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_LAY2, KEY_PAUSE, KEY_PRINTSCREEN, KEY_F11, KEY_F12,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO,
    KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO,
    KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_MACRO, KEY_LAY1,
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Typo
    KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO,
    KEY_TAB, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO,
    KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO,
    KEY_BACKSPACE, KEY_TYPO, KEY_TYPO, KEY_TYPO, KEY_TYPO,
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
  { // Umlaut
    KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT,
    KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT,
    KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT,
    KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_LEFT_SHIFT,
    KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT,
    KEY_RETURN, KEY_LEFT_ARROW, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT,
    KEY_BACKSPACE, KEY_UMLT, KEY_UMLT, KEY_UMLT, KEY_UMLT,
    ' ', KEY_QUASI, KEY_RIGHT_ALT
  },
};
#define LAY_NAV  3
#define LAY_NUM  4
#define LAY_SYM  5
#define LAY_FUNC 6
#define LAY_TYPO 7
#define LAY_UMLT 8

const char syms[KEYS][LAYOUTS] PROGMEM = {
  {'`', 0}, {'!', '!'}, {'@', 0}, {'#', 0}, {'$', 0}, {'%', '%'},
  {0, 0}, {'^', 0}, {'&', 0}, {'*', '*'}, {'(', '('}, {')', ')'},
  {'.', '/'}, {'/', '|'}, {'=', '='}, {'_', '_'}, {'|', 0},
  {0, 0}, {0, 0}, {0, 0},
  {'~', 0}, {0, '#'}, {'{', 0}, {'}', 0}, {';', '$'}, {'\'', 0},
  {0, 0}, {0, 0}, {'[', 0}, {']', 0}, {':', '^'}, {'"', '@'},
  {0, 0}, {'?', '&'}, {'<', 0}, {'>', 0}, {',', '?'},
  {0, 0}, {0, 0}, {0, 0}
};//`!@#$%^&*().  

#define BUF 40
byte ibuf = 0;
char buf[BUF] = {};

byte layout = 0;
byte layer = 0;
byte mods = 0;

void changeLayout(byte l) {
  if (layout != l) {
    Keyboard.releaseAll();
#if OS == MACOS
    Keyboard.press(KEY_LEFT_WIN);
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
  layout = l;
  digitalWrite(LED_LAYER, layout == 0 ? HIGH : LOW); // LOW = light
}

#define KRELEASE 0
#define KPRESS 1
#define KHOLD 2
byte keyMode = KRELEASE;
byte multiple = 0;

void press(char keyNum) {
  keyMode = KPRESS;
  byte l = 0;
  if (layer) l = LAYOUTS + 1;
  byte keyCode = pgm_read_byte(&layers[l][keyNum - 1]);
  if (keyCode >= KEY_LEFT_CTRL && keyCode <= KEY_RIGHT_WIN) {
    if (keyCode == KEY_LEFT_ALT && (mods & RALT)) {
      Keyboard.release(KEY_RIGHT_ALT);
      mods &= ~ RALT;
      keyCode = KEY_LEFT_WIN;
    } else if (keyCode == KEY_RIGHT_ALT && (mods & LALT)) {
      Keyboard.release(KEY_LEFT_ALT);
      mods &= ~ LALT;
      keyCode = KEY_LEFT_WIN;
    }
    Keyboard.press(keyCode);
    mods |= (1 << (keyCode - KEY_LEFT_CTRL));
  } else if (keyCode >= KEY_QUASI) {
    layer = keyCode;
  } else if (keyCode == ' ' && ibuf == 0 && layer == 0) {
    layer = KEY_NUM;
  } else if (keyCode == '5') {
    multiple = 10;
  } else if (keyCode == '0') {
    multiple = 20;
  } else if (keyCode >= '0' && keyCode <= '9') {
    multiple = keyCode - '1' + 1;
  }
  if (ibuf < BUF && keyCode < KEY_QUASI && ! (keyCode >= KEY_LEFT_CTRL && keyCode <= KEY_RIGHT_WIN)) {
    buf[ibuf] = keyNum;
    ibuf ++;
  }
}

void release(char keyNum) {
  byte l = 0;
  if (layer) l = LAYOUTS + 1;
  byte keyCode = pgm_read_byte(&layers[l][keyNum - 1]);
  if (keyCode >= KEY_QUASI && keyMode == KPRESS && ibuf == 0) {
    if (layer == KEY_QUASI) {
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.write(KEY_LEFT_ARROW);
      if (! (mods & SHIFT)) Keyboard.release(KEY_LEFT_SHIFT);
    }
  }
  if (keyCode == KEY_QUASI) {
    layer = ibuf ? KEY_FUNC : 0;
    multiple = 0;
  } else if (layer == KEY_NUM && keyCode == ' ') {
    layer = 0;
  } else if (keyCode > KEY_QUASI) {
    layer = KEY_QUASI;
  } else if (keyCode >= '0' && keyCode <= '9') {
    multiple = 0;
  }
  l = layout + 1;
  Serial.println(layer, DEC);
  if (keyCode >= KEY_LEFT_CTRL && keyCode <= KEY_RIGHT_WIN) {
    if (mods & MODS) l = 0;
    if (keyMode == KPRESS && ibuf == 0) {
      if (keyCode == KEY_LEFT_SHIFT) {
        Keyboard.release(KEY_LEFT_SHIFT);
        Keyboard.write(' ');
      } else if (keyCode == KEY_LEFT_CTRL) {
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.write(KEY_DELETE);
      } else if (keyCode == KEY_LEFT_ALT) {
        Keyboard.release(KEY_LEFT_ALT);
        Keyboard.write(KEY_ENTER);
      } else if (keyCode == KEY_RIGHT_ALT) {
        Keyboard.release(KEY_RIGHT_ALT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write(KEY_DELETE);
      }
    }
  } else if (keyCode == KEY_QUASI && layer == KEY_QUASI) {
    l = LAY_FUNC;
    multiple = 0;
  } else if (layer == 0) {
    Serial.println(keyCode, DEC);
    if (mods & LALT) {
      if (keyCode != KEY_TAB) Keyboard.release(KEY_LEFT_ALT);
      l = LAY_TYPO;
    } else if (mods & CTRL) {
      if (keyCode != KEY_TAB) Keyboard.release(KEY_LEFT_CTRL);
      l = LAY_SYM;
    } else if (mods & RALT) {
      if (keyCode != KEY_TAB) Keyboard.release(KEY_RIGHT_ALT);
      l = LAY_UMLT;
    }
  } else {
    l = layer - KEY_QUASI + LAYOUTS + 1;
  }
  if (keyMode >= KPRESS) {
    for (byte i = 0; i < ibuf; i++) {
      byte keyCodeL = pgm_read_byte(&layers[l][buf[i] - 1]);
      if (keyCodeL >= KEY_LEFT_CTRL && keyCodeL <= KEY_RIGHT_WIN) {
      } else if (keyCodeL == KEY_NUM ) {
        Keyboard.write(' ');
      } else if (keyCodeL >= KEY_QUASI) {
      } else if (keyCodeL == KEY_SYM) {
        bool cl = false;
        byte keyCodeS = pgm_read_byte(&syms[buf[i] - 1][layout]);
        if (keyCodeS) {
          Keyboard.write(keyCodeS);
        } else {
          keyCodeS = pgm_read_byte(&syms[buf[i] - 1][1 - layout]);
          if (keyCodeS) {
            changeLayout(1 - layout);
            cl = true;
            Keyboard.write(keyCodeS);
          }
        }
        if (cl) changeLayout(1 - layout);
      } else if (keyCodeL == KEY_MACRO) {
        // TODO
      } else if (keyCodeL == KEY_TYPO) {
        // TODO
      } else if (keyCodeL == KEY_UMLT) {
        // TODO
      } else if (keyCodeL == KEY_LAY1) {
        if (keyMode == KPRESS) changeLayout(0);
      } else if (keyCodeL == KEY_LAY2) {
        if (keyMode == KPRESS) changeLayout(1);
      } else if (keyCodeL == '+' && (mods & SHIFT)) {
        Keyboard.release(KEY_LEFT_SHIFT);
        Keyboard.write('=');
        Keyboard.press(KEY_LEFT_SHIFT);
      } else if (keyCodeL == '+' && (mods & MODS)) {
        Keyboard.write('=');
      } else if (multiple && keyCodeL >= '0' && keyCodeL <= '9') {
      } else if (multiple && keyCodeL >= KEY_PAGE_UP && keyCodeL <= KEY_UP_ARROW) {
        for (byte m = 0; m < multiple; m++) {
          Keyboard.write(keyCodeL);
        }
      } else if (keyCodeL == KEY_ESC2) {
        Keyboard.write(KEY_ESC);
        Keyboard.write(KEY_ESC);
      } else {
        Keyboard.write(keyCodeL);
      }
    }
    ibuf = 0;
  }
  if (keyCode >= KEY_LEFT_CTRL && keyCode <= KEY_RIGHT_WIN) {
    if (keyCode == KEY_LEFT_ALT && (mods & WIN)) {
      keyCode = KEY_LEFT_WIN;
    }
    Keyboard.release(keyCode);
    mods &= ~ (1 << (keyCode - KEY_LEFT_CTRL));
  }
  for (byte i = 0; i < 8; i++) {
    if (mods & (1 << i)) {
      Keyboard.press(KEY_LEFT_CTRL + i);
    }
  }
  keyMode = KRELEASE;
}

void setup() {
  pinMode(LED_BUILTIN_TX, INPUT); // disable LED TX
  pinMode(LED_LAYER, OUTPUT);
  Keyboard.begin();
  changeLayout(layout);
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
            keyMode = KHOLD;
          }
        }
      }
    }
  }
}
