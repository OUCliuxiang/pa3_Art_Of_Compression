/*************************************************************************
	> File Name: stats.cpp
	> Author: OUC_LiuX
	> Mail: liuxiang@stu.ouc.edu.cn
	> Created Time: Thu 03 May 2018 04:30:36 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#include <cmath>
#include <vector>
#include <utility>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "stats.h"
using namespace cs221util;

long stats::getSum( char channel, pair< int, int> ul, pair< int, int>lr){
    long result;
    switch ( channel){
        case 'r':
            if( !ul.first && !ul.second )
                result = sumRed[lr.first][lr.second];
            else if( !ul.first && ul.second )
                result = sumRed[lr.first][lr.second] - 
                         sumRed[ul.first][ul.second - 1];
            else if( ul.first && !ul.second )
                result = sumRed[lr.first][lr.second] - 
                         sumRed[ul.first - 1][ul.second];
            else
                result = sumRed[lr.first][lr.second] - 
                         sumRed[ul.first - 1][ul.second] - 
                         sumRed[ul.first][ul.second - 1] + 
                         sumRed[ul.first][ul.second];
            break;

        case 'g':
            if( !ul.first && !ul.second )
                result = sumGreen[lr.first][lr.second];
            else if( !ul.first && ul.second )
                result = sumGreen[lr.first][lr.second] - 
                         sumGreen[ul.first][ul.second - 1];
            else if( ul.first && !ul.second )
                result = sumGreen[lr.first][lr.second] - 
                         sumGreen[ul.first - 1][ul.second];
            else
                result = sumGreen[lr.first][lr.second] - 
                         sumGreen[ul.first - 1][ul.second] - 
                         sumGreen[ul.first][ul.second - 1] + 
                         sumGreen[ul.first][ul.second];
            break;
        
        case 'b':
            if( !ul.first && !ul.second )
                result = sumBlue[lr.first][lr.second];
            else if( !ul.first && ul.second )
                result = sumBlue[lr.first][lr.second] - 
                         sumBlue[ul.first][ul.second - 1];
            else if( ul.first && !ul.second )
                result = sumBlue[lr.first][lr.second] - 
                         sumBlue[ul.first - 1][ul.second];
            else
                result = sumBlue[lr.first][lr.second] - 
                         sumBlue[ul.first - 1][ul.second] - 
                         sumBlue[ul.first][ul.second - 1] + 
                         sumBlue[ul.first][ul.second];
            break;
        
        default:
            return NULL;
    }
    return result;
}

long stats::getSumSq( char channel, pair< int, int> ul, pair< int, int>lr){
    long result;
    switch ( channel){
        case 'r':
            if( !ul.first && !ul.second )
                result = sumSqRed[lr.first][lr.second];
            else if( !ul.first && ul.second )
                result = sumSqRed[lr.first][lr.second] - 
                         sumSqRed[ul.first][ul.second - 1];
            else if( ul.first && !ul.second )
                result = sumSqRed[lr.first][lr.second] - 
                         sumSqRed[ul.first - 1][ul.second];
            else
                result = sumSqRed[lr.first][lr.second] - 
                         sumSqRed[ul.first - 1][ul.second] - 
                         sumSqRed[ul.first][ul.second - 1] + 
                         sumSqRed[ul.first][ul.second];
            break;

        case 'g':
            if( !ul.first && !ul.second )
                result = sumSqGreen[lr.first][lr.second];
            else if( !ul.first && ul.second )
                result = sumSqGreen[lr.first][lr.second] - 
                         sumSqGreen[ul.first][ul.second - 1];
            else if( ul.first && !ul.second )
                result = sumSqGreen[lr.first][lr.second] - 
                         sumSqGreen[ul.first - 1][ul.second];
            else
                result = sumSqGreen[lr.first][lr.second] - 
                         sumSqGreen[ul.first - 1][ul.second] - 
                         sumSqGreen[ul.first][ul.second - 1] + 
                         sumSqGreen[ul.first][ul.second];
            break;
        
        case 'b':
            if( !ul.first && !ul.second )
                result = sumSqBlue[lr.first][lr.second];
            else if( !ul.first && ul.second )
                result = sumSqBlue[lr.first][lr.second] - 
                         sumSqBlue[ul.first][ul.second - 1];
            else if( ul.first && !ul.second )
                result = sumSqBlue[lr.first][lr.second] - 
                         sumSqBlue[ul.first - 1][ul.second];
            else
                result = sumSqBlue[lr.first][lr.second] - 
                         sumSqBlue[ul.first - 1][ul.second] - 
                         sumSqBlue[ul.first][ul.second - 1] + 
                         sumSqBlue[ul.first][ul.second];
            break;
        
        default:
            return NULL;
    }
    return result;
}


stats::stats( PNG& im ){
    /* notice that width and heigth is privated variables in class PNG
     * we can only get them via public function.
     */
    unsigned int width = im.PNG::width();
    unsigned int height = im.PNG::height();

    /* sumRed ... are 2-dimension vectors, just to resize them.
     */
    sumRed.resize( width, vector< long >( height, 0 ) ); 
    sumGreen.resize( width, vector< long >( height, 0 ) ); 
    sumBlue.resize( width, vector< long >( height, 0 ) ); 
    sumSqRed.resize( width, vector< long >( height, 0 ) ); 
    sumSqGreen.resize( width, vector< long >( height, 0 ) ); 
    sumSqBlue.resize( width, vector< long >( height, 0 ) ); 

    /* where are the sum of the color values ???
     * the .hpp file doesn't tell us.
     * Now we just have a PNG objective. 
     * Then we find that function PNG::getPixel*(unsigned int, unsigned int) 
     * return a RGBAPixel's pointer.
     * However, RGBAPixel has only the variables type in unsigned char.
     * unsigned char give range [0, 255]. from StackOverflow, and I have done the 
     * empriment that long can be assigned by unsigned char.
     * 
     * JUST DO IT!
     */
    
    RGBAPixel* tempRGB = im.getPixel( 0, 0 );
    sumRed[0][0] = tempRGB -> r;
    sumGreen[0][0] = tempRGB -> g;
    sumBlue[0][0] = tempRGB -> b;
    sumSqRed[0][0] = pow( tempRGB -> r, 2);
    sumSqGreen[0][0] = pow( tempRGB -> g, 2);
    sumSqBlue[0][0] = pow( tempRGB -> b, 2);

    /* first suberscript is column-script; 
     * second suberscript is row-script.
     */
    for( int i = 1; i < width; ++ i ){
        // work out the first row;
        // fixed the row, and move the column.
        RGBAPixel* tempRGB = im.PNG::getPixel( i, 0 );
        sumRed[i][0] = tempRGB -> r + sumRed[i - 1][0];
        sumGreen[i][0] = tempRGB -> g + sumGreen[ i - 1 ][0];
        sumBlue[i][0] = tempRGB -> b + sumBlue[ i - 1 ][0];
        sumSqRed[i][0] = pow( tempRGB -> r, 2 ) + sumSqRed[ i - 1 ][0];
        sumSqGreen[i][0] = pow( tempRGB -> g, 2 ) + sumSqGreen[ i - 1 ][0];
        sumSqBlue[i][0] = pow( tempRGB -> b, 2 ) + sumSqBlue[ i - 1 ][0];
    }

    for( int i = 1; i < height; ++ i ){
        //work out the first column, fixed the column, move the row;
        RGBAPixel* tempRGB = im.PNG::getPixel( 0, i );
        sumRed[0][i] = tempRGB -> r + sumRed[0][ i - 1 ];
        sumGreen[0][i] = tempRGB -> g + sumGreen[0][ i - 1 ];
        sumBlue[0][i] = tempRGB -> b + sumBlue[0][ i - 1 ];
        sumSqRed[0][i] = pow( tempRGB -> r, 2 ) + sumSqRed[0][ i - 1 ];
        sumSqGreen[0][i] = pow( tempRGB -> g, 2 ) + sumSqGreen[0][ i - 1 ];
        sumSqBlue[0][i] = pow( tempRGB -> b, 2 ) + sumSqBlue[0][ i - 1 ];
    }

    for ( int i = 1; i < width; ++ i )
        for ( int j = 1; j < height; ++ j ){
            /* recurse the tabel( matrix )
             * outside loop is width, inside loop is heigth */
            RGBAPixel* tempRGB = im.PNG::getPixel( i, j );
            sumRed[i][j] = sumRed[i][j-1] + sumRed[i-1][j] - 
                           sumRed[i-1][j-1] + tempRGB -> r;
            sumGreen[i][j] = sumGreen[i][j-1] + sumGreen[i-1][j] - 
                             sumGreen[i-1][j-1] + tempRGB -> g;
            sumBlue[i][j] = sumBlue[i][j-1] + sumBlue[i-1][j] -
                            sumBlue[i-1][j-1] + tempRGB -> b;
            sumSqRed[i][j] = sumSqRed[i][j-1] + sumSqRed[i-1][j] -
                             sumSqRed[i-1][j-1] + pow( tempRGB -> r, 2);
            sumSqGreen[i][j] = sumSqGreen[i][j-1] + sumSqGreen[i-1][j] -
                               sumSqGreen[i-1][j-1] + pow( tempRGB -> g, 2);
            sumSqBlue[i][j] = sumSqBlue[i][j-1] + sumSqBlue[i-1][j] -
                              sumSqBlue[i-1][j-1] + pow( tempRGB -> b, 2 );
        } 
}


