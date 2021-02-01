Image filter
==== 

Simple image filter application written in C as part of the [![CS50 Badge](https://img.shields.io/badge/-CS50-red)](https://cs50.harvard.edu) class problem sets.

Table of content
----
* [General info](#general-info)
* [Setup](#setup)
* [Technologies](#technologies)

### General info

Image filter program written in C. The aim of the application is to apply different filters to selected images. During the problem set I had to implement the functions for the actual filters: **grayscale**, **sepia**, **blur** and **reflect**.

### Setup

The application can be ran locally or using the [![CS50 Badge](https://img.shields.io/badge/-CS50-red)](https://cs50.harvard.edu) <a href="https://ide.cs50.io">IDE</a> after logging in with your GitHub account.

To run the program:
 1. It needs to be complied: `$ make filter`
 2. Started with the selected key as an argument: `$ ./filter -g/r/s/b (depending on the filter chosen) images/yard.bmp out.bmp`
 
### Technologies
 
 Libraries:
 * stdio.h
 * math.h
 * getopt.h
 * stdbool.h
 * string.h
 * ctype.h
 * stdlib.h
 * [![C](https://img.shields.io/badge/-C-blue)](https://www.cprogramming.com/)
