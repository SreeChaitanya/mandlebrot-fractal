# mandlebrot-fractal
Fractal generation using mandlebrot set

[Mandlebrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set)  is obtained from quadratic recurrence relation : **z<sub>(n+1)</sub>=z<sub>n</sub><sup>2</sup>+C**.

---
#### Description:


mandlebrot.cpp can be used to obtain a plot of mandlebrot set.

Mandelbrot set images are created by sampling the complex numbers and determining, for each sample point c, whether the result of iterating the above function goes to infinity.

In this case infinity is denoted by max count.Typically points for which the sequence does not diverge are coloured black.

Coloured plots are obtained by colouring points according to the  number of steps taken to reach max_count.

Multibrot sets are obtained by using polynomials of higher degrees.
