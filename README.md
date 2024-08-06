# COP3530 Project 3
## Estimating Property Prices in Clark County, Washington
This repo contains source code for Project 3b for Team CDE

# Commands
**LOAD Datapoints**\
```load <dp>```\
\
**dp**: The total number of data points to load.\
**Functionality**: Loads X amount of datapoints from the 'data.csv' file into memory.\
\
**PRINT Datapoints**\
```printData```\
\
**Functionality**: Prints loaded datapoints.

---

**PREDICT from Linear Regression**\
```lr <dp> <x1> <x2>```\
\
**dp**: Quantity of data points to be used in algorithm.\
**x1**: Construction year prediction variable. (Ex. "1965")\
**x2**: Square footage prediction variable. (Ex. "2235")\
\
**PREDICT from K-Nearest Neighbor**\
```knn <dp> <x1> <x2> <K>```
**K**: The value of K (the amount of nearby points to take the average from) as applied in the algorithm.\
\
**Functionality**: Both of these commands will print the predicted price using the given variable(s) as input, using the specified algorithm.

---

**BENCHMARK**\
```benchmark <dp>```\
\
**Functionality**: The method for determining which algorithm makes more accurate predictions. Automatically runs LR and KNN and prints results and statistics.

---
**EXIT**\
```exit```
\
**Functionality**: Exits the program.