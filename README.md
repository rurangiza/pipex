# pipex
### Recreating the UNIX "pipe" (pipeline) program


<img src="documentation/Unix_pipeline_v1.gif" width="100%" alt="animation of how pipeline work in UNIX"/>

> Animation by [Computerphile](https://www.youtube.com/watch?v=bKzonnwoR2I)

Pipe is a mechanism for connecting the output of one program to the input of another program

### Benefits of having pipes
1. Instead of having one big program that does one thing. We can have multiple small ones that can be connected to do the same thing as the big one, but also can be connected in different ways to basically create other programs. It's like having multiple leggo blocks vs one already made structure. 
2. Back in the days, discs had 1mb or too if your were lucky, so programs were limited by the size the required to run. Having multiple smaller programs that consume less memory we could build bigger things by reusing the same memory and storing just little parts of at a time.