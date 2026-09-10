#include <graphx.h>
#include <keypadc.h>
#include <stdbool.h>
#include <stdint.h>
#include <tice.h>

enum {
  COL_BLACK = 0,
  COL_WHITE,
  COL_MINT,
  COL_MINT_DARK,
  COL_DESKTOP,
  COL_PANEL,
  COL_WINDOW,
  COL_BORDER,
  COL_TEXT,
  COL_MUTED,
  COL_BLUE,
  COL_RED,
  COL_YELLOW
};

static void palette_init(void) {
  gfx_palette[COL_BLACK] = gfx_RGBTo1555(0, 0, 0);
  gfx_palette[COL_WHITE] = gfx_RGBTo1555(255, 255, 255);
  gfx_palette[COL_MINT] = gfx_RGBTo1555(82, 190, 128);
  gfx_palette[COL_MINT_DARK] = gfx_RGBTo1555(30, 94, 66);
  gfx_palette[COL_DESKTOP] = gfx_RGBTo1555(38, 71, 60);
  gfx_palette[COL_PANEL] = gfx_RGBTo1555(31, 39, 36);
  gfx_palette[COL_WINDOW] = gfx_RGBTo1555(239, 242, 240);
  gfx_palette[COL_BORDER] = gfx_RGBTo1555(115, 127, 121);
  gfx_palette[COL_TEXT] = gfx_RGBTo1555(28, 32, 30);
  gfx_palette[COL_MUTED] = gfx_RGBTo1555(117, 128, 123);
  gfx_palette[COL_BLUE] = gfx_RGBTo1555(52, 136, 210);
  gfx_palette[COL_RED] = gfx_RGBTo1555(204, 70, 70);
  gfx_palette[COL_YELLOW] = gfx_RGBTo1555(226, 183, 64);
}

static void text(const char *s, int x, int y, uint8_t color) {
  gfx_SetTextFGColor(color);
  gfx_SetTextBGColor(COL_WINDOW);
  gfx_SetTextTransparentColor(COL_WINDOW);
  gfx_PrintStringXY(s, x, y);
}

static void wait_release(void) {
  do {
    kb_Scan();
    delay(10);
  } while (kb_AnyKey());
}

static void titlebar(const char *title) {
  gfx_SetColor(COL_PANEL);
  gfx_FillRectangle(0, 0, 320, 18);
  gfx_SetTextFGColor(COL_WHITE);
  gfx_SetTextBGColor(COL_PANEL);
  gfx_SetTextTransparentColor(COL_PANEL);
  gfx_PrintStringXY("LM", 6, 5);
  gfx_PrintStringXY(title, 34, 5);
  gfx_PrintStringXY("CE", 296, 5);
}

static void window_frame(const char *title) {
  gfx_SetColor(COL_DESKTOP);
  gfx_FillScreen(COL_DESKTOP);
  titlebar("Linux Mint CE");
  gfx_SetColor(COL_WINDOW);
  gfx_FillRectangle(15, 30, 290, 190);
  gfx_SetColor(COL_BORDER);
  gfx_Rectangle(15, 30, 290, 190);
  gfx_SetColor(COL_PANEL);
  gfx_FillRectangle(16, 31, 288, 18);
  gfx_SetTextFGColor(COL_WHITE);
  gfx_SetTextBGColor(COL_PANEL);
  gfx_SetTextTransparentColor(COL_PANEL);
  gfx_PrintStringXY(title, 23, 36);
  gfx_SetColor(COL_RED);
  gfx_FillCircle(292, 40, 4);
}

static void boot_screen(void) {
  uint8_t i;
  gfx_FillScreen(COL_BLACK);
  gfx_SetTextFGColor(COL_WHITE);
  gfx_SetTextBGColor(COL_BLACK);
  gfx_SetTextTransparentColor(COL_BLACK);
  gfx_SetTextScale(2, 2);
  gfx_PrintStringXY("LM", 137, 63);
  gfx_SetTextScale(1, 1);
  gfx_PrintStringXY("Linux Mint CE", 105, 105);
  gfx_PrintStringXY("calculator shell", 101, 119);
  gfx_SetColor(COL_BORDER);
  gfx_Rectangle(70, 148, 180, 10);
  for (i = 0; i < 6; i++) {
    gfx_SetColor(COL_MINT);
    gfx_FillRectangle(72, 150, (uint24_t)(29 * (i + 1)), 6);
    delay(110);
  }
}

