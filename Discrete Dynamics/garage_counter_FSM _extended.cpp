#include <iostream>
#include <cstdlib>
#include <ctime>

class ExtendedGarageCounterFSM {
private:
    int state;
    int max_capacity;
    bool up_present;
    bool down_present;

public:
    // FSM을 초기화하는 생성자
    ExtendedGarageCounterFSM(int initial_state = 0, int max_capacity = 10) {
        this->state = initial_state;
        this->max_capacity = max_capacity;
        this->up_present = false;
        this->down_present = false;
    }

    // 입력 신호를 설정하는 메서드
    void input_signals(bool up, bool down) {
        this->up_present = up;
        this->down_present = down;
    }

    // 입력 신호에 따라 상태를 업데이트하는 메서드
    void update_state() {
        if (up_present && !down_present && state < max_capacity) {
            state++;
        } else if (!up_present && down_present && state > 0) {
            state--;
        }
        // 처리 후 신호를 리셋
        up_present = false;
        down_present = false;
    }

    // 현재 상태를 반환하는 메서드
    int get_state() const {
        return state;
    }

    // 무작위 입력으로 환경을 시뮬레이션하는 메서드
    void environment(bool &up, bool &down) {
        up = rand() % 2;
        down = rand() % 2;
        if (up && down) {
            down = false; // up과 down이 동시에 true가 되지 않도록 보장
        }
    }
};

int main() {
    srand(time(0)); // 랜덤 숫자 생성기를 초기화

    ExtendedGarageCounterFSM garage_counter;

    // 환경 입력을 시뮬레이션
    for (int i = 0; i < 20; ++i) {  // 20 단계 동안 시뮬레이션 실행
        bool up, down;
        garage_counter.environment(up, down);
        garage_counter.input_signals(up, down);
        garage_counter.update_state();
        std::cout << "현재 상태 (차량 수): " << garage_counter.get_state() << std::endl;
    }

    return 0;
}