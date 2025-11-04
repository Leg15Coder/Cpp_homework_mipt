#include <iostream>

class List {
    public:
        struct Node {
            int value = 0;
            Node *next = nullptr;
        };

        void push_back(int value) {
            if (this->empty()) {
                head = new Node{value, nullptr};
                return;
            }

            if (!this->tail) {
                tail = new Node{value, nullptr};
                head->next = tail;
                return;
            }

            tail->next = new Node{value, nullptr};
        }

        void push_front(int value) {
            Node *new_node = new Node{value, head};
            head = new_node;
        }

        void pop_back() {
            if (this->empty()) return;

            if (!head->next) {
                Node *tmp = head;
                head = nullptr;
                delete tmp;
                return;
            }

            if (head->next == tail) {
                head->next = nullptr;
                Node *tmp = tail;
                tail = nullptr;
                delete tmp;
                return;
            }

            Node *cur = head;
            while (cur->next->next != tail) cur = cur->next;

            Node *tmp = cur->next;
            tail = cur;
            cur->next = nullptr;
            delete tmp;
        }

        void pop_front() {
            if (this->empty()) return;

            Node *tmp = head;
            head = head->next;
            delete tmp;
        }

        Node* get() {
            if (!head) return nullptr;
            if (!head->next) return head;

            Node *cur = head;
            Node *faster = head;

            while (faster->next) {
                faster = faster->next;

                if (faster->next) faster = faster->next;
                else break;

                cur = cur->next;
            }

            return cur;
        }

        void show() {
            Node *cur = head;
            while (cur) {
                std::cout << cur->value << " ";
                cur = cur->next;
            }
            std::cout << std::endl;
        }

        bool empty() {
            return head == nullptr;
        }

        ~List() {
            Node *cur = head;
            Node *next;

            while (cur) {
                next = cur->next;
                delete cur;
                cur = next;
            }
        }

    private:
        Node *tail{nullptr};
        Node *head{nullptr};
};

int main() {
    List list;

    for (int i = 1; i <= 5; i++) {
        list.push_front(i);
    }

    std::cout << list.get()->value << std::endl;
    list.pop_front();
    std::cout << list.get()->value << std::endl;
    list.pop_back();
    std::cout << list.get()->value << std::endl;
    list.show();

    return 0;
}
