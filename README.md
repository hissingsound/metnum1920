# Numerical Methods Application

## About

Application of some numerical methods. Created as a project for the Numerical Methods class.

## Group members

Name | ID
--- | ---
Caroline | D1041181030
Muslimah | D1041181004
Steven Hans | D1041181019

## Compiling

### Windows

Using g++.exe (MinGW.org GCC-8.2.0-5) 8.2.0:

`g++ main.cpp -o app.exe`

Then run the application:

`app.exe`

## Usage

Interface guides should suffice. But here are some sample inputs as a guide. For the sake of brevity, complete output is not shown here.

Input 1:
We'll use this system of equations: http://courses.wccnet.edu/~palay/math181/se_4x4s.htm
```
> 2
Input jumlah variabel: 4
Koefisien-koefisien baris ke-1: 2 5 -9 3
Koefisien-koefisien baris ke-2: 5 6 -4 2
Koefisien-koefisien baris ke-3: 3 -4 2 7
Koefisien-koefisien baris ke-4: 11 7 4 -8
Input solusi-solusi persamaan: 151 103 16 -32
> 2
```

End of output 1:
```
Answer: 3.000   5.000   -11.000 7.000
```

Input 2:
Suppose there exists a collection of data defined as follows: (1, 2), (2, 4), (3, 8), (4, 16), (5, 32). We wanted to find the exponential model for these.

```
>3
Memilih bagian regresi.
1) Model linear
2) Model exponensial
3) Model power
4) Model saturation growth rate
>2
Jumlah data: 5
Input data x y: 1 2 
2 4 
3 8 
4 16 
5 32
```

End of output 2:

```
y = 1.00000e^(0.69315x)
```

If one plots above function, one can tell that it almost looks like y = 2^x. It's because the data points **are** from 2^x.

## Notes

Keep in mind that this C++ implementation has a precision 
limitation. External library is not used to maintain portability.

Documentation is provided in English, while the main interface is provided in Indonesian.

## Contributing

Pull requests are accepted. Here are some things you can do:

1. More documentation.
2. Handling table printing in a more modular way.
3. Add some test cases.
4. Translating main interface to English (English port).
It is more prefered to contribute in English so others can understand your contribution more clearly.


