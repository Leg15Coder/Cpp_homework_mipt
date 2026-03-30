#include <cstdio>

const char* s = "#include <cstdio>%c%cconst char* s = %c%s%c;%c%cint main()%c{%c    std::printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10, 10, 10, 10);%c}%c";

int main()
{
    std::printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10, 10, 10, 10);
}
