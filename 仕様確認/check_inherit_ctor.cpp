//継承コンストラクタ 動作確認
#include <stdio.h>
#include <string>
#include <iostream>

class A {
public:

    A (int a) {}
    A (int a, char b) {}
    A (std::string str) {}
    A (int a, int b, int c, int d, int e)
{
     printf("e, %d\n", e);
}
    A (int a, int b) {
         printf("A, %d\n", a + b);
    }

    void display() {
         printf("called display\n");
    }
};

class B : public A {
public:
    using A::A; // 継承コンストラクタ
};

int main() {
    B b1(1, 2);
    B b2(1, 2, 3, 4, 5);
    b1.display(); // "called display"
    b2.display();
}
