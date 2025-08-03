#include <iostream>

__declspec(naked) int run_calculation()
{
    __asm
    {
        push ebp;
        mov ebp, esp;

        mov eax, [ebp + 16];
        mov edx, [ebp + 20];

        sub eax, edx;
        shr eax, 31;

        mov esp, ebp;
        pop ebp;
        ret;
    }
}

int case_0_func()
{
    return 10;
}

int case_1_func()
{
    return 50;
}

int (*jump_table[2])() = { case_0_func, case_1_func };

int main()
{
    int retval{};

    __asm
    {
        push ebp;
        mov ebp, esp;

        push 40;
        push 40;
        push 30;
        push 30;

        call run_calculation;

        mov ecx, offset jump_table;
        call dword ptr [ecx + eax * 4];

        add esp, 16;

        mov retval, eax;
        mov esp, ebp;
        pop ebp;
        ret;
    }

    printf("we're here! %i", retval);

    return 0;
}