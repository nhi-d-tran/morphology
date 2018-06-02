#include <iostream>
#include <fstream>
using namespace std;

//global variables
int numRowsImg;
int numColsImg;
int minImg;
int maxImg;
int* neighbors;

int numRowsStrctElem;
int numColsStrctElem;
int minStrctElem;
int maxStrctElem;

int rowOrigin;
int colOrigin;

int rowFrameSize = 0;
int colFrameSize = 0;

int** imgAry;
int** morphAry;
int** structElemAry;
int** tempAry;

void computeFrameSize()
{
	rowFrameSize = numRowsStrctElem;
	colFrameSize = numColsStrctElem;
}

void loadImg(ifstream &inFile, int row, int maxRow, int col, int maxCol)
{
	for(int i = row; i < maxRow; i++)
	{
		for(int j = col; j < maxCol; j++)
		{
			int value = 0;
			inFile >> value;
			imgAry[i][j] = value;
		}
	}

}

void loadStruct(ifstream &inFile, int row, int col)
{
	while(!inFile.eof())
	{
		for(int i = 1; i <= row; i++)
		{
			for(int j = 1; j <= col; j++)
			{
				int value = 0;
				inFile >> value;
				structElemAry[i][j] = value;
			}
		}
	}
}

void initMorphAry(int row, int col)
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			morphAry[i][j] = 0;
		}
	}
}

void zeroFramed()
{
	for(int col = 0; col < numColsImg; col++)
	{
		imgAry[0][col] = 0;
	}

	for(int row = 0; row < numRowsImg; row++)
	{
		imgAry[row][0] = 0;
	}
}

void prettyPrint(int** Ary, int row, int col, ofstream &outFile)
{
	for(int i = 0; i < row ; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if(Ary[i][j] > 0)
			{
				cout << Ary[i][j] << " ";
				outFile << Ary[i][j] << " ";
			}
			else
			{
				cout << "  ";
				outFile << "  ";
			}
		}
		cout << endl;
		outFile << endl;
	}
}

void delation(int numRowsImg, int numColsImg, int **img, int** ary)
{
	int r = numRowsImg + rowFrameSize;

	int c = numColsImg + colFrameSize;

	for(int i = numRowsStrctElem; i < r; i++)
	{
		for(int j = numColsStrctElem; j < c; j++)
		{
			if(img[i][j] > 0)
			{
				for(int k = 0; k < numRowsStrctElem; k++)
				{
					for(int l = 0; l < numColsStrctElem ; l++)
					{
						if(structElemAry[k][l] == 1)
						{
							ary[i - rowOrigin + k][j - colOrigin + l] = structElemAry[k][l];

						}
					}
				}
			}

		}
	}
}

bool isSameWithStructure(int row, int col, int **img)
{
	int r = 0;
	int c = 0;

	for(int i = row-1; i <= row+1; i++)
	{
		for(int j = col-1; j <= col+1; j++)
		{
			if(structElemAry[r][c] <= img[i][j])
			{
				c++;
			}
			else
			{
				return false;
			}
		}
		r++;
		c = 0;
	}

	return true;
}
void erosion(int numRowsImg, int numColsImg, int **img, int** ary)
{
	int r = numRowsImg + rowFrameSize;
	int c = numColsImg + colFrameSize;

	for(int i = numRowsStrctElem; i < r; i++)
	{
		for(int j = numRowsStrctElem; j < c; j++)
		{
			if(img[i][j] > 0)
			{
				if(isSameWithStructure(i,j, img))
				{
					ary[i][j] = 1;

				}
				else
				{
					ary[i][j] = 0;
				}
			}
		}
	}
}

void closing(int numRowsImg, int numColsImg)
{
	delation(numRowsImg, numColsImg, imgAry, tempAry);
	erosion(numRowsImg, numColsImg, tempAry, morphAry);
}

void opening(int numRowsImg, int numColsImg)
{
	erosion(numRowsImg, numColsImg, imgAry, tempAry);
	delation(numRowsImg, numColsImg, tempAry, morphAry);
}

