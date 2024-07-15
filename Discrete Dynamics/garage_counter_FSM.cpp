#include <iostream>
#include <vector>
#include <utility>

class GarageCounterFSM {
private:
    int state;
    bool up_present;
    bool down_present;

public:
    // FSM을 초기화하는 생성자
    GarageCounterFSM(int initial_state = 0) {
        this->state = initial_state;
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
        if (up_present && !down_present) {
            state++;
        }
        else if (!up_present && down_present) {
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
};

int main() {
    GarageCounterFSM garage_counter;

    // 입력 신호를 시뮬레이션
    std::vector<std::pair<bool, bool>> inputs = {
        {true, false},  // 차량 도착
        {true, false},  // 차량 도착
        {false, true},  // 차량 출발
        {true, false},  // 차량 도착
        {false, true},  // 차량 출발
        {false, true}   // 차량 출발
    };

    std::cout << "시뮬레이션 시작\n";
    for (size_t i = 0; i < inputs.size(); ++i) {
        auto input = inputs[i];
        garage_counter.input_signals(input.first, input.second);
        garage_counter.update_state();
        std::cout << "단계 " << i + 1 << ": ";
        std::cout << "입력 (up: " << (input.first ? "true" : "false") << ", down: " << (input.second ? "true" : "false") << ") -> ";
        std::cout << "현재 상태 (차량 수): " << garage_counter.get_state() << std::endl;
    }
    std::cout << "시뮬레이션 종료\n";

    return 0;
}
