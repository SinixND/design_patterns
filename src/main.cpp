#include <stdio.h>
#include <string.h>

#define arrayLength 6

int main(/* int argc, char **argv */)
{
    char eingabe[arrayLength];
    char kopie[arrayLength];
    char kopiekopie[arrayLength];

    char* pEingabe = eingabe;
    char* pKopie = kopie;
    char* pKopieKopie = kopiekopie;

    printf("String eingeben:\n");
    scanf("%s", pEingabe);
    strcpy(pKopie, pEingabe);

    strcpy(pKopieKopie, pKopie);
    printf("%s\n", pKopieKopie);

    int k = strlen(kopie);

    for (int i = 0; i < k; ++i)
    {
        kopie[i] = kopiekopie[(k-1) - i];
    }

    return 0;
}
