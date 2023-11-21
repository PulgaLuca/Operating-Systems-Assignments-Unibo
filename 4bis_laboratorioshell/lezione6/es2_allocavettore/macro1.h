#define ALLOCA_VETTORE(PTR) 			  \
do{ 						  \
	PTR=(int32_t*)malloc(10*sizeof(int32_t)); \
	if (PTR!=NULL){				  \
		int j=0;			  \
		for(;j<10;j++){			  \
			PTR[j]=-1000+j;		  \
		}				  \
	}					  \
}while(0);					  \
