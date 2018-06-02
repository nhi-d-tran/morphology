# morphology

*******************************
I. Inputs: There are two input files.
*******************************
1 Input1 (argv[1]): a txt file representing a binary image with header.

2. Input2 (argv[2]): a txt file representing a binary image of a structuring element with header and the origin of the structuring element. The format of the structuring element is as follows:

1th text line is the header; the 2nd text line is the position (w.r.t. index) of the origin of the structuring element follows by the rows and column of the structuring element.

For example:
5 5 0 1 // 5 rows, 5 columns, min is 0, max is 1: 2-D structuring element

2 2 // origin is at row index 2 and column index 2.

0 0 1 0 0

0 0 1 0 0

1 1 1 1 1

0 0 1 0 0

0 0 1 0 0

*******************************
II. Outputs:
- Console output
- Output1 (argv[3]): the result of dilation image with header, should be the same dimension as input1
- Output2 (args[4]): the result of erosion image with header, should be the same dimension as input1
- Output3 (args[5]): the result of closing image with header, should be the same dimension as input1
- Output4 (args[6]): the result of opening image with header, should be the same dimension as input1

*******************************
III. Data structure:
*******************************
- numRowsImg (int)
- numColsImg (int)
- minImg (int)
- maxImg (int)
- numRowsStructElem (int)
- numColsStructElem (int)
- minStrctElem (int)
- maxStrctElem (int)
- rowOrigin (int)
- colOrigin (int)
- rowFrameSize (int)
- colFrameSize (int)
- imgAry (int **) // a 2D array, to store the input image,
- morphAry (int **) // a 2D array, need to dynamically allocate at run time // of size numRowsImg + rowFrameSize by numColsImg + colFrameSize.
- structElemAry (int **) //a 2D array, need to dynamically allocate at run time of size numRowsStructElem by numColsStructElem.

- computeFrameSize(...)
- loadImage // load imgAry from input1
- loadstruct // load structElem from input2
- zeroFrameImg // frame the input image with zero
- initMorphAry( ) // initialize morphAry to zero
- delation (i,j) // place the origin of the structuring element at pixel(i,j),
- erosion (i,j) 
- closing (i,j) 
- opening (i,j) 
- prettyPrint ()
- outputResult ()

*******************************
III. Algorithm steps in main()
*******************************

step 0: open all files
( numRowsImg, numColsImg, minImg, maxImg ) <- get from input1
( numRowsStrctElem, numColsStrctElem, minStrctElem, maxStrctElem ) <- get from input2
( rowOrigin, colOrigin) <-get from input2

step 1: computeFrameSize

step 2: - dynamically allocate imgAry with extra rows and extra columns
- loadImage // load input file to imgAry
- zeroFrameImg ()
- prettyPrint (imgAry) 
- dynamically allocate morphAry with extra rows and extra columns

step 3:
- dynamically allocate structElemAry
- loadstruct // load input2 file to structElem array
- prettyPrint (structElemAry)

step 4: - initMorphAry( ) // initialize morphAry to zero
- call dilation // see your lecture note
- prettyPrint (morphAry) // pretty print to the *console* the result of dilation
- outputResult //write the delation result to Output1 (argv[3])

step 5: - initMorphAry( ) // initialize morphAry to zero
- call erosion // see your lecture note
- prettyPrint (morphAry) // pretty print to the *console* the result of erosion
- outputResult //write the delation result to Output2 (argv[4])

step 6: - initMorphAry( ) // initialize morphAry to zero
- call closing // By call those two morphological ops one after the other
- prettyPrint (morphAry) // pretty print to the *console* the result of closing
- outputResult //write the closing result to Output3 (argv[5])

step 7: - initMorphAry( ) // initialize morphAry to zero
- call opening // By call those two morphological ops one after the other
- prettyPrint (morphAry) // pretty print to the *console* with &quot;Opening Result&quot;
- outputResult //write the opening result to Output4 (argv[6])

step 8: close all files
