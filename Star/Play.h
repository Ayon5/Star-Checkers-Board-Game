int choose() // choosing the target positions for computer
{
	int i, limit;
	if (hard) limit = 10;
	else limit = 6;
	for (i = 0; i < limit; i++) {
		int p = finpos[now - 5][i][0], q = finpos[now - 5][i][1];
		if (a[p][q] != now) return i;
	}
	return -1; // -1 indicates this player has won the game. no target left to choose.
}

int stalemate(int x, int y) // checking possible options for after stalemate
{
	if (a[y][x] != now) return 0;
	int d = ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x);
	if (y % 2 == 0) {
		if (y > 0 && a[y - 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x) > d) { a[y - 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (y > 0 && a[y - 1][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x + 1) > d) { a[y - 1][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (x > 0 && a[y][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x - 1) > d) { a[y][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x + 1) > d) { a[y][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y + 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x) > d) { a[y + 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y + 1][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x + 1) > d) { a[y + 1][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
	}
	else {
		if (a[y - 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x) > d) { a[y - 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (x>0 && a[y - 1][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x - 1) > d) { a[y - 1][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (x>0 && a[y][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x - 1) > d) { a[y][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x + 1) > d) { a[y][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y + 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x) > d) { a[y + 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (x>0 && a[y + 1][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x - 1) > d) { a[y + 1][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
	}
	return 0;
}

int stale() // a rare case of target position mis-match
{
	int w = 0;
	if (choice == 0) {
		w = stalemate(finpos[now - 5][3][1], finpos[now - 5][3][0]);
		if (!w) w = stalemate(finpos[now - 5][5][1], finpos[now - 5][5][0]);
	}
	else if (choice == 1) {
		w = stalemate(finpos[now - 5][6][1], finpos[now - 5][6][0]);
		if (!w) w = stalemate(finpos[now - 5][8][1], finpos[now - 5][8][0]);
	}
	else if (choice == 2) {
		w = stalemate(finpos[now - 5][7][1], finpos[now - 5][7][0]);
		if (!w) w = stalemate(finpos[now - 5][9][1], finpos[now - 5][9][0]);
	}

	return w;
}

int check_winner()
{
	if (choose() < 0 && !winner[now - 5]) {
		int last = 0;
		for (int i = 0; i < 6; i++) {
			if (winner[i] > last) last = winner[i];
		}
		winner[now - 5] = last + 1;
		plmoves[now - 5] = movecnt / 6;
		if (last == 5) return 1;
	}
	return 0;
}

void reset() // changes current player
{
	iPauseTimer(overtime);
	xselect = -1, yselect = -1;
	selected = 0;
	if (check_winner()) {
		game_state = 2, gamestart = 0;
	}
	now++, movecnt++;
	if (now == 11) now = 5; //changes players from 5 to 10
	remtime = total_time;
	timerstart = 0;
	ps = 0;
	if (pos>0) iResumeTimer(tmove);
	else aidone = 1;
}

void timeup() // timer countdown
{
	if (!paused) remtime--;
	if (!remtime) {
		pos = 0;
		reset();
	}
}

void decider() // timer on
{
	if (!paused && gamestart && !computer[now - 5] && !timerstart && ps == pos) {
		timerstart = 1;
		iResumeTimer(overtime);
	}
}