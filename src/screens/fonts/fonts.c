

#include <raylib.h>
#include <stdio.h>
Font FontTitle;
Font FontRegular;

void LoadFonts(void) {
    FontTitle = LoadFontEx("assets/fonts/Anton.ttf", 256, NULL, 0);
    FontRegular = LoadFontEx("assets/fonts/Geist.ttf", 128, NULL, 0);
    SetTextureFilter(FontTitle.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(FontRegular.texture, TEXTURE_FILTER_TRILINEAR);
}

void UnloadFonts(void) {
    UnloadFont(FontTitle);
    UnloadFont(FontRegular);
}
