## Linux Basics Exercise
Practice the materials from the topic by completing the tasks presented below. 

### 1. FTP 
Using the program **FileZilla**, establish a remote connection to the working server at address **46.10.253.12**. 
Upload the file **LSPp1.pdf** to the user's home folder, which you can download from the Internet at the address **[https://github.com/dimitarminchev/LSP/presentations/01_Linux_Basics.pdf](https://github.com/dimitarminchev/LSP/blob/master/presentations/01_Linux_Basics.pdf)**. 

For the username and password, use those provided by the instructor. 
Alternatively, you can log in with the username **students** and password **password123**. 

### 2. SSH 
Using the program **putty**, establish a remote connection to the working server at address **46.10.253.12**. 

For the username and password, use those provided by the instructor. 
Alternatively, you can log in with the username **students** and password **password123**.

## 3. Terminal
1. Check if the file **LSPp1.pdf** is present in the user's home folder.
2. Change your password.
3. In your home folder **~**, create a new folder **exercises** for the exercises and a subdirectory **day01** in it for this lecture.
4. Go to the last folder **day01** and create a file **listing.txt** there, which contains a list of files from the folder **/sbin**.
5. Open the last file with the text editor **nano** and add your names at the beginning.
6. In your home directory, create a link to the directory **/home/students/**.

Example:
```
ls /home/students/LSPp1.pdf 
passwd
cd ~
mkdir exercises
mkdir exercises/day01
cd exercises/day01/
ls -l /sbin/ > listing.txt
nano listing.txt
cd ~
ln -s /home/students/ shared
```
