# Code Salon
A library(probably? or a script) that is used to change the [indentation style](https://en.wikipedia.org/wiki/Indentation_style) of code.

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

And in the Chinese programmers' community, these questions can cause [holy wars](https://code2048.com/series/%E5%9C%A3%E6%88%98%E7%B3%BB%E5%88%97/).  
This library will help converting a program from one style to another.  
However, to stop the "holy wars" completely, we should use Python or Go instead of C/C++, Java or Javacript.  

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
* Communicate with C++ part with [exec](https://tutorialedge.net/golang/executing-system-commands-with-golang/).
