////////////////////////////////////////
// SurvivalCE Version DEV_0.22
// Author: Michael0x18 and TimmyTurner62
// License: Gnu GPLv2?
// Description: Cemetech CC24 submission.
////////////////////////////////////////

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

//Include the graphics routines from the
// graphx c lib. These are the same as in ICE.
#include <graphx.h>

#include <keypadc.h>
#include <keypadc.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "gfx/gfx.h"


    static uint16_t x;
    static uint16_t y;
    static uint16_t OldX;
    static uint16_t OldY;
    static uint16_t health;
    static uint16_t startX;
    static uint16_t dir;
    static uint16_t redraw;
    static uint16_t i;
    static uint16_t option;
    static uint16_t playerX;
    static uint16_t playerY;
    static uint16_t xa;
    static uint16_t xb;
    static uint16_t roomX;
    static uint16_t roomY;
    static uint16_t room;
    static ti_var_t appvar;
    static char screenMap[20 * 15];
    static char wholeMap[(20 * 14) * (15 * 14)];
    static gfx_sprite_t* sprites[12] = { dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth };
    static uint8_t gamedata[28] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    //CREDITS: (required for CC24, it's the right thing to do)
    //Map Engine by TimmyTurner62 at cemetech.net. Thanks to Michael0x18 for constant help with code.
    //Credits to pretty much everyone on cemetech.net, since there's too many helpful people who've helped all throughout!


/* Other available headers: stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h */

    void printText(const char *text, uint8_t x, uint8_t y);


    void run_intro(void);

    void draw_splash(void);

    void text_box(void);

    void play(void);
    void help(void);
    void quit(void);
    void DrawPlayer(void);
    void LoadMapData(void);
    void saveData(void);
       
        gfx_TempSprite(background, 16, 16);

void main(void){
    gfx_Begin();
    //set the palette...
    gfx_SetPalette(mypalette, sizeof_mypalette, 0);
    // Always have to change transparent value any time a new sprite is added and converted :/
    gfx_SetTransparentColor(192);
    gfx_SetColor(21);
    gfx_SetTextFGColor(120);
    //Go to the main menu    
    run_intro();
    //Display Splash screen.
    //draw_splash();
    //Restore the screen.
    gfx_End();
}



void LoadMapData(void) {

    xa = 0;
    xb = room;
    for (y = 0; y < 15; y++) {
        for (x = 0; x < 20; x++) {
            screenMap[xa] = wholeMap[xb];
            xb++;
            xa++;
        }
        xb += 20 * 13;
    }

}

void drawRoom(void) {

    redraw = 0;
    i = room;
    for (y = 0; y < 15; y++) {
        for (x = 0; x < 20; x++) {
                if ((screenMap[i] > -1))
                gfx_Sprite(sprites[screenMap[i]], x * 16, y * 16);
        i++;
        }
    }

}


