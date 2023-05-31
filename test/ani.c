/*
캐릭터 움직이는 표현 테스트 코드
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<sys/stat.h>
#include <string.h>
#include <time.h>

#define dot "/dev/dot"
#define clcd "/dev/clcd"
#define tact "/dev/tactsw"
#define fnd "/dev/fnd"

int dot_mtx = 0;

unsigned char c[9][8] = { 
    {0x00, 0x3c, 0x7e, 0x5a, 0x66, 0x7e, 0x66, 0x42},   //유년기
    {0x00, 0x84, 0x58, 0x20, 0x6E, 0x1F, 0x29, 0x2A},   //사슴, run, fly
    {0x00, 0x00, 0x8E, 0x5F, 0x00, 0x29, 0x00, 0x00},   //거북이, run, swim
    {0x0E, 0x11, 0x20, 0x36, 0x70, 0x78, 0x68, 0x08},   //독수리,   fly, run
    {0x00, 0x00, 0x67, 0x18, 0x24, 0x02, 0x00, 0x00},   //잠자리, fly  swim
    {0x00, 0x00, 0x08, 0x3D, 0x6E, 0x11, 0x00, 0x00},   //돌고래, swim, run
    {0x1C, 0x22, 0x41, 0x7F, 0x2A, 0x2A, 0x2A, 0x2A},   //해파리, swim, fly
    {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81},   // 게임오버 표시 X
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}    //초기화
};
void print_dot_mtx_gameover()
{
    write(dot_mtx, &c[8], sizeof(c[8])); 
    sleep(1); 
    write(dot_mtx, &c[9], sizeof(c[9])); 
    sleep(1); 
    write(dot_mtx, &c[8], sizeof(c[8])); 
    sleep(3); 
    write(dot_mtx, &c[9], sizeof(c[9])); 
    usleep(500000); 
    close(dot_mtx); 
    return;
}


void main()
{
    int count = 0;

    while(count < 30)
    {
        for(int j = 0; j<2; j++)
        {
            dot_mtx = open(dot, O_RDWR);
            if (dot_mtx < 0) 
            {
                printf("Can't open dot matrix.\n"); 
                exit(0);
            }

            write(dot_mtx, &c[(count%6) + 1], sizeof(c[(count%6) + 1])); 
            usleep(500000); 
            close(dot_mtx);
            sleep(2);

            dot_mtx = open(dot, O_RDWR);
            if (dot_mtx < 0) 
            {
                printf("Can't open dot matrix.\n"); 
                exit(0);
            }

            unsigned char c_move[1][8] = {{0,}};
            for(int i = 0; i<8; i++)
            {
                c_move[0][i] = c[(count%6) + 1][i] << 1;        // 시프트 이동으로 왼쪽으로 1칸씩 미루기
            }

            write(dot_mtx, &c_move[0], sizeof(c_move[0])); 
            usleep(500000); 
            close(dot_mtx);
            sleep(2);
        }
        
    }
    
    return;
}
