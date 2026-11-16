// Exercises the real i18n.cpp lookup, not a hand-copied translation table.
#include "Arduino.h"
#include "Preferences.h"
#include "i18n.h"
#include "dex.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
uint32_t g_seed = 1;
FakeSerial Serial; FakeESP ESP; FakeWire Wire;
volatile int g_touchX = 0, g_touchY = 0;
volatile bool g_touchDown = false;
bool wasPressed = false;
uint32_t millis() { return 0; }
void FakeESP::restart() { exit(0); }
int FakeSerial::available() { return 0; }
String FakeSerial::readStringUntil(char) { return String(""); }
void sfxPlay(uint8_t) {}

int main() {
  int bad = 0;
  setLang(LANG_DE);
  const char *expected[][2] = {{"BISASAM", "1"}, {"GLUMANDA", "4"},
                                {"SCHIGGY", "7"}, {"INFAMOMO", "1025"}};
  const unsigned ids[] = {1,4,7,1025};
  for (int i=0; i<4; ++i) {
    if (strcmp(pokemonName(ids[i]), expected[i][0])) {
      std::printf("FAIL DE #%u got %s, expected %s\n", ids[i], pokemonName(ids[i]), expected[i][0]);
      ++bad;
    }
  }
  if (strcmp(pokemonName(0), "?") || strcmp(pokemonName(1026), "?")) ++bad;
  setLang(LANG_EN);
  if (strcmp(pokemonName(1), "BULBASAUR")) { std::puts("FAIL EN fallback"); ++bad; }
  setLang(LANG_ES);
  if (strcmp(pokemonName(4), DEX_TBL[4].name)) { std::puts("FAIL ES fallback"); ++bad; }
  std::printf("%s: German Pokemon names and other-language fallbacks\n", bad ? "FAIL" : "PASS");
  return bad ? 1 : 0;
}