void draw_splash(void) {
 
    OldX = playerX;
    OldY = playerY;

   // playerX = 156;
   // playerY = 113;
   // dir = 1;
    gfx_SetDrawBuffer();
    drawRoom();

    gfx_GetSprite(background, playerX, playerY);
    DrawPlayer();

    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
        if kb_IsDown(kb_KeyUp) {
            dir = 2;
            playerY--;
            DrawPlayer();
        }
        if kb_IsDown(kb_KeyDown) {
            dir = 1;
            playerY++;
            DrawPlayer();
        }
        if kb_IsDown(kb_KeyLeft) {
            dir = 3;
            playerX--;
            DrawPlayer();
        }
        if kb_IsDown(kb_KeyRight) {
            dir = 4;
            playerX++;
            DrawPlayer();
        }


        if (kb_IsDown(kb_Key4) && roomX > 1) {
            redraw = 1;
            delay(100);
            roomX--;
            room -= 20;
            xa -= 20;
        }
        if (kb_IsDown(kb_Key6) && roomX < 14) {
            redraw = 1;
            delay(100);
            roomX++;
            room += 20;
            xa += 20;
        }
        if (kb_IsDown(kb_Key8) && roomY > 1) {
            redraw = 1;
            delay(100);
            roomY--;
            room -= 4200;
            xa -= 4200;
        }
        if (kb_IsDown(kb_Key2) && roomY < 14) {
            redraw = 1;
            delay(100);
            roomY++;
            room += 4200;
            xa += 4200;
        }




        for (x = 0; x < health; x++) {
            gfx_ScaledTransparentSprite_NoClip(heart, 200 + (x * 13), 222, 2, 2);
        }

        if kb_IsDown(kb_KeyStat) {
   
                gfx_SetColor(21);
                for (xa = 1; xa < 30; xa++) {
                    if (xa < 18) gfx_FillRectangle(0, 0, 320, xa);
                    gfx_FillRectangle(0, 241-xa, 320, xa);
                    for (xb = 0; xb < 30; xb++) {
                        if (!kb_IsDown(kb_KeyStat)) drawRoom();
                    }
                    gfx_BlitBuffer();
                }
                gfx_PrintStringXY("Objective: None", 2, 2);
                //inventory hotbar
                gfx_Sprite_NoClip(inventory_box, 117 - 25, 213);
                gfx_Sprite_NoClip(inventory_box, 117, 213);
                gfx_Sprite_NoClip(inventory_box, 117 + 25, 213);
                gfx_Sprite_NoClip(inventory_box, 117 + 50, 213);
                gfx_Sprite_NoClip(inventory_box, 117 + 75, 213);
                for (x = 0; x < health; x++) {
                    gfx_ScaledTransparentSprite_NoClip(heart, 200 + (x * 13), 194, 2, 2);
                }
                gfx_BlitBuffer();
                DrawPlayer();
                while (kb_IsDown(kb_KeyStat)){
                    kb_Scan();
                };
                for (xa = 1; xa < 30; xa++) {
                    drawRoom();
                    kb_Scan();
                    if kb_IsDown(kb_KeyUp) {
                        dir = 2;
                        playerY -= 2;
                        DrawPlayer();
                    }
                    if kb_IsDown(kb_KeyDown) {
                        dir = 1;
                        playerY += 2;
                        DrawPlayer();
                    }
                    if kb_IsDown(kb_KeyLeft) {
                        dir = 3;
                        playerX -= 2;
                        DrawPlayer();
                    }
                    if kb_IsDown(kb_KeyRight) {
                        dir = 4;
                        playerX += 2;
                        DrawPlayer();
                    }
                    DrawPlayer();
                    if (xa < 18) gfx_FillRectangle(0, 0, 320, 19 - xa);
                    gfx_FillRectangle(0, 240 - (30 - xa), 320, 30 - xa);
                    for (x = 0; x < health; x++) {
                        gfx_ScaledTransparentSprite_NoClip(heart, 200 + (x * 13), 193 + xa, 2, 2);
                    }
                    gfx_BlitBuffer();
                }
                drawRoom();
                DrawPlayer();
        }


             gfx_BlitBuffer();

        }

        saveData();
        

    }

    void saveData(void) {
        
        delay(100);
            gamedata[0] = health;
            gamedata[1] = room;
            gamedata[2] = playerX;
            gamedata[3] = playerY;
            gamedata[4] = dir;
            gamedata[5] = roomX;
            gamedata[6] = roomY;
        ti_CloseAll();
        appvar = ti_Open("SrvCEss", "w");
        ti_Write(gamedata, sizeof(gamedata), 1, appvar);
        ti_CloseAll();

    }


void DrawPlayer(void) {

    gfx_Sprite(background, OldX, OldY);
    gfx_GetSprite(background, playerX, playerY);
    if (dir == 1) gfx_TransparentSprite_NoClip(player_dirF_1, playerX, playerY);
    if (dir == 2) gfx_TransparentSprite_NoClip(player_dirB_1, playerX, playerY);
    if (dir == 3) gfx_TransparentSprite_NoClip(player_dirL_1, playerX, playerY);
    if (dir == 4) gfx_TransparentSprite_NoClip(player_dirR_1, playerX, playerY);

    OldX = playerX;
    OldY = playerY;

}

