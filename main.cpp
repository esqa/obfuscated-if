#include <iostream>

__declspec(naked) int run_calculation(int a, int b)
{
    __asm
    {
        push ebp;
        mov ebp, esp;

        sub eax, edx;
        shr eax, 31;

        mov esp, ebp;
        pop ebp;
        ret;
    }
}

int main()
{
    int retval{};

    __asm
    {
        mov eax, 10;
        mov edx, 10;
        call run_calculation;
        mov retval, eax;

        call get_eip;
        get_eip:
        pop ecx;

        mov ecx, jmp_table;
        jmp [jmp_table + retval * 4];

        jmp_table:
    }

    printf("we're here! %i", retval);

    return 0;
}