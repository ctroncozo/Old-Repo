The Grid Problem
================

Cristian Troncoso

Definition
----------

Given a collection of 2D points, create an algorithm that classifies
each point into rows and columns.

Problem Specifications

-   Points form a grid in 2D space.

-   Input points are in no particular order.

-   The grid is square – there are the same number of rows as columns.

-   The grid is fully populated – there are no missing points.

-   The distance between two neighboring points in the same row or
    column is constant.

-   Columns and Rows may or may not be aligned with the x and y axes.

-   The number of columns and rows are arbitrary.


Algorithm

1.  Sort the data by increasing order of its x-component.

2.  Find the lowest y-value. If the data is tilted to either side, there
    will always be a lower corner. If the data is aligned with the
    x-axis, the lower corner will be the lowest y with the lowest x
    (because the data is sorted).

3.  Translate the grid to the origin such that the lowest point becomes
    the position (0,0).

4.  Rotate the Grid, either counter-clockwise or clockwise. This will
    depend on the quadrant the grid got translated to. If the grid is
    tilted left, it will be translated to the right quadrant. If the
    grid is tilted right it will be translated to the left quadrant. By
    this point the data is fully transformed into a new aligned grid.

5.  Sort transformed grid by its y-value, so the data will be grouped by
    rows

6.  Grab each group which represent a row and sort it by its transformed
    x-value.

7.  Iterate through each sorted group and label the data with counters
    (I,j).

> Implementation
>
> A Class Data was created to handle the data input; it can feed either
> data from memory or from a file.
>
> A class Point2D was implemented to contain the information for each
> point; original position, transformed position and labels.
>
> Finally, a class Row and Column were implemented to organize the
> points by row or by column.
>
> The algorithm uses encapsulation by delegating the creation of Point2D
> objects to a factory class, Point2DFactory (Factory method pattern).
>
> The most important functions are rotation, and translation.
