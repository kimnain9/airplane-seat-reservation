#include <iostream>
using namespace std;

// 구역, 행, 열의 크기를 상수로 선언
const int ZONE = 3;
const int ROW = 4;
const int COL = 6;

// 좌석 상태를 저장하는 3차원 배열
// 0이면 빈 좌석, 1이면 예약된 좌석
int seat[ZONE][ROW][COL] = { 0 };

// 성인, 유아 인원 수 누적 저장
int totalAdult = 0;
int totalChild = 0;

// 구역 번호가 유효한지 확인하는 함수
bool isValidZone(int zone) {
    return zone >= 1 && zone <= 3;
}

// 행 번호가 유효한지 확인하는 함수
bool isValidRow(int row) {
    return row >= 1 && row <= 4;
}

// 열 번호가 유효한지 확인하는 함수
bool isValidCol(int col) {
    return col >= 1 && col <= 6;
}

// 구역, 행, 열이 모두 유효한지 한 번에 확인하는 함수
bool isValidSeat(int zone, int row, int col) {
    return isValidZone(zone) && isValidRow(row) && isValidCol(col);
}

// 메뉴를 출력하는 함수
void printMenu() {
    cout << "**비행기 예약 시스템**" << endl;
    cout << "1.좌석 예약" << endl;
    cout << "2.좌석 변경" << endl;
    cout << "3.프로그램 종료" << endl;
    cout << "번호를 입력하세요 : ";
}

// 현재 좌석표를 출력하는 함수
void printSeats() {
    // 구역 반복
    for (int z = 0; z < ZONE; z++) {
        cout << "1 2 3   4 5 6  (" << z + 1 << "구역)" << endl;
        cout << "----------------" << endl;

        // 각 구역의 행과 열 출력
        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {
                cout << seat[z][r][c] << " ";

                // 3열 뒤에 통로처럼 공백 추가
                if (c == 2) {
                    cout << "  ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

// 좌석 예약 함수
void reserveSeat() {
    int adult, child;
    int totalPeople;

    // 현재 좌석표 먼저 출력
    printSeats();

    // 성인, 유아 인원 입력
    cout << "성인(50000원): ";
    cin >> adult;
    cout << "유아(40000원): ";
    cin >> child;

    // 음수 입력 방지
    if (adult < 0 || child < 0) {
        cout << "인원 수는 음수가 될 수 없습니다." << endl;
        return;
    }

    // 총 예약 인원 계산
    totalPeople = adult + child;

    // 예약 인원이 0명인 경우
    if (totalPeople == 0) {
        cout << "예약할 인원이 없습니다." << endl;
        return;
    }

    // 종료 시 총 금액 계산을 위해 누적
    totalAdult += adult;
    totalChild += child;

    // 총 인원 수만큼 좌석 예약 반복
    for (int i = 0; i < totalPeople; i++) {
        int zone, row, col;

        while (true) {
            // 예약할 구역 입력
            cout << "어떤 구역을 예약 하시겠습니까?" << endl;
            cin >> zone;

            // 구역 범위 검사
            if (!isValidZone(zone)) {
                cout << "예약가능한 구역이 아닙니다." << endl;
                continue;
            }

            // 예약할 행, 열 입력
            cout << "몇열, 몇번째 좌석을 예약하시겠습니까?" << endl;
            cin >> row >> col;

            // 좌석 범위 검사
            if (!isValidSeat(zone, row, col)) {
                cout << "예약가능한 좌석이 아닙니다." << endl;
                continue;
            }

            // 이미 예약된 좌석인지 검사
            if (seat[zone - 1][row - 1][col - 1] == 1) {
                cout << "이미 예약되었습니다. 다른 좌석을 선택하세요" << endl;
                continue;
            }

            // 예약 처리
            seat[zone - 1][row - 1][col - 1] = 1;
            cout << "예약되었습니다." << endl;
            break;
        }
    }

    // 예약 완료 후 좌석표 다시 출력
    cout << endl;
    printSeats();
}

// 좌석 변경 함수
void changeSeat() {
    int count;

    // 현재 좌석표 출력
    printSeats();

    // 바꿀 좌석 개수 입력
    cout << "바꿀 좌석의 갯수를 입력하세요 : ";
    cin >> count;

    // 잘못된 개수 입력 방지
    if (count <= 0) {
        cout << "변경할 좌석 수가 올바르지 않습니다." << endl;
        return;
    }

    // 입력한 개수만큼 좌석 변경 반복
    for (int i = 0; i < count; i++) {
        int curZone, curRow, curCol;
        int newZone, newRow, newCol;

        while (true) {
            cout << "현재 좌석과 바꿀 좌석을 입력하세요" << endl;

            // 현재 좌석 입력
            cout << "현재 좌석(H구역, N열, M번째): ";
            cin >> curZone >> curRow >> curCol;

            // 현재 좌석 범위 검사
            if (!isValidSeat(curZone, curRow, curCol)) {
                cout << "좌석 범위를 벗어났습니다. 다시 입력해주세요" << endl;
                continue;
            }

            // 현재 좌석이 실제 예약된 좌석인지 검사
            if (seat[curZone - 1][curRow - 1][curCol - 1] == 0) {
                cout << "현재 예약되어있는 좌석이 아닙니다. 다시 입력해주세요" << endl;
                continue;
            }

            // 변경할 좌석 입력
            cout << "변경 좌석(H구역, N열, M번째): ";
            cin >> newZone >> newRow >> newCol;

            // 변경할 좌석 범위 검사
            if (!isValidSeat(newZone, newRow, newCol)) {
                cout << "좌석 범위를 벗어났습니다. 다시 입력해주세요" << endl;
                continue;
            }

            // 현재 좌석과 같은 좌석으로 변경하려는 경우
            if (curZone == newZone && curRow == newRow && curCol == newCol) {
                cout << "현재 좌석과 동일한 좌석입니다. 다시 입력해주세요" << endl;
                continue;
            }

            // 이미 예약된 좌석으로 변경하려는 경우
            if (seat[newZone - 1][newRow - 1][newCol - 1] == 1) {
                cout << "이미 예약되어있는 좌석입니다. 다시 입력해주세요" << endl;
                continue;
            }

            // 좌석 변경 처리
            seat[curZone - 1][curRow - 1][curCol - 1] = 0;
            seat[newZone - 1][newRow - 1][newCol - 1] = 1;

            cout << "변경되었습니다." << endl;
            break;
        }
    }

    // 변경 완료 후 좌석표 다시 출력
    cout << endl;
    printSeats();
}

// 메인 함수
int main() {
    int menu;

    // 메뉴를 반복해서 보여주기 위한 무한 반복문
    while (true) {
        printMenu();
        cin >> menu;

        // 1번 입력 시 좌석 예약
        if (menu == 1) {
            reserveSeat();
        }
        // 2번 입력 시 좌석 변경
        else if (menu == 2) {
            changeSeat();
        }
        // 3번 입력 시 총 금액 출력 후 종료
        else if (menu == 3) {
            int totalPrice = totalAdult * 50000 + totalChild * 40000;
            cout << "총 " << totalPrice << "원 입니다." << endl;
            break;
        }
        // 잘못된 메뉴 번호 입력 시
        else {
            cout << "올바른 번호를 입력해주세요." << endl;
        }

        cout << endl;
    }

    return 0;
}