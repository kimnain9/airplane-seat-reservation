#include <iostream>
using namespace std;

// 좌석 구조 설정 (구역, 행, 열)
const int ZONE = 3;
const int ROW = 4;
const int COL = 6;

// 좌석 상태 저장 배열 (0: 빈 좌석, 1: 예약됨)
int seat[ZONE][ROW][COL] = { 0 };

// 총 예약 인원 저장
int totalAdult = 0;
int totalChild = 0;

// 구역 번호가 올바른지 검사
bool isValidZone(int zone) {
    return zone >= 1 && zone <= ZONE;
}

// 행 번호 검사
bool isValidRow(int row) {
    return row >= 1 && row <= ROW;
}

// 열 번호 검사
bool isValidCol(int col) {
    return col >= 1 && col <= COL;
}

// 좌석 전체 범위 검사 (구역 + 행 + 열)
bool isValidSeat(int zone, int row, int col) {
    return isValidZone(zone) && isValidRow(row) && isValidCol(col);
}

// 사용자 메뉴 출력
void printMenu() {
    cout << "**비행기 예약 시스템**" << endl;
    cout << "1.좌석 예약" << endl;
    cout << "2.좌석 변경" << endl;
    cout << "3.프로그램 종료" << endl;
    cout << "번호를 입력하세요 : ";
}

// 현재 좌석 상태 출력
void printSeats() {
    for (int z = 0; z < ZONE; z++) {
        cout << "1 2 3   4 5 6  (" << z + 1 << "구역)" << endl;
        cout << "----------------" << endl;

        // 행 기준으로 출력
        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {
                cout << seat[z][r][c] << " ";

                // 가운데 통로 표현
                if (c == 2) cout << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

// 좌석 예약 기능
void reserveSeat() {
    int adult, child;
    int totalPeople;

    printSeats();

    // 인원 입력
    cout << "성인(50000원): ";
    cin >> adult;
    cout << "유아(40000원): ";
    cin >> child;

    // 잘못된 입력 처리
    if (adult < 0 || child < 0) {
        cout << "인원 수는 음수가 될 수 없습니다." << endl;
        return;
    }

    totalPeople = adult + child;

    if (totalPeople == 0) {
        cout << "예약할 인원이 없습니다." << endl;
        return;
    }

    // 총 인원 누적
    totalAdult += adult;
    totalChild += child;

    // 인원 수 만큼 반복 예약
    for (int i = 0; i < totalPeople; i++) {
        int zone, col, row;  // 입력: 열 → 행

        while (true) {
            cout << "어떤 구역을 예약 하시겠습니까?" << endl;
            cin >> zone;

            // 구역 검사
            if (!isValidZone(zone)) {
                cout << "예약가능한 구역이 아닙니다." << endl;
                continue;
            }

            cout << "몇열, 몇번째 좌석을 예약하시겠습니까?" << endl;
            cin >> col >> row;

            // 좌석 범위 검사 (행, 열 순서로 검사)
            if (!isValidSeat(zone, row, col)) {
                cout << "예약가능한 좌석이 아닙니다." << endl;
                continue;
            }

            // 이미 예약된 좌석인지 확인
            if (seat[zone - 1][row - 1][col - 1] == 1) {
                cout << "이미 예약되었습니다. 다른 좌석을 선택하세요" << endl;
                continue;
            }

            // 실제 배열 저장은 [행][열] 순서
            seat[zone - 1][row - 1][col - 1] = 1;
            cout << "예약되었습니다." << endl;
            break;
        }
    }

    cout << endl;
    printSeats();
}

// 좌석 변경 기능
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

            // 현재 좌석 입력 (구역, 열, 행)
            cin >> curZone >> curCol >> curRow;

            if (!isValidSeat(curZone, curRow, curCol) ||
                seat[curZone - 1][curRow - 1][curCol - 1] == 0) {
                cout << "현재 좌석이 틀렸습니다. 다시 입력해주세요" << endl;
                continue;
            }

            // 변경할 좌석 입력
            cin >> newZone >> newCol >> newRow;

            if (!isValidSeat(newZone, newRow, newCol)) {
                cout << "좌석 번호를 다시 입력해주세요" << endl;
                continue;
            }

            // 이미 예약된 좌석 확인
            if (seat[newZone - 1][newRow - 1][newCol - 1] == 1) {
                cout << "이미 예약되었습니다. 다른 좌석을 선택하세요" << endl;
                continue;
            }

            // 좌석 이동 처리
            seat[curZone - 1][curRow - 1][curCol - 1] = 0;
            seat[newZone - 1][newRow - 1][newCol - 1] = 1;

            cout << "변경되었습니다." << endl;
            break;
        }
    }

    cout << endl;
    printSeats();
}

// 프로그램 시작 지점
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
            // 총 금액 계산 후 종료
            int totalPrice = totalAdult * 50000 + totalChild * 40000;
            cout << "총 " << totalPrice << "원 입니다." << endl;
            break;
        }
        else {
            cout << "올바른 번호를 입력해주세요." << endl;
        }

        cout << endl;
    }

    return 0;
}