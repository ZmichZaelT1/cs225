#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  	traversal = NULL;

	isVisited.resize(png.width());
	for (unsigned x = 0; x < isVisited.size(); x++) {
		isVisited[x].resize(png.height());
		for (unsigned y = 0; y < isVisited[x].size(); y++) {
			isVisited[x][y] = false;
		}
	}
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, PNG png, Point start, double tolerance) {
	this->traversal = traversal;
	this->png = png;
	this->start = start;
  	this->tolerance = tolerance;
  	curr = start;

  	isVisited.resize(png.width());
  	for (unsigned i = 0; i < isVisited.size(); i++) {
    	isVisited[i].resize(png.height());
      	for (unsigned j = 0; j < isVisited[i].size(); j++) {
        	isVisited[i][j] = false;
      	}
  	}
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
	isVisited[curr.x][curr.y] = true;

	if(isLegal(Point(curr.x + 1, curr.y), tolerance)) {
		traversal->add(Point(curr.x + 1, curr.y));
	}
	if(isLegal(Point(curr.x, curr.y + 1), tolerance)) {
		traversal->add(Point(curr.x, curr.y + 1));
	}
	if(isLegal(Point(curr.x - 1, curr.y), tolerance)) {
		traversal->add(Point(curr.x - 1, curr.y));
	}
	if(isLegal(Point(curr.x, curr.y - 1), tolerance)) {
		traversal->add(Point(curr.x, curr.y - 1));
	}

  	while(!traversal->empty() && !isLegal(traversal->peek(), tolerance)) {
    	traversal->pop();
  	}

  	if(!traversal->empty()) {
    	curr = traversal->peek();
  	}
	return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //refer to lab_trees
    bool thisEmpty = false; 
    bool otherEmpty = false;

    if (traversal == NULL) { thisEmpty = true; }
    if (other.traversal == NULL) { otherEmpty = true; }

    if (!thisEmpty)  { thisEmpty = traversal->empty(); }
    if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

    if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
    else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
    else return true; // one is empty while the other is not, return true
}

bool ImageTraversal::Iterator::isLegal(Point curr, double tolerance) {
  	if(curr.x < png.width() && curr.y < png.height()) {
		HSLAPixel p1 = png.getPixel(start.x,start.y);
    	HSLAPixel p2 = png.getPixel(curr.x,curr.y);

	    if(!isVisited[curr.x][curr.y] && calculateDelta(p1, p2) < tolerance) {
    		return true;
    	}
 	}
  	return false;
}
