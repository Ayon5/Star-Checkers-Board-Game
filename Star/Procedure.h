void placed(int ara[6][10][2], int pos, int cator[], int limit)
{
	int k = 0;
	for (int i = 0; i < limit; i++) {
		for (int j = 0; j < 2; j++) {
			ara[pos][i][j] = cator[k++];
		}
	}
}

void color_assign()
{
	FILE *colorf;
	fopen_s(&colorf, "Files/colors.txt", "r");
	for (int i = 0; i < 6; i++) {
		int r, g, b;
		fscanf_s(colorf, "%d %d %d", &r, &g, &b);
		colors[i].red = r;
		colors[i].blue = b;
		colors[i].green = g;
	}
	fclose(colorf);
}

void final_position_assign(int finpos[6][10][2]) // 6 piece-per-player board
{
	FILE *posf;
	fopen_s(&posf, "Files/final position.txt", "r");
	for (int i = 0; i < 6; i++) {
		int posara[30];
		for (int j = 0; j < 12; j++) {
			fscanf_s(posf, "%d", &posara[j]);
		}
		placed(finpos, i, posara, 6);
	}
	fclose(posf);
}

void final_position_assign2(int finpos[6][10][2]) // 10 piece-per-player board
{
	FILE *posf;
	fopen_s(&posf, "Files/final position2.txt", "r");
	for (int i = 0; i < 6; i++) {
		int posara[30];
		for (int j = 0; j < 20; j++) {
			fscanf_s(posf, "%d", &posara[j]);
		}
		placed(finpos, i, posara, 10);
	}
	fclose(posf);
}

void pic_position_assign()
{
	FILE *resf;
	fopen_s(&resf, "Files/picture resolution.txt", "r");
	for (int i = 0; i < 8; i++) {
		int x, y;
		fscanf_s(resf, "%d %d", &x, &y);
		picres[i].x = x;
		picres[i].y = y;
	}
	fclose(resf);
}

void menu_position_assign()
{
	FILE *menuf;
	fopen_s(&menuf, "Files/menu.txt", "r");
	for (int i = 0; i < 8; i++) {
		int x, y;
		fscanf_s(menuf, "%d %d", &x, &y);
		menu[i].x = x;
		menu[i].y = y;
	}
	fclose(menuf);
}

void player_position_assign(int player[6][2], int W, int H)
{
	player[0][0] = (3 * W) / 5, player[0][1] = 100; // "P" sign
	player[1][0] = 725, player[1][1] = (H) / 3;
	player[2][0] = 725, player[2][1] = (2 * H) / 3;
	player[3][0] = (3 * W) / 5, player[3][1] = 700;
	player[4][0] = 50, player[4][1] = (2 * H) / 3;
	player[5][0] = 50, player[5][1] = (H) / 3;
}

void directory_assign()
{
	FILE *menuf;
	fopen_s(&menuf, "Files/path.txt", "r");
	for (int i = 0; i < 8; i++) fscanf_s(menuf, "%s", menu_directories[i], _countof(menu_directories[i]));
	fclose(menuf);
}

void high_score_assign()
{
	FILE *highf;
	fopen_s(&highf, "Files/high score.txt", "r");
	for (int i = 0; i < 10; i++) {
		fscanf(highf, "%s %d %d", high[i].name, &high[i].moves, &high[i].color);
	}
	fclose(highf);
}

