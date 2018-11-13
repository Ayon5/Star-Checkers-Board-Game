# define Wframe 800
# define Hframe 800
# define xstart 120
# define ystart 710

int length, height, radius;
int a[30][30];  //a[] indicates position of circles
int xselect, yselect, selected = 0, xtarget, ytarget;
int route[100][2], done[30][30], pos, ps, now; // 'now' variable indicates current player 
int player[6][2], computer[6], finpos[6][10][2], winner[6], plmoves[6], movecnt; //player[] is position of triangle sign on screen //computer[i]=1 means computer is playing that piece //finpos is destination positions of each player
int searchon, diff[5], choice, aidone = 1; //aidone indicate computer's move is done
int gamestart = 0, timerstart = 0, placehigh = 0;
int total_time = 20, remtime = total_time, set_time, tmove, overtime;

int game_state = 0, build_state = 0, hard = 1;
int mposx = 0, mposy = 0, page = 0, paused = 0;
char menu_directories[10][50], high_name[100];
int arrow_indx = 0, arrow_indx2 = 0;
int istype = 0, saved = 0;

struct pic_pos 
{
	int x;
	int y;
} menu[10];

struct pic_res 
{
	int x;
	int y;
} picres[10];

struct rgb
{
	int red;
	int green;
	int blue;
} colors[6];

struct scores
{
	int moves;
	char name[100];
	int color;
} high[10];

struct high_change
{
	int current;
	int changed;
	int clockwise;
} position;

void board(int a[30][30]) //creating 6 piece-per-player board
{
	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 12; j++) {
			a[i][j] = 0;
		}
	}
	int s = 4, e = 5; // triangle one and its values
	for (i = 0; i < 10; i++) {
		for (j = s; j < e; j++) {
			if (i < 3) a[i][j] = 8;
			else if (i > 6 && j - s < i - 6) a[i][j] = 10;
			else if (i > 6 && e - j <= i - 6) a[i][j] = 6;
			else a[i][j] = 1;
		}
		if (i % 2) s--;
		else e++;
	}

	s = 4, e = 5; // triangle two and its values
	for (i = 12; i > 2; i--) {
		for (j = s; j < e; j++) {
			if (i > 9) a[i][j] = 5;
			else if (i < 6 && j - s < 6 - i) a[i][j] = 9;
			else if (i < 6 && e - j <= 6 - i) a[i][j] = 7;
			else a[i][j] = 1;
		}
		if (i % 2) s--;
		else e++;
	}
}

void board2(int a[30][30]) //creating 10 piece-per-player board
{
	int i, j;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			a[i][j] = 0;
		}
	}
	int s = 6, e = 7; // triangle one and its values
	for (i = 0; i < 13; i++) {
		for (j = s; j < e; j++) {
			if (i < 4) a[i][j] = 8;
			else if (i > 8 && j - s < i - 8) a[i][j] = 10;
			else if (i > 8 && e - j <= i - 8) a[i][j] = 6;
			else a[i][j] = 1;
		}
		if (i % 2) s--;
		else e++;
	}

	s = 6, e = 7; // triangle two and its values
	for (i = 16; i > 3; i--) {
		for (j = s; j < e; j++) {
			if (i > 12) a[i][j] = 5;
			else if (i < 8 && j - s < 8 - i) a[i][j] = 9;
			else if (i < 8 && e - j <= 8 - i) a[i][j] = 7;
			else a[i][j] = 1;
		}
		if (i % 2) s--;
		else e++;
	}
}
