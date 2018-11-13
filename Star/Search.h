int bfs1(int x, int y) //determining if player can move the piece from (x,y) to (xtaget,ytarget) which is only ONE step away
{
	// if y is even , a[y-1][x] is on the upper-left side of a[y][x]
	if (y % 2 == 0) {
		if (y>0 && a[y - 1][x] == 1 && xtarget == x && ytarget == y - 1)  return 1;
		if (y>0 && a[y - 1][x + 1] == 1 && xtarget == x + 1 && ytarget == y - 1)  return 1;
		if (x>0 && a[y][x - 1] == 1 && xtarget == x - 1 && ytarget == y)  return 1;
		if (a[y][x + 1] == 1 && xtarget == x + 1 && ytarget == y)  return 1;
		if (a[y + 1][x] == 1 && xtarget == x && ytarget == y + 1)  return 1;
		if (a[y + 1][x + 1] == 1 && xtarget == x + 1 && ytarget == y + 1)  return 1;
	}
	else {
		if (a[y - 1][x] == 1 && xtarget == x && ytarget == y - 1)  return 1;
		if (x>0 && a[y - 1][x - 1] == 1 && xtarget == x - 1 && ytarget == y - 1)  return 1;
		if (x>0 && a[y][x - 1] == 1 && xtarget == x - 1 && ytarget == y)  return 1;
		if (a[y][x + 1] == 1 && xtarget == x + 1 && ytarget == y)  return 1;
		if (a[y + 1][x] == 1 && xtarget == x && ytarget == y + 1)  return 1;
		if (x>0 && a[y + 1][x - 1] == 1 && xtarget == x - 1 && ytarget == y + 1)  return 1;
	}
	return 0;
}

int bfs2(int x, int y) //computer's ONE-step move
{
	int choice = choose();
	int d = ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x); // d is used to measure in the following if cases, whether going one-step in any direction, DECREASES the distance of the piece and finpos[][];
	if (y % 2 == 0) {
		if (y > 0 && a[y - 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x) < d) { a[y - 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (y > 0 && a[y - 1][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x + 1) < d) { a[y - 1][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (x > 0 && a[y][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x - 1) < d) { a[y][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x + 1) < d) { a[y][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y + 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x) < d) { a[y + 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y + 1][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x + 1) < d) { a[y + 1][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
	}
	else {
		if (a[y - 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x) < d) { a[y - 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (x>0 && a[y - 1][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y - 1, x - 1) < d) { a[y - 1][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (x>0 && a[y][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x - 1) < d) { a[y][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y][x + 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x + 1) < d) { a[y][x + 1] = a[y][x]; a[y][x] = 1; return 1; }
		if (a[y + 1][x] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x) < d) { a[y + 1][x] = a[y][x]; a[y][x] = 1; return 1; }
		if (x>0 && a[y + 1][x - 1] == 1 && ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y + 1, x - 1) < d) { a[y + 1][x - 1] = a[y][x]; a[y][x] = 1; return 1; }
	}
	return 0;
}


void dfs(int x, int y, int p) // JUMP MOVE DEPTH-FIRST-SEARCH
{
	if (done[x][y]) return;
	if (done[xtarget][ytarget]) return;
	route[p][0] = x; //route[][] contains the dfs positions later used to move the selected piece
	route[p][1] = y;
	done[x][y] = 1;
	if (x == xtarget && y == ytarget) {
		///printf("yes %d %d\n", x, y);
		pos = p;
		return;
	}
	if (searchon) { // searchon=1 means computer is searching
		int choice = choose();
		int d = ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], yselect, xselect) - ds(finpos[now - 5][choice][0], finpos[now - 5][choice][1], y, x); // this d is how much distance is DECREASED. The higher d is, the better the move is.
																																								 ///printf("%d\n", d);
		if (d > diff[0]) {
			diff[0] = d; //new maximum move d
			diff[1] = xselect, diff[2] = yselect; // piece that will be selected to move
			diff[3] = x, diff[4] = y; // new target positon
		}
	}
	if (y % 2 == 0) {
		if (y - 2 >= 0 && a[y - 1][x] > 1 && a[y - 2][x - 1] == 1)  dfs(x - 1, y - 2, p + 1);
		if (y - 2 >= 0 && a[y - 1][x + 1] > 1 && a[y - 2][x + 1] == 1)  dfs(x + 1, y - 2, p + 1);
		if (x - 2 >= 0 && a[y][x - 1] > 1 && a[y][x - 2] == 1)  dfs(x - 2, y, p + 1);
		if (x + 2 < 12 && a[y][x + 1] > 1 && a[y][x + 2] == 1)  dfs(x + 2, y, p + 1);
		if (y + 2 < 15 && a[y + 1][x] > 1 && a[y + 2][x - 1] == 1)  dfs(x - 1, y + 2, p + 1);
		if (y + 2 < 15 && a[y + 1][x + 1] > 1 && a[y + 2][x + 1] == 1)  dfs(x + 1, y + 2, p + 1);
	}
	else {
		if (y - 2 >= 0 && a[y - 1][x] > 1 && a[y - 2][x + 1] == 1)  dfs(x + 1, y - 2, p + 1);
		if (y - 2 >= 0 && a[y - 1][x - 1] > 1 && a[y - 2][x - 1] == 1)  dfs(x - 1, y - 2, p + 1);
		if (x - 2 >= 0 && a[y][x - 1] > 1 && a[y][x - 2] == 1)  dfs(x - 2, y, p + 1);
		if (x + 2 < 12 && a[y][x + 1] > 1 && a[y][x + 2] == 1)  dfs(x + 2, y, p + 1);
		if (y + 2 < 15 && a[y + 1][x] > 1 && a[y + 2][x + 1] == 1) dfs(x + 1, y + 2, p + 1);
		if (y + 2 < 15 && a[y + 1][x - 1] > 1 && a[y + 2][x - 1] == 1) dfs(x - 1, y + 2, p + 1);
	}
}