void output(ofstream &outFile, int row, int col, int min, int max)
{
	outFile <<  row << " " << col <<  " " <<  min  << " "<< max << endl;

	for(int i = 0;i< row; i++)
	{
		for(int j = 0; j < col;j++)
		{
			if(morphAry[i][j] > 0)
			{
				outFile<<morphAry[i][j]<<" ";
			}
			else
			{
				outFile << "  ";
			}
		}
		outFile << endl;
	}
}
int main(int argc,char** argv)
{
	ifstream inFile1, inFile2;
	ofstream outFile1, outFile2, outFile3, outFile4;


	if (!inFile1 || !inFile2)
	{
		cout << "ERROR to open file";
		exit(1);
	}
	inFile1.open(argv[1]);
	inFile2.open(argv[2]);
	outFile1.open(argv[3]);
	outFile2.open(argv[4]);
	outFile3.open(argv[5]);
	outFile4.open(argv[6]);

	int numRowsImg, numColsImg, minImg, maxImg;

	inFile1 >> numRowsImg >>numColsImg >> minImg >> maxImg;
	inFile2 >> numRowsStrctElem >> numColsStrctElem >> minStrctElem >> maxStrctElem >>rowOrigin >> colOrigin ;

	computeFrameSize();

	//dynamically allocate imgAry, morphAry, structElemAry
	int row = numRowsImg + (rowFrameSize * 2);
	int col = numColsImg + (colFrameSize * 2);

	morphAry = new int*[row];
	imgAry = new int*[row];
	tempAry = new int*[row];
	for(int i = 0; i < row; i++)
	{
		imgAry[i] = new int[col];
		tempAry[i] =  new int[col];
		morphAry[i] = new int[col];
	}

	structElemAry = new int*[numRowsStrctElem];
	for(int i = 0; i < numRowsStrctElem; i++)
	{
		structElemAry[i] = new int[numColsStrctElem];
	}

	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			imgAry[i][j] = 0;
			tempAry[i][j] = 0;
			morphAry[i][j] = 0;
		}
	}


	for(int i = 0; i < numRowsStrctElem; i++)
	{
		for(int j = 0; j < numColsStrctElem; j++)
		{
			structElemAry[i][j] = 0;
		}
	}

	loadImg(inFile1, rowFrameSize, row - rowFrameSize, colFrameSize, col - rowFrameSize);
	cout << "Input Image" << endl;
	for(int i = 0; i < row ; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if(imgAry[i][j] > 0)
			{
				cout << imgAry[i][j] << " ";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	cout << "---------------------------------------------------" << endl;

	for(int i = 0; i < numRowsStrctElem; i++)
	{
		for(int j = 0; j < numColsStrctElem; j++)
		{
			int value = 0;
			inFile2 >> value;
			structElemAry[i][j] = value;
		}
	}

	cout << "Structuring Image" << endl;
	for(int i = 0; i < numRowsStrctElem; i++)
	{
		for(int j = 0; j < numColsStrctElem; j++)
		{
			if(structElemAry[i][j] > 0)
			{
				cout <<structElemAry[i][j] << " ";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	cout << "---------------------------------------------------" << endl;

	initMorphAry(row, col);
	delation(numRowsImg, numColsImg, imgAry, morphAry);
	cout << "Result of Delation" << endl;
	prettyPrint(morphAry, row, col, outFile1);
	cout << "---------------------------------------------------" << endl;

	initMorphAry(row, col);
	erosion(numRowsImg, numColsImg, imgAry, morphAry);
	cout << "Result of Erosion" << endl;
	prettyPrint(morphAry, row, col, outFile2);
	cout << "---------------------------------------------------" << endl;


	initMorphAry(row, col);
	opening(numRowsImg, numColsImg);
	cout << "Result of Opening" << endl;
	prettyPrint(morphAry, row, col, outFile3);

	cout << "---------------------------------------------------" << endl;

	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			morphAry[i][j] = 0;
			tempAry[i][j] = 0;
		}
	}
	initMorphAry(row, col);
	closing(numRowsImg, numColsImg);
	cout << "Result of Closing" << endl;
	prettyPrint(morphAry, row, col, outFile4);
	cout << "---------------------------------------------------" << endl;


	inFile1.close();
	inFile2.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();
	outFile4.close();

	return 0;
}
