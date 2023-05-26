//the code has to be executed line by line in spark shell

val data=sc.textFile("sparkdata.txt")  //reading the data from the file

data.collect;  

val splitdata = data.flatMap(line => line.split(" "));  //splitting the data

splitdata.collect;  

val mapdata = splitdata.map(word => (word,1)); 

mapdata.collect;  

val reducedata = mapdata.reduceByKey(_+_);  //reducing the data by key and aggregating the values of the same key 

reducedata.collect;



