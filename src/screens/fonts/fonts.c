

#include <raylib.h>
#include <stdio.h>
Font FontTitle;
Font FontRegular;

void LoadFonts(void) {
    FontTitle = LoadFontEx("assets/fonts/Anton.ttf", 4096, NULL, 0);
    FontRegular = LoadFontEx("assets/fonts/Geist.ttf", 4096, NULL, 0);
}

void UnloadFonts(void) {
    UnloadFont(FontTitle);
    UnloadFont(FontRegular);
}