static void draw_icon(int x, int y, uint8_t kind, const char *label,
                      bool selected) {
  if (selected) {
    gfx_SetColor(COL_MINT);
    gfx_FillRectangle(x - 6, y - 6, 72, 53);
  }
  gfx_SetColor(kind == 0 ? COL_PANEL : (kind == 1 ? COL_BLUE : COL_WINDOW));
  gfx_FillRectangle(x + 10, y, 30, 25);
  gfx_SetColor(kind == 2 ? COL_MINT_DARK : COL_WHITE);
  if (kind == 0) {
    gfx_SetTextFGColor(COL_WHITE);
    gfx_SetTextBGColor(COL_PANEL);
    gfx_SetTextTransparentColor(COL_PANEL);
    gfx_PrintStringXY(">_", x + 17, y + 9);
  } else if (kind == 1) {
    gfx_FillRectangle(x + 14, y + 6, 22, 3);
    gfx_FillRectangle(x + 14, y + 12, 18, 3);
  } else {
    gfx_FillCircle(x + 25, y + 12, 7);
  }
  gfx_SetTextFGColor(COL_WHITE);
  gfx_SetTextBGColor(selected ? COL_MINT : COL_DESKTOP);
  gfx_SetTextTransparentColor(selected ? COL_MINT : COL_DESKTOP);
  gfx_PrintStringXY(label, x, y + 33);
}

static void desktop(uint8_t selected) {
  gfx_FillScreen(COL_DESKTOP);
  titlebar("Mint CE  /  Desktop");
  draw_icon(65, 45, 0, "Terminal", selected == 0);
  draw_icon(195, 45, 1, "Files", selected == 1);
  draw_icon(65, 125, 2, "System", selected == 2);
  draw_icon(195, 125, 2, "Help", selected == 3);
  gfx_SetColor(COL_PANEL);
  gfx_FillRectangle(0, 222, 320, 18);
  gfx_SetColor(COL_MINT);
  gfx_FillRectangle(4, 225, 27, 12);
  gfx_SetTextFGColor(COL_BLACK);
  gfx_SetTextBGColor(COL_MINT);
  gfx_SetTextTransparentColor(COL_MINT);
  gfx_PrintStringXY("LM", 10, 228);
  gfx_SetTextFGColor(COL_WHITE);
  gfx_SetTextBGColor(COL_PANEL);
  gfx_SetTextTransparentColor(COL_PANEL);
  gfx_PrintStringXY("2nd/ENTER open   CLEAR exit", 44, 228);
}

static void terminal(void) {
  uint8_t choice = 0;
  const char *cmds[] = {"neofetch", "uname -a", "free", "clear"};
  while (1) {
    window_frame("Terminal");
    gfx_SetColor(COL_PANEL);
    gfx_FillRectangle(24, 58, 272, 147);
    gfx_SetTextFGColor(COL_MINT);
    gfx_SetTextBGColor(COL_PANEL);
    gfx_SetTextTransparentColor(COL_PANEL);
    gfx_PrintStringXY("mint@ti84:~$", 31, 66);
    gfx_SetTextFGColor(COL_WHITE);
    gfx_PrintStringXY(cmds[choice], 119, 66);
    gfx_PrintStringXY("Built-in command preview", 31, 88);
    gfx_PrintStringXY("LEFT/RIGHT choose   ENTER run", 31, 184);
    do {
      kb_Scan();
      delay(10);
    } while (!kb_AnyKey());
    if (kb_IsDown(kb_KeyClear))
      break;
    if (kb_IsDown(kb_KeyLeft))
      choice = choice ? choice - 1 : 3;
    if (kb_IsDown(kb_KeyRight))
      choice = (choice + 1) & 3;
    if (kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) {
      if (choice == 3) {
        wait_release();
        continue;
      }
      if (choice == 0) {
        gfx_PrintStringXY("Linux Mint CE 1.0", 31, 108);
        gfx_PrintStringXY("OS: simulated Mint shell", 31, 122);
        gfx_PrintStringXY("Host: TI-84 Plus CE", 31, 136);
        gfx_PrintStringXY("Display: 320x240", 31, 150);
      } else if (choice == 1) {
        gfx_PrintStringXY("MintCE ti84ce ez80 simulated", 31, 108);
      } else {
        gfx_PrintStringXY("RAM: calculator-managed", 31, 108);
        gfx_PrintStringXY("No swap; archive is storage", 31, 122);
      }
      gfx_PrintStringXY("Press any key", 31, 166);
      wait_release();
      do {
        kb_Scan();
      } while (!kb_AnyKey());
    }
    wait_release();
  }
  wait_release();
}

