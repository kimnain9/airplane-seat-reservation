#include <iostream>
using namespace std;

/*
 비행기 좌석 예약 시스템

 좌석은 3개 구역으로 나뉘며,
 각 구역은 4행 6열 구조로 표현된다.

 사용자는 "몇열, 몇번째 좌석" 순서로 입력하므로
 입력은 열(col), 행(row) 순서로 받는다.
 배열은 출력과 이해를 쉽게 하기 위해 [구역][행][열] 구조로 관리한다.
*/

const int ZONE = 3;
const int ROW = 4;
const int COL = 6;

// 0 : 빈 좌석, 1 : 예약된 좌석
int seat[ZONE][ROW][COL] = { 0 };

// 총 예약 인원 누적
int totalAdult = 0;
int totalChild = 0;

/*
 구역 번호가 정상 범위인지 검사한다.
*/
bool isValidZone(int zone) {
    return zone >= 1 && zone <= 3;
}

/*
 행 번호가 정상 범위인지 검사한다.
*/
bool isValidRow(int row) {
    return row >= 1 && row <= 4;
}

/*
 열 번호가 정상 범위인지 검사한다.
*/
bool isValidCol(int col) {
    return col >= 1 && col <= 6;
}

/*
 구역, 행, 열이 모두 정상 범위인지 한 번에 검사한다.
*/
bool isValidSeat(int zone, int row, int col) {
    return isValidZone(zone) && isValidRow(row) && isValidCol(col);
}

/*
 프로그램 시작 시 메뉴를 출력한다.
*/
void printMenu() {
    cout << "**비행기 예약 시스템**" << endl;
    cout << "1.좌석 예약" << endl;
    cout << "2.좌석 변경" << endl;
    cout << "3.프로그램 종료" << endl;
    cout << "번호를 입력하세요 : ";
}

/*
 현재 좌석 상태를 출력한다.

 출력은 행을 기준으로 한 줄씩 보여주고,
 각 줄 안에서는 열 순서대로 좌석을 출력한다.
 가운데 통로를 표현하기 위해 3열 뒤에 공백을 추가한다.
*/
void printSeats() {
    for (int z = 0; z < ZONE; z++) {
        cout << "1 2 3   4 5 6 (" << z + 1 << "구역)" << endl;
        cout << "----------------" << endl;

        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {
                cout << seat[z][r][c] << " ";
                if (c == 2) {
                    cout << "  ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

/*
 좌석 예약 기능

 성인, 유아 인원을 입력받은 뒤
 총 인원 수만큼 좌석을 반복해서 예약한다.

 사용자는 "몇열, 몇번째 좌석" 순서로 입력하므로
 입력은 col, row 순서로 받는다.
 하지만 배열 저장은 [행][열] 구조이므로
 실제 저장할 때는 seat[구역][row][col] 형태로 넣는다.
*/
void reserveSeat() {
    int adult, child;
    int totalPeople;

    printSeats();

    cout << "성인(50000원): ";
    cin >> adult;
    cout << "유아(40000원): ";
    cin >> child;

    if (adult < 0 || child < 0) {
        cout << "인원 수는 음수가 될 수 없습니다." << endl;
        return;
    }

    totalPeople = adult + child;

    if (totalPeople == 0) {
        cout << "예약할 인원이 없습니다." << endl;
        return;
    }

    totalAdult += adult;
    totalChild += child;

    for (int i = 0; i < totalPeople; i++) {
        int zone, col, row;

        while (true) {
            cout << "어떤 구역을 예약 하시겠습니까?" << endl;
            cin >> zone;

            if (!isValidZone(zone)) {
                cout << "예약가능한 구역이 아닙니다." << endl;
                continue;
            }

            cout << "몇열, 몇번째 좌석을 예약하시겠습니까?" << endl;
            cin >> col >> row;

            if (!isValidSeat(zone, row, col)) {
                cout << "예약가능한 좌석이 아닙니다." << endl;
                continue;
            }

            if (seat[zone - 1][row - 1][col - 1] == 1) {
                cout << "이미 예약되었습니다. 다른 좌석을 선택하세요" << endl;
                continue;
            }

            seat[zone - 1][row - 1][col - 1] = 1;
            cout << "예약되었습니다." << endl;
            break;
        }
    }

    cout << endl;
    printSeats();
}

/*
 좌석 변경 기능

 현재 좌석과 변경 좌석도 동일하게
 구역, 열, 행 순서로 입력받는다.
 입력은 col, row 순서이지만 저장과 비교는 [행][열] 구조로 처리한다.
*/
void changeSeat() {
    int count;

    printSeats();

    cout << "바꿀 좌석의 갯수를 입력하세요 : ";
    cin >> count;

    if (count <= 0) {
        cout << "변경할 좌석 수가 올바르지 않습니다." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        int curZone, curCol, curRow;
        int newZone, newCol, newRow;

        while (true) {
            cout << "현재 좌석과 바꿀 좌석을 입력하세요" << endl;

            cout << "현재 좌석(H구역 , N열 , M번째): ";
            cin >> curZone >> curCol >> curRow;

            if (!isValidSeat(curZone, curRow, curCol)) {
                cout << "현재 좌석이 틀렸습니다. 다시 입력해주세요" << endl;
                continue;
            }

            if (seat[curZone - 1][curRow - 1][curCol - 1] == 0) {
                cout << "현재 좌석이 틀렸습니다. 다시 입력해주세요" << endl;
                continue;
            }

            cout << "변경 좌석(H구역 , N열 , M번째): ";
            cin >> newZone >> newCol >> newRow;

            if (!isValidSeat(newZone, newRow, newCol)) {
                cout << "좌석 번호를 다시 입력해주세요" << endl;
                continue;
            }

            if (curZone == newZone && curRow == newRow && curCol == newCol) {
                cout << "똑같은 좌석 입니다. 다른 좌석을 선택하세요" << endl;
                continue;
            }

            if (seat[newZone - 1][newRow - 1][newCol - 1] == 1) {
                cout << "이미 예약되었습니다. 다른 좌석을 선택하세요" << endl;
                continue;
            }

            seat[curZone - 1][curRow - 1][curCol - 1] = 0;
            seat[newZone - 1][newRow - 1][newCol - 1] = 1;

            cout << "변경되었습니다." << endl;
            break;
        }
    }

    cout << endl;
    printSeats();
}

/*
 메인 함수

 사용자가 3번을 입력할 때까지 메뉴를 반복하며,
 종료 시 누적 인원을 바탕으로 총 금액을 출력한다.
*/
int main() {
    int menu;

    while (true) {
        printMenu();
        cin >> menu;

        if (menu == 1) {
            reserveSeat();
        }
        else if (menu == 2) {
            changeSeat();
        }
        else if (menu == 3) {
            int totalPrice = totalAdult * 50000 + totalChild * 40000;
            cout << "총 " << totalPrice << "원 입니다." << endl;
            break;
        }
        else {
            cout << "올바른 번호를 입력해주세요." << endl << endl;
        }
    }

    return 0;
}