package com.hsgui.interview;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-15
 * Time: 下午11:02
 * To change this template use File | Settings | File Templates.
 *
 * 1. https://github.com/forcefront/point-in-polygon/blob/gh-pages/point-in-polygon.html
 *
 * 2. http://en.wikipedia.org/wiki/Even-odd_rule
 *    This rule determines the "insideness" of a point on the canvas by
 *    drawing a ray from that point to infinity in any direction and
 *    counting the number of path segments from the given shape that the ray crosses.
 *    If this number is odd, the point is inside;
 *    if even, the point is outside.
 *
 *    http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
 *
 * 3. http://en.wikipedia.org/wiki/Winding_number
 *
 * 4. http://en.wikipedia.org/wiki/Point_in_polygon
 */
public class PointInPolygon {

    public boolean isPointInPolygonUsingEvenOldRule(Point p, Point[] polygon){
        boolean isInPolygonFlag = false;

        for (int i = 0, j = polygon.length - 1; i < polygon.length; j = i, i++){
            //p is the vertex of the polygon
            if (p.equals(polygon[i]) || p.equals(polygon[j])){
                isInPolygonFlag = true;
                break;
            }
            if ((polygon[i].y < p.y && p.y <= polygon[j].y) ||
                    (polygon[j].y < p.y && p.y <= polygon[i].y)){
                double crossX = polygon[i].x + (double)(polygon[j].x - polygon[i].x)/(polygon[j].y - polygon[i].y)*(p.y - polygon[i].y);
                //p is on the edge of the polygon.
                if (crossX == p.x){
                    isInPolygonFlag = true;
                    break;
                }else if (p.x > crossX){    //the ray cross the edge of Point[i]-->Point[j]
                    isInPolygonFlag = !isInPolygonFlag;
                }
            }
        }
        return isInPolygonFlag;
    }

    public boolean isPointInPolygonUsingWindingNumber(Point p, Point[] polygon){
        return false;
    }
}

class Point{
    public int x;
    public int y;

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Point){
            Point other = (Point)obj;
            return other.x == x && other.y == y;
        }
        return false;
    }

    @Override
    public int hashCode() {
        return 31*x + y;
    }
}