# Hack Assembler Project 📄 --> 011010111010

When I was in my Freshman year of college during my Spring semester, I took a class called Computer Organization & Assembly Language, where we spent the first half of the semester focused on the [Nand2Tetris](https://www.nand2tetris.org/) course.
I learned a lot about logic gates, computer memory, computer architecture, and more. One especially interesting part of this course was when we learned about how an assembly language worked.
At this point we hadn't learned about the x86 assembly language, so we were using an incredibly simplified version of an assembly language.
I was then tasked by my professor to create an assembler program in C that would take a .asm file input and write a binary .hack file. 

The first time I did this project, I didn't do great. I had numerous amounts of memory leaks and bugs associated with my code. 
Although it was still a pretty functional program, I was incredibly dissatisfied with the end result. But unfortunately I had to step away from it to address other assignments and projects.

Then comes Spring Semester of my Sophomore year. Since I did very well in the class the year prior, I signed up to be a TA for the class. 
I was accepted into the role and had office hours dedicated to helping those who were struggling. When the assignment came up again, instead this time for the current students, I had an overwhelming desire to try again.
I knew that I had grown in my knowledge of C and programming practices overall, so I began from scratch and created the assembler program again. Only this time I did things differently.

1. I didn't use any template code from my professor or from the internet. All data structures, C files, and Make files were written by me.
2. I focused on a "finish what you started" mentality, something I picked up from [The Pragmatic Programmer](https://pragprog.com/titles/tpp20/the-pragmatic-programmer-20th-anniversary-edition/). This meant that "When possible, the function or object that allocates a resource should be responsible for deallocating it", which is a very important mentality when approaching manual memory management.
3. I made sure to act locally (Another piece of knowledge from [The Pragmatic Programmer](https://pragprog.com/titles/tpp20/the-pragmatic-programmer-20th-anniversary-edition/)), trying to keep functions as black boxes and having no global variables, only parameters and local variables were allowed in functions.
4. I separated code into methods that focus on very specific functionality to avoid giant code blocks with untraceable bugs and no organization.
5. Engineered the overall and file-based architecture to act similarly to a DAG (directed acyclic graph). This means that no two files and no two functions are dependent upon each other.
6. Give functions clear names and purposes. 
7. Use tools such as GDB and Valgrind to debug code and find memory leaks

There were more aspects I worked to improve on, but these were the core principles I wanted to establish when engineering my solution. Of course, there are multiple sections that can still be improved. But in comparison to my original submission the quality jumped more than a hundred times.

When I wrote the first assembler I had so many memory leaks, but with the new assembler I was able to spot and fix all possible memory issues. There are no memory leaks that I have found in my new solution.
When I wrote the first assembler I had so many bugs that I couldn't find the source of, but with my new mentality I was able to isolate and exterminate any bugs in my code with ease.
When I wrote the first assembler I could barely tell what I had written the day before, but with the way I structured my code and named my functions I knew what I meant in almost every snippet of code.
When I wrote the first assembler I couldn't use pointers effectively, but now I know how to use them for addresses, arrays, and structs. 

I'm happy that I found the chance to attempt this project again because it helped me practice and learn so much about lower-level programming languages like C and by association x86 assembly.
