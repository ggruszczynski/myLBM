

http://stackoverflow.com/questions/13042561/fatal-error-lnk1104-cannot-open-file-libboost-system-vc110-mt-gd-1-51-lib
The simplest way for the amature like me that is studying c++ on their own.

Firstly Unzip the boost library to any directory of your choice. I recommend you to c:\directory.

Open your visual c++.
Create a new project.
Right click on the project solution.
Click on property.
Click on c/c++.
Click on general.
Select additional include library.
Include the library destination. e.g. c:\boost_1_57_0.
Click on pre-compiler header.
Click on create/use pre-compiled header.
Select not using pre-compiled header.
Then the work now go over to the link library were you experience your problem as an armature.

Go to were the extracted file was c:\boost_1_57_0.
Click on booststrap.bat (don't bother to type on the command window just wait and don't close the window that is the place I had my problem that took me two weeks to solve. After a while the booststrap will run and produce the same file, but now in two different name b2, and bjam.
Click on b2 and wait it to run.
Click on bjam and wait it to run. Then a folder will be produce call stage. Then go back to stage 4.
Click on linker.
Click on general.
Click on include additional library directory.
Select the part of the library e.g. c:\boost_1_57_0\stage\lib.
And you are good to go!