static void files(void) {
  window_frame("Files - /home/mint");
  text("Name", 31, 60, COL_MUTED);
  text("Documents/", 31, 80, COL_BLUE);
  text("Pictures/", 31, 98, COL_BLUE);
  text("README.txt", 31, 116, COL_TEXT);
  text("calculator.info", 31, 134, COL_TEXT);
  text("This is a themed file browser.", 31, 166, COL_MUTED);
  text("No calculator files are opened.", 31, 180, COL_MUTED);
  text("CLEAR: desktop", 31, 202, COL_TEXT);
  wait_release();
  do {
    kb_Scan();
  } while (!kb_IsDown(kb_KeyClear));
  wait_release();
}

static void system_info(void) {
  window_frame("System Information");
  text("Linux Mint CE", 31, 65, COL_MINT_DARK);
  text("Edition: Cinnamon-inspired", 31, 85, COL_TEXT);
  text("Machine: TI-84 Plus CE", 31, 103, COL_TEXT);
  text("CPU: eZ80", 31, 121, COL_TEXT);
  text("Display: 320 x 240 color", 31, 139, COL_TEXT);
  text("Runtime: native CE program", 31, 157, COL_TEXT);
  text("Mode: visual shell (not Linux)", 31, 175, COL_RED);
  text("CLEAR: desktop", 31, 202, COL_TEXT);
  wait_release();
  do {
    kb_Scan();
  } while (!kb_IsDown(kb_KeyClear));
  wait_release();
}

static void help(void) {
  window_frame("Welcome");
  text("Arrow keys: move selection", 31, 67, COL_TEXT);
  text("2nd or ENTER: open", 31, 87, COL_TEXT);
  text("CLEAR: back / exit", 31, 107, COL_TEXT);
  text("Terminal commands are simulated.", 31, 137, COL_MUTED);
  text("No Linux programs are executed.", 31, 154, COL_MUTED);
  text("No calculator files are modified.", 31, 171, COL_MUTED);
  text("CLEAR: desktop", 31, 202, COL_TEXT);
  wait_release();
  do {
    kb_Scan();
  } while (!kb_IsDown(kb_KeyClear));
  wait_release();
}

int main(void) {
  uint8_t selected = 0;
  bool running = true;
  gfx_Begin();
  palette_init();
  boot_screen();
  wait_release();

  while (running) {
    desktop(selected);
    do {
      kb_Scan();
    } while (!kb_AnyKey());
    if (kb_IsDown(kb_KeyClear))
      running = false;
    else if (kb_IsDown(kb_KeyLeft))
      selected ^= 1;
    else if (kb_IsDown(kb_KeyRight))
      selected ^= 1;
    else if (kb_IsDown(kb_KeyUp))
      selected = (selected + 2) & 3;
    else if (kb_IsDown(kb_KeyDown))
      selected = (selected + 2) & 3;
    else if (kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) {
      wait_release();
      if (selected == 0)
        terminal();
      else if (selected == 1)
        files();
      else if (selected == 2)
        system_info();
      else
        help();
    }
    wait_release();
  }
  gfx_End();
  return 0;
}
