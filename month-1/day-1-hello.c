#include <stdio.h> //telling the compiler to include the standard input/output library. I am curious what is inside the library and how it works. I will have to look into that later. For now, I just want to get the basics of C programming down.

int main(){ //I forgot to put "()" after main and it gave me an error. I guess I have to put "()" after main to indicate that it is a function. I also forgot to put "int" before main and it gave me another error. I guess I have to put "int" before main to indicate that it returns an integer value. I will have to remember these things in the future.
    printf("Hello, world!\n"); //don't forget the semicolon, guys ;)
}

//turns out, you have to use int main() instead of just main() in C. Who knew? it said in the book that you use main() but it doesn't work. I guess they meant int main() but just forgot to put the int in there. Or maybe that book is old and back then you could just use main() without specifying the return type. In any case, using int main() is the correct way to define the main function in C, and it should work without any issues.
// I am curious, can i do a basic input and output without including the stdio.h library? I will have to try that out later.