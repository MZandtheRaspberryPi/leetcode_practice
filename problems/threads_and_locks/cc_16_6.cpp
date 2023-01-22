/*
 you are given a class with synchronized method A and a normal method C.
If you have two threads in one instance of a program, can they both execute A at the same
time? Can they execute A and C at the same time?

two threads cannot execute A on the same object at the same time, as it is a synchronized method. If diff instances, then can.

if both methods synchronized and static, wouldnt be able to tho.
*/

