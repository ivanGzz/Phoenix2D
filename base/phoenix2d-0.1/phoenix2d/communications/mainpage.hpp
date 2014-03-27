/**
 * @mainpage Phoenix2D-Library
 *
 * @author Iván González Magaña
 * @author claudiordgz
 *
 * @version 0.0010
 *
 * @section intro Introduction
 * Phoenix2D team base code for RoboCup 2D Simulation League.
 * <br> <br>
 * @section disclaimer DISCLAIMER
 * @subsection styleguide Styleguide for Phoenix2D
 * Please favor small, readable methods when implementing changes
 * in Phoenix2D. If implementing a package try to use the filesystem
 * to scope your entire package, for example an implementation of a
 * b-tree data structure could be enclosed in a folder named BTree.<br>
 * Convenience is remarkably less important on the long run when providing maintenance
 * to a program. Always keep in mind that not only you are going to be using this module.
 * C++ is a very complex language, and with complexity comes bugs, readibility of code
 * worsens, and maintainability costs rise.
* @subsection rules RULES
* - For every header, there is an Include Guard.
* - If using templates send the implementation to another hpp with the impl suffix
* - Only document the header files, in the CPP or impl files just use meaningful
*   comments for weird stuff (like jumps inside a for loop).
* - Do not inline functions unless they're templates.
*   - The compiler already optimizes your code, it's job is to inline functions where
*   deemed appropriate. Inline functions bloat header files which should be already
*   bloated with documentation to allow proper knowledge. No one should have to read
*   your code to understand it unless he is going to make changes to it.
* - Use functors for functions that are to be used across different objects.
*   - Compilers tend to inline functors if possible, and using a functor provides the
*     advantage of being able to save your current state and storing certain variables
*     without using static members.
* - Do not use <em> using </em> for a whole library. It creates confusion not only to
*   the reader, but also the compiler and could cause several problems hard to detect.
*   - Use using for single objects like <em> boost::array </em> thus it is easy to
*     replace with <em> std::array </em> later on.
* - Nested Classes, Static members, Global Functions
*   - Does a simple namespace doesn't get the job done?
*   - Scope them, don't use them all around the code.
* - Default Constructor
*   - Initialize everything to zero, it is not redundant, it is robust. And keep
*   constructors lightweight. Rest of work should be done in a private method. E.G. Setup
* - Rule of Three
*   - Explicitly Define a Destructor, Copy Constructor, and Copy assignment
*   Operator (=) in case you are already defining one of those. If you are not changing
*   either one.
* - Inheritance
*   - Prefer composition unless you are using dynamic polymorphism.
* - Exceptions
*   - Find an alternative, if no alternative, scope the expception. Remember to
*     define a case for all pertinent exception cases.
* - Excess functionality
*   - Overloading operators should only be done when necessary. This is because an operator
*   could work differently. We use references and pointers often in our code, thus an object
*   with an overloaded operator- or operator+ could allow us to add something to a memory
*   address when we wanted to add it to the object. Errors of that type are hard to debug.
* - Break up functions
*   - If it measures more than 50 lines, it can be broken down in smaller functions.
* - Smart Pointers
*   - In the case of auto_ptr do some extensive testing on it. Auto_ptr could have problems
*   when transferring ownership. Which could cause problems with certain functions, like
*   std::copy or std::accumulate.
*   - In general prefer shared_ptr or unique_ptr, or scoped_ptr
* - Console Information
*   - Must be meaningful and auto explanatory.
* - Increment variables using pre increment ALWAYS. (++i);
* - Use consts, specially with passing references and pointers, it helps the programmer
* know if the variable is going to change.
*
 * <hr>
 * @todo Finish the project
 *
*/
