void AImove() // computer's move
{
	if (paused || !aidone) return;
	else aidone = 0;

	if (gamestart && !computer[now - 5] && choose() < 0) {
		pos = 0;
		goto end;
	}
	if (gamestart && computer[now - 5] && ps == pos && !searchon) {
		searchon = 1; //search ongoing
					///		int delayvar = 200000000;
					///		while (delayvar) delayvar--;

		int i, j;
		for (i = 0; i < 5; i++) diff[i] = 0;
		choice = choose(); // choosing target positon
		if (choice < 0) { // this player's game is complete!!
			pos = 0;
			searchon = 0;
			goto end;
		}

		for (i = 0; i < 30; i++) { // loop to find this player's pieces
			for (j = 0; j < 30; j++) {
				if (a[i][j] == now) {
					int flag = 0;
					for (int k = 0; k < choice; k++) { // if piece at a[i][j] is already in a finpos[], skip that piece
						if (finpos[now - 5][k][0] == i && finpos[now - 5][k][1] == j) flag = 1;
					}
					if (flag) continue;

					memset(done, 0, 30 * 30 * sizeof done[0][0]);
					xtarget = 0, ytarget = 0;
					xselect = j, yselect = i;
					dfs(j, i, 0); // calculates and stores the best move so far
				}
			}
		}
		searchon = 0; // search complete
		int z = 0;

		if (diff[0] == 0) { // if there is no SKIPPING move
			pos = 0;
			for (i = 0; i < 30; i++) {
				for (j = 0; j < 30; j++) { // loop to find piece
					if (a[i][j] == now) {
						int flag = 0;
						for (int k = 0; k < choice; k++) {
							if (finpos[now - 5][k][0] == i && finpos[now - 5][k][1] == j) flag = 1;
						}
						if (flag) continue;

						z = bfs2(j, i); // checking one-step move
						if (z) break;
					}
				}
				if (z) break;
			}
			if (!z) { // used for stalemate() function
				stale();
			}
		}
		else {
			memset(route, 0, 100 * 2 * sizeof route[0][0]);
			memset(done, 0, 30 * 30 * sizeof done[0][0]);
			pos = 0;
			xselect = diff[1], yselect = diff[2], xtarget = diff[3], ytarget = diff[4]; //FINAL selection & target
			dfs(xselect, yselect, 0); // dfs is called again to store route[][]
		}

		///printf("%d = %d %d %d %d\n", diff[0], xselect, yselect, xtarget, ytarget);
	end: reset();
	}
}

void player_picked(int button, int state, int mx, int my) // player making move
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!game_state) page_change(mx, my);
		if (!paused && gamestart && !computer[now - 5]) { // computer is NOT playing this piece
			int y = (ystart - my + height / 2) / height; // calculating y coordinate from screen
			if (y >= 0 && y < 30) {
				int z;
				if (y % 2 == 0) {
					if (!hard) z = 30;
					else z = 22;
				}
				else z = 0;
				int x = (mx - xstart - z + length / 2) / length; // calculating x coordinate from screen
				if (x >= 0 && x < 30) {
					///printf("clicked: %d %d\n", x, y);
					if (a[y][x] == now) { // checks if a[y][x] is player's piece
						yselect = y;
						xselect = x;
						selected = 1; // a valid player piece is selected
					}
					else if (selected) { // if a piece is already selected, target is selected here
						ytarget = y;
						xtarget = x;
						int one = bfs1(xselect, yselect); // one-step move
														  ///printf("%d\n", one);
						if (one) {
							a[yselect][xselect] = 1;
							a[ytarget][xtarget] = now;
							pos = 0;
							reset();
						}
						else {
							memset(route, 0, 100 * 2 * sizeof route[0][0]);
							memset(done, 0, 15 * 15 * sizeof done[0][0]);
							pos = 0;
							dfs(xselect, yselect, 0);
							if (done[xtarget][ytarget]) { // if it is possible to go to selected positon with that piece
								reset();
							}
						}
					}
				}
			}
		}
		if (!gamestart) { // before gamestart, selecting players and computers
			for (int i = 0; i < 6; i++) {
				if (mx >= player[i][0] + 6 - 15 && mx <= player[i][0] + 6 + 15 && my >= player[i][1] + 9 - 15 && my <= player[i][1] + 9 + 15) computer[i] ^= 1;
			}
		}
	}
}

void movement() // moves pieces
{
	if (!paused) {
		int x, y, z;
		x = route[ps][0];
		y = route[ps][1];
		z = a[y][x];
		a[y][x] = 1;
		ps++; //piece movement by increasing ps in route[][] array

		x = route[ps][0];
		y = route[ps][1];
		a[y][x] = z;

		if (ps == pos) { //if ps is final pos, move completed
			aidone = 1; //move completed
			iPauseTimer(tmove); // movement timer pause
		}
	}
}