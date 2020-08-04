#include <iostream>
using namespace std;
int main()
{
	
	/* some comments 
		comment
	*/
	// some other comments
	cout << "\"Hello\", \n\tworld" << endl;
	int i = 0;
	while(i < 10)
	{
		int bar = 0;
		i++;
		while(j < 10)
		{
			int foo = 0;
			j++;
		}
		// some empty lines(decided by the user, about to keep them or not)
		
		
		
		
		
		for(int k = 0; k < 10;/* a comment in a weird place*/k++)
		{
			int foobar = 0;
		}
		
		/* case that doesn't work currently:
		
		if(true) {
			int foobarbar = 10;
		} // some other comments in a weird place
		
		*/
	}
	return 0;
}
