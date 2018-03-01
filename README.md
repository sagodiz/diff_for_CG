# diff_for_CG

# load
A loader loads a given file format and reads all the methods and connections in that.
It tryes to match the loaded method to an already existing method. If it can't match to anything, it creates a new Id and stores the method.
# connection Transformation
It tryes to transform the connections. Instead of the names used by the tool it stores the ids assigned by the load method.
Returns the connection set. It is a set of pairs of ids.