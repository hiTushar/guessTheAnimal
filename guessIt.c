#include <stdio.h>  // standard I/O library
#include <stdlib.h> // standard library for exit and malloc
#include <string.h> // string library

struct node {
    struct node *no;  // references no answer node
    struct node *yes; // references yes answer node
    char string[1];   // question or animal
};

struct node * create_node(char *string){
    struct node *memory; // newly allocated memory

    if ((memory = (struct node *)malloc(sizeof (struct node) + strlen(string))) == (struct node *)0) {
    (void)fprintf(stderr, "gta: out of memory.\n");
    exit(-1);
    }

    (void)strcpy(memory->string, string);
    memory->yes = memory->no = (struct node *)0;

    return (memory);
}

int main(int argc, char *argv[]) {
    char animal[50];       // new animal name buffer
    char buffer[3];        // user input buffer
    int c;                 // current character from buffer
    struct node **current; // current tree traversal node 
    FILE *in;              // input file for training data or typing 
    struct node *new;      // newly created node
    FILE *out;             // output file for saving training data 
    char *p;               // newline removal pointer 
    char question[100];    // new question buffer 
    struct node *root;     // root of the tree of knowledge

    in = out = (FILE *)0;

    for (argc--, argv++; argc > 1 && argc % 2==0;argc-=2,argv+=2){
        if (strcmp(argv[0], "-i") == 0 && in == (FILE *)0) { 
            if ((in = fopen(argv[1], "r")) == (FILE *)0) {
                (void)fprintf(stderr, "gta: can't open input file `%s'.\n", argv[1]);
                exit(-1); 
            }
        }
        else if (strcmp(argv[0], "-o") == 0 && out == (FILE *)0) {
            if ((out = fopen(argv[1], "w")) == (FILE *)0) {
                (void)fprintf(stderr, "gta: can't open output file `%s'.\n", argv[1]); 
                exit(-1);
            } 
        }
        else 
            break;
    }

    if(argc>0){
        (void)fprintf(stderr, "usage: gta [-i input-file-name] [-o output-file-name]\n"); 
        exit(-1);
    }

    // Read from standard input if no input file was specified on the command line.
    if (in == (FILE *)0) 
        in = stdin;

    // Create the initial tree of knowledge.
    root = create_node("Does it bark"); 
    root->yes = create_node("dog"); 
    root->no = create_node("cat");

    for (;;) {           // play games until the user quits.
        if (in == stdin)
            (void)printf("Think of an animal.\n");

        current = &root; // start at the top
        
        for (;;) {       // play a game
            for(;;) {    // get valid user input
                if (in  == stdin) {
                    if((*current)->yes == (struct node *)0) 
                        (void)printf("Is it a ");

                    (void)printf("%s?[ynq] ", (*current)->string); 
                }

                if (fgets(buffer, sizeof (buffer), in) == (char *)0 || strcmp(buffer, "q\n") == 0) { 
                    if (in != stdin) {
                        (void)fclose(in);
                        in = stdin; 
                    }
                    else {
                        if (in == stdin)
                            (void)printf("\nThanks for playing. Bye.\n"); 
                        exit(0);
                    } 
                }
                else if (strcmp(buffer, "y\n") == 0) { 
                    if (out != (FILE *)0)
                        fputs("y\n", out);

                    current = &((*current)->yes);
    
                    if (*current == (struct node *)0) { 
                        (void)printf("I knew it!\n"); 
                        break;
                    } 
                }
                else if (strcmp(buffer, "n\n") == 0) { 
                    if (out != (FILE *)0)
                        fputs("n\n", out);
                    
                    if ((*current)->no == (struct node *)0) { 
                        if (in == stdin)
                            (void)printf("I give up. What is it? ");

                        fgets(animal, sizeof (animal), in);

                        if (out != (FILE *)0) 
                            fputs(animal, out);

                        if ((p = strchr(animal, '\n')) != (char *)0) 
                            *p = '\0';

                        if (in == stdin) 
                            (void)printf(
                                "What's a good question that I could use to tell a %s from a %s? ", 
                                animal, (*current)->string);
                        fgets(question, sizeof (question), in);

                        if (out != (FILE *)0) 
                            fputs(question, out);

                        if ((p = strchr(question, '\n')) != (char *)0) 
                            *p = '\0';

                        new = create_node(question); 
                        new->yes = create_node(animal); 
                        new->no = *current;
                        *current = new;

                        if (in == stdin)
                            (void)printf("Thanks! I'll remember that.\n");

                        break; 
                    }
                    else
                        current = &((*current)->no);
                }
                else {
                    if (in == stdin)
                        (void)printf("Huh? Please answer y for yes, n for no, or q for quit.\n");

                    while ((c = getc(in)) != '\n' && c != EOF) 
                        ;
                } 
            }

            break; 
        }

        if (in == stdin)
            (void)printf("Let's play again.\n\n");
    } 
}
