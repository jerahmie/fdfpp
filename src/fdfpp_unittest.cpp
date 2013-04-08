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
    // create the fdf file with our fdfpp C++ wrapper
    FdfPP myFdfPP;
    myFdfPP.openWrite("unittest_fdf.fdf",0);
    myFdfPP.close();

    // open the file; delete if it exists
    ifstream test_file("unittest_fdf.fdf");
    cout << "test_file.good(): " << test_file.good() << endl;
    if (test_file.good())
      {
	cout << "found file." << endl;
	file_exists = true;
	test_file.close();
	remove("unittest_fdf.fdf");
      }
    
    return(file_exists);
  }


//  bool fdfppWriteReadFloat(void)
//  {
//    bool read_write_status = false;
//    // create a random name for our fdf file
//    string fdf_file_name = "unittest_fdf.fdf";
//    // create the fdf file with our fdfpp C++ wrapper
//    cout << "fdf_char: " << fdf_char << endl;
//    cout << "fdf_float: " << fdf_float << endl;
//    cout << "fdf_double: " << fdf_double << endl;
//    cout << "FDF_MAXDIMS: " << FDF_MAXDIMS << endl;
//    cout << "FDF_ITEMNAME_LENGTH: " << FDF_ITEMNAME_LENGTH << endl;
//    
//    FdfPP myFdfPP;
//
//    myFdfPP.openWrite(fdf_file_name,0);
//    
//    // add float values to fdf file
//    // filetype fdf item
//    long dim0, dim1, dim2, dim64, dim_data, write_item_status;
//    long *pdim0, *pdim1, *pdim2, *pdim64, *pdimDATA;
//    char fdfname[FDF_ITEMNAME_LENGTH];
//    char filetype[FDF_ITEMNAME_LENGTH];
//
//    // close the file
//    myFdfPP.close();
//    
//    // re-open the fdf file,
//    // read the data value
//    // close the file
//    // compare the data and change read_write_status to 'true' if equal
//    //read_write_status = true;
//    return(read_write_status);
//  }
//
    
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
  FdfPP test4FdfPP;
  // fdf file types
  EXPECT_NO_THROW(test4FdfPP.fileType(cp_info));
  EXPECT_EQ(cp_info,test4FdfPP.fileType());
  EXPECT_NO_THROW(test4FdfPP.fileType(t0dt_scaled));
  EXPECT_EQ(t0dt_scaled,test4FdfPP.fileType());
  // header and units
  EXPECT_NO_THROW(test4FdfPP.header("This is a header"));
  EXPECT_STREQ("This is a header", test4FdfPP.header().c_str());
  EXPECT_NO_THROW(test4FdfPP.units("arbitrary units"));
  EXPECT_STREQ("arbitrary units", test4FdfPP.units().c_str());
  // zero crossing voltage
  EXPECT_NO_THROW(test4FdfPP.zcv(23.0));
  EXPECT_DOUBLE_EQ(23.0, test4FdfPP.zcv());
  EXPECT_NO_THROW(test4FdfPP.zcv(-1.1));
  EXPECT_DOUBLE_EQ(-1.1, test4FdfPP.zcv());
  EXPECT_NO_THROW(test4FdfPP.zcv(0.0));
  EXPECT_DOUBLE_EQ(0.0, test4FdfPP.zcv());
  // volts per channel
  EXPECT_NO_THROW(test4FdfPP.vpc(42.0));
  EXPECT_DOUBLE_EQ(42.0, test4FdfPP.vpc());
  EXPECT_NO_THROW(test4FdfPP.vpc(-1.0));
  EXPECT_DOUBLE_EQ(-1.0, test4FdfPP.vpc());  
  EXPECT_NO_THROW(test4FdfPP.vpc(0.0));
  EXPECT_DOUBLE_EQ(0.0, test4FdfPP.vpc());  
  EXPECT_NO_THROW(test4FdfPP.vpc(1.0));
  EXPECT_DOUBLE_EQ(1.0, test4FdfPP.vpc());  
  // t0, initial time
  EXPECT_NO_THROW(test4FdfPP.t0(42.42));
  EXPECT_DOUBLE_EQ(42.42, test4FdfPP.t0());
  EXPECT_NO_THROW(test4FdfPP.t0(-1.0));
  EXPECT_DOUBLE_EQ(-1.0, test4FdfPP.t0());
  EXPECT_NO_THROW(test4FdfPP.t0(0.0));
  EXPECT_DOUBLE_EQ(0.0, test4FdfPP.t0());
  // dt, delta time (sample interval)  -- should be greater than zero
  EXPECT_NO_THROW(test4FdfPP.dt(0.001));
  EXPECT_DOUBLE_EQ(0.001, test4FdfPP.dt());  
  EXPECT_NO_THROW(test4FdfPP.dt(-0.001));
  EXPECT_DOUBLE_EQ(0.001, test4FdfPP.dt());
  EXPECT_NO_THROW(test4FdfPP.dt(0.0));
  EXPECT_DOUBLE_EQ(0.001, test4FdfPP.dt());  
  EXPECT_NO_THROW(test4FdfPP.dt(0.001));
  EXPECT_DOUBLE_EQ(0.001, test4FdfPP.dt());
  // nbits
  EXPECT_NO_THROW(test4FdfPP.nbits(16));
  EXPECT_EQ(16, test4FdfPP.nbits());  
  EXPECT_NO_THROW(test4FdfPP.nbits(-64));
  EXPECT_NE(-64, test4FdfPP.nbits());
  EXPECT_NO_THROW(test4FdfPP.nbits(0));
  EXPECT_NE(0, test4FdfPP.nbits());
  EXPECT_NO_THROW(test4FdfPP.nbits(16));
  EXPECT_EQ(16, test4FdfPP.nbits());
  EXPECT_NO_THROW(test4FdfPP.nbits(64));
  EXPECT_EQ(64, test4FdfPP.nbits());      
  
  // dims
  std::vector<int> dims1, dims2, dims3, dims_get;
  dims1.push_back(64);  // linear array of 64
  dims2.push_back(32);
  dims2.push_back(32);  // 32x32 matrix
  dims3.push_back(8);
  dims3.push_back(2);
  dims3.push_back(5);   // 8x2x5
  EXPECT_EQ(64,dims1[0]);
  EXPECT_EQ(32,dims2[0]);
  EXPECT_EQ(32,dims2[1]);
  EXPECT_EQ(8,dims3[0]);
  EXPECT_EQ(2,dims3[1]);
  EXPECT_EQ(5,dims3[2]);
  EXPECT_NO_THROW(test4FdfPP.dims(dims1));
  dims_get = test4FdfPP.dims();
  EXPECT_EQ(64,dims_get[0]);
  dims_get.clear();
  EXPECT_NO_THROW(test4FdfPP.dims(dims2));
  dims_get = test4FdfPP.dims();
  EXPECT_EQ(32,dims_get[0]);
  EXPECT_EQ(32,dims_get[1]);  
  dims_get.clear();
  EXPECT_NO_THROW(test4FdfPP.dims(dims3));
  dims_get = test4FdfPP.dims();
  EXPECT_EQ(8,dims_get[0]);
  EXPECT_EQ(2,dims_get[1]);
  EXPECT_EQ(5,dims_get[2]);
}

