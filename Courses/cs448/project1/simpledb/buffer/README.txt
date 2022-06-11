Maxime Kotur - kotur@purdue.edu

I used IntelliJ for this project as did my teammates.
I have modified the files BufferMgr.java and P1Test.java
I have also added another testfile named Test_Cases_New.java
Furthermore, P1Test.java should be in the simpledb/buffer directory and
Test_Cases_New.java should be in the simpleclient/embedded directory.

To use P1Test.java, you should first name the csv file into what you want.
What I did is that I ran my BufferMgr.java code with that test file, named
it modified.csv. Then I use the original BufferMgr.java code and used the
test file on it with the csv file named original.csv. I then compared both
results. This tests only the runtime of the pinning and unpinning functions,
as well as the search function.

For the Test_Cases_New.java file, this file was created by my team and I in
order to test the integrity of the data base. The method that I used to it
is the same. Use my code then run. Then swap out to the original then run.
I would then compare both csv files.

In BufferMgr.java I only changed Bufferpool into a Hashtable and create an
ArrayList for the buffers with a null BlockId. The Hashtable contains those
with an existing id. I thought it would be better to implement it like this
as it is the only unique identifier given. Therefore I changed the functions
that use bufferpool's contents to fit it with a Hashtable.
