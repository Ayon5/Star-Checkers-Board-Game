# include "iGraphics.h"
# include "Startup.h"
# include "Procedure.h"
# include "Distance.h"
# include "Play.h"
# include "Search.h"
# include "Automate.h"

void iDraw()
{
	iClear();
	if (game_state == 0) {
		if(!build_state) buildup();

		if(!page) {
			iShowBMP(0, 0, "Pics\\wallpaper.bmp");
			iShowBMP(menu[0].x - 100, menu[arrow_indx].y, "Pics\\arrow5.bmp");
			for (int i = 0; i < 7; i++) iShowBMP(menu[i].x, menu[i].y, menu_directories[i]);
		}
		else if (page) {
			if (page == 2) {
				char s[10];
				iShowBMP(0, 0, "Pics\\clock.bmp");
				iSetColor(0, 0, 255);
				iText(Wframe / 2 - 320, Hframe / 2 + 260, "Type Desired Time in Seconds for Each Player and press SPACE", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 - strlen(tostr(s, set_time)) * 5, Hframe / 2 + 150, tostr(s, set_time), GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else if (page == 3) {
				iShowBMP(0, 0, "Pics\\inspic2.bmp");
			}
			else if (page == 4) {
				iSetColor(0, 0, 255);
				iText(Wframe / 2 - 320, Hframe / 2 + 260, "Press Z to play with 6 pieces", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 - 320, Hframe / 2 + 160, "Press X to play with 10 pieces", GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else if (page == 5) {
				iShowBMP(0, 0, "Pics\\s.bmp");
				iSetColor(31, 56, 115);
				iText(Wframe / 2 - 70, Hframe - 30, "HIGH SCORES", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(50, 200, "LARGE", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(50, 170, "BOARD", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(50, 600, "SMALL", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(50, 570, "BOARD", GLUT_BITMAP_TIMES_ROMAN_24);

				iText(Wframe / 2 - 190, Hframe / 2 + 300, "Name", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 - 20, Hframe / 2 + 300, "Color", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 + 125, Hframe / 2 + 300, "Moves", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 - 190, Hframe / 2 - 100, "Name", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 - 20, Hframe / 2 - 100, "Color", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(Wframe / 2 + 125, Hframe / 2 - 100, "Moves", GLUT_BITMAP_TIMES_ROMAN_24);
				
				for (int i = 0; i < 5; i++) {
					iSetColor(colors[high[i].color].red, colors[high[i].color].green, colors[high[i].color].blue);
					char s[100];
					iText(Wframe / 2 - 190, Hframe / 2 + 300 - (i + 1) * 50, high[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(Wframe / 2 - 20, Hframe / 2 + 300 - (i + 1) * 50, writecolor(high[i].color), GLUT_BITMAP_TIMES_ROMAN_24);
					iText(Wframe / 2 + 145, Hframe / 2 + 300 - (i + 1) * 50, tostr(s, high[i].moves), GLUT_BITMAP_TIMES_ROMAN_24);
				}
				for (int i = 5; i < 10; i++) {
					iSetColor(colors[high[i].color].red, colors[high[i].color].green, colors[high[i].color].blue);
					char s[100];
					iText(Wframe / 2 - 190, Hframe / 2 - 100 - (i - 4) * 50, high[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(Wframe / 2 - 20, Hframe / 2 - 100 - (i - 4) * 50, writecolor(high[i].color), GLUT_BITMAP_TIMES_ROMAN_24);
					iText(Wframe / 2 + 145, Hframe / 2 - 100 - (i - 4) * 50, tostr(s, high[i].moves), GLUT_BITMAP_TIMES_ROMAN_24);
				}
			}
			iShowBMP(menu[7].x, menu[7].y, "Pics\\main_menu.bmp");
		}
	}
	else if (game_state == 1) {
		build_state = 0;
		iShowBMP(0, 0, "Pics\\square5.bmp");
		iSetColor(255, 255, 255);
		if (!paused) saved = 0;
		if (paused) {
			iShowBMP(0, 0, "Pics\\pause.bmp");
			iText(Wframe - 290, Hframe - 20, "Press BACKSPACE to Exit Match", GLUT_BITMAP_HELVETICA_18);
			iText(10, Hframe - 50, "Press S to save game", GLUT_BITMAP_HELVETICA_18);
			if (saved) 	iText(10, Hframe - 80, "GAME SAVED!", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			int i, j, z;
			for (i = 0; i < 30; i++) {
				if (i % 2 == 0) {
					if (!hard) z = 30;
					else z = 22;
				}
				else z = 0;
				for (j = 0; j < 30; j++) {
					if (a[i][j] == 1) { // 1 means there is a circle here
						iSetColor(252, 225, 155);
						iCircle(z + xstart + j * length, ystart - i * height, radius);
					}
					else if (a[i][j] > 1) { // >1 means there is a piece here
						int c = a[i][j];
						iSetColor(colors[c - 5].red, colors[c - 5].green, colors[c - 5].blue);

						iFilledCircle(z + xstart + j * length, ystart - i * height, radius);
						if (i == yselect && j == xselect) { //selected piece
							iSetColor(255, 255, 255);
							iCircle(z + xstart + j * length, ystart - i * height, radius + 3); // circle indicating piece is selected
						}
					}
				}
			}
			for (i = 0; i < 6; i++) {
				iSetColor(colors[i].red, colors[i].green, colors[i].blue); // circle and color for "P" sign
				iCircle(player[i][0] + 6, player[i][1] + 9, 15);
				if (!gamestart && !computer[i]) { // selecting players before game start
					iLine(player[i][0] + 6 + 15, player[i][1] + 9, player[i][0] + 6 - 15, player[i][1] + 9);
					iLine(player[i][0] + 7, player[i][1] + 9 + 15, player[i][0] + 7, player[i][1] + 9 - 15);
				}
			}

			if (gamestart) {
				iSetColor(colors[now - 5].red, colors[now - 5].green, colors[now - 5].blue);
				double xtriangle[3], ytriangle[3], x = player[now - 5][0], y = player[now - 5][1];
				xtriangle[0] = x - 6, xtriangle[1] = x + 18, xtriangle[2] = x + 6;
				ytriangle[0] = y, ytriangle[1] = y, ytriangle[2] = y + 24;
				iFilledPolygon(xtriangle, ytriangle, 3);
				///iText(player[now - 5][0], player[now - 5][1], "P", GLUT_BITMAP_TIMES_ROMAN_24); // "P" sign
			}
			else {
				iSetColor(0, 0, 255);
				iText(130, Hframe - 40, "Click inside the circle to add player. Press SPACE to start game!", GLUT_BITMAP_HELVETICA_18);
			}

			iSetColor(0, 0, 0);
			iText(Wframe - 100, Hframe - 20, "Timer : ", GLUT_BITMAP_HELVETICA_18);
			char time_str[10];
			iText(Wframe - 40, Hframe - 20, tostr(time_str, remtime), GLUT_BITMAP_HELVETICA_18);
		}
		if (gamestart) {
			iText(10, Hframe - 20, "Press P to toggle Pause", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else if (game_state == 2) {
		iShowBMP(0, 0, "Pics\\square3.bmp");
		iSetColor(235, 235, 235);
		iText(Wframe / 2 - 68, Hframe / 2 + 250, "Game Over!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(Wframe / 2 - 140, Hframe / 2 + 200, "Position", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(Wframe / 2 - 30, Hframe / 2 + 200, "Color", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(Wframe / 2 + 60, Hframe / 2 + 200, "Moves", GLUT_BITMAP_TIMES_ROMAN_24);

		for (int i = 1; i <= 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (winner[j] == i) {
					char s[100];
					iSetColor(colors[j].red, colors[j].green, colors[j].blue);
					iText(Wframe / 2 - 140, Hframe / 2 + 200 - i * 50, tostr(s, winner[j]), GLUT_BITMAP_TIMES_ROMAN_24);
					iText(Wframe / 2 - 30, Hframe / 2 + 200 - i * 50, writecolor(j), GLUT_BITMAP_TIMES_ROMAN_24);
					iText(Wframe / 2 + 80, Hframe / 2 + 200 - i * 50, tostr(s, plmoves[j]), GLUT_BITMAP_TIMES_ROMAN_24);
				}
			}
		}
		iSetColor(0, 0, 0);
		iText(Wframe / 2 - 130, 50, "Press SPACE for MAIN MENU", GLUT_BITMAP_HELVETICA_18);
	}
	else if (game_state == 3) {
		iShowBMP(0, 0, "Pics\\square3.bmp");
		iSetColor(61, 76, 95);
		if (position.changed) {
			char s[100];
			strcpy(s, "Enter Name for Player ");
			strcat(s, writecolor(position.current));
			strcat(s, " & Press SPACE");
			iText(Wframe / 2 - 230, Hframe / 2 + 200, s, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(Wframe / 2 - strlen(high_name) * 5, Hframe / 2 - 50, high_name, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		iSetColor(0, 0, 0);
		iText(Wframe / 2 - 130, 50, "Press SPACE for MAIN MENU", GLUT_BITMAP_HELVETICA_18);
	}
}

void iMouse(int button, int state, int mx, int my)
{
	player_picked(button, state, mx, my);
}

void iMouseMove(int mx, int my) {}

void iKeyboard(unsigned char key)
{
	options(key);
}

void iSpecialKeyboard(unsigned char key) {
	options(key);
}

int main()
{
	//place your own initialization codes here. 
	tmove = iSetTimer(400, movement); // controls how fast pieces move
	overtime = iSetTimer(1000, timeup);
	iSetTimer(800, AImove); //controls how fast computer selects moves
	iSetTimer(10, decider);

	iPauseTimer(tmove); //initially there is no movement
	iPauseTimer(overtime);

	iInitialize(Wframe, Hframe, "STAR");
	return 0;
}