/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * out = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    vector<Point<3>> colorPoints(theTiles.size());
    map<Point<3>, unsigned> map;
    for(unsigned i = 0; i < theTiles.size(); i++) {
        Point<3> aveColor = convertToXYZ(theTiles[i].getAverageColor());
        colorPoints[i] = aveColor;
        map[aveColor] = i;
    }

    KDTree<3> colorTree(colorPoints);

    for(unsigned x = 0; x < theSource.getRows(); x++) {
        for (unsigned y = 0; y < theSource.getColumns(); y++) {
            LUVAPixel pixel = theSource.getRegionColor(x, y);
            Point<3> cor = convertToXYZ(pixel);
            Point<3> nearest = colorTree.findNearestNeighbor(cor);
            out->setTile(x, y, &theTiles[map[nearest]]);
        }
    }



    return out;
}