TEST_F(fdfppClassTest, fdfpp_preamble)
{
  FdfPP test5FdfPP;
  // preamble -- test the whole thing at once
  double zcv = 0.0;
  double vpc = 1.0;
  double t0 = 0.0;
  double dt = 0.001;
  int nbits = 64;
  std::string test_header = "test of fdfpp: the CXX wrapper of the fdf C library";
  std::string units = "volts";
  std::vector<int> test_dims;
  test_dims.push_back(1024);  

  EXPECT_NO_THROW(test5FdfPP.preamble(t0dt_scaled, test_header,
                                      zcv, vpc, t0, dt, nbits,
                                      units, test_dims));
  EXPECT_EQ(t0dt_scaled, test5FdfPP.fileType());
  EXPECT_STREQ(test_header.c_str(), test5FdfPP.header().c_str());
  EXPECT_EQ(nbits, test5FdfPP.nbits());
  EXPECT_STREQ(units.c_str(), test5FdfPP.units().c_str());
  EXPECT_DOUBLE_EQ(zcv, test5FdfPP.zcv());
  EXPECT_DOUBLE_EQ(vpc, test5FdfPP.vpc());
  EXPECT_DOUBLE_EQ(t0, test5FdfPP.t0());
  EXPECT_DOUBLE_EQ(dt, test5FdfPP.dt());
  std::vector<int> read_dims;
  read_dims = test5FdfPP.dims();
  EXPECT_EQ(1024, read_dims[0]);
}

