# CS 201 Mass Tester

### Used to run multiple tests at once for projects
This program runs and compares multiple test cases at once for projects related to CS 201 in a Lusth-like fashion.

## To Add Test Cases: 
Add your <test case>.c code file into "submission". Your <test case>.c file should be unique in name.
Add the expected results into "expected". The file must be .txt, and must have the same name as your <test case>.c file.

## To Use/Run:
Add your project code into "assign". You will need a specific argument in your Makefile. See Makefile within the root folder of the repository for an example.
Your program's results will show in the folder "results".

### Using Valgrind
You have the option to use valgrind with the mass tester. Run the program with "-valgrind" in the command line argument. Valgrind will run on every test case entity.

Valgrind can return a particular error code with the argument "--error-exitcode=D", where D is an integer value. For the case of the mass tester, valgrind will return an integer value of 5 if a memory leak was detected. Otherwise it will return a 0.

### Ignoring successful tests
You have the option to ignore passed tests when rerunning the program if you run with the argument "-ignore".  The next run of the program will only run the tests that you failed on the previous run.

To reset the files to be tested to their original state, run the program with the argument "-reset".