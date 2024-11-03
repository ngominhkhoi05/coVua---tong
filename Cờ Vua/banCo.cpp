#pragma once
#include "banCo.h"

void nhapBC(quanCo* BC[][8]) {
    for (int i = 0; i < 8; i++) {
        BC[1][i] = new chot(1);
        BC[6][i] = new chot(0);
    }
    BC[0][0] = BC[0][7] = new xe(1);

    BC[7][0] = BC[7][7] = new xe(0);

    BC[0][1] = BC[0][6] = new ma(1);

    BC[7][1] = BC[7][6] = new ma(0);

    BC[0][2] = BC[0][5] = new tuong(1);

    BC[7][2] = BC[7][5] = new tuong(0);

    BC[0][3] = new hau(1);

    BC[7][3] = new hau(0);

    BC[0][4] = new vua(1);

    BC[7][4] = new vua(0);
}

void xuatBC(quanCo* BC[][8]) {
    cout << "     a    b    c    d    e    f    g    h\n";
    cout << "  +----+----+----+----+----+----+----+----+\n";
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << " |";
        for (int j = 0; j < 8; j++) {
            if (!BC[i][j])
                cout << "    |";
            else
                if (BC[i][j]->kiemTraMau())
                    cout << " " << BC[i][j]->getName() << "t |";
                else
                    cout << " " << BC[i][j]->getName() << "d |";
        }
        cout << " " << i + 1;
        cout << endl;
        cout << "  +----+----+----+----+----+----+----+----+\n";
    }
    cout << "     a    b    c    d    e    f    g    h\n";
}

bool kiemTraAn(int x, int y, int xNew, int yNew, quanCo* BC[][8]) {
    if (BC[x][y]->kiemTraMau() == BC[xNew][yNew]->kiemTraMau()) return 0;
    return 1;
}

bool getMau(int x, int y, quanCo* BC[][8]) {
    return BC[x][y]->kiemTraMau();
}

bool getQuanCo(int x, int y, quanCo* BC[][8]) {
    return BC[x][y]->kiemTraQuanCo();
}

void nhapThanh(int x, int y, int xNew, int yNew, quanCo* BC[][8]){
    delete BC[xNew][yNew];
    BC[xNew][yNew] = BC[x][y];
    BC[x][y] = NULL;
    if (yNew > y) {
        BC[x][5] = BC[x][7];
        BC[x][7] = NULL;
    }
    else {
        BC[x][3] = BC[x][0];
        BC[x][0] = NULL;
    }
}

void phong(int x, int y, int xNew, int yNew, quanCo* BC[][8]) {
    cout << "moi ban chon quan muon phong\n";
    cout << "1. hau\n";
    cout << "2. xe\n";
    cout << "3. ma\n";
    cout << "4. tuong\n";
    int n;
    cin >> n;
    switch (n)
    {
    case 1:
        delete BC[xNew][yNew];
        BC[xNew][yNew] = new hau(getMau(x, y, BC));
        delete BC[x][y];
        BC[x][y] = NULL;
        break;
    case 2:
        delete BC[xNew][yNew];
        BC[xNew][yNew] = new xe(getMau(x, y, BC));
        delete BC[x][y];
        BC[x][y] = NULL;
        break;
    case 3:
        delete BC[xNew][yNew];
        BC[xNew][yNew] = new ma(getMau(x, y, BC));
        delete BC[x][y];
        BC[x][y] = NULL;
        break;
    case 4:
        delete BC[xNew][yNew];
        BC[xNew][yNew] = new tuong(getMau(x, y, BC));
        delete BC[x][y];
        BC[x][y] = NULL;
        break;
    default:
        break;
    }
}

void setQuanCo(int x, int y, int xNew, int yNew, quanCo* BC[][8]) {
    delete BC[xNew][yNew];
    BC[xNew][yNew] = BC[x][y];
    BC[x][y] = NULL;
}



