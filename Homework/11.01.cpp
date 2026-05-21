#include <iostream>

class Wrapper;

using TestFuncPtr = Wrapper(*)();

using TaskFuncPtr = void (*)();

void task_to_execute();


class Wrapper {
private:
    TestFuncPtr m_creator_ptr;
    TaskFuncPtr m_task_ptr;

public:
    explicit Wrapper(TestFuncPtr creator, TaskFuncPtr task) : m_creator_ptr(creator), m_task_ptr(task) {}

    TaskFuncPtr* operator()() {
        return &m_task_ptr;
    }

    operator TaskFuncPtr() const {
        return m_task_ptr;
    }
};

Wrapper test() {
    std::cout << " test()\n";
    return Wrapper(&test, &task_to_execute);
}

void task_to_execute() {
    std::cout << " --> task_to_execute()\n";
}

int main() {
    Wrapper function = test();

    (*function())();

    void (*task_ptr)() = function;
    task_ptr();
}
