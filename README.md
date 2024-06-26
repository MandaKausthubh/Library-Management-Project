# Library Management Project

## Structure of the Project.
The Project consists of two types of executables:

 - Librarian: This is an executable that operates as an interface for the librarian.
 - Client: This is the client side which operates as an interface for those who want to borrow books from the library.

 ## Fucntionalities that are availabe:
 - Serves requests for Returning books.
 - Has the ability to insert new books.
 - Displays the list of new books that are added.
 - Provides a login/verification services.

 ### Client.
 - Creates requests for the borrowing of a book.
 - Creates request for borrowing of books.
 - Gives valid user ID and login.

## How is it implemented ?
 1. **Login page**: Stores the list of all valid Librarians in (Library.txt) and list of all registered Clients in (Clients.txt)
 2. **Borrow and Returns**: 

    2.1 **Creating a request**:
        The client side creates a TCP request, which is received by the Librarian which creates a new processes using fork().

    2.2 **Servicing a request**:
        Each *stack* of books is treated as a (multi) Producer-Consumer Problem which is solved using a Semaphor and Locking Mechanism.

    2.3 **Creating a Return Request**:
        The client side creates a TCP request, which is received by the Librarian which creates a new process using fork().
        
    2.4 **Servicing a Return Request**:
        The same semaphor is used to solve the problem.

