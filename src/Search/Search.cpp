// Search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SearchVectorianModel.h"

int main(int argc, char* argv[])
{
	if ( argc < 2 )
	{
		perror( "Usage: Search QueryWord1 QueryWord2 ... \n");
		exit( 1);
	}
	
	// create an instance of CSearchVectorianModel. and pass the query-words
	// as arguments, without the "Search" command:
	CSearchVectorianModel SearchVectorianModel( argc-1, &argv[1] );
	
	return 0;
}

