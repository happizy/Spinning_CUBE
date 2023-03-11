#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

float A, B, C;
float cubeWidth = 20;
const int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
const int backGround = ' ';
const int distance = 100;
float VAR = 40;

float incrementSpeed = 0.6;

float x, y, z;
float flo;
int xp, yp, idx;

float calculateX(int i, int j, int k)
{
    return (j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C));
}

float calculateY(int i, int j, int k)
{
    return (j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C));
}

float calculateZ(int i, int j, int k)
{
    return (k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B));
}

void calculateSurface(float cubeX, float cubeY, float cubeZ, int ch)
{
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distance;

    flo = 1 / z;
    xp = (int)(width / 2 + VAR * flo * x * 2);
    yp = (int)(height / 2 + VAR * flo * y);

    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height && flo > zBuffer[idx])
    {
        zBuffer[idx] = flo;
        buffer[idx] = ch;
    }
}

int main(int argc, char const *argv[])
{
    printf("\x1b[2J");
    while (1)
    {
        memset(buffer, backGround, width * height);
        memset(zBuffer, 0, width * height * 4);
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed)
        {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed)
            {
                calculateSurface(cubeX, cubeY, -cubeWidth, '~');
                calculateSurface(cubeWidth, cubeY, cubeX, '$');
                calculateSurface(-cubeWidth, cubeY, cubeX, '*');
                calculateSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateSurface(cubeX, -cubeWidth, -cubeY, '!');
                calculateSurface(cubeX, cubeWidth, cubeY, '@');
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < width * height; k++)
        {
            putchar(k % width ? buffer[k] : 10);
        }
        A += 0.005;
        B += 0.005;
        usleep(1000);
    }
    return 0;
}
