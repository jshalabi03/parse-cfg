// SAMPLE SOURCE FILE

void bar() { int x = 1; }
void foo() { bar(); }

int main() {
    int x = 0;
    while (x < 10) {
        if (x % 2 == 0) {
            foo();
        } else {
            bar();
        }
        x++;
    }
    return 0;
}