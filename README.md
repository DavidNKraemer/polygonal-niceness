# polygonal-niceness

A project for measuring the "niceness" of polygonal subsets of the plane.

## Project description 

[from Professor Mitchell's list]

There are various notions of quantifying how "nice" or how "fat" a simple
polygon *P* is. A "nicest" polygon might be a regular *n*-gon, which most
closely approximates a circular disk. This project seeks to implement some
precise metrics for niceness, and compare them on simple polygons (possibly
moused in by a user or read in from a file, etc).  

To make it simple and discrete, I propose that you discretize the boundary of
*P* with discrete points pi (additional vertices), with a prescribed spacing, δ.
(That is, for edges of *P* longer than δ, add vertices along the edge so that
the new subsegments are of length at most δ, for a user-specified parameter δ.)
Then, consider discrete choices of radii r = ρ, 2ρ, 3ρ, . . . for disks, *B*(pi
, *r*), centered at the discrete boundary points pi , for each radius r. The
(discrete) fatness of *P* is given by the smallest value of the ratio
area(*B*(pi , *r*) ∩ *P*)/area(*B*(pi , *r*), over all choices of pi and *r* =
ρ, 2ρ, 3ρ, . . . such that *P* is not contained fully inside *B*(pi , *r*).

Implement and experiment with this fatness measure. It may be possible to use
the algorithm to assist a project at Harvard on Gerrymandering, where the goal
is to quantify how "compact" polygonal election districts are. (So I hope that
at least a couple of people choose to do this project! We can discuss further.)

(Theoretically, we are interested in finding an algorithm to compute the "exact"
fatness of *P* (which allows disks centered anywhere inside *P*, of any radius
such that the disk does not contain all of *P*), without resorting to the simple
discretization. Or, can we compute a provable approximation to the exact
fatness?)
