*For the purpose of storing the cities, 
I chose to use a map of which we would like to support multiple search operations for the location of a city 
according to its name, and the search time on the map is relatively fast (log(n)). In addition, 
this data structure is really convenient for searching elements in the structure - the [] operator - which makes it possible 
to maintain a clean and readable code.

*For the purpose of arranging the cities according to distances from a given city, 
I chose to use a vector - on which you can run a sorting operation in a 
relatively good time - nlog(n) and also a partition operation that will allow us to count 
the northern cities - also in nlog(n)

*I also chose to use a dictionary for the distance operations - which allows us an easy and clean way 
to retrieve the correct formula based on the name the user entered. (Since there are only 3 such functions 
and there is no need to support the introduction of other formulas - the runtime is not important here.)