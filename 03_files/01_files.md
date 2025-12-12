## Files

One of the basic principles in Unix and Linux states: **Everything is a file!**.
Data files, directories, information about hardware devices in the system, information about processes, or important system configuration parameters are all represented as files.

The following types of files exist:
- **inode** - a data structure that describes a file system object.
- Files are always opened from user space with a name.
- The pair **filename** and **inode** is called a link.
- **Regular files** = bytes of data.
- **Directories** = mapping between file names and inodes (links).
- **Hard links** = multiple links connect different names to the same inode.
- **Symbolic links** = like regular files that contain the full path of the linked files.
- **Special files** = block device files, character device files, named pipes, Unix domain sockets.
