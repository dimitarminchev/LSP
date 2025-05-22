## Users and Groups

To access the features of Linux, every user must go through an identification process called **login**, where a username and password are entered. After entering the correct combination, the user registers in the operating system and is associated with a unique identifier called **uid**, which represents a positive integer. Since names must also be unique, they are more commonly used in practice than **uid** for user identification.

Each user belongs to one or more user **groups**. This way, the same attributes or permissions can be assigned to multiple users at once, depending on their role in the system.

Authorization for access to resources in Linux is provided through this concept of users and groups. For example, the operations you can perform with files in the OS depend on the permissions that your user account and the group it belongs to possess.