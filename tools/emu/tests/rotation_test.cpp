// Exercise the real settings screen, touch resolver and NVS setting together.
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "Preferences.h"
#include "pet.h"
#include "i18n.h"
#include "save.h"
#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>

uint32_t g_seed = 4;
FakeSerial Serial;
FakeESP ESP;
FakeWire Wire;
volatile int g_touchX = 0, g_touchY = 0;
volatile bool g_touchDown = false;
void FakeESP::restart() { exit(0); }
int FakeSerial::available() { return 0; }
String FakeSerial::readStringUntil(char) { return String(""); }

void setup();
void handleTouch();
void openClock();
void renderClock();
void loadDisplayRotation();
bool setDisplayRotated(bool rotated);
extern Arduino_Canvas *gfx;
extern Pet pet;
extern bool clockOpen;
extern int clockH, clockM;

static int failures = 0;
static void check(bool ok, const char *message) {
  printf("%s %s\n", ok ? "PASS" : "FAIL", message);
  if (!ok) failures++;
}

static void poll(int x, int y, bool down) {
  g_touchX = x;
  g_touchY = y;
  g_touchDown = down;
  std::this_thread::sleep_for(std::chrono::milliseconds(25));
  emuFireInterrupt();
  handleTouch();
}

static void tap(int x, int y) {
  poll(x, y, true);
  poll(x, y, false);
}

static void screenshot(const char *path) {
  FILE *file = fopen(path, "wb");
  if (!file) { check(false, "write settings screenshot"); return; }
  fprintf(file, "P6\n466 466\n255\n");
  for (int i = 0; i < 466 * 466; i++) {
    uint16_t color = gfx->buffer()[i];
    unsigned char rgb[] = {
      (unsigned char)(((color >> 11) & 31) * 255 / 31),
      (unsigned char)(((color >> 5) & 63) * 255 / 63),
      (unsigned char)((color & 31) * 255 / 31)
    };
    fwrite(rgb, 1, 3, file);
  }
  fclose(file);
}

int main() {
  nvs().clear();
  setup();
  if (pet.awaitingStarter()) pet.chooseStarter(4);
  check(gfx->rotation == 0, "old saves default to zero degrees");
  setLang(LANG_DE);
  openClock();
  renderClock();
  screenshot("settings-0.ppm");

  tap(185, 364);
  check(gfx->rotation == 2 && clockOpen, "rotation button rotates without closing settings");
  Preferences prefs;
  prefs.begin("tamapoke", true);
  check(prefs.getBool("rotate", false), "rotation is stored in NVS");
  gfx->setRotation(0);
  loadDisplayRotation();
  check(gfx->rotation == 2, "saved rotation is restored on load");
  renderClock();
  screenshot("settings-180.ppm");

  int oldHour = clockH;
  tap(465 - 199, 465 - 219);
  check(clockH == (oldHour + 1) % 24, "rotated touch reaches the hour-plus button");
  tap(465 - 185, 465 - 364);
  check(gfx->rotation == 0 && clockOpen, "the rotated button can turn the screen back");
  loadDisplayRotation();
  check(gfx->rotation == 0, "zero degrees is persisted too");

  tap(308, 364);
  check(clockOpen && gfx->rotation == 0, "gap between rotate and OK is inert");
  tap(356, 364);
  check(!clockOpen, "OK still applies the clock and closes settings");

  openClock();
  setDisplayRotated(true);
  tap(465 - 356, 465 - 364);
  check(!clockOpen, "OK works with the rotated touch coordinates");
  openClock();
  poll(233, 465 - 130, true);
  poll(233, 465 - 260, true);
  poll(233, 465 - 260, false);
  check(!clockOpen, "downward swipe in rotated UI closes settings");

  gfx->fillScreen(0);
  gfx->fillRect(10, 20, 1, 1, 0xFFFF);
  check(gfx->buffer()[445 * 466 + 455] == 0xFFFF,
        "drawing rotates around the full 466-by-466 frame");

  nvsFailWritesAfter(0);
  check(!setDisplayRotated(false) && gfx->rotation == 2,
        "failed save keeps the active orientation consistent");
  nvsResumeWrites();

  bool backedUp = false;
  for (int i = 0; i < SAVE_FIELD_COUNT; i++) {
    if (!strcmp(SAVE_FIELDS[i].key, "rotate") && SAVE_FIELDS[i].kind == SK_BOOL)
      backedUp = true;
  }
  check(backedUp, "save backups include the orientation setting");
  uint8_t backup[SAVE_TRANSFER_MAX];
  size_t backupSize = saveExport(backup, sizeof(backup));
  setDisplayRotated(false);
  check(backupSize > 0 && saveImport(backup, backupSize), "orientation backup restores successfully");
  loadDisplayRotation();
  check(gfx->rotation == 2, "restored backup reinstates the saved orientation");
  for (int language = 0; language < LANG_COUNT; language++) {
    setLang((Lang)language);
    const char *label = T(S_DISPLAY_ROTATE);
    check(label && strlen(label) * 12 <= 210, "translated label fits its button");
  }
  check(prefs.getUChar("lang", 255) < LANG_COUNT, "other settings remain readable");
  prefs.end();
  printf("Rotation failures: %d\n", failures);
  return failures ? 1 : 0;
}
