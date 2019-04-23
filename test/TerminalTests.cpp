#include "main.h"

TEST(Terminal, DISABLED_Test){
    constexpr int w = 80;
    constexpr int h = 30;
    int i = 0;
    printf(TERM_CLS);
    while(true){
        i++;
        
        const char chars[] = "=-o/#%*.:\\|!~";

        printf(TERM_00);

        for(int row = 0; row < h; row++){
            for(int j = 0; j < w; j++){
                char c = chars[(row + i/2) % (sizeof(chars) - 1)];

                if (RandomInt(0, 1) == 0){
                    printf(RED_TEXT);
                } else {
                    printf(PURPLE_TEXT);
                }

                printf("%c", c);
            }
            printf(DEFAULT_TEXT);
            printf("\n");
        }

        usleep(1000 * 1000 / 30);
    }
}

