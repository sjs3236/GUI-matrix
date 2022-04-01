/*
 * File:   	      	binio.cc
 * Date:                11/21/2020
 * Author:              Junsik Seo
 * Email:               jxs161930@utdallas.edu
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *   This program will read data from bin file. and return vector string to main function
 *  	
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t 	magicNumber;
  uint32_t versionNumber;
  uint64_t	numRecords;
};	

const int maxRecordStringLength=25;

class BinaryFileRecord
{
public:
  uint8_t strlength;
  char stringbuffer[maxRecordStringLength];
};


vector<string>  binio()
{
  ifstream binInfile;
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  // Read in the single record
  cout << "Reading record to file: binaryfile.bin" << endl;
  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);
  // should check for errors here.  Keeping it simple...
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  //for record
  int n=myHeader->numRecords;
  BinaryFileRecord myRecord[n];
  for (int i=0;i<n;i++){
    binInfile.read((char*)& myRecord[i],sizeof(BinaryFileRecord));
  }
  // Done... clean up
  binInfile.close();
  cout << "Finished reading record to file: binaryfile.bin" << endl;
  cout << endl;

  int size=3+(2*n);
  vector<string>  passing(size);
  char number[100];
  sprintf(number,"Maigc: 0x%X",myHeader->magicNumber);
  passing[0]=number;
  sprintf(number,"Version: %d",myHeader->versionNumber);
  passing[1]=number;
  sprintf(number,"NumRecords: %lu",myHeader->numRecords);
  passing[2]=number;

  int index=0;
   for (int i=3; i<size;i=i+2){
      
     char temp1[maxRecordStringLength];
     char temp2[maxRecordStringLength];
     
      sprintf(temp2, myRecord[index].stringbuffer);
      sprintf(temp1,"strlen: %d",myRecord[index].strlength);
      passing[i]=temp1;
      passing[i+1]=temp2;
      index++;
  }


  // Clean up and exit
  cout << "Done... cleaning up" << endl;
  delete myHeader;

  return passing;
}