bool kiemTraChieu(int x, int y, quanCo* BC[][8]) {
    // Tren
    for (int i = x; i >= 0; i--) {
        if (BC[i][y]) {
            if (BC[i][y]->getName() == 'H' || BC[i][y]->getName() == 'X') {
                if (BC[i][y]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Duoi
    for (int i = x; i <= 7; i++) {
        if (BC[i][y]) {
            if (BC[i][y]->getName() == 'H' || BC[i][y]->getName() == 'X') {
                if (BC[i][y]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Phai
    for (int i = y; i <= 7; i++) {
        if (BC[x][i]) {
            if (BC[x][i]->getName() == 'H' || BC[x][i]->getName() == 'X') {
                if (BC[x][i]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Trai
    for (int i = y; i >= 0; i--) {
        if (BC[x][i]) {
            if (BC[x][i]->getName() == 'H' || BC[x][i]->getName() == 'X') {
                if (BC[x][i]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Tren trai
    int i = x, j = y;
    while (i > 0 && j > 0) {
        i--;
        j--;
        if (BC[i][j]) {
            if (BC[i][j]->getName() == 'H' || BC[i][j]->getName() == 'T') {
                if (BC[i][j]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Tren phai
    i = x, j = y;
    while (i > 0 && j < 7) {
        i--;
        j++;
        if (BC[i][j]) {
            if (BC[i][j]->getName() == 'H' || BC[i][j]->getName() == 'T') {
                if (BC[i][j]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Duoi phai
    i = x, j = y;
    while (i < 7 && j < 7) {
        i++;
        j++;
        if (BC[i][j]) {
            if (BC[i][j]->getName() == 'H' || BC[i][j]->getName() == 'T') {
                if (BC[i][j]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Duoi trai
    i = x, j = y;
    while (i < 7 && j > 0) {
        i++;
        j--;
        if (BC[i][j]) {
            if (BC[i][j]->getName() == 'H' || BC[i][j]->getName() == 'T') {
                if (BC[i][j]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            }
            break;
        }
    }

    // Ma
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (abs(dx) + abs(dy) == 3) {
                int newX = x + dx;
                int newY = y + dy;
                if (newX >= 0 && newX <= 7 && newY >= 0 && newY <= 7 && BC[newX][newY]) {
                    if (BC[newX][newY]->getName() == 'M' && BC[newX][newY]->kiemTraMau() != BC[x][y]->kiemTraMau()) {
                        return 0;
                    }
                }
            }
        }
    }

    // Kiem tra vua
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (abs(dx) + abs(dy) == 1) {
                int newX = x + dx;
                int newY = y + dy;
                if (newX >= 0 && newX <= 7 && newY >= 0 && newY <= 7 && BC[newX][newY]) {
                    if (BC[newX][newY]->getName() == 'V' && BC[newX][newY]->kiemTraMau() != BC[x][y]->kiemTraMau()) {
                        return 0;
                    }
                }
            }
        }
    }

    // Kiem tra chot
    if (BC[x][y]->kiemTraMau()) {
        if (x + 1 <= 7) {
            if(BC[x + 1][y - 1])
                if (y - 1 >= 0 && BC[x + 1][y - 1]->getName() == 'C' && BC[x + 1][y - 1]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            if(BC[x + 1][y + 1])
                if (y + 1 <= 7 && BC[x + 1][y + 1]->getName() == 'C' && BC[x + 1][y + 1]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
        }
    }
    else {
        if (x - 1 >= 0) {
            if (BC[x - 1][y - 1])
                if (y - 1 >= 0 && BC[x - 1][y - 1]->getName() == 'V' && BC[x - 1][y - 1]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
            if (BC[x - 1][y + 1])
                if (y + 1 <= 7 && BC[x - 1][y + 1]->getName() == 'V' && BC[x - 1][y + 1]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
        }
    }
    return 1;
}

bool kiemTraChieuXungQuanh(int x, int y, quanCo* BC[][8]) {
    int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX <= 7 && newY >= 0 && newY <= 7) {
            if (kiemTraChieu(newX, newY, BC) && !BC[newX][newY]->kiemTraQuanCo())
                return 0;
            else if (kiemTraChieu(newX, newY, BC) && BC[newX][newY]->kiemTraQuanCo())
                if (BC[newX][newY]->kiemTraMau() != BC[x][y]->kiemTraMau())
                    return 0;
        }
    }
    return 1;
}