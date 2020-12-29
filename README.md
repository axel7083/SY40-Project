SY40-Project

SY40-Project

The goal of this program is to `simulate` the behaviour of a jam factory. We split the problem in 4 separated elements which must be synchronized.
-	The small jar injector
-	The big jar injector
-	The valve
-	The clock
We need to make the same exercise using two separate sets of tools
-	Processus and semaphores
-	Threads and monitors
For both we can write a solution (pseudo-code) considering we have a function P(int i) which is called by a processus/threads waiting for another processus/threads to call V(int i).

| Jar Function | Valve Function | Clock Function | Jar_2 Function |
|-|-|-|-|
| ```Start<br>While True Then<br>    Insert_Jar()<br>    V(1)<br>    P(0)<br>    Remove_Jar()<br>    V(3)<br>    P(3)<br>End While<br>End ```| Start<br>While True Then<br>    P(1)<br>    Open_Valve()<br>    V(2)<br>    P(2)<br>    Close_Valve()<br>    V(0)<br>End While<br>End | Start<br>While True Then<br>    P(2)<br>    Sleep(30)<br>    V(2)<br>End While<br>End | Start<br>While True Then<br>    P(3)<br>    Insert_Jar()<br>    For i from 0 to 2<br>        V(1)<br>        P(0)<br>    Remove_Jar()<br>    V(3)<br>End While<br>End |

TODO:
- [x] Make a workflow for compiling
- [ ] Make doc
- [ ] Check memory leaks
- [ ] Make README with example 
- [ ] Remove unused libaries
- [ ] Check code quality
