#include <iostream>
#include <random>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//-----------------Функции----------------//


//Создание файла с рандомными числами
bool createFileWithRandomNumbers(const string &fileName, const int numbersCount,const int maxNumberValue)
{
  int mas[numbersCount];
  ofstream file(fileName);
  if(!file.is_open())
    return -1;
  for (int i=0;i<numbersCount;i++)
    {
      // используем возможности библиотеки рандом 
      mt19937 engine;
      random_device rd;
      engine.seed(rd());
      uniform_int_distribution<unsigned> distrib(0,maxNumberValue);
      mas[i] = distrib(engine);
      file<<mas[i]<<' ';
    }
  file.close();
  return true;
}



//Проверка файла на упорядоченность
bool isFileSorted(const string &fileName)
{
  int temp, temp1;
  ifstream *file = new ifstream(fileName);
  if(!file->is_open())
    return -1;
  *file>>temp;
  while (*file)
    {
      *file>>temp1;
      if (temp1 < temp )
      {
        file->close();
        return false;
      }
      temp = temp1;
    }
  file->close();
  return true;
}


// функция разбиения файла на 2
bool shareFiles(const string &fileName , const string &fileName1 , const string &fileName2)
{
  int n ,i , x;
  ifstream file(fileName);
  ofstream file1(fileName1);
  ofstream file2(fileName2);
  if ( !file.is_open() || !file1.is_open() || !file2.is_open())
    return false;
  file>>x;
  while (file)
    {
      i=0;
      while(file && i<1)
        {
          file1<<x<<' ';
          file>>x;
          i++;
        }
      i=0;
      while(file && i<1)
        {
          file2<<x<<' ';
          file>>x;
          i++;
        }
    }
  file.close();
  file1.close();
  file2.close();
  return true;
}


//Функция слияния файлов
bool mixFiles(const string &fileName1, const string &fileName2, const string &fileName3, const string &fileName4, int p)
{
  int x,y,i,j;
  ifstream file1(fileName1);
  ifstream file2(fileName2);
  ofstream filesToWrite[2]= {ofstream (fileName3), ofstream(fileName4)}; // сюда будем записывать числа
  if ( !file1.is_open() || !file2.is_open())
    return false;
  for (j =0; j<2; j++)
    {
      if(!filesToWrite[j].is_open())
        return false;
    }
  file1>>x;
  file2>>y;
  int n=0;
  while(file1 && file2)
    {
      i=j=0;
      while (file1 && file2 && i<p && j<p)
        {
          if (x<y)
          {
            filesToWrite[n]<<x<<' ';
            file1>>x;
            i++;
          }
          else
          {
            filesToWrite[n]<<y<<' ';
            file2>>y;
            j++;
          }
        }

      while (file1 && i<p)
        {
          filesToWrite[n]<<x<<' ';
          file1>>x;
          i++;
        }
      while(file2 && j<p)
        {
          filesToWrite[n]<<y<<' ';
          file2>>y;
          j++;
        }
      n=1-n;
    }

  while (file1)
    {
      filesToWrite[n]<<x<<' ';
      file1>>x;
    }
  while (file2)
    {
      filesToWrite[n]<<y<<' ';
      file2>>y;
    }
  file1.close();
  file2.close();
  for (j =0; j<2; j++)
    {
      filesToWrite[j].close();
    }
  return true;
}

//Проверка файла на пустоту
bool isEmpty(const string &fileName)
{
  ofstream file(fileName);
  if(file)
  {
    file.close();
    return false;
  }
  file.close();
  return true;
}

//Реализация сортировки
int sortFile(const string &fileName)
{
  int p = 1;
  int x;
  string fileName1 = "1.txt";
  string fileName2 = "2.txt";
  string fileName3 = "3.txt";
  string fileName4 = "4.txt";
  //shareFiles(fileName , fileName1 , fileName2);
  ifstream file2(fileName2);
 // ifstream file3(fileName3);
  //if (!file2.is_open() || !file3.is_open())
  //  return -1;
  //shareFiles(fileName , fileName1 , fileName2);
  if (!shareFiles(fileName , fileName1 , fileName2))
    return -1;
  while( file2>>x ) 
    { 
      if(!mixFiles(fileName1 , fileName2, fileName3, fileName4,p))
        {
          return -1;
        } 
      else
      {
        p=p*2;
        if(isEmpty(fileName1))
          break;
      }

      if(!mixFiles(fileName3 , fileName4, fileName1, fileName2,p))
        {
          return -1;
        }
      else
      {
        p=p*2;
        if(isEmpty(fileName3))
          break;
      }
    }
  file2.close();
  if (!isFileSorted(fileName3) || !isFileSorted(fileName1))
    {
     //file3.close();
      return -2;
    }
 // file3.close();
  return 1;
}


int createAndSortFile(const string &fileName,const int numbersCount,const int maxNumberValue)
{
  if(!createFileWithRandomNumbers(fileName,numbersCount,maxNumberValue))
    return -1;
  if (sortFile(fileName) )
    return 1;
  else 
    return -2;
}


int main()
{
  string fileName = "test.txt";
  const int numbersCount = 453;
  const int maxNumberValue = 10;
  for(int i = 0 ;i<10;i++)
  {  
    switch(createAndSortFile(fileName,numbersCount,maxNumberValue))
    {
      case -1:
      cout<<"Test failed:Troubles with file" << endl;
      break;

      case -2:
      cout<<"Test failed: isnt corted" << endl;
      break;

      case 1:
      cout<<"Test passed" << endl;
      break;
    }
  }
  return 0;
}