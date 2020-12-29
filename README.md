# SY40-Project
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/axel7083/SY40-Projec/C/C++%20CI)

The goal of this program is to `simulate` the behaviour of a jam factory. We split the problem in 4 separated elements which must be synchronized.
-	The small jar injector
-	The big jar injector
-	The valve
-	The clock
We need to make the same exercise using two separate sets of tools
-	Processus and semaphores
-	Threads and monitors
For both we can write a solution (pseudo-code) considering we have a function P(int i) which is called by a processus/threads waiting for another processus/threads to call V(int i).

## Pseudo-code

<table>
<tr>
<th>
Jar Function
</th>
<th>
Valve Function
</th>
<th>
Clock Function
</th>
<th>
Jar_2 Function
</th>
</tr>
<tr>
<td>
<pre>
Start
While True Then
    Insert_Jar()
    V(1)
    P(0)
    Remove_Jar()
    V(3)
    P(3)
End While
End<br>
</pre>
</td>
<td>
<pre>
Start
While True Then
    P(1)
    Open_Valve()
    V(2)
    P(2)
    Close_Valve()
    V(0)
End While
End<br>
</pre>
</td>
<td>
<pre>
<br>
Start
While True Then
    P(2)
    Sleep(30)
    V(2)
End While
End 
<br>
</pre>
</td>
<td>
<pre>
Start
While True Then
    P(3)
    Insert_Jar()
    For i from 0 to 2
        V(1)
        P(0)
    Remove_Jar()
    V(3)
End While
End
</pre>
</td>
</tr>
</table>
