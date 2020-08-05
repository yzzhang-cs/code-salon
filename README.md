# Code Salon
A program that is used to change the [indentation style](https://en.wikipedia.org/wiki/Indentation_style) of code.

## CMPT383 Project Requirements
### Language Requirements
* At least one “systems” language (like C, C++, Go, Rust).
    * C++
    * Go
* At least one “scripting” language (like Bash, JavaScript, Julia, Perl, PHP, Python, R, Tcl).
    * Python
* C and C++ count as one language.
    * only C++ is used
* Only programming languages count toward your language count (e.g. not SQL, HTML, CSS, etc).
    * none of these languages are used
* Languages should be reasonably appropriate to the work done with them.
    * C++
        * used to process strings
        * taking the advantage of speed
    * Python
        * used to (pre-)process strings
        * taking the advantage of the [re](https://docs.python.org/3/library/re.html) library
    * Go
        * used to concurrently do things
        * taking the advantage of goroutines' simplicity
        * used to produce binary file (go build)

### Cross-Language Communication
* ffi
    * use C++ classes in Python using [SWIG](http://www.swig.org/Doc1.3/Python.html)
* exec
    * run Python scripts in Go using [exec](https://tutorialedge.net/golang/executing-system-commands-with-golang/)

### Implementation and Deployment
By running `vagrant up`, you can `vagrant ssh` into the machine then use the program immediately.  

#### Example
1. `vagrant up` on the host machine
2. `vagrant ssh` into the VM
3. `salon` this should show the usage of the program
4. `salon -in project/sample_input/ -out output` this will take all .cpp files in the `sample_output` directory, style them then output to the `output` directory
5. `salon -in project/sample_input/hello_world.cpp -out output.cpp` this will style the `hello_world.cpp` file, then output to `output.cpp`
6. `salon -in project/sample_input/hello_world.cpp -out output.cpp -new-line 1` same as above, but with line-breaks before parentheses 



## Purpose of this project
Lets look at the following pieces of code:
```
#include <iostream>
using namespace std;
int main() {
    cout << "Hello world!" << endl;
    return 0;
}
```
```
#include <iostream>
using namespace std;
int main() {
  cout << "Hello world!" << endl;
  return 0;
}
```
```
#include <iostream>
using namespace std;
int main(){
    cout << "Hello world!" << endl;
    return 0;
}
```
```
#include <iostream>
using namespace std;
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
```
So the main questions are:
* to new line or not new line?
* to space or not to space?
* to space or to tab?
* to 4 spaces or to 2 spaces?
* ......

In the Chinese programmers' community, these questions can cause [holy wars](https://code2048.com/series/%E5%9C%A3%E6%88%98%E7%B3%BB%E5%88%97/)(this is not serious).  
This library will help converting a program from one style to another.  

## Implementation Details
### Python part
* Handle file input, because using Python is easier.
* "Clean" the input, to make the input into a form that is easier to process
    * remove all unnessesary '\n', '\t' and spaces.
        * nessesary ones stay the same(i.e. the one after `#include <iostream>`)
        * the result should be a single string
* Communicate with C++ part using [SWIG](http://www.swig.org/Doc1.3/Python.html).  

### C++ part
* Process the "cleaned" string
* Handle file output, so we can output while processing the string
* Plan to handle C++(.cpp files) only in this project. If I have time and if I am still interested in this project, other programming languages will be added.

### Go part
* Used to process multiple files concurrently, because goroutines are easy to use to achieve concurrency.
* Communicate with python part with [exec](https://tutorialedge.net/golang/executing-system-commands-with-golang/).
