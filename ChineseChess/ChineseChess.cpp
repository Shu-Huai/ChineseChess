#include <easyx.h>
#include <stdio.h>
#include <stdlib.h>

void firstmap(void);
void pmap(void);
void pmap_zhexian(int x, int y);
void pmap_qizi(int user, int number, int x, int y);
void pmap_allqizi(void);
int mousexy(void);
void hit(int player);
void pmap_xuanzhong(int x, int y);
int mouseleft(void);
void pmap_cleanxuanzhong(int x, int y);
void pmap_qipan(void);
int panding1(int x1, int y1, int x2, int y2);
int panding2(int x1, int y1, int x2, int y2);
int panding3(int x1, int y1, int x2, int y2);
int panding4(int x1, int y1, int x2, int y2);
int panding5(int x1, int y1, int x2, int y2);
int panding6(int x1, int y1, int x2, int y2);
int panding7(int x1, int y1, int x2, int y2);

int map[10][9][2];
int MOUSELEFT = 0;

int main(void)
{
    BOOL player = 0;
    firstmap();
    pmap();
    pmap_allqizi();
    //int x = mousexy();
    //pmap_qizi(1, 1, (x % 10)*100+47, 47 + (x / 10) * 100);//鼠标下棋
    while (1)
    {

        hit(player);
        cleardevice();
        pmap_qipan();
        pmap_allqizi();
        player = !player;
    }
}

void firstmap(void) //棋盘初始化  有问题
{
    for (int a = 0; a < 9; a++) //设置全部棋子归属
    {
        if (a < 4)
        {
            for (int b = 0; b < 9; b++)
            {
                map[a][b][0] = 1;
            }
        }
        if (a > 4)
        {
            for (int b = 0; b < 9; b++)
            {
                map[a][b][0] = 0;
            }
        }
    }

    for (int a = 0, b = 8; a < 9; a++, b--)
    {
        if (a < 5)
        {
            map[0][a][1] = a + 1;
            map[9][a][1] = a + 1;
        }
        else
        {
            map[0][a][1] = b + 1;
            map[9][a][1] = b + 1;
        }
    }

    map[2][1][1] = 6;
    map[2][7][1] = 6; //炮
    map[7][1][1] = 6;
    map[7][7][1] = 6;

    map[3][0][1] = 7;
    map[3][2][1] = 7;
    map[3][4][1] = 7;
    map[3][6][1] = 7;
    map[3][8][1] = 7; //卒
    map[6][0][1] = 8;
    map[6][2][1] = 8;
    map[6][4][1] = 8;
    map[6][6][1] = 8;
    map[6][8][1] = 8; //兵

    map[9][2][1] = 9;
    map[9][6][1] = 9; //象

    map[9][4][1] = 10; //帅
}

void pmap(void)
{
    initgraph(900, 1000);
    setbkcolor(RGB(204, 232, 207));
    cleardevice();

    pmap_qipan();
}

