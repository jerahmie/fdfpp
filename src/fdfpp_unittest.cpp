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


  bool fdfppWriteReadFloat(void)
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
    int dim0 = 0;
    int dim1 = 1;
    int dim2 = 2;
    int dim64 = FDF_ITEMNAME_LENGTH;
    int dim_data = DATA_POINTS;
    const int *pdim0 = &dim0;
    const int *pdim1 = &dim1;
    const int *pdim2 = &dim2;
    const int *pdim64 = &dim64;
    const int *pdimDATA = &dim_data;
    long append0 = 0;
    long append1 = 1;
    char *pfiletype = "filetype";
    char *pheader = "header";
    char *pvpc = "vpc";
    char *pzcv = "zcv";
    char *pt0 = "t0";
    char *pdt = "dt";
    char *pnbits = "nbits";
    char *punits = "units";
    char *pdata = "data";
    long ndims0 = 0;
    long ndims1 = 1;
    long ndims2 = 2;
    long ndims3 = 3;
    char *filetype = "t0dt_scaled";
    int file_type_len = strlen(filetype);
    const int *pfile_type_len = &file_type_len;
    char *header = "test of write floats with fdfpp CXX wrapper.";
    int header_len = strlen(header);
    const int *pheader_len = &header_len;
    double zcv = 0.0;
    double vpc = 1.0;
    double t0 = 0.0;
    double dt = 0.001;
    long nbits = 64;
    char *units = "volts";
    int unit_len= strlen(units);
    const int *punit_len = &unit_len;
    double data[DATA_POINTS];
    const double f0 = 10.0e6;
    const double delta_t = 0.001;
    for (int indx=0; indx < DATA_POINTS; indx++)
      data[indx] = 10.0*sin(2.0 * M_PI * f0 * delta_t * indx);
    
    long write_item_status = 0;
    write_item_status = myFdfPP.writeItem(append0,
					  pfiletype,
					  ndims1,
					  pfile_type_len,
					  fdf_char,
					  (void*)filetype);
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

  

