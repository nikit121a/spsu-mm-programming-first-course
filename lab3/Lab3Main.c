#include "stdio.h"
#include "stdlib.h"
#include "math.h"   

double const PI = 3.141592653589;

double triangle(double edge1, double edge2, double edge3) // ������������� ������������.
{
    int exist = 0;
    if ((edge1 + edge2 > edge3) && (edge1 + edge3 > edge2) && (edge2 + edge3 > edge1))
    {
        exist = exist + 1;
    }
    return (exist);
}

double angle(double edge1, double edge2, double edge3) // ���� ����� edge2 � edge3.
{

    double cosAng = (edge2 * edge2 + edge3 * edge3 - edge1 * edge1) / (2 * edge2 * edge3);
    return acos(cosAng) * 180 / PI;
}

void printAngle(double angle) // ������� ������� ����� ���� � ������� � ������.
{
    int degrees = (int) angle;
    int minutes_and_seconds = (int) ((angle - (double) degrees) * 3600);
    int minutes = minutes_and_seconds / 60;
    int seconds = minutes_and_seconds % 60;
    printf("%d'%d'%d", degrees, minutes, seconds);


}


int main()
{
    double edge1, edge2, edge3, angle1_2, angle1_3, angle2_3;

    while (1)
    {
        printf("Enter the edges of the triangle: ");
        scanf("%lf%lf%lf", &edge1, &edge2, &edge3);
        scanf("%*[^\n]");
        if (edge1 > 0 && edge2 > 0 && edge3 > 0)
        {
            int j = triangle(edge1, edge2, edge3);
            if (j)
            {
                angle1_2 = angle(edge3, edge1, edge2);
                printf("%s", "Angle between edge1 and edge2 = ");
                printAngle(angle1_2);

                angle1_3 = angle(edge2, edge1, edge3);
                printf("\n%s", "Angle between edge1 and edge3 = ");
                printAngle(angle1_3);

                angle2_3 = angle(edge1, edge2, edge3);
                printf("\n%s", "Angle between edge2 and edge3 = ");
                printAngle(angle2_3);
                break;
            }
            else
            {
                printf("%s\n", "There is no triangle with such edges.");
                printf("%s\n", "Please, try again.");
            }
        }
        else
        {
            printf("%s\n", "Incorrect input.");
            printf("%s\n", "Please, try again.");
        }
    }
    getchar();
    return 0;
}