void pmap_qipan(void)
{
    setfillcolor(BLACK);
    for (int i = 0; i < 10; i++) //棋盘方框
    {
        solidrectangle(45, 45 + 100 * i, 849, 49 + 100 * i); //横
        solidrectangle(45 + 100 * i, 49, 49 + 100 * i, 949); //竖
    }
    clearrectangle(49, 449, 845, 545); //清理楚河汉界

    int shi_xiexian1[] = { 351, 47, 347, 51, 543, 247, 547, 243 }; //士的两条斜线  \\//顺序
    solidpolygon((POINT*)shi_xiexian1, 4);
    int shi_xiexian2[] = { 351, 747, 347, 751, 543, 947, 547, 943 };
    solidpolygon((POINT*)shi_xiexian2, 4);
    int shi_xiexian3[] = { 351, 251, 347, 247, 543, 43, 547, 47 };
    solidpolygon((POINT*)shi_xiexian3, 4);
    int shi_xiexian4[] = { 351, 951, 347, 947, 543, 743, 547, 747 };
    solidpolygon((POINT*)shi_xiexian4, 4);

    pmap_zhexian(147, 247);
    pmap_zhexian(747, 247);
    pmap_zhexian(847, 347);
    pmap_zhexian(647, 347);
    pmap_zhexian(447, 347);
    pmap_zhexian(247, 347);
    pmap_zhexian(47, 347); //炮 兵 折线
    pmap_zhexian(147, 747);
    pmap_zhexian(747, 747);
    pmap_zhexian(847, 647);
    pmap_zhexian(647, 647);
    pmap_zhexian(447, 647);
    pmap_zhexian(247, 647);
    pmap_zhexian(47, 647);
    clearrectangle(0, 0, 44, 999);
    clearrectangle(850, 0, 899, 999); //清理边界兵 折线

    RECT wenzi = { 49, 449, 845, 545 };
    settextstyle(66, 0, NULL);
    settextcolor(RED);
    drawtext(_T("楚河                    汉界"), &wenzi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void pmap_zhexian(int x, int y)
{
    solidrectangle(x + 5, y + 20, x + 10, y + 5);
    solidrectangle(x + 10, y + 10, x + 20, y + 5);
    solidrectangle(x + 5, y - 5, x + 10, y - 20);
    solidrectangle(x + 10, y - 5, x + 20, y - 10);
    solidrectangle(x - 10, y - 5, x - 5, y - 20);
    solidrectangle(x - 20, y - 5, x - 10, y - 10);
    solidrectangle(x - 10, y + 20, x - 5, y + 5);
    solidrectangle(x - 20, y + 10, x - 10, y + 5);
}

void pmap_cleanxuanzhong(int x, int y)
{
    clearrectangle(x - 45, y + 45, x - 40, y + 20);
    clearrectangle(x - 40, y + 45, x - 20, y + 40);
    clearrectangle(x + 40, y + 45, x + 45, y + 20);
    clearrectangle(x + 20, y + 45, x + 40, y + 40);
    clearrectangle(x - 45, y - 20, x - 40, y - 45);
    clearrectangle(x - 40, y - 40, x - 20, y - 45);
    clearrectangle(x + 40, y - 20, x + 45, y - 45);
    clearrectangle(x + 20, y - 40, x + 40, y - 45);
}

void pmap_qizi(int user, int number, int x, int y)
{
    setfillcolor(RGB(248, 226, 128)); //填充黄色
    fillcircle(x, y, 40);             //圆的半径

    RECT xy_qizi = { x - 20, y - 20, x + 20, y + 20 }; //文字区域坐标

    if (user == 0)
        settextcolor(RGB(255, 0, 0)); //获取用户ID
    else
        settextcolor(BLACK);

    setbkmode(TRANSPARENT); //文字背景设置为透明
    settextstyle(46, 0, NULL);
    switch (number)
    {
    case 1:
        drawtext(_T("车"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    case 2:
        drawtext(_T("马"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    case 3:
        drawtext(_T("象"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break; //红相黑象
    case 4:
        drawtext(_T("士"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    case 5:
        drawtext(_T("将"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break; //红帅黑将
    case 6:
        drawtext(_T("炮"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    case 7:
        drawtext(_T("卒"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break; //红兵黑卒
    case 8:
        drawtext(_T("兵"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    case 9:
        drawtext(_T("相"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    case 10:
        drawtext(_T("帅"), &xy_qizi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        break;
    }
}

void pmap_allqizi(void)
{
    for (int a = 0; a < 9; a++)
    {
        for (int b = 0; b < 10; b++)
        {
            if (map[b][a][1] != 0)
                pmap_qizi(map[b][a][0], map[b][a][1], 47 + a * 100, 47 + b * 100);
        }
    }
}

int mousexy(void)
{
    MOUSEMSG mousemg;
    mousemg = GetMouseMsg();
    Sleep(5); //直到鼠标左键按下
again:
    while (mousemg.mkLButton == false)
        mousemg = GetMouseMsg();
    Sleep(5);

    int x = mousemg.y / 100;
    int xx = mousemg.y % 100;
    int y = mousemg.x / 100;
    int yy = mousemg.x % 100;
    mousemg.mkLButton = false;
    if (xx > 87 || xx < 7)
        goto again;
    if (yy > 87 || yy < 7)
        goto again;

    return 10 * x + y;
}

void hit(int player)
{
    int x1 = 0;
    int y1 = 0;

jump1:
    x1 = mousexy();
    y1 = x1 % 10;
    x1 /= 10;

    while (1)
    {
        if (map[x1][y1][1] != 0 && map[x1][y1][0] == player)
            break; //直到获取到一个可用的选中坐标
        x1 = mousexy();
        y1 = x1 % 10;
        x1 /= 10;
    }
    pmap_xuanzhong(47 + 100 * y1, 47 + 100 * x1); //数组交换坐标

    /* 开始进行第二次坐标获取 */

    int x2 = 0;
    int y2 = 0;

getmouse:
    x2 = mouseleft();

    if (x2 == -1)
    {
        pmap_cleanxuanzhong(47 + 100 * y1, 47 + 100 * x1);
        goto jump1;
    }
    y2 = x2 % 10;
    x2 /= 10;

    switch (map[x1][y1][1])
    {
    case 1:
        if (panding1(x1, y1, x2, y2))
            goto next;
        goto getmouse; //
    case 2:
        if (panding2(x1, y1, x2, y2))
            goto next;
        goto getmouse; //
    case 3:
        if (panding3(x1, y1, x2, y2))
            goto next;
        goto getmouse; //
    case 4:
        if (panding4(x1, y1, x2, y2))
            goto next;
        goto getmouse; //
    case 5:
        if (panding5(x1, y1, x2, y2))
            goto next;
        goto getmouse; //帅
    case 6:
        if (panding6(x1, y1, x2, y2))
            goto next;
        goto getmouse; //炮
    case 7:
        if (panding7(x1, y1, x2, y2))
            goto next;
        goto getmouse; //兵
    case 8:
        if (panding7(x1, y1, x2, y2))
            goto next;
        goto getmouse; //兵
    case 9:
        if (panding3(x1, y1, x2, y2))
            goto next;
        goto getmouse; //象
    case 10:
        if (panding5(x1, y1, x2, y2))
            goto next;
        goto getmouse; //将
    }

next:
    map[x2][y2][0] = map[x1][y1][0];
    map[x2][y2][1] = map[x1][y1][1];
    map[x1][y1][1] = 0;
}

void pmap_xuanzhong(int x, int y)
{
    setfillcolor(GREEN);
    solidrectangle(x - 45, y + 45, x - 40, y + 20);
    solidrectangle(x - 40, y + 45, x - 20, y + 40);
    solidrectangle(x + 40, y + 45, x + 45, y + 20);
    solidrectangle(x + 20, y + 45, x + 40, y + 40);
    solidrectangle(x - 45, y - 20, x - 40, y - 45);
    solidrectangle(x - 40, y - 40, x - 20, y - 45);
    solidrectangle(x + 40, y - 20, x + 45, y - 45);
    solidrectangle(x + 20, y - 40, x + 40, y - 45);
}

int mouseleft(void)
{
    MOUSEMSG mouselr;
    MOUSELEFT = 0;
    mouselr = GetMouseMsg();
    Sleep(5);
againx:
    while ((mouselr.mkLButton == false) && (mouselr.mkRButton == false))
    {
        mouselr = GetMouseMsg();
        Sleep(5);
    }
    if (mouselr.mkRButton)
    {
        MOUSELEFT = 1;
        return -1;
    }
    int x = mouselr.y / 100;
    int xx = mouselr.y % 100;
    int y = mouselr.x / 100;
    int yy = mouselr.x % 100;
    mouselr.mkLButton = false;
    if (xx > 87 || xx < 7)
        goto againx;
    if (yy > 87 || yy < 7)
        goto againx;

    return 10 * x + y;
}

int panding1(int x1, int y1, int x2, int y2)
{
    int qx = ((x1 >= x2) ? -1 : 1);
    int qy = ((y1 >= y2) ? -1 : 1);
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0; //不是原点  目标点归属不为自己或为自己但是空
    if (x1 == x2)
    {
        for (int a = 1, b = 0; a < (b = ((y1 > y2) ? (y1 - y2) : (y2 - y1))); a++) //两点之间为空
        {
            if (map[x1][y1 + qy * a][1] != 0)
                return 0;
        }
        if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
            return 0;
        return 1;
    }
    else if (y1 == y2)
    {
        for (int a = 1, b = 0; a < (b = ((x1 > x2) ? (x1 - x2) : (x2 - x1))); a++)
        {

            if (map[x1 + qx * a][y1][1] != 0)
                return 0;
        }
        return 1;
    }
    else
        return 0;
}

int panding2(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0;

    if (x2 - x1 == 2)
    {
        if (y1 - y2 == 1 || y2 - y1 == 1)
        {
            if (map[x1 + 1][y1][1] != 0)
                return 0;
            return 1;
        }

        return 0;
    }
    if (x2 - x1 == -2)
    {
        if (y1 - y2 == 1 || y2 - y1 == 1)
        {
            if (map[x1 - 1][y1][1] != 0)
                return 0;
            return 1;
        }
        return 0;
    }
    if (y2 - y1 == 2)
    {
        if (x1 - x2 == 1 || x2 - x1 == 1)
        {
            if (map[x1][y1 + 1][1] != 0)
                return 0;
            return 1;
        }

        return 0;
    }
    if (y2 - y1 == -2)
    {
        if (x1 - x2 == 1 || x2 - x1 == 1)
        {
            if (map[x1][y1 - 1][1] != 0)
                return 0;
            return 1;
        }

        return 0;
    }

    return 0;
}

int panding3(int x1, int y1, int x2, int y2) //象 相
{
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0;

    if (map[x1][y1][0] == 0)
    {
        if (x2 <= 4)
            return 0;

        if (x2 - x1 == 2 && y2 - y1 == 2)
        {
            if (map[x1 + 1][y1 + 1][1] == 0)
                return 1;
            return 0;
        }
        if (x2 - x1 == -2 && y2 - y1 == 2)
        {
            if (map[x1 - 1][y1 + 1][1] == 0)
                return 1;
            return 0;
        }
        if (x2 - x1 == -2 && y2 - y1 == -2)
        {
            if (map[x1 - 1][y1 - 1][1] == 0)
                return 1;
            return 0;
        }
        if (x2 - x1 == 2 && y2 - y1 == -2)
        {
            if (map[x1 + 1][y1 - 1][1] == 0)
                return 1;
            return 0;
        }
        return 0;
    }
    if (map[x1][y1][0] == 1)
    {
        if (x2 >= 5)
            return 0;

        if (x2 - x1 == 2 && y2 - y1 == 2)
        {
            if (map[x1 + 1][y1 + 1][1] == 0)
                return 1;
            return 0;
        }
        if (x2 - x1 == -2 && y2 - y1 == 2)
        {
            if (map[x1 - 1][y1 + 1][1] == 0)
                return 1;
            return 0;
        }
        if (x2 - x1 == -2 && y2 - y1 == -2)
        {
            if (map[x1 - 1][y1 - 1][1] == 0)
                return 1;
            return 0;
        }
        if (x2 - x1 == 2 && y2 - y1 == -2)
        {
            if (map[x1 + 1][y1 - 1][1] == 0)
                return 1;
            return 0;
        }
        return 0;
    }
    return 0;
}

int panding4(int x1, int y1, int x2, int y2) //士
{
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0;

    //范围限制
    if (y2 > 5 || y2 < 3)
        return 0;
    if (map[x1][y1][0] == 0)
    {
        if (x2 <= 6)
            return 0;
    }
    if (map[x1][y1][0] == 1)
    {
        if (x2 > 2)
            return 0;
    }

    if (x2 - x1 == 1 && y2 - y1 == 1)
        return 1;
    if (x2 - x1 == -1 && y2 - y1 == -1)
        return 1;
    if (x2 - x1 == -1 && y2 - y1 == 1)
        return 1;
    if (x2 - x1 == 1 && y2 - y1 == -1)
        return 1;

    return 0;
}

int panding5(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0;

    if (y2 > 5 || y2 < 3)
        return 0;
    if (map[x1][y1][0] == 0)
    {
        if (x2 <= 6)
            return 0;
    }
    if (map[x1][y1][0] == 1)
    {
        if (x2 > 2)
            return 0;
    }

    if (x2 - x1 == 1 && y2 - y1 == 0)
        return 1;
    if (x2 - x1 == 0 && y2 - y1 == -1)
        return 1;
    if (x2 - x1 == -1 && y2 - y1 == 0)
        return 1;
    if (x2 - x1 == 0 && y2 - y1 == 1)
        return 1;

    return 0;
}

int panding6(int x1, int y1, int x2, int y2) //炮
{
    int t = 0;
    int qx = ((x1 >= x2) ? -1 : 1);
    int qy = ((y1 >= y2) ? -1 : 1);
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0; //不是原点  目标点归属不为自己或为自己但是空
    if (x1 == x2)
    {
        for (int a = 1, b = 0; a < (b = ((y1 > y2) ? (y1 - y2) : (y2 - y1))); a++) //两点之间为空
        {
            if (map[x1][y1 + qy * a][1] != 0)
                t++;
        }
        if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
            return 0;
        if (t >= 2)
            return 0;
        if (t == 1 && map[x2][y2][1] == 0)
            return 0;
        if (t == 0 && map[x2][y2][1] != 0)
            return 0;
        return 1;
    }
    else if (y1 == y2)
    {
        for (int a = 1, b = 0; a < (b = ((x1 > x2) ? (x1 - x2) : (x2 - x1))); a++)
        {

            if (map[x1 + qx * a][y1][1] != 0)
                t++;
        }
        if (t >= 2)
            return 0;
        if (t == 1 && map[x2][y2][1] == 0)
            return 0;
        if (t == 0 && map[x2][y2][1] != 0)
            return 0;

        return 1;
    }
    else
        return 0;
}

int panding7(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return 0;
    if (map[x2][y2][0] == map[x1][y1][0] && map[x2][y2][1] != 0)
        return 0;

    if (map[x1][y1][0] == 1)
    {
        if ((x2 - x1) < 0)
            return 0;
        if (x1 <= 4)
        {
            if (x2 - x1 == 1 && y2 - y1 == 0)
                return 1;
            //		if (x2 - x1 == 0 && y2 - y1 == -1)return 1;
            //		if (x2 - x1 == -1 && y2 - y1 == 0)return 1;
            //		if (x2 - x1 == 0 && y2 - y1 == -1)return 1;
            return 0;
        }
        if (x2 - x1 == 1 && y2 - y1 == 0)
            return 1;
        if (x2 - x1 == 0 && y2 - y1 == -1)
            return 1;
        //		if (x2 - x1 == -1 && y2 - y1 == 0)return 1;
        if (x2 - x1 == 0 && y2 - y1 == 1)
            return 1;
        return 0;
    }

    if (map[x1][y1][0] == 0)
    {
        if ((x2 - x1) > 0)
            return 0;
        if (x1 >= 5)
        {
            //			if (x2 - x1 == 1 && y2 - y1 == 0)return 1;
            //			if (x2 - x1 == 0 && y2 - y1 == -1)return 1;
            if (x2 - x1 == -1 && y2 - y1 == 0)
                return 1;
            //			if (x2 - x1 == 0 && y2 - y1 == -1)return 1;
            return 0;
        }
        //		if (x2 - x1 == 1 && y2 - y1 == 0)return 1;
        if (x2 - x1 == 0 && y2 - y1 == 1)
            return 1;
        if (x2 - x1 == -1 && y2 - y1 == 0)
            return 1;
        if (x2 - x1 == 0 && y2 - y1 == -1)
            return 1;
        return 0;
    }

    return 0;
}