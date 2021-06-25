// tower of hanoi
// you have 3 towers and n disks of diff sizes which can slide onto any tower
// puzzle starts w/ disks sorted in ascending order of szie from top to bottom, (each disk sits on even larger one)
// got constraints:
// 1) only one disk can be moved at a time
// 2) a disk is slid off the top of one tower onto the next tower
// 3) a disk can only be placed on top of a larger disk
// write a program to move disks from first tower to last using stacks

// if 1 disk
// put disk on third tower

// if 2 disks
// put first from first tower to second tower
// put second from first tower to third tower
// put first from second tower to third tower

// if 3 disks
// put first from first t to second t
// put second from first tower to third tower
// put first from second tower to third tower
// put third from first tower to second tower
// put second from third tower to first tower
// put first from third tower to first tower
// put third from second tower to third tower
// put first from first tower to second tower
// put second from first tower to third tower
// put first from second tower to third tower

// if 4 disks
// get three on 2
// put 4 on three.
// put one from 2 to 4.
// put 2 from 2 to 1
// put 1 from 4 to 1
// put 3 from 2 to 3.
// put 1 from 1 to 2
// put 2 from 1 to 3
// put 1 from 2 to 3