TEST_F(fdfppClassTest, fdfpp_header_write)
{
  long append1 = 1;
  double zcv = 0.0;
  double vpc = 1.0;
  double t0 = 0.0;
  double dt_header_write = 0.0001;
  int nbits = 64;
  std::string test_header = "test of fdfpp: the CXX wrapper of the fdf C library";
  std::string units = "volts";
  std::vector<int> test_dims;
  const int data_length = 1024;
  test_dims.push_back(data_length);

  double A = 1.0;
  double phi = 0.0;
  double f0 = 50.0;  // 50 Hz
  double data[data_length];
  for (int indx=0; indx < data_length; indx++)
    data[indx] = A * cos(2.0 * M_PI * f0 * dt_header_write * indx + phi);
  
    string fdf_file_name = "one_unittest_fdf.fdf";  
  FdfPP oneFdfPP;
  oneFdfPP.openWrite(fdf_file_name,0);
  EXPECT_NO_THROW(oneFdfPP.preamble( t0dt_scaled,
                                     test_header,
                                     zcv,
                                     vpc,
                                     t0,
                                     dt_header_write,
                                     nbits,
                                     units,
                                     test_dims 
                                     )
                  );

  oneFdfPP.writeT0DTScaledData(append1, (void*)data);
  oneFdfPP.close();
}

TEST_F(fdfppClassTest, fdfpp_copy_constructor)
{
  // test assignment constructor then the copy constructor
  std::vector<int> one_dims;
  one_dims.push_back(2048);
  std::string one_header = "oneFdfPP file header";
  std::string one_units = "sprinkles";
  FdfPP oneFdfPP(t0dt_scaled,
                 one_header,
                 0.0, 1.0, 0.0, 0.123, 32,
                 one_units, one_dims);
  
  FdfPP twoFdfPP(oneFdfPP);
  EXPECT_DOUBLE_EQ(0.0, twoFdfPP.zcv());
  EXPECT_DOUBLE_EQ(1.0, twoFdfPP.vpc());
  EXPECT_DOUBLE_EQ(0.0, twoFdfPP.t0());
  EXPECT_DOUBLE_EQ(0.123, twoFdfPP.dt());
  std::vector<int> two_dims;
  two_dims = twoFdfPP.dims();
  EXPECT_EQ(2048, two_dims[0]);
  EXPECT_EQ(32, twoFdfPP.nbits());
  EXPECT_STREQ(one_units.c_str(), twoFdfPP.units().c_str());
}

TEST_F(fdfppClassTest, fdfpp_assignment_operator)
{
  // test assignment constructor then the copy constructor
  std::vector<int> one_dims;
  one_dims.push_back(2048);
  std::string one_header = "oneFdfPP file header";
  std::string one_units = "sprinkles";
  FdfPP oneFdfPP(t0dt_scaled,
                 one_header,
                 1.1, 2.2, 3.3, 0.123, 16,
                 one_units, one_dims);
  
  FdfPP twoFdfPP;
  twoFdfPP = oneFdfPP;
  EXPECT_DOUBLE_EQ(1.1, twoFdfPP.zcv());
  EXPECT_DOUBLE_EQ(2.2, twoFdfPP.vpc());
  EXPECT_DOUBLE_EQ(3.3, twoFdfPP.t0());
  EXPECT_DOUBLE_EQ(0.123, twoFdfPP.dt());
  std::vector<int> two_dims;
  two_dims = twoFdfPP.dims();
  EXPECT_EQ(2048, two_dims[0]);
  EXPECT_EQ(16, twoFdfPP.nbits());
  EXPECT_STREQ(one_units.c_str(), twoFdfPP.units().c_str());
}

TEST_F(fdfppClassTest, fdfpp_read_write)
{
  // test the ability to create a .fdf file,
  // write data, read float data
  std::string wr_fdf_file_name = "one_unittest_fdf.fdf";
  FdfPP wr_FdfPP;
  wr_FdfPP.open(wr_fdf_file_name);
  wr_FdfPP.readPreamble();
  EXPECT_EQ(0, wr_FdfPP.fileType());
  EXPECT_STREQ("test of fdfpp: the CXX wrapper of the fdf C library",
               wr_FdfPP.header().c_str());
  cout << wr_FdfPP.header() << endl;
  EXPECT_DOUBLE_EQ(0.0, wr_FdfPP.zcv());
  EXPECT_DOUBLE_EQ(1.0, wr_FdfPP.vpc());
  EXPECT_DOUBLE_EQ(0.0, wr_FdfPP.t0());
  EXPECT_DOUBLE_EQ(0.0001, wr_FdfPP.dt());
  EXPECT_STREQ("volts", wr_FdfPP.units().c_str());
  wr_FdfPP.close();
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  cout << "Run album1 cli google unit tests" << endl ;
  
  return RUN_ALL_TESTS();
}

  

