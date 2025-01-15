this pulls in 8x PWM signals and spits them out as comma seperated microsecond values over the UART
it uses the port change inturrupts instead of pulseIn() so you don't need to care which order the pinchanges arrive in.
PWM in on D2-D12
I'm ignoring fields 0 and 1 in the arrays because i'm terrible and lazy, but it works.
maybe i'll do some digitalRead(i+2) stuff at some point, but that point is not today  

the only thing that explicitly wont work is rading two pins changing at once. i think.
there might be other edgecases. 