void high_score_rewrite()
{
	FILE *highf;
	fopen_s(&highf, "Files/high score.txt", "w");
	for (int i = 0; i < 10; i++) {
		fprintf(highf, "%s %d %d\n", high[i].name, high[i].moves, high[i].color);
	}
	fclose(highf);
}
void save_game()
{
	FILE *savef;
	fopen_s(&savef, "Files/savegame.txt", "w");
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			fprintf_s(savef, "%d ", a[i][j]);
		}
		fprintf_s(savef, "\n");
	}
	fprintf_s(savef, "\n");
	fprintf_s(savef, "%d %d %d %d %d\n", xselect, yselect, selected, xtarget, ytarget);
	for (int i = 0; i < 100; ++i) {
		fprintf_s(savef, "%d %d\n", route[i][0], route[i][1]);
	}
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			fprintf_s(savef, "%d ", done[i][j]);
		}
		fprintf_s(savef, "\n");
	}
	fprintf_s(savef, "%d %d %d\n", pos, ps, now);
	for (int i = 0; i < 6; ++i) {
		fprintf_s(savef, "%d ", computer[i]);
	}
	fprintf_s(savef, "\n");
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 10; ++j) {
			fprintf_s(savef, "%d %d\n", finpos[i][j][0], finpos[i][j][1]);
		}
	}
	fprintf_s(savef, "\n");
	for (int i = 0; i < 6; ++i) {
		fprintf_s(savef, "%d ", winner[6]);
	}
	fprintf_s(savef, "\n");
	for (int i = 0; i < 6; ++i) {
		fprintf_s(savef, "%d ", plmoves[i]);
	}
	fprintf_s(savef, "\n%d %d\n", movecnt, searchon);
	for (int i = 0; i < 5; ++i) {
		fprintf_s(savef, "%d ", diff[i]);
	}
	fprintf_s(savef, "\n%d %d %d %d %d %d %d %d %d %d %d\n", choice, aidone, gamestart, timerstart, placehigh, total_time, remtime, set_time, hard, length, height);
	fclose(savef);

}
void load_game()
{
	FILE *savef;
	fopen_s(&savef, "Files/savegame.txt", "r");
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			fscanf_s(savef, "%d ", &a[i][j]);
		}
	}
	fscanf_s(savef, "%d %d %d %d %d\n", &xselect, &yselect, &selected, &xtarget, &ytarget);
	for (int i = 0; i < 100; ++i) {
		fscanf_s(savef, "%d %d", &route[i][0], &route[i][1]);
	}
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			fscanf_s(savef, "%d ", &done[i][j]);
		}
	}
	fscanf_s(savef, "%d %d %d", &pos, &ps, &now);
	for (int i = 0; i < 6; ++i) {
		fscanf_s(savef, "%d ", &computer[i]);
	}
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 10; ++j) {
			fscanf_s(savef, "%d %d", &finpos[i][j][0], &finpos[i][j][1]);
		}
	}
	for (int i = 0; i < 6; ++i) {
		fscanf_s(savef, "%d ", &winner[6]);
	}
	for (int i = 0; i < 6; ++i) {
		fscanf_s(savef, "%d ", &plmoves[i]);
	}
	fscanf_s(savef, "%d %d", &movecnt, &searchon);
	for (int i = 0; i < 5; ++i) {
		fscanf_s(savef, "%d ", &diff[i]);
	}
	fscanf_s(savef, "%d %d %d %d %d %d %d %d %d %d %d", &choice, &aidone, &gamestart, &timerstart, &placehigh, &total_time, &remtime, &set_time, &hard, &length, &height);
	fclose(savef);

}
void buildup()
{
	if (!hard) {
		board(a);
		final_position_assign(finpos);
		length = 60, height = 52, radius = 12;
	}
	else {
		board2(a);
		final_position_assign2(finpos);
		length = 45, height = 39, radius = 12;
	}
	color_assign();
	pic_position_assign();
	menu_position_assign();
	player_position_assign(player, Wframe, Hframe);
	directory_assign();
	high_score_assign();
	now = 5, movecnt = 6;
	mposx = 0, mposy = 0;

	for (int i = 0; i < 6; i++) computer[i] = 1; //initially all are computer players
	for (int i = 0; i < 6; i++) winner[i] = 0;
	build_state = 1;
}

char* writecolor(int n)
{
	if (n == 0) return "Blue";
	else if (n == 1) return "Yellow";
	else if (n == 2) return "Violet";
	else if (n == 3) return "Red";
	else if (n == 4) return "Green";
	else return "Orange";
}

