// fdfpp_unittest.cpp
//
// unit testing for C++ wrapper of fdf library
//
// created by Jerahmie W. Radder, 22Mar2013
//


#define DATA_POINTS 1024
#define _USE_MATH_DEFINES

#include <cstdio>
#include <iostream>
#include <cmath>
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


  bool fdfppWriteReadFlost(void)
  {
    bool read_write_status = false;
    // create a random name for our fdf file
    string fdf_file_name = "unittest_fdf.fdf";
    // create the fdf file with our fdfpp C++ wrapper
    cout << "fdf_char: " << fdf_char << endl;
    cout << "fdf_float: " << fdf_float << endl;
    cout << "fdf_double: " << fdf_double << endl;
    cout << "FDF_MAXDIMS: " << FDF_MAXDIMS << endl;
    cout << "FDF_ITEMNAME_LENGTH: " << FDF_ITEMNAME_LENGTH << endl;
    
    FdfPP myFdfPP;

    myFdfPP.openWrite(fdf_file_name,0);
    
    // add float values to fdf file
    // filetype fdf item
    long dim0, dim1, dim2, dim64, dim_data, write_item_status;
    long *pdim0, *pdim1, *pdim2, *pdim64, *pdimDATA;
    char fdfname[FDF_ITEMNAME_LENGTH];
    char filetype[FDF_ITEMNAME_LENGTH];

    //const char* fdfname_str = "filetype";
    //const char* filetype_str = "t0dt_scaled";
    //    memset(&fdfname, 0, FDF_ITEMNAME_LENGTH);
    //    memset(&filetype, 0, FDF_ITEMNAME_LENGTH);
    //    memcpy(&fdfname, fdfname_str, strlen(fdfname_str));
    //    memcpy(&filetype, filetype_str, strlen(filetype_str));


//    write_item_status = myFdfPP.preamble( fdf_t0dt_scaled,
//                                          test_header,
//                                          zcv,
//                                          vpc,
//                                          t0,
//                                          dt,
//                                          nbits,
//                                          units,
//                                          test_dims
//                                          );
    //    write_item_status = myFdfPP.writeData(append0, "data", (void*)data);
    
					  
//    write_item_status = myFdfPP.writeItem(append1,
//					  pheader,
//					  ndims1,
//					  pheader_len,
//					  fdf_char,
//					  (void*)header);
//    write_item_status = myFdfPP.writeItem(append1,
//					  pzcv,
//					  ndims1,
//					  pdim64,
//					  fdf_double,
//					  (void*)&zcv);
//    write_item_status = myFdfPP.writeItem(append1,
//					  pvpc,
//					  ndims1,
//					  pdim64,
//					  fdf_double,
//					 (void*)&vpc);
//    write_item_status = myFdfPP.writeItem(append1,
//					  pt0,
//					  ndims1,
//					  pdim2,
//					  fdf_double,
//					  (void*)&t0);
//    write_item_status = myFdfPP.writeItem(append1,
//					  pdt,
//					  ndims1,
//					  pdim64,
//					  fdf_double,
//					  (void*)&dt);
//    write_item_status = myFdfPP.writeItem(append1,
//					  pnbits,
//					  ndims1,
//					  pdim64,
//					  fdf_i32,
//					  (void*)&nbits);
//    write_item_status = myFdfPP.writeItem(append1,
//					  punits,
//					  ndims1,
//					  punit_len,
//					  fdf_char,
//					  (void*)units);
//    write_item_status = myFdfPP.writeItem(append1,
//					  pdata,
//					  ndims1,
//					  pdimDATA,
//					  fdf_double,
//					  (void*)data);
//    

    
    // close the file
    myFdfPP.close();
    
    // re-open the fdf file,
    // read the data value
    // close the file
    // compare the data and change read_write_status to 'true' if equal
    //read_write_status = true;
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

TEST_F(fdfppClassTest, fdfpp_setters_and_getters)
{
  // test the setter and getter functions
  double zcv = 0.0;
  double vpc = 1.0;
  double t0 = 0.0;
  double dt = 0.001;
  int nbits = 64;
  std::string test_header = "test of fdfpp: the CXX wrapper of the fdf C library";
  std::string units = "volts";
  std::vector<int> test_dims;
  test_dims.push_back(1024);
  
  
}

TEST_F(fdfppClassTest, fdfpp_header_write)
{
  
  double zcv = 0.0;
  double vpc = 1.0;
  double t0 = 0.0;
  double dt = 0.001;
  int nbits = 64;
  std::string test_header = "test of fdfpp: the CXX wrapper of the fdf C library";
  std::string units = "volts";
  std::vector<int> test_dims;
  test_dims.push_back(1024);

  string fdf_file_name = "one_unittest_fdf.fdf";  
  FdfPP oneFdfPP;
  oneFdfPP.openWrite(fdf_file_name,0);
  EXPECT_NO_THROW(oneFdfPP.preamble( fdf_t0dt_scaled,
                                     test_header,
                                     zcv,
                                     vpc,
                                     t0,
                                     dt,
                                     nbits,
                                     units,
                                     test_dims 
                                     )
                  );
  //  EXPECT_EQ(-1, oneFdfPP.
  //  EXPECT_EQ(1,fdfppWriteHeader());
  oneFdfPP.close();
}


TEST_F(fdfppClassTest, DISABLED_fdfpp_read_write)
{
  // test the ability to create a .fdf file,
  // write data, read float data
  //  EXPECT_TRUE(fdfppWriteReadFloat());
}


int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  cout << "Run album1 cli google unit tests" << endl ;
  
  return RUN_ALL_TESTS();
}

  

