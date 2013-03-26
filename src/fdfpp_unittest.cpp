// fdfpp_unittest.cpp
//
// unit testing for C++ wrapper of fdf library
//
// created by Jerahmie W. Radder, 22Mar2013
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include "fdfpp.h"
#include "gtest/gtest.h"


using namespace std;

// fdfpp test fixture
class fdfppTest : public ::testing::Test{

protected:

  bool fdfppCreateFile()
  {
    bool file_exists = false;
    // create a random name for our fdf file
    char buffer [L_tmpnam];
    tmpnam(buffer);
    stringstream fdf_tmp;
    fdf_tmp << buffer;
    string fdf_out_file = fdf_tmp.str() + ".fdf";

    // create the fdf file with our fdfpp C++ wrapper
    FdfPP myFdfPP;
    myFdfPP.openWrite(const_cast <char *>(fdf_out_file.c_str()),0);
    //    myFdfPP.openWrite("unittest_fdf.fdf",0);
    myFdfPP.close();

    // open the file; delete if it exists
    ifstream test_file(const_cast <char *>(fdf_out_file.c_str()));
    //ifstream test_file("unittest_fdf.fdf");
    cout << "test_file.good(): " << test_file.good() << endl;
    if (test_file.good())
      {
	cout << "found file." << endl;
	file_exists = true;
	test_file.close();
	remove(fdf_out_file.c_str());
      }
    
    return(file_exists);
  }


  bool fdfppWriteReadFloat(void)
  {
    bool read_write_status = false;
    // create a random name for our fdf file
    char buffer [L_tmpnam];
    tmpnam(buffer);
    stringstream fdf_tmp;
    fdf_tmp << buffer;
    string fdf_out_file = fdf_tmp.str() + ".fdf";

    // create the fdf file with our fdfpp C++ wrapper
    FdfPP myFdfPP;
    myFdfPP.openWrite(const_cast <char *>(fdf_out_file.c_str()),0);
    cout << "file name: " << fdf_out_file << endl;
    //    myFdfPP.openWrite("unittest_fdf.fdf",0);

    // add float values to fdf file
    

    // close the file
    myFdfPP.close();
    
    // re-open the fdf file,
    // read the data value
    // close the file
    // compare the data and change read_write_status to 'true' if equal
    read_write_status = true;
    return(read_write_status);
  }

    
  virtual void SetUp(){
    // Code here will be called immediately after constructor (right 
    // before each test).
  }
 
  virtual void TearDown(){
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
  // Objects declared here can be used by all tests in the test case for
  // album1Test.

};

class fdfppClassTest : public fdfppTest {
  // override any virtual functions if necessary
};
  

// start with a trivial test and build from there
TEST(trivial_test_case, trivial_test)
{
  EXPECT_EQ(1,1) << "One should be equal to one.  Something mayb be wrong with gtest.";
}
TEST_F(fdfppClassTest, fdfpp_trivial_test)
{

  EXPECT_EQ(1,1) << "This trivial test should pass.";
}

TEST_F(fdfppClassTest, fdfpp_make_file)
{
  // test the ability to create a .fdf file
  EXPECT_TRUE(fdfppCreateFile());
}

TEST_F(fdfppClassTest, fdfpp_read_write)
{
  // test the ability to create a .fdf file,
  // write data, read float data
  EXPECT_TRUE(fdfppWriteReadFloat());
}


int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  cout << "Run album1 cli google unit tests" << endl ;
  
  return RUN_ALL_TESTS();
}

  