void page_change(int mposx, int mposy)
{
	if (page) {
		if (mposx >= menu[7].x && mposx <= menu[7].x + picres[7].x && mposy >= menu[7].y && mposy <= menu[7].y + picres[7].y) page = 0;
	}
	else {
		if (mposx >= menu[0].x && mposx <= menu[0].x + picres[0].x && mposy >= menu[0].y && mposy <= menu[0].y + picres[0].y) game_state = 1;
		else if (mposx >= menu[1].x && mposx <= menu[1].x + picres[1].x && mposy >= menu[1].y && mposy <= menu[1].y + picres[1].y) {
			load_game(), paused = 0, game_state = 1, gamestart=1, iResumeTimer(overtime);
		}
		else if (mposx >= menu[2].x && mposx <= menu[2].x + picres[2].x && mposy >= menu[2].y && mposy <= menu[2].y + picres[2].y) page = 2, arrow_indx = 2;
		else if (mposx >= menu[3].x && mposx <= menu[3].x + picres[3].x && mposy >= menu[3].y && mposy <= menu[3].y + picres[3].y) page = 3, arrow_indx = 3;
		else if (mposx >= menu[4].x && mposx <= menu[4].x + picres[4].x && mposy >= menu[4].y && mposy <= menu[4].y + picres[4].y) page = 4, arrow_indx = 4;
		else if (mposx >= menu[5].x && mposx <= menu[5].x + picres[5].x && mposy >= menu[5].y && mposy <= menu[5].y + picres[5].y) page = 5, arrow_indx = 5;
		else if (mposx >= menu[6].x && mposx <= menu[6].x + picres[6].x && mposy >= menu[6].y && mposy <= menu[6].y + picres[6].y) exit(0);
	}
}

int highscore(int i)
{
	if (i > 6) return 0;
	for (int j = 0; j < 6; j++) {
		if (winner[j] == i) {
			if (computer[j]) break;
			int l;
			if (hard) l = 5;
			else l = 0;
			for (int k = l; k < l + 5; k++) {
				if (plmoves[j] < high[k].moves) {
					for (int t = l + 4; t > k; t--) {
						high[t] = high[t - 1];
					}
					position.current = j;
					position.changed = k + 1;
					position.clockwise = i;
					return 1;
				}
			}
		}
	}
	return highscore(i + 1);
}

void options(unsigned char key) // keyboard use
{
	if (key == ' ') {
		if (game_state == 1) {
			gamestart = 1;
			aidone = 1;
		}
		else if (game_state == 2) {
			game_state = 3;
			placehigh = highscore(1);
			if (!placehigh) game_state = 0;
		}
		else if (game_state == 3) {
			position.changed--;
			strcpy(high[position.changed].name, high_name);
			high[position.changed].moves = plmoves[position.current];
			high[position.changed].color = position.current;

			position.changed = 0;
			high_name[0] = '\0';
			placehigh = highscore(position.clockwise + 1);
			if (!placehigh) {
				high_score_rewrite();
				game_state = 0;
			}
		}
	}
	
	if (!game_state) {
		if (!page && key == 13) {
			if (arrow_indx == 0) {
				game_state = 1;
			}
			else if (arrow_indx == 1) {
				load_game(), paused = 0, game_state = 1, iResumeTimer(overtime);
			}
			else {
				if (arrow_indx == 6) {
					exit(0);
				}
				page = arrow_indx;
			}
		}
		else if (page == 4) {
			if (key == 'z') hard = 0, page = 0;
			else if (key == 'x') hard = 1, page = 0;
			build_state = 0;
		}
		else if (page == 2) {
			if (key >= '0' && key <= '9') {
				int lsb = key - '0';
				if (set_time < 99999) {
					set_time *= 10;
					set_time += lsb;
				}
			
			}
			if (key == '\b') set_time /= 10;
			if (key == ' ') {						
				total_time = set_time;
				remtime = total_time;
				page = 0;
			}
		}
		else if (key == 27) page = 0;
		else if (key == GLUT_KEY_DOWN) {
			if (arrow_indx != 6) ++arrow_indx;
		}
		else if (key == GLUT_KEY_UP) {
			if (arrow_indx != 0) --arrow_indx;
		}
	}
	
	if (gamestart) {
		if (key == 'p')  paused ^= 1;
		else if (paused) {
			if (key == '\b') {
				page = 0;
				iPauseTimer(overtime);
				remtime = total_time;
				gamestart = 0;
				game_state = 0;
				paused = 0;
			}
			else if (key == 's') {
				save_game();
				saved = 1;
			}
		}
	}

	if (game_state == 3) {
		int l = strlen(high_name);
		if (key == '\b') {
			high_name[l - 1] = '\0';
		}
		else if (key != ' ' && l < 15) {
			high_name[l] = key;
			high_name[++l] = '\0';
		}
	}
}