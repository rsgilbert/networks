# UNI Network Programming, Volume 1: The Sockets Networking API 

Code written while reading the UNIX Network Programming book.


To run the code, first start docker-compose services:

`docker-compose up -d`

Then open a shell into one of the containers created by docker-compose 
docker exec -it gcc_container bash 



# Generating the config.h header file 
First take a look at this: 
https://blog.actorsfit.com/a?ID=00250-23766d36-b0a2-4f08-a3c0-ef69172b75a3

To put simply, download the original source code from http://www.unpbook.com/unpv13e.tar.gz . A copy of the tar file is in this repository.

Now extract the files for the tar file. Change into the folder and run `./configure` , that will generate a config.h file that you can copy into the root of the directory. Right next to this readme.MD file.


I am studying networks because I want to learn how 
networks work. I believe serious programming begins with
knowing how networks work.

