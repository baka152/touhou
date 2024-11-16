#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<Windows.h>
#include<time.h>
IMAGE lm[2];
IMAGE mls[2];
IMAGE bj[3];
IMAGE g1;
IMAGE ykl[2];
enum my
{
	WIDTH = 525,
	HIGH = 933,
	LMW = 116,
	LMH = 128,
	MLSW = 116,
	MLSH = 122,
	YKLW = 75,
	YKLH = 62,
	G1W = 260,
	G1H = 25
};
struct plane
{
	int x;
	int y;
}player1;
struct plane player2, ball1, ball2;
struct speed
{
	int x;
	int y;
}ball;
static void lodimg()
{
	loadimage(&lm[0], "./re/lm1.png");
	loadimage(&lm[1], "./re/lm2.png");
	loadimage(&mls[0], "./re/mls1.png");
	loadimage(&mls[1], "./re/mls2.png");
	loadimage(&bj[0], "./re/bj1.1.png");
	loadimage(&g1, "./re./g1.png");
	loadimage(&ykl[0], "./re/ykl1.png");
	loadimage(&ykl[1], "./re/ykl2.png");
}
static void gameinit()
{
	player1.x = LMW / 2;
	player1.y = LMH / 2;
	player2.x = WIDTH - MLSW / 2;
	player2.y = HIGH - MLSH / 2;
	ball2.x = WIDTH / 2;
	ball2.y = HIGH / 2;
	while (1)
	{
		srand((unsigned)time(NULL));
		ball.x = rand() % 10 - 5;
		if (abs(ball.x) >= 3) break;
	}
	while (1)
	{
		srand((unsigned)time(NULL));
		ball.y = rand() % 10 - 5;
		if (abs(ball.y) >= 3) break;
	}
}
static void gamedraw()
{
	lodimg();
	putimage(0, 0, &bj[0]);
	putimage(ball2.x - YKLW / 2, ball2.y - YKLH / 2, &ykl[1], NOTSRCERASE);
	putimage(ball2.x - YKLW / 2, ball2.y - YKLH / 2, &ykl[0], SRCINVERT);
	putimage(player1.x - LMW / 2, player1.y - LMH / 2, &lm[1], NOTSRCERASE);
	putimage(player1.x - LMW / 2, player1.y - LMH / 2, &lm[0], SRCINVERT);
	putimage(player1.x - G1W / 2, player1.y + LMH / 2, &g1);
	putimage(player2.x - MLSW / 2, player2.y - MLSH / 2, &mls[1], NOTSRCERASE);
	putimage(player2.x - MLSW / 2, player2.y - MLSH / 2, &mls[0], SRCINVERT);
	putimage(player2.x - G1W / 2, player2.y - G1H - MLSH / 2, &g1);
}
static void gamemovelm(int speed)
{
	if (GetAsyncKeyState('W') && player1.y >= LMH / 2)
	{
		player1.y -= speed;
	}
	if (GetAsyncKeyState('S') && player1.y <= HIGH / 2 - LMH / 2 - G1H)
	{
		player1.y += speed;
	}
	if (GetAsyncKeyState('A') && player1.x >= LMW / 2)
	{
		player1.x -= speed;
	}
	if (GetAsyncKeyState('D') && player1.x <= WIDTH - MLSW / 2)
	{
		player1.x += speed;
	}
}
static void gamemovemls(int speed)
{
	if (GetAsyncKeyState('I') && player2.y >= HIGH / 2 + MLSH / 2 + 26)
	{
		player2.y -= speed;
	}
	if (GetAsyncKeyState('K') && player2.y <= HIGH - MLSH / 2)
	{
		player2.y += speed;
	}
	if (GetAsyncKeyState('J') && player2.x >= MLSW / 2)
	{
		player2.x -= speed;
	}
	if (GetAsyncKeyState('L') && player2.x <= WIDTH - MLSW / 2)
	{
		player2.x += speed;
	}
}
static void collidejudge()
{
	if (ball2.x - YKLW / 2 + 5 <= 0 || ball2.x + YKLW / 2 - 5 >= WIDTH)
	{
		ball.x *= -1;
		ball2.x = ball1.x;
	}
	if (ball2.y - YKLH / 2 + 5 <= 0 || ball2.y + YKLH / 2 - 5 >= HIGH)
	{
		ball.y *= -1;
		ball2.y = ball1.y;
	}
	if (abs(ball2.y - player1.y - LMH / 2) <= G1H + 3 && abs(ball2.x - player1.x) <= G1W / 2)
	{
		ball.y *= -1;
		ball2.y = ball1.y;
	}
	if (abs(player2.y - MLSH / 2 - ball2.y) <= G1H + 3 && abs(ball2.x - player2.x) <= G1W / 2)
	{
		ball.y *= -1;
		ball2.y = ball1.y;
	}
}
static void gamemoveball()
{
	ball1.x = ball2.x;
	ball1.y = ball2.y;
	ball2.x += ball.x;
	ball2.y += ball.y;
	collidejudge();
}
int main()
{
	initgraph(WIDTH, HIGH);
	gameinit();
	BeginBatchDraw();
	while (1)
	{
		gamedraw();
		FlushBatchDraw();
		gamemovelm(6);
		gamemovemls(6);
		gamemoveball();
	}
	return 0;

}