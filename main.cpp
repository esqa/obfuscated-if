#include <iostream>

__declspec(naked) int check_condition()
{
    __asm
    {
        sub eax, edx;
        shr eax, 31;
        ret;
    }
}

int case_0()
{
    return 20;
}

int case_1()
{
    return 10;
}

int (*jump_table[2])() = { case_0, case_1 };

int main()
{
    int retval{};

    __asm
    {
        mov eax, 10;
        mov edx, 10;
        call check_condition;

        mov ecx, offset jump_table;
        call dword ptr [ecx + eax * 4];

        mov retval, eax;
    }

    printf("we're here! %i", retval);

    return 0;
}