/* what's mean of over all color channels??
 * I decide to return the addition of three channels since just one 
 * long value being returned.
 *****************************************************************
 * **********    deviations = sum( (x - mean(x)) **2)    *********
 *****************************************************************/

/*******   Another calculative formula is given in pdf file *******/

long stats::getScore( pair<int, int > ul, pair< int, int>lr ){
    long reArea = rectArea( ul, lr );
    return ( getSumSq( 'r', ul, lr ) - 
             pow( getSum( 'r', ul, lr ), 2) / reArea ) + 
           ( getSumSq( 'g', ul, lr ) - 
             pow( getSum( 'r', ul, lr ), 2) / reArea ) +
           ( getSumSq( 'b', ul, lr ) - 
             pow( getSum( 'b', ul, lr ), 2) / reArea );
}

/* point "as a pixel";
 * point that ---average = sum / area. Sum is what we have knew, area 
 * is what we can work out. 
 * Function long getSum() and constructure function 
 * RGBAPixel(int, int, int ) are actually what we need.
 */
RGBAPixel stats::getAvg( pair< int, int> ul, pair< int, int> lr ){
    long Area = rectArea( ul, lr );
    return RGBAPixel( ( int)( getSum( 'r', ul, lr ) / Area ),
                      ( int)( getSum( 'g', ul, lr ) / Area ),
                      ( int)( getSum( 'b', ul, lr ) / Area ) );
}

/*
 * getSum() returns a long value, however what the RGBAPixel need 
 * is int, 
 */

long stats::rectArea( pair< int, int> ul, pair< int, int> lr ){
    return (lr.first - ul.first + 1) * ( lr.second - ul.second + 1 );
}
