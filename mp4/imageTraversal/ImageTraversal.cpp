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
ImageTraversal::Iterator::Iterator() : traversal(NULL) {
  // Nothing
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start) 
	:traversal(&traversal), start(start) {
	current = traversal.peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  	if (!traversal->empty()) {
  		current = traversal->pop();
  		traversal->add(current);
  		current = traversal->peek();
  	}
  	return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  	return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  	bool thisEmpty = false;
  	bool otherEmpty = false;

  	if (traversal == NULL) {thisEmpty = true;}
  	if (other.traversal == NULL) {otherEmpty = true;}

  	if (!thisEmpty) {thisEmpty = traversal->empty();}
  	if (!otherEmpty) {otherEmpty = other.traversal->empty();}

  	if (thisEmpty && otherEmpty) {return true;}
  	else if ((!thisEmpty) && (!otherEmpty)) {return traversal != other.traversal;}
  	else return true;
}

