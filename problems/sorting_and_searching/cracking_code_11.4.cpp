/*

imagine you have a 20gb file with one string per line. explain how you would sort the file.

*/

/*
to avoid loading all data into memory, load x megabytes, where x is data available. sort each chunk seperately, then save to file system. one chunks sorted, merge the chunks one by one. at end have a fully sorted file. external sort

*/

