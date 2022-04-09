# guessTheAnimal  
This is a text based game where the program makes a guess for the animal name you have in your mind. If it's unable to, then it can also _learn_ the prompts to ask for and make the guess.  
Let's see how it works -   
run in the terminal:   
                              `> gcc guessIt.c -o guessIt`   
                              `> ./guessIt`
                              
![gameplay screenshot](https://raw.githubusercontent.com/hiTushar/guessTheAnimal/main/Screenshot%20from%202022-04-09%2015-03-29.png)
![gameplay screenshot](https://raw.githubusercontent.com/hiTushar/guessTheAnimal/main/Screenshot%20from%202022-04-09%2015-07-20.png)

We can make the prompts and the answers learnt persistent by running it in training mode:   
`> ./guessIt -o training`  
And then again playing it by running:  
`> ./guessIt -i training`  
to read the learned prompts from the file  
![gameplay screenshot](https://raw.githubusercontent.com/hiTushar/guessTheAnimal/main/Screenshot%20from%202022-04-09%2015-54-40.png)  

