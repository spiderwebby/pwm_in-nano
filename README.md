this pulls in 8x PWM signals and spits them out as comma seperated microsecond values over the UART.<br>
it uses the port change inturrupts instead of pulseIn() so you don't need to care which order the pinchanges arrive in.<br>
PWM in on D2-D12.<br>
I'm ignoring fields 0 and 1 in the arrays because i'm terrible and lazy, but it works.<br>
maybe i'll do some digitalRead(i+2) stuff at some point, but that point is not today.<br>
<br>
the only thing that explicitly wont work is rading two pins changing at once. i think.<br>
there might be other edgecases. <br>
