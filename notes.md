-----------------------------------Get Next Line------------------------------------

in unix |**Everything is a file**|

# static variable:
>>Static variables have their memory allocated once when the program starts and persist the program ends.
_____________________________________________________________
Static varibles _____ <global static variables>:
               |                > Limited to the file they are declared in.
               |                > Exists throughout the program's execution.
               |                > Stored in the data segment of the memory.
               |_____ <local static variables>:
                                >Limited to the function/block where declared.
                                >Exists throughout the program's execution.
                                >Stored in the data segment of the memory 
____________________________________________________________________________
## Data Segment:
- contains the global variables and static variables that are initialized by the programmer.
- the data segment is not read-only, since the values of the variables can be altered at run time.
- can be further classified into the initialized read-only area and the initialized read-write area.
__________________________________________
___________________________________
_______________________
# File descriptor:
>> A file descriptor is typically a non-negative integer that uniquely identifies an open file within a process.

- In Unix-like operating systems, including Linux, file descriptors are used to represent open files, devices, and other I/O resources.
- In Unix, regular files, directories, sockets, pipes, and even hardware devices are all abstracted as file descriptors.
- When a program interacts with these entities, it does so through file descriptors.

___________________________________
## Descriptor Table:
 ###########
[    fd 0   ] -> stdin
[    fd 1   ] -> stdout
[    fd 2   ] -> stderr
[     ...   ]
 ###########

- One table per process.
- indexed by file descriptors.
- Contains pointers to the <open file table.>

[!] Try cmd `ulimit -a` to see the max of file descriptors that can be opened in your device.
_____________________________________
## open file table:
>A file table is a system structure that keeps track of information about open files, such as their inode, current position, and access mode, current file offset for each open file in the process.
- shared by all processes, especially when multiple processes open the same file.
____________

## File Descriptor’s Offset:
[!] Both the read and write system calls are affected by the file descriptor’s offset
## Adjusting the File Descriptor Offset with Lseek:
``` c
    off_t lseek(int fd, off_t offset, int whence);
```

- _fd_: the file descriptor for which to change the offset,
- _offset_: the number of bytes to move the offset,
- _whence_: the position from which to apply the offset. Possible options are:
    [SEEK_SET]: apply the offset relative to the beginning of the file (overwrites the offset with the one specified in the previous parameter),
    [SEEK_CUR]: apply the offset relative to the current position in the file (add the offset specified in the previous parameter to the current offset),
    [SEEK_END]: apply the offset relative to the end of the file (add the offset to the end of the file).


_______________________________
## process
>> A process is an active instance of a program in execution, encompassing its code, data, and state, managed by the operating system.
- A process can create other processes (child processes) via system calls like fork() in Unix.
- The parent process is responsible for managing its children.
- Each process is assigned a unique PID (Process ID).
- When a process closes or terminates, the OS ensures that all open file descriptors associated with it are closed.
- The entries in the open file table corresponding to the file descriptors are released.
[!] A process uses file descriptors as handles to access and interact with files, devices, or sockets, enabling operations like reading, writing, or closing.
__________________________________
## PID
>> A PID (Process Identifier) is a unique number assigned by the operating system to each running process for tracking and management.
[!]Get PID of the Current Process:
``` c
pid_t pid = getpid();
```
______________________
________________________________________________
## Inode vs Vnode:
> Inode and vnode are both data structures used to represent files, but they serve different purposes and are used in different contexts:

## inode:
<An inode is a data structure that stores information about a file, like its size, permissions, and location on disk, but not its name.>
The inode contains file-specific metadata, such as:
- File size.
- Ownership and permissions.
- Timestamps (creation, modification, etc.).
- Pointers to data blocks on the disk.

## vnode:
<A vnode is a system-level object that represents a file or directory in a way that works across different types of file systems.>

- A reference to the inode (if the file resides on a local disk).
- File type (e.g., regular file, directory, symbolic link).
- Operations: File operations like read, write, and open are executed using the vnode.
## Key Differences:
__File System vs. Abstraction:__
Inode is specific to a particular file system and contains metadata about files in that file system.
Vnode is a higher-level abstraction used by the Virtual File System (VFS) layer to allow the kernel to handle different file systems uniformly.
__Location:__
Inode exists within a specific file system on disk and holds information about files or directories.
Vnode exists in memory and represents a file in a way that can be managed by the VFS.
__Usage:__
Inode is used for managing files on disk (in a specific file system like ext4 or NTFS).
Vnode is used by the kernel to provide a unified interface to different file systems (through the VFS).
__Structure:__
Inode stores file-specific information like size, permissions, timestamps, and block pointers.
Vnode stores references to file system-specific structures (like inodes) and provides a unified interface for file operations.
__________________________________________________
__________________________________________
## What Happens If I Delete a File That’s Open by a Process?:
In Linux, if you delete a file that’s currently open by a process, the plot takes an interesting turn:

[1]**The Directory Entry Disappears:** The file becomes inaccessible via the file system, like a deleted phone number — you can’t call it anymore.
[2]**The Inode Lives On:** The file’s inode (think of it as the DNA of the file) still exists as long as there’s an open file descriptor pointing to it. The process can still read and write to it.
[3]**Disk Space:** The storage space occupied by the file won’t be freed until the file descriptor is closed. It’s like holding a seat for someone who has stepped out momentarily.
[4]**The Final Act:** Once the process closes the file descriptor or terminates, the inode is deleted, and the disk space is reclaimed. The curtain falls, the actors bow.

> So, in essence, the file continues to ‘live’ through the process that holds its file descriptor open, even if you’ve tried to make it ‘disappear’ from the file system.
------------------------------------------------
## Can different types of file descriptors (e.g., socket, pipe, file) have different limits?:
[!] No, they all share the same pool of available file descriptors, just like how every passenger on a train shares the same quota of seats.

___________________________________________________
________________________________________________________
