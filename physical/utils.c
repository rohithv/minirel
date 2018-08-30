
void CopyIntInBinary(void *buffer, int n){
	memcpy(buffer, (void *)&n, sizeof(int));
}