### What is naughty_polyfit?
**Naughty_polyfit** is a simple polyfit library. It can find the mostly right values for coefficients of a polynomial which seems like "y = Ax^3 + Bx^2 + Cx + D" according to a few of points.
**Naughty_polyfit** project and its dependences are written all in C++, this makes sure the portability. You can even run it on MCUs.

### How to use naughty_polyfit?
#### How to config the project?
**See TEST and Makefiles in this project.**
#### How to use the interface function to fit curve?
Example:
```C++
    // Points<Point<X, Y>>
    std::vector<std::pair<double, double>> test_points{{0, 0}, {1, 100}, {2, 202}, {3, 303}, {4, 488}, {5, 505}, {6, 600}}; // Points to input.
    size_t curve_order = 4; // If you want to fit curve which is like "y = Ax^4 + Bx^3 + Cx^2 + Dx + E".
    std::vector<double> result;
    naughty::polyfit(test_points, curve_order, 100, 50, result); // Function will random descent 100 times to find the best values, and the depth of each descent is 50.
    double var0 = result[0];
    double var1 = result[1];
    double var2 = result[2];
    double var3 = result[3];
    double var4 = result[4];

	printf("\nPolyfit Result:\n");
	printf("y = %fx^4 + %fx^3 + %fx^2 + %fx + %f\n", var0, var1, var2, var3, var4);
```

### Dependences

**Eigen**
Eigen is a C++ template library for linear algebra.
Note: To avoid violating the strong copyleft of GPL license, you had better ensure the macro EIGEN_MPL2_ONLY defined when compiling source files those include Eigen library headers.

**Naughty_descent**
Naughty_descent is a simple descent framework written in C++.
In this project, naughty_descent is used to find coefficients to make variance between inputed points and fitted curve least.