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
```printData```

---

**PREDICT from Linear Regression**\
```lr <dp> <x>```\
\
**PREDICT from K-Nearest Neighbor**\
```knn <dp> <x>```\
\
**dp**: The total number of data points that will be used in the algorithms.\
**x**: The first variable the prediction will be based upon. For the first stage of the project, this will just be the square footage.\
\
**Functionality**: Both of these commands will print the predicted price using the given variable(s) as input, using the specified algorithm.
