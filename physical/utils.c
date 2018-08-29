
void CopyIntInBinary(void *bufferptr, int n){
	memcpy(bufferptr, (void *)&n, sizeof(int));
}


int ReadIntFromBinary(void *bufferptr){
	return *(int *)bufferptr;
}