void run_intro(void) {

    /* main menu */
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 15; y++) {
            gfx_Sprite(dirt, x * 16, y * 16);
        }
    }
    /* buttons */
    for (OldY = 140; OldY < 200; OldY += 20) {
        for (OldX = 60; OldX < 244; OldX += 16) {
            gfx_Sprite(wood, OldX, OldY);
        }
    }
    gfx_SetTextFGColor(110);
    redraw = 1;
    y = 140;
    i = y;
    option = 0;
    while (option == 0) {
        gfx_SetColor(175);
        kb_Scan();
        if (redraw == 1) {
            redraw = 0;
            /* redraw only the one button that needs it */
            for (OldX = 60; OldX < 244; OldX += 16) {
                gfx_Sprite(wood, OldX, i);
            }
            /* button text */
            gfx_PrintStringXY("Play", 148, 142);
            gfx_PrintStringXY("Help  & Options", 118, 162);
            gfx_PrintStringXY("Quit", 148, 182);
            gfx_Rectangle(60, y, 192, 16);
            gfx_Rectangle(61, y + 1, 190, 14);
        }
        i = y;
        if (kb_IsDown(kb_KeyUp) && y > 140) {
            delay(150);
            y -= 20;
        }
        if (kb_IsDown(kb_KeyDown) && y < 180) {
            delay(150);
            y += 20;
        }
        if (i != y)                                 redraw = 1;
        if (kb_IsDown(kb_Key2nd))                   option = 1;
    }
    if (y == 140) play();
    if (y == 160) help();
    return;
}

    void play(void) {

        //Check for all required appvars...
        ti_CloseAll();
        appvar = ti_Open("SrvMap00", "r");

        if (!appvar) {
           
            /* error screen goes here, saying the Map file is missing */

        }


        if (appvar) {
            ti_CloseAll();
            appvar = ti_Open("SrvMap00", "r");
            ti_Read(wholeMap, ti_GetSize(appvar), 1, appvar);

            ti_CloseAll();
            LoadMapData();
            gfx_SetColor(255);
            drawRoom();
        }

        ti_CloseAll();
        appvar = ti_Open("SrvCEss", "r");

        if (appvar) {
            appvar = ti_Open("SrvCEss", "r");
            ti_Read(gamedata, 28, 1, appvar);
            health = gamedata[0];
            room = gamedata[1];
            roomX = gamedata[2];
            roomY = gamedata[3];
            playerX = gamedata[4];
            playerY = gamedata[5];
            dir = gamedata[6];
            draw_splash();
        }

        if (!appvar) {
            //gamedata = {player health, current room player is in, playerX, playerY, player direction, roomX value, roomY value, inventory slot 1, inv. 2, inv. 3, inv 4, inv5, objective #, chicken count, deer count, elephant count, lion count, tiger count, hippo count, gorilla count, monkey count, rhino count, scorpion count, python count, lion king hp, scorpion queen hp, emperor kong hp, Fred�s hp};
            //gamedata size is 28. There are 11 animals (4 bosses).
            uint16_t gamedata[28] = { 9, 1, 156, 113, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

            ti_CloseAll();
            appvar = ti_Open("SrvCEss", "w");
            ti_Write(gamedata, sizeof(gamedata), 1, appvar);
            ti_SetArchiveStatus(1, appvar);
            ti_CloseAll();

            for (x = 0; x < 20; x++) {
                for (y = 0; y < 15; y++) {
                    gfx_Sprite_NoClip(wood, x * 16, y * 16);
                }
            }
            delay(300);
            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("Your father was a senior member of the", 24, 195);
            gfx_PrintStringXY("highly exclusive and extremely", 24, 210);
            /* Need to change later to wait for the [2nd] key to be pressed */
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("prestigious Hunter's Club.", 24, 195);
            gfx_PrintStringXY("His collection of rare pelts and trophies", 24, 210);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("was the envy of everyone, especially", 24, 195);
            gfx_PrintStringXY("your uncle Fred.", 24, 210);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("One day, your father went hunting with", 24, 195);
            gfx_PrintStringXY("Fred and vanished. Fred said that he", 24, 210);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("was finally killed by one of the beasts", 24, 195);
            gfx_PrintStringXY("he pursued, and everyone believed", 24, 210);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("him. However, you think your uncle", 24, 195);
            gfx_PrintStringXY("actually killed your father so that he", 24, 210);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("could hold the title of Greatest Hunter.", 24, 195);
            gfx_PrintStringXY("To get revenge, you decide to pursue the", 24, 210);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("title yourself...", 24, 195);
            while (!os_GetCSC());

            gfx_FillRectangle(20, 190, 280, 40);
            gfx_PrintStringXY("And so the saga begins...", 24, 195);
            while (!os_GetCSC());

            health = 9;
            room = 1;
            roomX = 1;
            roomY = 1;
            playerX = 156;
            playerY = 113;
            dir = 1;

            ti_CloseAll();
            draw_splash();

        }



    }


/* Draw text on the homescreen at the given X/Y cursor location */
void printText(const char *text, uint8_t xpos, uint8_t ypos){
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}


void help(void) {
    /* need a help/options screen. I'm thinking similar to main menu... ? */

    return;

}


void input(void) {
    const char* chars = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
    uint8_t key, i = 0;
    char buffer[50];
    gfx_Begin();
    while ((key = os_GetCSC()) != sk_Enter) {
        if (chars[key]) {
            buffer[i++] = chars[key];
            gfx_PrintStringXY(buffer, 1, 1);
        }
    }

    delay(100);
    return;
}