#include <stdio.h>

// Declare variables
int favNum = 68, sike = 69;
float favFloatNum = 420;
char favLetter = 'J';

int main()
{
    // My favorite things
    printf("Hello world! This is vsteam81's first C program. Enjoy the below output.\nMy favorite number is %d.\n", favNum);
    printf("My favorite float number is %f.\n", favFloatNum);
    printf("My favorite letter is %c.\n\n", favLetter);

    // We do some trolling
    favNum = sike;
    favFloatNum = sike;

    printf("Sike! My favorite number is actually %d.\n", sike);
    printf("And my favorite float number is actually %f.\n\n", favFloatNum);

    // Define some maths
    int add = favNum + favFloatNum, sub = favNum - favFloatNum, mul = favNum * favFloatNum, div = favNum / favFloatNum, tot = add + sub + mul + div;

    // Do some maths
    printf("Let's do some math now!\n");
    printf("All my favorite numbers added equal %d.\n", add);
    printf("All my favorite numbers subtracted equal %d.\n", sub);
    printf("All my favorite numbers multiplied in their exact order equal %d.\n", mul);
    printf("All my favorite numbers divided in their exact order equal %d.\n\n", div);
    printf("So, this means that the total of all the values we got from the above math session would equal %d!\n\n", tot);
    printf("This was a math session in C from vsteam81. I enjoyed writing my first C program. Albeit very basic, it is still a script that works. There will be another copy that will have more features soon.");
    return 0;
}
